#include "software/backend/simulation/physics_field.h"
#include "../../../../../../.cache/bazel/_bazel_mathew/84b6638ae5fbabc0fbab9d81e91fe5fc/execroot/__main__/external/box2d/Box2D/Box2D.h"

PhysicsField::PhysicsField(std::shared_ptr<b2World> world, const Field &field) {
    pos_y_field_boundary_shape.SetAsBox()
    pos_y_field_boundary_body_def.type = b2_staticBody;
    pos_y_field_boundary_body_def.position.Set(0, field.width() / 2.0);
    pos_y_field_boundary_body_def.angle(0.0);

    neg_y_field_boundary_body_def.type = b2_staticBody;
    neg_y_field_boundary_body_def.position.Set(0, -field.width() / 2.0);
    neg_y_field_boundary_body_def.angle(0.0);

    pos_x_field_boundary_body_def.type = b2_staticBody;
    pos_x_field_boundary_body_def.position.Set(field.length() / 2.0, 0);
    // TODO: radians?
    pos_x_field_boundary_body_def.angle(90);

    neg_x_field_boundary_body_def.type = b2_staticBody;
    neg_x_field_boundary_body_def.position.Set(field.length() / 2.0, 0);
    // TODO: radians?
    neg_x_field_boundary_body_def.angle(90);
}

