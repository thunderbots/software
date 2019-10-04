#pragma once

#include <Box2D/Box2D.h>
//#include "software/geom/point.h"
#include "software/ai/world/field.h"
#include "Box2D/Box2D.h"
#include "../../../../../../.cache/bazel/_bazel_mathew/84b6638ae5fbabc0fbab9d81e91fe5fc/execroot/__main__/external/box2d/Box2D/Collision/Shapes/b2PolygonShape.h"

class PhysicsField {
public:
    PhysicsField() = delete;

    explicit PhysicsField(std::shared_ptr<b2World> world, const Field& field);

    Field getField() const;
private:
    // The 4 boundary walls that surround the field
    b2BodyDef pos_y_field_boundary_body_def;
    b2PolygonShape pos_y_field_boundary_shape;
    b2BodyDef neg_y_field_boundary_body_def;
    b2PolygonShape neg_y_field_boundary_shape;
    b2BodyDef pos_x_field_boundary_body_def;
    b2PolygonShape pos_x_field_boundary_shape;
    b2BodyDef neg_x_field_boundary_body_def;
    b2PolygonShape neg_x_field_boundary_shape;

//    b2CircleShape ball_shape;
//    b2BodyDef ball_body_def;
//    b2FixtureDef ball_fixture_def;
//    b2Body* ball_body;
};
