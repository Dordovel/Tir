#include "../header/text.hpp"
#include "../header/graphic_object.hpp"
#include "../header/rectf.hpp"
#include "../header/vector2f.hpp"

#include <cassert>

#include <SFML/Graphics/Font.hpp>

#include <SFML/Graphics/Color.hpp>

namespace 
{
	class Rgb : public sf::Color
	{
		public:
            Rgb(int red, int green, int blue) : sf::Color(red, green, blue){};
			
		 	static Rgb color (const ColorDef& color)
			{
				switch(color)
				{
					case ColorDef::WHITE:
						return Rgb(255, 255, 255);

					case ColorDef::BLACK:
						return Rgb(0, 0, 0);

					case ColorDef::GREEN:
						return Rgb(0, 255, 0);

					case ColorDef::RED:
						return Rgb(255, 0, 0);

					case ColorDef::YELLOW:
						return Rgb(255, 255, 0);

					case ColorDef::BLUE:
						return Rgb(0, 0, 255);

				}

				return Rgb(0, 0, 0);
			}

	};
};


Text::Text(std::string_view path)
{
   	this->_font = std::make_shared<sf::Font>();
	assert(this->_font->loadFromFile(path.data()) && "Resource file not load");

	this->_text.setFont(*this->_font);
}

GraphicObject Text::get_object() const noexcept
{
	return GraphicObject{this->_text};
}

RectF Text::get_global_bounds() const noexcept
{
	sf::FloatRect bounds = this->_text.getGlobalBounds();

	RectF rect{};
	rect.top = bounds.top;
    rect.left = bounds.left;
    rect.width = bounds.width;
    rect.height = bounds.height;

	return rect;
}

void Text::set_scale(float x, float y) noexcept
{
	this->_text.setScale(x, y);
}

void Text::set_position(float x, float y) noexcept
{
	this->_text.setPosition(x, y);
}

void Text::set_position(Vector2f pos) noexcept
{
	this->set_position(pos.x, pos.y);
}

Vector2f Text::get_position() const noexcept
{
	sf::Vector2f pos = this->_text.getPosition();

	return Vector2f{pos.x, pos.y};
}

void Text::set_rotation(float angle) noexcept
{
	this->_text.setRotation(angle);
}

float Text::get_rotation() const noexcept
{
    return this->_text.getRotation();
}

void Text::set_text(std::string_view str) noexcept
{
	this->_text.setString(str.data());
}

std::string Text::get_text() const noexcept
{
	auto str = this->_text.getString();
	return std::string(std::begin(str), std::end(str));
}

void Text::move(float x, float y) noexcept
{
    this->_text.move(x, y);
}

void Text::move(Vector2f pos) noexcept
{
    this->move(pos.x, pos.y);
}

void Text::set_color(ColorDef color) noexcept
{
	this->_text.setFillColor(Rgb::color(color));
}