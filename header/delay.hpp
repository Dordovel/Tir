#ifndef PROJECT_MOVE_HEADER
#define PROJECT_MOVE_HEADER

#include <SFML/System/Time.hpp>

template<typename T>
class Delay;

template<typename T>
Delay(int, T)->Delay<T>;

template <typename Functor>
class Delay
{
    private:
        Functor _functor;

        sf::Time _frame;
        sf::Time _current;

        bool _isRun;

    public:
        Delay(float delay, Functor functor): _functor(functor), _isRun(false)
        {
            this->_frame = sf::seconds(delay);
        }

        bool is_run()
        {
            return this->_isRun;
        }

        void run()
        {
            this->_isRun = true;
        }

        void stop()
        {
            this->_isRun = false;
        }

        void update(unsigned int delta)
        {
            if(this->_isRun)
            {
                this->_current += sf::milliseconds(delta);
                if (this->_current >= this->_frame)
                {
                    this->_current = sf::microseconds(this->_current.asMicroseconds() % this->_frame.asMicroseconds());

                    this->_functor();
                }
            }
        }
};

#endif //PROJECT_MOVE_HEADER


