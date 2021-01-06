#ifndef PROJECT_SPRITE_HEADER
#define PROJECT_SPRITE_HEADER

#include "../interface/isprite.hpp"

#include <memory>
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
	class Texture;
};

class Sprite final : public ISptire
{
    private:
        std::shared_ptr<sf::Texture> _texture;
        sf::Sprite _sprite;

	public:
		GraphicObject get_object() const noexcept override;

		RectF get_global_bounds() const noexcept override;

		void set_scale(float x, float y) noexcept override;

        void set_position(float x, float y) noexcept override;

        void set_position(Vector2f pos) noexcept override;

        void move(float x, float y) noexcept override;

        void move(Vector2f pos) noexcept override;

        void set_rotation(float angle) noexcept override;

        float get_rotation() const noexcept override;

		void set_origin(float x, float y) noexcept override;

        Vector2f get_origin() const noexcept override;

        Vector2f get_position() const noexcept override;

        bool intersect(const IStatic* const object) const noexcept override;

        bool intersect(const IStatic& object) const noexcept override;

        bool intersect(const Vector2f&  object) const noexcept override;

        bool intersect(float x, float y) const noexcept override;

        explicit Sprite(std::string_view path);
};

#endif //PROJECT_SPRITE_HEADER

