#ifndef FUNCTOR
#define FUNCTOR

#include "./header/vector2ui.hpp"
#include "./header/vector2f.hpp"
#include "./header/rectf.hpp"
#include "./struct.hpp"
#include "./header/text.hpp"

#include <vector>
namespace
{
	TYPE inverce(TYPE type)
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

	void move(Target* const value, Vector2f step)
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

	void generate(Target* const value, Vector2ui place)
	{
		RectF bounds = value->sprite.get_global_bounds();

		value->isLife = true;
		value->type = static_cast<TYPE>(0 + rand() % 4);

		if(value->type == TYPE::TYPE_0)
		{
			value->sprite.set_position(5, 5);
			value->sprite.set_color(ColorDef::WHITE);
		}
		else if(value->type == TYPE::TYPE_1)
		{
			value->sprite.set_position(5, bounds.height + 5);
			value->sprite.set_color(ColorDef::WHITE);
		}
		else if(value->type == TYPE::TYPE_2)
		{
			value->sprite.set_position((place.x - bounds.width) - 5, 5);
			value->sprite.set_color(ColorDef::BLUE);
		}
		else if(value->type == TYPE::TYPE_3)
		{
			value->sprite.set_position((place.x - bounds.width) - 5,
									bounds.height + 5);
			value->sprite.set_color(ColorDef::BLUE);
		}
	}

	void collision(Target* const lv, Target* const rv)
	{
		if(lv->sprite.intersect(rv->sprite))
		{
			lv->type = inverce(lv->type);
			rv->type = inverce(rv->type);

			move(lv, {15, 0});
			move(rv, {15, 0});
		}
	}
};

void functor(Gun& gun, Text& score, std::vector<Target>& targets, Vector2ui windowSize)
            {
				for(auto&& val : targets)
				{
					Vector2f pos = val.sprite.get_position();
					RectF bounds = val.sprite.get_global_bounds();

					if(val.isLife)
					{
						for(auto&& other : targets)
						{
							if(&other != &val)
							{
								collision(&val, &other);
							}
						}

						if(gun.ball)
						{
							CannonBall* cannonBall = gun.ball;

							if (val.sprite.intersect(cannonBall->sprite))
							{
								if(cannonBall->type == GunBallType::BOMB)
								{
									for(auto && innerVal : targets)
									{
										innerVal.isLife = false;
										cannonBall->sprite = nullptr;
										gun.ball = nullptr;

										int points = std::stoi(score.get_text());
										points += 20;
										score.set_text(std::to_string(points));
									}

									return;
								}
								else
								{
									val.isLife = false;
									cannonBall->sprite = nullptr;
									gun.ball = nullptr;

									int points = std::stoi(score.get_text());
									points += 20;
									score.set_text(std::to_string(points));
								}
							}
						}

						if(pos.x >= (windowSize.x - bounds.width)
							|| pos.x <= 0
							|| pos.y <= 0
							|| pos.y >= (windowSize.y - bounds.height))
						{
							val.isLife = false;
						}

						if(val.isLife)
						{
							move(&val, {3, 0});
						}
					}
					else
					{
						generate(&val, windowSize);
					}
				}
            };

#endif //FUNCTOR
