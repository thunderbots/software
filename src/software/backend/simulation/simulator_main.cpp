#include <iostream>
#include <reactphysics3d.h>

int main(int argc, char **argv)
{
    std::cout << "simulation" << std::endl;
    rp3d::Vector3 gravity(0, -9.81, 0);
    rp3d::DynamicsWorld world(gravity);

    rp3d::Vector3 init_position(0, 0.25, 0);
    rp3d::Quaternion init_orientation = rp3d::Quaternion::identity();
    rp3d::Transform transform(init_position, init_orientation);
    rp3d::RigidBody* ball_body = world.createRigidBody(transform);
    rp3d::SphereShape ball_shape(0.1);
    rp3d::ProxyShape* ball_shape_proxy = ball_body->addCollisionShape(&ball_shape, rp3d::Transform::identity(), 1.0);

    rp3d::CollisionBody* ground_body = world.createCollisionBody(rp3d::Transform::identity());
    ground_body->setType(rp3d::BodyType::STATIC);
    rp3d::BoxShape ground_shape({100, 100, 0.01});
    rp3d::ProxyShape* ground_shape_proxy = ground_body->addCollisionShape(&ground_shape, rp3d::Transform::identity());

    const double time_step = 1.0 / 60.0;

    for(int i = 0; i < 100; i++) {
        std::cout << ground_body->getTransform().getPosition().y << std::endl;
//        std::cout << ball_body->getTransform().getPosition().y << std::endl;
        world.update(time_step);
    }
}

