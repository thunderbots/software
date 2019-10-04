#include "software/backend/simulation/physics_field.h"

PhysicsField::PhysicsField(std::shared_ptr<b2World> world, const Field &field) : field(field) {
    field_boundary_body_def.type = b2_staticBody;
    field_boundary_body_def.position.Set(0, 0);
    field_boundary_body = world->CreateBody(&field_boundary_body_def);

    // TODO: Use a real field rectangle to set these values
    b2Vec2 vs[4];
    vs[0].Set(-field.totalLength() / 2, field.totalWidth() / 2);
    vs[1].Set(field.totalLength() / 2, field.totalWidth() / 2);
    vs[2].Set(field.totalLength() / 2, -field.totalWidth() / 2);
    vs[3].Set(-field.totalLength() / 2, -field.totalWidth() / 2);
    field_boundary_shape.CreateLoop(vs, 4);
    field_boundary_fixture_def.shape = &field_boundary_shape;
    field_boundary_fixture_def.restitution = 1.0;
    field_boundary_fixture_def.friction = 1.0;
    field_boundary_body->CreateFixture(&field_boundary_fixture_def);
}

Field PhysicsField::getField() const {
    return field;
}

