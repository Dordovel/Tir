#ifndef PROJECT_TYPE_SCORE_HEADER
#define PROJECT_TYPE_SCORE_HEADER

#include "../types.hpp"

#include <unordered_map>

class TypeScore
{
    private:
        std::unordered_map<TYPE, int> _score;

    public:
		void add_score_for_type(TYPE type, int score) noexcept;
		int get_score_for_type(TYPE type) const noexcept;
};

#endif //PROJECT_TYPE_SCORE_HEADER
