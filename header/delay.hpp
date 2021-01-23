#ifndef PROJECT_DELAY_IMPL_HEADER
#define PROJECT_DELAY_IMPL_HEADER

#include "./delay_base.hpp"

#include <tuple>


template<typename T, typename ...Args>
class Delay;

template<typename T, typename ...Args>
Delay(int, T, Args...)->Delay<T, Args...>;

template <typename Functor>
class Delay<Functor> final : public ADelay
{
    private:
        Functor _functor;

		void invoke() const noexcept override
		{
			this->_functor();
		}

    public:
        Delay(long delay, Functor functor): ADelay(delay, false), _functor(functor){}
};

template <typename Functor, typename ...Args>
class Delay final : public ADelay
{
    private:
        Functor _functor;
		std::tuple<Args...> _functorParams;

		void invoke() const noexcept override
		{
			std::apply(this->_functor, this->_functorParams);
		}

    public:
        Delay(long delay, Functor functor, Args... args):ADelay(delay, false),
															_functor(functor),
															_functorParams(std::make_tuple(args...)){}

};

#endif // PROJECT_DELAY_IMPL_HEADER


