#ifndef PROJECT_WINDOW_HEADER
#define PROJECT_WINDOW_HEADER

#include "../interface/iwindow.hpp"

#include <string_view>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class Window : public IWindow, public sf::RenderWindow
{
	public:
		Window(unsigned int width, unsigned int height, std::string_view title);

		void draw(const IDrawable* const object) noexcept override;
		void draw(const IDrawable& object) noexcept override;

		Vector2ui get_size() const noexcept override;

		void clear() noexcept override;
		void display() noexcept override;

		bool is_open() const noexcept override;
		void close() noexcept override;

        Vector2f map_pixel_to_coord(int x, int y) const noexcept override;
        Vector2f map_pixel_to_coord(const Vector2i& pos) const noexcept override;

        const IEvent& get_event() const noexcept override;
		bool poll_events() noexcept override;
};
#endif //PROJECT_WINDOW_HEADER
