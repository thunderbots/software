#include "software/backend/simulation/simulator.h"
#include <Box2D/Box2D.h>
#include <thread>
#include <pthread.h>
#include <thread>
#include <chrono>

Simulator::Simulator() : in_destructor(false), thread_started(false) {
    b2Vec2 gravity(0, 0);
    world = std::make_shared<b2World>(gravity);
    velocity_iterations = 8;
    position_iterations = 3;
    time_step = Duration::fromSeconds(1.0 / 60.0);
}

Simulator::~Simulator() {
    in_destructor_mutex.lock();
    in_destructor = true;
    in_destructor_mutex.unlock();

    if(thread_started) {
        simulation_thread.join();
    }
}

void Simulator::start(std::function<void(World)> world_update_callback) {
    thread_started = true;
    simulation_thread = std::thread([this, world_update_callback]() {
        return simulation_loop(world_update_callback);
    });
}

void Simulator::setBall(const Ball &ball) {
    // TODO: delete ball if it exists?
    std::scoped_lock world_lock(world_mutex);
    physics_ball = std::make_optional(PhysicsBall(world, ball));
}

void Simulator::simulation_loop(std::function<void(World)> world_update_callback) {
    // Take ownership of the in_destructor flag so we can use it for the conditional
    // check
    in_destructor_mutex.lock();
    while(!in_destructor) {
        // Give up ownership of the in_destructor flag now that we're done the
        // conditional check
        in_destructor_mutex.unlock();

        {
            std::scoped_lock world_lock(world_mutex);
            world->Step(time_step.getSeconds(), velocity_iterations, position_iterations);
            if(physics_ball) {
                std::cout << physics_ball->getBall().position() << std::endl;
            }

            // Create world from simualted objects
            World new_world;
            if(physics_ball) {
                new_world.mutableBall() = physics_ball->getBall();
            }
            if(physics_field) {
                new_world.mutableField() = physics_field->getField();
            }
            world_update_callback(new_world);

        }

        // TODO: better time management
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

        // Take ownership of the `in_destructor` flag so we can use it for the conditional
        // check
        in_destructor_mutex.lock();
    }
}

void Simulator::setField(const Field &field) {
    // TODO: delete field if it exists?
    std::scoped_lock world_lock(world_mutex);
    physics_field = std::make_optional(PhysicsField(world, field));
}
