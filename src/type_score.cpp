#include "../header/type_score.hpp"

void TypeScore::add_score_for_type(TYPE type, int score) noexcept
{
	this->_score.emplace(type, score);
}

int TypeScore::get_score_for_type(TYPE type) const noexcept
{
	auto find = this->_score.find(type);
	if(find != std::end(this->_score))
		return find->second;

	return 0;
}
