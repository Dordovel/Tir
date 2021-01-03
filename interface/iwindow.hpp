#ifndef PROJECT_WINDOW_INTERFACE
#define PROJECT_WINDOW_INTERFACE

#include "./idrawable.hpp"
#include "./ievent.hpp"

struct Vector2i;
struct Vector2f;
struct Vector2ui;

class IWindow
{
	public:
		virtual void draw(const IDrawable* const object) noexcept = 0;
		virtual void draw(const IDrawable& object) noexcept = 0;

		virtual Vector2ui get_size() const noexcept = 0;

		virtual void clear() noexcept = 0;
		virtual void display() noexcept = 0;

		virtual bool is_open() const noexcept = 0;
		virtual void close() noexcept = 0;

		virtual const IEvent& get_event() const noexcept = 0;
		virtual bool poll_events() noexcept = 0;

		virtual Vector2f map_pixel_to_coord(int x, int y) const noexcept = 0;
        virtual Vector2f map_pixel_to_coord(const Vector2i& pos) const noexcept = 0;

		virtual ~IWindow() = default;
};

#endif //PROJECT_WINDOW_INTERFACE
