#include <Interface/Animation/AnimationSnakes.hpp>
#include <Interface/Colors.hpp>
#include <Misc/Utils.hpp>

AnimationSnakes::AnimationSnakes(Window* window):
	Animation(window)
{ }
void AnimationSnakes::load()
{
	this->addSnake();

	updateTimer.start();
	addTimer.start();
}
void AnimationSnakes::update()
{
	// Adding yet another snake
	if ((addTimer.delta_ms() > (Utils::Random::between(1, 3) * 100)) &&
	    (this->lilsnakes.size() < MAX_SNAKES))
	{
		this->addSnake();

		addTimer.start();
	}

	// Random add burst!
	if (Utils::Random::booleanWithChance(25.01))
	{
		for (int i = 0; i < Utils::Random::between(3, 5); i++)
			this->addSnake();
	}

	// Updating all snakes
	// They all drop once and get deleted as soon as they
	// leave the Window.
	if (updateTimer.delta_ms() > 50)
	{
		auto it = this->lilsnakes.begin();

		while (it != this->lilsnakes.end())
		{
			if (((*it).y - (*it).size) > (this->window->getH() - 1))
			{
				it = this->lilsnakes.erase(it);
			}
			else
			{
				(*it).y++;
				++it;
			}
		}
		updateTimer.start();
	}
}
void AnimationSnakes::draw()
{
	for (unsigned int i = 0; i < (this->lilsnakes.size()); i++)
	{
		window->printChar('@',
		                  this->lilsnakes[i].x,
		                  this->lilsnakes[i].y,
		                  Colors::pair(COLOR_GREEN, COLOR_DEFAULT, true));

		for (int j = 1; j < (this->lilsnakes[i].size); j++)
		{
			window->printChar('o',
			                  this->lilsnakes[i].x,
			                  this->lilsnakes[i].y - j,
			                  Colors::pair(COLOR_GREEN, COLOR_DEFAULT));

		}
	}
}
void AnimationSnakes::addSnake()
{
	int newx = Utils::Random::between(1, this->window->getW() - 1);
	int newy = Utils::Random::between(0, 3);
	int size = Utils::Random::between(2, 14);

	this->lilsnakes.push_back(LilSnake(newx, newy, size));
}
