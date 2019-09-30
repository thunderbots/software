#include "software/backend/simulator_backend.h"

#include "software/backend/backend_factory.h"

const std::string SimulatorBackend::name = "simulator";

SimulatorBackend::SimulatorBackend()
{
}

void SimulatorBackend::onValueReceived(ConstPrimitiveVectorPtr primitives)
{
    setMostRecentlyReceivedPrimitives(primitives);
}

void SimulatorBackend::setMostRecentlyReceivedWorld(World world)
{
    std::scoped_lock lock(most_recently_received_world_mutex);
    most_recently_received_world = world;
}

void SimulatorBackend::setMostRecentlyReceivedPrimitives(ConstPrimitiveVectorPtr primitives)
{
    std::scoped_lock lock(most_recently_received_primitives_mutex);
    most_recently_received_primitives = std::move(primitives);
}

// Register this backend in the BackendFactory
static TBackendFactory<SimulatorBackend> factory;
