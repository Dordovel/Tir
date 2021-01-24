#ifndef FUNCTOR
#define FUNCTOR

#include "vector2ui.hpp"
#include "./score_manage.hpp"
#include "../struct.hpp"

#include <vector>

void targets_functor(Cannon& cannon, ScoreManage& score, std::vector<Target>& targets, Vector2ui windowSize) noexcept;

#endif //FUNCTOR
