#include "../header/targets_functor.hpp"

#include "../header/vector2f.hpp"
#include "../header/rectf.hpp"

#include <cmath>

namespace FUNCTOR
{
    TYPE reverse_type(TYPE type) noexcept;

    void move_target_on_step(Target* value, Vector2f step) noexcept;

    void update_target_params(Target* value, TYPE type, Vector2ui place) noexcept;

    TYPE generate_type_for_target() noexcept;

    bool check_collision(const Target& lv, const Target& rv) noexcept;

    bool check_damage(const Target& target, const CannonBall& cannonBall) noexcept;

    void collision_handling(Target* lv, Target* rv) noexcept;

    void update_score_value(ScoreManage* score, const Target& target) noexcept;
};

void targets_functor(Cannon& cannon, ScoreManage& score, std::vector<Target>& targets, Vector2ui windowSize) noexcept
{
    for(auto&& currentTarget : targets)
    {
        Vector2f pos = currentTarget.sprite.get_position();
        RectF bounds = currentTarget.sprite.get_global_bounds();

        if(currentTarget.isLife)
        {
            for(auto&& otherTarget : targets)
            {
                if(&otherTarget != &currentTarget)
                {
                    if(check_collision(currentTarget, otherTarget))
                        collision_handling(&currentTarget, &otherTarget);
                }
            }

            if(cannon.cannonBall)
            {
                CannonBall* cannonBall = cannon.cannonBall;

                if (check_damage(currentTarget, *cannonBall))
                {
                    if(cannonBall->type == GunBallType::BOMB)
                    {
                        for(auto && otherTarget : targets)
                        {
	                        otherTarget.isLife = false;
                            cannonBall->sprite = nullptr;
                            cannon.cannonBall = nullptr;

                            update_score_value(&score, otherTarget);
                        }

                        return;
                    }
                    else
                    {
                        currentTarget.isLife = false;
                        cannonBall->sprite = nullptr;
                        cannon.cannonBall = nullptr;

                        update_score_value(&score, currentTarget);
                    }
                }
            }

            if(pos.x >= (windowSize.x - bounds.width)
               || pos.x <= 0
               || pos.y <= 0
               || pos.y >= (windowSize.y - bounds.height))
            {
                currentTarget.isLife = false;
            }

            if(currentTarget.isLife)
            {
                move_target_on_step(&currentTarget, {3, 0});
            }
        }
        else
        {
            TYPE generatedType = generate_type_for_target();
            update_target_params(&currentTarget, generatedType, windowSize);
        }
    }
};

namespace FUNCTOR
{
    TYPE reverse_type(TYPE type) noexcept
    {
        if(type == TYPE::TYPE_0)
        {
            return TYPE::TYPE_3;
        }
        else if(type == TYPE::TYPE_1)
        {
            return TYPE::TYPE_2;
        }
        else if(type == TYPE::TYPE_2)
        {
            return TYPE::TYPE_1;
        }

        return TYPE::TYPE_0;
    }

    void move_target_on_step(Target* const value, Vector2f step) noexcept
    {
        if(value->type == TYPE::TYPE_0
           || value->type == TYPE::TYPE_1)
        {
            value->sprite.move((step.x / 2), step.y);
        }
        else if(value->type == TYPE::TYPE_2
                || value->type == TYPE::TYPE_3)
        {
            value->sprite.move(step.x * (-1), step.y);
        }
    }

    void update_target_params(Target* const value, TYPE type, Vector2ui place) noexcept
    {
        RectF bounds = value->sprite.get_global_bounds();
        value->isLife = true;

        value->type = type;

        if(value->type == TYPE::TYPE_0)
        {
            value->sprite.set_position(5, 5);
            value->sprite.set_color(ColorDef::WHITE);
        }
        else if(value->type == TYPE::TYPE_1)
        {
            value->sprite.set_position(5, bounds.height + 5);
            value->sprite.set_color(ColorDef::CYAN);
        }
        else if(value->type == TYPE::TYPE_2)
        {
            value->sprite.set_position((place.x - bounds.width) - 5, 5);
            value->sprite.set_color(ColorDef::GREEN);
        }
        else if(value->type == TYPE::TYPE_3)
        {
            value->sprite.set_position((place.x - bounds.width) - 5,
                                       bounds.height + 5);
            value->sprite.set_color(ColorDef::BLUE);
        }
    }

    TYPE generate_type_for_target() noexcept
    {
        return static_cast<TYPE>(0 + rand() % 4);
    }

    bool check_collision(const Target& lv, const Target& rv) noexcept
    {
        return lv.sprite.intersect(rv.sprite);
    }

    bool check_damage(const Target& target, const CannonBall& cannonBall) noexcept
    {
        return target.sprite.intersect(cannonBall.sprite);
    }

    void collision_handling(Target* const lv, Target* const rv) noexcept
    {
        lv->type = reverse_type(lv->type);
        rv->type = reverse_type(rv->type);

        move_target_on_step(lv, {15, 0});
        move_target_on_step(rv, {15, 0});
    }

    void update_score_value(ScoreManage* const score, const Target& target) noexcept
    {
    	score->add_score(target.type);
    }
};
