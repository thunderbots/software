#include "software/ai/hl/stp/tactic/goalie_tactic.h"

#include "shared/constants.h"
#include "software/ai/hl/stp/action/chip_action.h"
#include "software/ai/hl/stp/action/move_action.h"
#include "software/ai/hl/stp/evaluation/calc_best_shot.h"
#include "software/ai/hl/stp/tactic/tactic_visitor.h"
#include "software/geom/point.h"
#include "software/geom/ray.h"
#include "software/geom/segment.h"
#include "software/geom/util.h"
#include "software/util/parameter/dynamic_parameters.h"


GoalieTactic::GoalieTactic(const Ball &ball, const Field &field,
                           const Team &friendly_team, const Team &enemy_team)
    : Tactic(true),
      ball(ball),
      field(field),
      friendly_team(friendly_team),
      enemy_team(enemy_team)
{
    addWhitelistedAvoidArea(AvoidArea::FRIENDLY_DEFENSE_AREA);
}

std::string GoalieTactic::getName() const
{
    return "Goalie Tactic";
}

void GoalieTactic::updateWorldParams(const Ball &ball, const Field &field,
                                     const Team &friendly_team, const Team &enemy_team)
{
    // Update the world parameters stored by this Tactic
    this->ball          = ball;
    this->field         = field;
    this->friendly_team = friendly_team;
    this->enemy_team    = enemy_team;
}

double GoalieTactic::calculateRobotCost(const Robot &robot, const World &world)
{
    // Strongly prefer the robot assigned to be the goalie.
    // TODO: This is a hack to "ensure" the right robot will be assigned. We should
    // normally return values in the range [0, 1]
    if (world.friendlyTeam().getGoalieID() &&
        robot.id() == world.friendlyTeam().getGoalieID().value())
    {
        return 0.0;
    }
    else
    {
        return 1000000;
    }
}

void GoalieTactic::calculateNextIntent(IntentCoroutine::push_type &yield)
{
    MoveAction move_action = MoveAction();
    ChipAction chip_action = ChipAction();
    do
    {
        // Goalie Tactic
        //
        // The goalie tactic is responsible for blocking as many shots as it can, to the
        // best of its ability. The tactic consists of 3 cases
        //
        // Case 1: The ball is moving towards the goal and has a speed that is concerning
        //      Goalie moves onto the closest point on the oncoming line to stop the ball
        //
        // Case 2: The ball is moving at a slow speed and is inside the defense area
        //      Goalie moves to the ball and chips it out of the defense area
        //
        // Case 3: Any other case
        //      Goalie blocks the cone to the net. (Cone being from the ball to either
        //      goal post) The goalie also snaps to a semicircle inside the defense area,
        //      to avoid leaving the defense area
        //
        std::unique_ptr<Intent> next_intent;

        // compute intersection points from ball position and velocity
        Ray ball_ray = Ray(ball.position(), ball.velocity());
        Segment full_goal_segment =
            Segment(field.friendlyGoalpostNeg(), field.friendlyGoalpostPos());

        std::optional<Point> intersection1 =
            raySegmentIntersection(ball_ray, full_goal_segment).first;

        // Case 1
        if (intersection1.has_value() &&
            ball.velocity().len() > BALL_SLOW_SPEED_THRESHOLD)
        {
            // the ball is heading towards the net. move to block the shot
            Point goalie_pos = closestPointOnSeg(
                (*robot).position(), Segment(ball.position(), *intersection1));
            Angle goalie_orientation = (ball.position() - goalie_pos).orientation();

            next_intent = move_action.updateStateAndGetNextIntent(
                *robot, goalie_pos, goalie_orientation, 0.0, false, false, AUTOCHIP);
        }
        // Case 2
        else if (ball.velocity().len() < BALL_SLOW_SPEED_THRESHOLD &&
                 field.pointInFriendlyDefenseArea(ball.position()))
        {
            // if the ball is slow or stationary inside our defense area, chip it out
            next_intent = chip_action.updateStateAndGetNextIntent(
                *robot, ball, ball.position(),
                (ball.position() - field.friendlyGoal()).orientation(), 2);
        }
        // Case 3
        else
        {
            // block the cone by default
            float radius =
                Util::DynamicParameters::GoalieTactic::block_cone_buffer.value() +
                ROBOT_MAX_RADIUS_METERS;
            Point goalie_pos =
                calcBlockCone(field.friendlyGoalpostNeg(), field.friendlyGoalpostPos(),
                              ball.position(), radius);

            // restrict the goalie to a semicircle inscribed inside the defense area
            Point goalie_restricted_pos =
                field.friendlyGoal() - (field.friendlyDefenseArea().yLength() *
                                        (field.friendlyGoal() - goalie_pos).norm());

            // restrict the point to be within the defense area
            auto goalie_orientation = (ball.position() - goalie_pos).orientation();
            next_intent             = move_action.updateStateAndGetNextIntent(
                *robot, goalie_restricted_pos, goalie_orientation, 0.0, false, false,
                AUTOCHIP);
        }

        yield(std::move(next_intent));

    } while (!move_action.done());
}

void GoalieTactic::accept(TacticVisitor &visitor) const
{
    visitor.visit(*this);
}
