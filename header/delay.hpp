#ifndef PROJECT_MOVE_HEADER
#define PROJECT_MOVE_HEADER

#include <SFML/System/Time.hpp>
#include <tuple>

class DelayBase
{
    protected:
        bool _isRun;

    public:
		DelayBase(bool stat): _isRun(stat){}

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
};

template<typename T, typename ...Args>
class Delay;

template<typename T, typename ...Args>
Delay(int, T, Args...)->Delay<T, Args...>;

template <typename Functor>
class Delay<Functor, void> : public DelayBase
{
    private:
        Functor _functor;

        sf::Time _frame;
        sf::Time _current;

    public:
        Delay(float delay, Functor functor): DelayBase(false), _functor(functor)
        {
            this->_frame = sf::seconds(delay);
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

template <typename Functor, typename ...Args>
class Delay : public DelayBase
{
    private:
        Functor _functor;
		std::tuple<Args...> _functorParams;

        sf::Time _frame;
        sf::Time _current;

    public:
        Delay(float delay, Functor functor, Args... args):DelayBase(false), _functor(functor), _functorParams(std::forward_as_tuple(args...))
        {
            this->_frame = sf::seconds(delay);
        }

        void update(unsigned int delta)
        {
            if(this->_isRun)
            {
                this->_current += sf::milliseconds(delta);
                if (this->_current >= this->_frame)
                {
                    this->_current = sf::microseconds(this->_current.asMicroseconds() % this->_frame.asMicroseconds());

					std::apply(this->_functor, this->_functorParams);
                }
            }
        }
};

#endif //PROJECT_MOVE_HEADER


