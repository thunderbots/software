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
    auto f = [](Ball b) {};
    simulator.start(f);
}

// Register this backend in the BackendFactory
static TBackendFactory<SimulatorBackend> factory;
