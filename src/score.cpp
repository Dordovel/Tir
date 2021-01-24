//
// Created by dordovel on 24.01.2021.
//

#include "../header/score.hpp"

Score::Score(long score):_score(score) { }

void Score::add_score(long score) noexcept
{
	this->_last = score;
	this->_score += this->_last;
}

long Score::get_score() const noexcept
{
	return this->_score;
}

long Score::get_last_score() const noexcept
{
	return this->_last;
}


