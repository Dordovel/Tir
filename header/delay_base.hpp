#ifndef PROJECT_DELAY_ABSTRACT_HEADER
#define PROJECT_DELAY_ABSTRACT_HEADER

#include <SFML/System/Time.hpp>

class ADelay
{
	private:

        sf::Time _frame;
        sf::Time _current;

        bool _isRun;

    protected:

		virtual void invoke() = 0;

		ADelay(float delay, bool stat);

    public:

        bool is_run() const noexcept;

        void run() noexcept;

        void stop() noexcept;

        void update(unsigned int delta) noexcept;
};

#endif //PROJECT_DELAY_ABSTRACT_HEADER
