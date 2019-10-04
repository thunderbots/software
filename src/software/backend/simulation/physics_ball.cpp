#include "software/backend/simulation/physics_ball.h"
#include "shared/constants.h"

PhysicsBall::PhysicsBall(std::shared_ptr<b2World> world, const Point &position, const Vector &velocity) {
    // All the BodyDef must be defined before the body is created.
    // Changes made after aren't reflected
    ball_body_def.type = b2_dynamicBody;
    ball_body_def.position.Set(position.x(), position.y());
    ball_body_def.linearVelocity.Set(velocity.x(), velocity.y());

    ball_body = world->CreateBody(&ball_body_def);

    initializeBall();
}

PhysicsBall::PhysicsBall(std::shared_ptr<b2World> world, const Ball &ball) {
    // All the BodyDef must be defined before the body is created.
    // Changes made after aren't reflected
    ball_body_def.type = b2_dynamicBody;
    ball_body_def.position.Set(ball.position().x(), ball.position().y());
    ball_body_def.linearVelocity.Set(ball.velocity().x(), ball.velocity().y());

    ball_body = world->CreateBody(&ball_body_def);

    initializeBall();
}

void PhysicsBall::initializeBall() {
    ball_shape.m_radius = BALL_MAX_RADIUS_METERS;

    ball_fixture_def.shape = &ball_shape;
    ball_fixture_def.density = 1.0;
    ball_fixture_def.restitution = 1.0;
    ball_fixture_def.friction = 1.0;

    ball_body->CreateFixture(&ball_fixture_def);
}

b2Body *PhysicsBall::getBallBodyPtr() const {
    return ball_body;
}

Ball PhysicsBall::getBall() const {
    auto position = Point(ball_body->GetPosition().x, ball_body->GetPosition().y);
    auto velocity = Vector(ball_body->GetLinearVelocity().x, ball_body->GetLinearVelocity().y);
    // TODO: timestamps
    return Ball(position, velocity, Timestamp::fromSeconds(0));
}
