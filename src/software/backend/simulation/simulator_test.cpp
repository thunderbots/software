#include <iostream>
#include "software/backend/simulation/simulator.h"
#include "software/ai/world/ball.h"

int main(int argc, char **argv)
{
    std::cout << "simulator test" << std::endl;
    Simulator sim = Simulator();
//    Ball b(Point(), Vector(1, 2), Timestamp::fromSeconds(0));
//    sim.setBall(b);
//    auto f = [](Ball b) {};
//    sim.start(f);
    std::cout << "done" << std::endl;
}
