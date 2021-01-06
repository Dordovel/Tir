#ifndef PROJECT_EVENT_HEADER
#define PROJECT_EVENT_HEADER

#include "../interface/ievent.hpp"

#include <SFML/Window/Event.hpp>

class Event final : public IEvent
{
	public:
		sf::Event _object;

		sf::Event get_object() const noexcept override;
};

#endif //PROJECT_EVENT_HEADER
