#include "./header/window.hpp"
#include "./header/event.hpp"
#include "./header/sprite.hpp"
#include "./header/text.hpp"
#include "./header/vector2ui.hpp"
#include "./header/vector2f.hpp"
#include "./header/rectf.hpp"
#include "./header/delay.hpp"

#include <cmath>
#include <iostream>

enum class TYPE
{
	TYPE_0,
	TYPE_1,
	TYPE_2,
	TYPE_3
};

enum class GunBallType
{
	BALL,
	BOMB
};

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

static inline std::string RESOURCES_FOLDER = "../resources/";

struct Target
{
    Sprite sprite;
    bool isLife = false;
    TYPE type;
};

struct CannonBall
{
    Sprite* sprite = nullptr;
	GunBallType type;
};

struct Gun
{
	CannonBall* ball = nullptr;
    float angle = 0;
};

Vector2f move(float angle, Vector2f pos, Vector2f vel)
{
    sf::Transform rotation;
    rotation.rotate(angle);
    sf::Vector2f velosity(vel.x, vel.y);

    sf::Vector2f step = sf::Vector2f{pos.x, pos.y} + rotation.transformPoint(velosity);

    return {step.x, step.y};
}

int main()
{
    Window window = Window(500, 500, "Test");

    Sprite background = Sprite(RESOURCES_FOLDER + "background.png");

	RectF backgroundSize = background.get_global_bounds();

	Vector2ui windowSize = window.get_size();

	background.set_scale((windowSize.x / backgroundSize.width),
									(windowSize.y / backgroundSize.height));


	Text score = Text(RESOURCES_FOLDER + "Font.otf");
	{
		score.set_text("0");
		score.set_position(windowSize.x - (windowSize.x / 6), windowSize.y - (windowSize.y / 6));
		score.set_color(ColorDef::RED);
	}

    Sprite aim = Sprite(RESOURCES_FOLDER + "Aim.png");
    aim.set_scale(0.3f, 0.3f);

	Sprite stand = Sprite(RESOURCES_FOLDER + "Stand.png");
    stand.set_scale(0.2f, 0.2f);

	Sprite cannon = Sprite(RESOURCES_FOLDER + "Cannon.png");
	{
		RectF cannonSize = cannon.get_global_bounds();
		cannon.set_origin((cannonSize.left + (cannonSize.width / 2)),
									((cannonSize.top + cannonSize.height) - (cannonSize.height / 3)));
		cannon.set_scale(0.17f, 0.17f);
	}


	RectF standSize = stand.get_global_bounds();

	Vector2f coords = Vector2f{windowSize.x / 2.f,
                       windowSize.y - (windowSize.y / 5.f)};

	stand.set_position(coords.x - (standSize. width / 2), coords.y);

	cannon.set_position((coords.x), (coords.y + standSize.height / 3));

	std::vector<Target> targets;
	{
		Target target = {Sprite(RESOURCES_FOLDER + "Target.png"), true, TYPE::TYPE_0};
		target.sprite.set_scale(0.2f, 0.2f);
		target.sprite.set_position(10, 5);

		targets = std::vector(3, target);
	}

	std::vector<Sprite> gunDrum;
	{
		gunDrum.emplace_back(RESOURCES_FOLDER + "Cannonball.png");
		Sprite* tmp = &gunDrum.back();
		tmp->set_scale(0.2f, 0.2f); 

		gunDrum.emplace_back(RESOURCES_FOLDER + "Bomb.png");
		tmp = &gunDrum.back();
		tmp->set_scale(0.2f, 0.2f); 
	}

	CannonBall cannonBall;
	Gun gun;

    auto functor = [&gun, &score,  &targets, windowSize = window.get_size()]()
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

    Delay delay(30.f, functor);
    if(!delay.is_run())
        delay.run();

    auto cannonFunctor = [&gun, windowSize = window.get_size()]()
            {
				if(!gun.ball) return;

				CannonBall* cannonBall = gun.ball;

                Vector2f pos = cannonBall->sprite->get_position();

				if (pos.x >= (windowSize.x)
					|| pos.x <= 0
					|| pos.y <= 0
					|| pos.y >= (windowSize.y))
				{
					cannonBall->sprite = nullptr;
					gun.ball = nullptr;
				}
				else
				{
					Vector2f pos = cannonBall->sprite->get_position();
					float angle = (gun.angle - 180) + 45;
					Vector2f coord = move(angle, pos, Vector2f{2.f, 2.f});

					cannonBall->sprite->set_position(coord);
				}
            };

    Delay cannonDelay(20.0f, cannonFunctor);
        cannonDelay.run();

	sf::Event event;
	sf::Clock clock;
	float time = 1;

	sf::Time timer = sf::seconds(60 * 2);

	Text timerStat = score;

	bool appIsRun = false;

	Text buttonNew = timerStat;
	buttonNew.set_text("New");
	buttonNew.set_position((windowSize.x / 2) , ((windowSize.y / 2) - buttonNew.get_global_bounds().height));

	Text buttonExit = buttonNew;
	buttonExit.set_text("Exit");
	buttonExit.set_position((windowSize.x / 2) , ((windowSize.y / 2) + buttonExit.get_global_bounds().height));

    while (window.is_open())
	{
		while (window.poll_events())
		{
			event = window.get_event().get_object();
			if (event.type == sf::Event::Closed)
				window.close();

				if(event.type == sf::Event::MouseButtonPressed)
				{
					if(event.mouseButton.button == sf::Mouse::Left)
					{
						Vector2f coords = window.map_pixel_to_coord(event.mouseButton.x, event.mouseButton.y);
						
						if(buttonNew.intersect(coords))
						{
							appIsRun = true;
						}

						if(buttonExit.intersect(coords))
						{
							window.close();
						}
					}
				}
		}

		while(appIsRun)
		{
			time += clock.getElapsedTime().asMilliseconds();

			timer -= clock.getElapsedTime();
			timerStat.set_text("Time: " + std::to_string(int(timer.asSeconds())) + " sec");
			timerStat.set_position((windowSize. x - timerStat.get_global_bounds().width) - 20, windowSize. y / 2);

			clock.restart();

			if(!cannonBall.sprite)
			{
				int rnd = 0 + rand() % 10;

				if(rnd != 6)
				{
					cannonBall.sprite = &gunDrum.front();
					cannonBall.type = GunBallType::BALL;
				}
				else
				{
					cannonBall.sprite = &gunDrum.back();
					cannonBall.type = GunBallType::BOMB;
				}

				cannonBall.sprite->set_position(10, (windowSize.y - (windowSize.y / 5)));
			}

			cannonDelay.update(time);
			delay.update(time);


			if(timer.asSeconds() <= 0)
				appIsRun = false;

			while (window.poll_events())
			{
				event = window.get_event().get_object();
				if (event.type == sf::Event::Closed)
					appIsRun = false;

				if(event.type == sf::Event::MouseButtonPressed)
				{
					if(event.mouseButton.button == sf::Mouse::Left)
					{
						if(cannonBall.sprite)
						{
							RectF bound = cannonBall.sprite->get_global_bounds();
							RectF boundCannon = cannon.get_global_bounds();

							Vector2f pos = cannon.get_position();
							float angle = (cannon.get_rotation() - 180) + 45;
							Vector2f coord = move(angle, pos, Vector2f{boundCannon.height / 2, boundCannon.height / 2});

							cannonBall.sprite->set_position(coord.x - (bound.width / 2), coord.y - (bound.height / 2));

							gun.angle = cannon.get_rotation();
							gun.ball = &cannonBall;
							cannonDelay.run();
						}
					}
				}

				if(event.type == sf::Event::MouseMoved)
				{
					Vector2f coords = window.map_pixel_to_coord(event.mouseMove.x, event.mouseMove.y);

					RectF aimBound = aim.get_global_bounds();

					aim.set_position(coords.x - (aimBound.width / 2), coords.y - (aimBound.height / 2));

					Vector2f pos = cannon.get_position();
					float angle = std::atan2(coords.y - pos.y, coords.x - pos.x);
					angle = ((angle * 180.f) / float(M_PI) + 90);

					cannon.set_rotation(angle);
				}
			}
			

			window.clear();
			window.draw(background);
			window.draw(stand);
			window.draw(cannon);

			if(cannonBall.sprite)
				window.draw(cannonBall.sprite);

			for(auto&& val : targets)
				if(val.isLife)
					window.draw(val.sprite);

			window.draw(aim);

			window.draw(score);
			window.draw(timerStat);
			window.display();
		}

		window.clear();
		window.draw(background);
		window.draw(buttonNew);
		window.draw(buttonExit);
		window.display();

    }

    return 0;
}
