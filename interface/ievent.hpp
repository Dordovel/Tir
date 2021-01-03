#ifndef  PROJECT_EVENT_INTERFACE
#define PROJECT_EVENT_INTERFACE

namespace sf
{
	class Event;
};

class IEvent
{
	public:
		virtual sf::Event get_object() const noexcept = 0;
		virtual ~IEvent() = default;
};

#endif //PROJECT_EVENT_INTERFACE
