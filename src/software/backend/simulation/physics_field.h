#pragma once

#include "software/ai/world/field.h"
#include "Box2D/Box2D.h"

class PhysicsField {
public:
    PhysicsField() = delete;

    explicit PhysicsField(std::shared_ptr<b2World> world, const Field& field);

    Field getField() const;
private:
    // This body represents the 4 boundary walls around the edge of the field
    b2BodyDef field_boundary_body_def;
    b2ChainShape field_boundary_shape;
    b2Body* field_boundary_body;
    b2FixtureDef field_boundary_fixture_def;

    // This body represents the enemy net
    b2BodyDef enemy_net_body_def;
    b2ChainShape enemy_net_shape;
    b2Body* enemy_net_body;
    b2FixtureDef enemy_net_fixture_def;

    // This body represents the friendly net
    b2BodyDef friendly_net_body_def;
    b2ChainShape friendly_net_shape;
    b2Body* friendly_net_body;
    b2FixtureDef friendly_net_fixture_def;

    Field field;
};
