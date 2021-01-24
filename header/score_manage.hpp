//
// Created by dordovel on 24.01.2021.
//

#ifndef PROJECT_SCORE_MANAGE_HEADER
#define PROJECT_SCORE_MANAGE_HEADER

#include "./score.hpp"
#include "./type_score.hpp"

class ScoreManage : public Score
{
	private:
		TypeScore _types;
		mutable bool _isUpdate;

	public:
		ScoreManage(TypeScore types);

		void add_score(TYPE type) noexcept;

		bool is_update() const noexcept;
};

#endif //PROJECT_SCORE_MANAGE_HEADER
