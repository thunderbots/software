#include <iostream>
#include "software/backend/simulation/simulator.h"
#include "software/ai/world/ball.h"
#include <thread>
#include <pthread.h>
#include <future>

int main(int argc, char **argv)
{
    std::cout << "simulator test" << std::endl;
    Simulator sim = Simulator();
    Ball b(Point(), Vector(0.5, 0.12), Timestamp::fromSeconds(0));
    sim.setBall(b);
    Field field = Field(9.0, 6.0, 1.0, 2.0, 1.0, 0.3, 0.5, Timestamp::fromSeconds(0));
    sim.setField(field);
    auto func = [](World w) {};
    sim.start(func);
    std::cout << "sim started" << std::endl;
    std::promise<void>().get_future().wait();
    std::cout << "done" << std::endl;
}
