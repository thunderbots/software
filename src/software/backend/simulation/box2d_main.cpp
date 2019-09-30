#include <iostream>
//#include <Box2D/Box2D.h>
//#include "software/backend/simulation/physics_ball.h"
//#include "software/geom/point.h"
#include "software/backend/simulation/simulator.h"
//#include "software/ai/world/ball.h"
//#include <thread>

int main(int argc, char **argv)
{
    Simulator sim(false);
//    Ball b(Point(), Vector(1, 2), Timestamp::fromSeconds(0));
//    sim.setBall(b);
//    auto f = [](Ball b) {};
//    sim.start(f);
//    b2Vec2 gravity(0, 0);
//    auto world = std::make_shared<b2World>(gravity);
//    double time_step = 1.0/60.0;
//    int velocity_iterations = 8;
//    int position_iterations = 3;
//
//    PhysicsBall ball(world, Point(0, 2), Vector(0.1, -0.22));
//
//    for(int i = 0; i < 100; i++) {
//        world->Step(time_step, velocity_iterations, position_iterations);
//        std::cout << ball.getBall().position() << std::endl;
//    }
//    std::cout << "done" << std::endl;
}


//std::cout << "simulation" << std::endl;
//b2Vec2 gravity(1, 0);
//b2World world(gravity);
//double time_step = 1.0/60.0;
//int velocity_iterations = 8;
//int position_iterations = 3;
//
//b2BodyDef ball_body_def;
//ball_body_def.type = b2_dynamicBody;
//ball_body_def.position.Set(0, 0);
//ball_body_def.linearVelocity.Set(0.0, 0.0);
//b2Body* ball_body = world.CreateBody(&ball_body_def);
//
//b2CircleShape ball_shape;
//ball_shape.m_radius = 1;
//
//b2FixtureDef ball_fixture_def;
//ball_fixture_def.shape = &ball_shape;
//ball_fixture_def.density = 1.0;
//
//ball_body->CreateFixture(&ball_fixture_def);
//
//for(int i = 0; i < 100; i++) {
//world.Step(time_step, velocity_iterations, position_iterations);
////        world.DrawDebugData();
////        auto foo = world.GetBodyCount();
//std::cout << ball_body->GetPosition().x << std::endl;
////        std::cout << ball_body->GetLinearVelocity().x << std::endl;
//
//
//}
//std::cout << "done" << std::endl;
//

