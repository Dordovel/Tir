#include "../header/window.hpp"
#include "../header/vector2i.hpp"
#include "../header/vector2f.hpp"
#include "../header/vector2ui.hpp"
#include "../header/graphic_object.hpp"
#include "../header/event.hpp"

static inline Event event;

Window::Window(unsigned int width, unsigned int height, std::string_view title):
				sf::RenderWindow(sf::VideoMode(width, height), title.data(), sf::Style::Titlebar | sf::Style::Close)
{
	sf::RenderWindow::setMouseCursorVisible(false);
}

void Window::draw(const IDrawable* const object) noexcept
{
	sf::RenderWindow::draw(object->get_object().object);
}

void Window::draw(const IDrawable& object) noexcept
{
	sf::RenderWindow::draw(object.get_object().object);
}

Vector2ui Window::get_size() const noexcept
{
	sf::Vector2u size = sf::RenderWindow::getSize();
	return {size.x, size.y};
}

void Window::clear() noexcept
{
	sf::RenderWindow::clear();
}

void Window::display() noexcept
{
	sf::RenderWindow::display();
}

bool Window::is_open() const noexcept
{
	return sf::RenderWindow::isOpen();
}

void Window::close() noexcept
{
	sf::RenderWindow::close();
}

bool Window::poll_events() noexcept
{
	return sf::RenderWindow::pollEvent(event._object);
}

const IEvent& Window::get_event() const noexcept
{
	return event;
}

Vector2f Window::map_pixel_to_coord(int x, int y) const noexcept
{
    sf::Vector2f coord = sf::RenderWindow::mapPixelToCoords(sf::Vector2i {x, y});

    return {coord.x, coord.y};
}

Vector2f Window::map_pixel_to_coord(const Vector2i& pos) const noexcept
{
    return this->map_pixel_to_coord(pos.x, pos.y);
}

