#pragma once

#include <Box2D/Box2D.h>
#include "software/geom/point.h"
#include "software/ai/world/ball.h"
#include "Box2D/Box2D.h"

class PhysicsBall {
public:
    PhysicsBall() = delete;

    explicit PhysicsBall(std::shared_ptr<b2World> world, const Point& position, const Vector& velocity);
    explicit PhysicsBall(std::shared_ptr<b2World> world, const Ball& ball);

    Ball getBall() const;
private:
    b2Body* getBallBodyPtr() const;
    void initializeBall();

    b2CircleShape ball_shape;
    b2BodyDef ball_body_def;
    b2FixtureDef ball_fixture_def;
    b2Body* ball_body;
};
