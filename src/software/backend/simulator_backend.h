#pragma once

#include "software/ai/world/world.h"
#include "software/backend/backend.h"

class SimulatorBackend : public Backend
{
   public:
    static const std::string name;
    SimulatorBackend();

   private:
    void onValueReceived(ConstPrimitiveVectorPtr primitives) override;

    /**
     * Set the most recently received world
     *
     * @param world The new most recently received world
     */
    void setMostRecentlyReceivedWorld(World world);

    /**
     * Set the most recently received primitives
     *
     * @param world The new most recently received primitives
     */
    void setMostRecentlyReceivedPrimitives(ConstPrimitiveVectorPtr primitives);

    std::optional<World> most_recently_received_world;
    std::mutex most_recently_received_world_mutex;

    ConstPrimitiveVectorPtr most_recently_received_primitives;
    std::mutex most_recently_received_primitives_mutex;
};
