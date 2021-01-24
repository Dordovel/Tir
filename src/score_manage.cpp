//
// Created by dordovel on 24.01.2021.
//

#include "../header/score_manage.hpp"

ScoreManage::ScoreManage(TypeScore types) : Score(0), _types(std::move(types)), _isUpdate(false) {}

void ScoreManage::add_score(TYPE type) noexcept
{
	this->_isUpdate = true;
	Score::add_score(this->_types.get_score_for_type(type));
}

bool ScoreManage::is_update() const noexcept
{
	bool update = this->_isUpdate;
	this->_isUpdate = false;
	return update;
}

