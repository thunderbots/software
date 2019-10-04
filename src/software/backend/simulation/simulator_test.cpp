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
    Ball b(Point(), Vector(1, 2), Timestamp::fromSeconds(0));
    sim.setBall(b);
    auto f = [](Ball b) {};
    sim.start(f);
    std::cout << "sim started" << std::endl;
    std::promise<void>().get_future().wait();
    std::cout << "done" << std::endl;
}
