#include "../header/type_score.hpp"

#include <algorithm>

void TypeScore::add_score_for_type(TYPE type, int score) noexcept
{
	this->_score.emplace_back(type, score);
}

int TypeScore::get_score_for_type(TYPE type) const noexcept
{
	auto find = std::find_if(std::begin(this->_score), std::end(this->_score),
									[&type](typename decltype(this->_score)::value_type value)
									{
										return value.first == type;
									});

	if(find != std::end(this->_score))
		return find->second;

	return 0;
}
