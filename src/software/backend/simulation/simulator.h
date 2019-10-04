#pragma once

#include <thread>
#include "software/ai/world/ball.h"
#include "software/ai/world/world.h"
#include "software/ai/world/field.h"
#include "software/backend/simulation/physics_ball.h"
#include "software/backend/simulation/physics_field.h"
#include "software/util/time/duration.h"
#include <optional>
#include <mutex>
#include <thread>
#include <pthread.h>

class Simulator {
public:
    Simulator();

    // Delete the copy and assignment operators because this class really shouldn't
    // need them and we don't want to risk doing anything nasty with the internal
    // multithreading this class uses
    Simulator& operator=(const Simulator&) = delete;
    Simulator(const Simulator&)            = delete;

    ~Simulator();
    void start(std::function<void(World)> world_update_callback);
    void setBall(const Ball& ball);
    void setField(const Field& field);

private:
    void simulation_loop(std::function<void(World)> world_update_callback);

    // The mutex for the in_destructor flag
    Duration time_step;
    std::mutex in_destructor_mutex;
    bool in_destructor;
    bool thread_started;

    std::shared_ptr<b2World> world;
    std::mutex world_mutex;
    int velocity_iterations;
    int position_iterations;

    std::optional<PhysicsBall> physics_ball;
    std::optional<PhysicsField> physics_field;

    std::thread simulation_thread;
};

