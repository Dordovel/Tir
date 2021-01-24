#ifndef PROJECT_SCORE_HEADER
#define PROJECT_SCORE_HEADER

class Score
{
	private:
		long _score;
		long _last;

	protected:
		void add_score(long score) noexcept;
		Score(long score);

	public:
		long get_score() const noexcept;
		long get_last_score() const noexcept;
};

#endif //PROJECT_SCORE_HEADER
