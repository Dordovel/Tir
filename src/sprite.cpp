#include "../header/sprite.hpp"
#include "../header/graphic_object.hpp"
#include "../header/rectf.hpp"
#include "../header/vector2f.hpp"

#include <cassert>

#include <SFML/Graphics/Texture.hpp>

Sprite::Sprite(std::string_view path)
{
	this->_texture = std::make_shared<sf::Texture>();
	assert(this->_texture->loadFromFile(path.data()) && "Resource file not load");

	this->_sprite = sf::Sprite(*this->_texture);
}

void Sprite::set_origin(float x, float y) noexcept
{
	this->_sprite.setOrigin(x, y);
}

GraphicObject Sprite::get_object() const noexcept
{
	return GraphicObject{this->_sprite};
}

RectF Sprite::get_global_bounds() const noexcept
{
	sf::FloatRect bounds = this->_sprite.getGlobalBounds();

	RectF rect{};
	rect.top = bounds.top;
    rect.left = bounds.left;
    rect.width = bounds.width;
    rect.height = bounds.height;

	return rect;
}

void Sprite::set_scale(float x, float y) noexcept
{
	this->_sprite.setScale(x, y);
}

void Sprite::set_position(float x, float y) noexcept
{
	this->_sprite.setPosition(x, y);
}

void Sprite::set_position(Vector2f pos) noexcept
{
	this->set_position(pos.x, pos.y);
}

Vector2f Sprite::get_position() const noexcept
{
	sf::Vector2f pos = this->_sprite.getPosition();

	return Vector2f{pos.x, pos.y};
}

void Sprite::set_rotation(float angle) noexcept
{
	this->_sprite.setRotation(angle);
}

float Sprite::get_rotation() const noexcept
{
    return this->_sprite.getRotation();
}

bool Sprite::intersect(const IStatic *const object) const noexcept
{
    RectF bound = object->get_global_bounds();

    sf::FloatRect rect;
    rect.top = bound.top;
    rect.left = bound.left;
    rect.height = bound.height;
    rect.width = bound.width;

    return this->_sprite.getGlobalBounds().intersects(rect);
}

bool Sprite::intersect(const IStatic& object) const noexcept
{
    return this->intersect(&object);
}

bool Sprite::intersect(const Vector2f& object) const noexcept
{
	return this->intersect(object.x, object.y);
}

bool Sprite::intersect(float x, float y) const noexcept
{
    return this->_sprite.getGlobalBounds().contains(x, y);
}

void Sprite::move(float x, float y) noexcept
{
    this->_sprite.move(x, y);
}

void Sprite::move(Vector2f pos) noexcept
{
    this->move(pos.x, pos.y);
}

Vector2f Sprite::get_origin() const noexcept
{
    sf::Vector2f origin = this->_sprite.getOrigin();
    return {origin.x, origin.y};
}

