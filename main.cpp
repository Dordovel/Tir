#include "./header/window.hpp"
#include "./header/event.hpp"
#include "./header/sprite.hpp"
#include "./header/text.hpp"
#include "./header/vector2ui.hpp"
#include "./header/vector2f.hpp"
#include "./header/rectf.hpp"
#include "./header/delay.hpp"
#include "./functor.hpp"
#include "./header/data.hpp"

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

	Resources resources = Resources("../resources");

	Sprite background = Sprite(resources.get_resources("background"));

	RectF backgroundSize = background.get_global_bounds();

	Vector2ui windowSize = window.get_size();

	Sprite aim = Sprite(resources.get_resources("Aim"));
	aim.set_scale(0.3f, 0.3f);

	auto mouse_move = [&aim](Vector2f coords)
				{
					RectF aimBound = aim.get_global_bounds();

					aim.set_position(coords.x - (aimBound.width / 2),
										coords.y - (aimBound.height / 2));
				};

	background.set_scale((windowSize.x / backgroundSize.width),
									(windowSize.y / backgroundSize.height));


	Text scoreTitle = Text(resources.get_resources("Font"));
	Text score = scoreTitle;
	{
		scoreTitle.set_text("Score: ");
		scoreTitle.set_color(ColorDef::RED);

		Vector2f pos = {
							windowSize.x - (windowSize.x / 3.f),
							windowSize.y - (windowSize.y / 6.f)
					};
		scoreTitle.set_position(pos);

		RectF size = scoreTitle.get_global_bounds();

		score.set_text("0");
		score.set_position(
							pos.x + size.width,
							pos.y);

		score.set_color(ColorDef::RED);
	}

	Text buttonNew = score;
	buttonNew.set_text("New");
	buttonNew.set_position((windowSize.x / 2) ,
							((windowSize.y / 2) - buttonNew.get_global_bounds().height));

	Text buttonExit = buttonNew;
	buttonExit.set_text("Exit");
	buttonExit.set_position((windowSize.x / 2) ,
							((windowSize.y / 2) + buttonExit.get_global_bounds().height));

	Text timerStat = buttonExit;

	Sprite timerIcon = Sprite( resources.get_resources("Clock"));
	timerIcon.set_scale(0.2, 0.2);

	Sprite stand = Sprite(resources.get_resources("Stand"));
	stand.set_scale(0.2f, 0.2f);

	Sprite cannon = Sprite(resources.get_resources("Cannon"));
	{
		RectF cannonSize = cannon.get_global_bounds();
		cannon.set_origin((cannonSize.left + (cannonSize.width / 2)),
									((cannonSize.top + cannonSize.height) - (cannonSize.height / 3)));
		cannon.set_scale(0.17f, 0.17f);
	}

	{
		RectF standSize = stand.get_global_bounds();

		Vector2f coords = Vector2f{windowSize.x / 2.f,
						   windowSize.y - (windowSize.y / 5.f)};

		stand.set_position(coords.x - (standSize. width / 2), coords.y);

		cannon.set_position((coords.x), (coords.y + standSize.height / 3));
	}

	std::vector<Target> targets;
	{
		Target target = {Sprite(resources.get_resources("Target")), true, TYPE::TYPE_0};
		target.sprite.set_scale(0.2f, 0.2f);
		target.sprite.set_position(10, 5);

		targets = std::vector(4, target);
	}

	std::vector<Sprite> gunDrum;
	{
		gunDrum.emplace_back(resources.get_resources("Cannonball"));
		Sprite* tmp = &gunDrum.back();
		tmp->set_scale(0.2f, 0.2f);

		gunDrum.emplace_back(resources.get_resources("Bomb"));
		tmp = &gunDrum.back();
		tmp->set_scale(0.2f, 0.2f);
	}

	CannonBall cannonBall;
	Gun gun;

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

    /*Delay cannonDelay(15, cannonFunctor);
		cannonDelay.run();

    Delay delay(20, functor, gun, score, targets, windowSize);
	if(!delay.is_run())
		delay.run();
*/
	sf::Event event;
	sf::Clock clock;
	float time = 1;
    sf::Time timer;

	bool appIsRun = false;


	while (window.is_open())
	{
		//MAIN MENU EVENT LOOP
		while (window.poll_events())
		{
			event = window.get_event().get_object();
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if(event.type == sf::Event::MouseMoved)
			{
				Vector2f coords = window.map_pixel_to_coord(event.mouseMove.x, event.mouseMove.y);

				mouse_move(coords);
			}

			if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					Vector2f coords = window.map_pixel_to_coord(event.mouseButton.x, event.mouseButton.y);

					if(buttonNew.intersect(coords))
					{
						appIsRun = true;
						timer = sf::seconds(60 * 2);
					}

					if(buttonExit.intersect(coords))
					{
						window.close();
					}
				}
			}
		} //MAIN MENU EVENT LOOP

		//GAME LOOP
		while(appIsRun)
		{
			timer -= clock.getElapsedTime();
            time += clock.restart().asSeconds();

			{
				float sec = timer.asSeconds();
				timerStat.set_text(std::to_string(int(sec / 60)) + ":" + std::to_string(int(sec) % 60));

				RectF bound = timerStat.get_global_bounds();
				Vector2f pos = {(windowSize. x - bound.width) - 20,
								windowSize. y / 2.f};

				timerStat.set_position(pos);

				bound = timerIcon.get_global_bounds();

				timerIcon.set_position(pos.x - bound.width, pos.y);
			}


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

			if(timer.asSeconds() <= 0)
				appIsRun = false;

			while (window.poll_events())
			{
				event = window.get_event().get_object();
				if (event.type == sf::Event::Closed)
				{
					appIsRun = false;
				}

				if(event.type == sf::Event::KeyPressed)
				{
					if(event.key.code == sf::Keyboard::Escape)
					{
						appIsRun = false;
					}
				}

				if(event.type == sf::Event::MouseButtonPressed)
				{
					if(event.mouseButton.button == sf::Mouse::Left)
					{
						if(cannonBall.sprite && !gun.ball)
						{
							RectF bound = cannonBall.sprite->get_global_bounds();
							RectF boundCannon = cannon.get_global_bounds();

							Vector2f pos = cannon.get_position();
							float angle = (cannon.get_rotation() - 180) + 45;
							Vector2f coord = move(angle, pos,
													Vector2f{boundCannon.height / 2,
																boundCannon.height / 2});

							cannonBall.sprite->set_position(coord.x - (bound.width / 2),
															coord.y - (bound.height / 2));

							gun.angle = cannon.get_rotation();
							gun.ball = &cannonBall;
						}
					}
				}

				if(event.type == sf::Event::MouseMoved)
				{
					Vector2f coords = window.map_pixel_to_coord(event.mouseMove.x, event.mouseMove.y);

					mouse_move(coords);

					Vector2f pos = cannon.get_position();
					float angle = std::atan2(coords.y - pos.y, coords.x - pos.x);
					angle = ((angle * 180.f) / float(3.14) + 90);

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

			window.draw(scoreTitle);
			window.draw(score);
			window.draw(timerStat);
			window.draw(timerIcon);
			window.display();
		}//GAME LOOP

		window.clear();
		window.draw(background);
		window.draw(aim);
		window.draw(buttonNew);
		window.draw(buttonExit);
		window.display();

	}

	return 0;
}
