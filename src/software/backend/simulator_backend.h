#pragma once

#include "software/ai/world/world.h"
#include "software/backend/backend.h"
#include "software/backend/simulation/simulator.h"

class SimulatorBackend : public Backend
{
   public:
    static const std::string name;
    SimulatorBackend();

    void start();

   private:
    void onValueReceived(ConstPrimitiveVectorPtr primitives) override;

    Simulator simulator;
    ConstPrimitiveVectorPtr most_recently_received_primitives;
    std::mutex most_recently_received_primitives_mutex;
};
