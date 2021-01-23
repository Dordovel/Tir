#ifndef FUNCTOR
#define FUNCTOR

#include "vector2ui.hpp"
#include "text.hpp"
#include "../struct.hpp"

#include <vector>

void targets_functor(Cannon& cannon, Text& score, std::vector<Target>& targets, Vector2ui windowSize) noexcept;

#endif //FUNCTOR
