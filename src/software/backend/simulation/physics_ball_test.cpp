#include "software/backend/simulation/physics_ball.h"
#include <gtest/gtest.h>
#include <Box2D/Box2D.h>
#include "software/ai/world/ball.h"

TEST(PhysicsBallTest, test_constructor_with_ball_state_params)
{
    b2Vec2 gravity(0, 0);
    world = std::make_shared<b2World>(gravity);

    auto physics_ball = PhysicsBall(world, Point(1, -2.33), Vector(0, 5.09));
    auto ball = physics_ball.getBall();

    EXPECT_EQ(Point(1, -2.33), ball.position());
    EXPECT_EQ(Vector(0, 5.09), ball.velocity());
    EXPECT_EQ(Timestamp::fromSeconds(0), ball.lastUpdateTimestamp());
}

TEST(PhysicsBallTest, test_constructor_with_ball_param)
{
    b2Vec2 gravity(0, 0);
    world = std::make_shared<b2World>(gravity);

    Ball ball_parameter(Point(0.1, -0.04), Vector(1, -2), Timestamp::fromSeconds(0));
    auto physics_ball = PhysicsBall(world, ball_parameter);
    auto ball = physics_ball.getBall();

    EXPECT_EQ(ball_parameter.position(), ball.position());
    EXPECT_EQ(ball_parameter.velocity(), ball.velocity());
    EXPECT_EQ(ball_parameter.lastUpdateTimestamp(), ball.lastUpdateTimestamp());
}
