#include "software/backend/simulator_backend.h"

#include "software/backend/backend_factory.h"

const std::string SimulatorBackend::name = "simulator";

SimulatorBackend::SimulatorBackend()
{
}

void SimulatorBackend::onValueReceived(ConstPrimitiveVectorPtr primitives)
{
    std::scoped_lock lock(most_recently_received_primitives_mutex);
    most_recently_received_primitives = std::move(primitives);
}

void SimulatorBackend::start() {
    auto f = [this](World world) {
        Subject<World>::sendValueToObservers(world);
    };
    Ball b(Point(0, 0), Vector(0.7, -0.2), Timestamp::fromSeconds(0));
    simulator.setBall(b);

    Field field = Field(9.0, 6.0, 1.0, 2.0, 1.0, 0.3, 0.5, Timestamp::fromSeconds(0));
    simulator.setField(field);

    simulator.start(f);
}

// Register this backend in the BackendFactory
static TBackendFactory<SimulatorBackend> factory;
