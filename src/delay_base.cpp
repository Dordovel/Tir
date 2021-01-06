#include "../header/delay_base.hpp"


ADelay::ADelay(float delay, bool stat):_frame(sf::seconds(delay)), _isRun(stat){}

bool ADelay::is_run() const noexcept
{
	return this->_isRun;
}

void ADelay::run() noexcept
{
	this->_isRun = true;
}

void ADelay::stop() noexcept
{
	this->_isRun = false;
}

void ADelay::update(unsigned int delta) noexcept
{
	if(this->_isRun)
	{
		this->_current += sf::milliseconds(delta);
		if (this->_current >= this->_frame)
		{
			this->_current = sf::microseconds(this->_current.asMicroseconds() % this->_frame.asMicroseconds());

			this->invoke();
		}
	}
}
