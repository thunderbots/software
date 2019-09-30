#include "software/backend/simulation/simulator.h"
#include <Box2D/Box2D.h>

Simulator::Simulator(bool thread_started) : in_destructor(false), thread_started(thread_started) {
    b2Vec2 gravity(0, 0);
    world = std::make_shared<b2World>(gravity);
    velocity_iterations = 8;
    position_iterations = 3;
    time_step = Duration::fromSeconds(1.0 / 60.0);


//    thread_started =true;
//    auto f = [this]() {return simulation_loop();};
    auto f = []() {for(int i = 0; i < 3; i++) {
        std::cout << "looping" << std::endl;
    }};
    simulation_thread = std::thread(f);
}

Simulator::~Simulator() {
    in_destructor_mutex.lock();
    in_destructor = true;
    in_destructor_mutex.unlock();

    if(thread_started) {
        simulation_thread.join();
    }
}

void Simulator::start(std::function<void(Ball)> world_update_callback) {
    thread_started = true;
//    simulation_thread = std::thread([this]() {
//        return simulation_loop();
//    });
}

void Simulator::setBall(const Ball &ball) {
    std::scoped_lock world_lock(world_mutex);
    physics_ball = std::make_optional(PhysicsBall(world, ball));
}

void Simulator::simulation_loop() {
    // Take ownership of the in_destructor flag so we can use it for the conditional
    // check
    in_destructor_mutex.lock();
    while(!in_destructor) {
        // Give up ownership of the in_destructor flag now that we're done the
        // conditional check
        in_destructor_mutex.unlock();

        std::scoped_lock world_lock(world_mutex);
        world->Step(time_step.getSeconds(), velocity_iterations, position_iterations);
        std::cout << physics_ball->getBall().position() << std::endl;

        // Take ownership of the `in_destructor` flag so we can use it for the conditional
        // check
        in_destructor_mutex.lock();
    }
}
