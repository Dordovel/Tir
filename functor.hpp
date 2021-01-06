#ifndef FUNCTOR
#define FUNCTOR

#include "./header/vector2ui.hpp"
#include "./header/vector2f.hpp"
#include "./header/rectf.hpp"
#include "./struct.hpp"
#include "./header/text.hpp"

#include <vector>

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
								if(val.sprite.intersect(other.sprite))
								{
									val.type = inverce(val.type);
									other.type = inverce(other.type);
								}
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
							if(val.type == TYPE::TYPE_0)
								val.sprite.move(3, 0);
							else if(val.type == TYPE::TYPE_1)
								val.sprite.move(3, 1);
							else if(val.type == TYPE::TYPE_2)
								val.sprite.move(-3, 1);
							else if(val.type == TYPE::TYPE_3)
								val.sprite.move(-3, 0);
						}
					}
					else
					{
						val.type = static_cast<TYPE>(0 + rand() % 4);

						if(val.type == TYPE::TYPE_0 || val.type == TYPE::TYPE_1)
						{
							val.sprite.set_position(5, 5);
							val.isLife = true;
						}
						else if(val.type == TYPE::TYPE_2 || val.type == TYPE::TYPE_3)
						{
							val.sprite.set_position((windowSize.x - bounds.width) - 5, 5);
							val.isLife = true;
						}
					}
				}
            };

#endif //FUNCTOR
