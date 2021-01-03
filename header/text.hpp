#ifndef PROJECT_TEXT_HEADER
#define PROJECT_TEXT_HEADER

#include "../interface/itext.hpp"
#include <SFML/Graphics/Text.hpp>

#include <memory>

namespace sf
{
	class Font;
};

class Text : public IText
{
    private:
		sf::Text _text;

		std::shared_ptr<sf::Font> _font;

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

        Vector2f get_position() const noexcept override;

		void set_text(std::string_view str) noexcept override;

		std::string get_text() const noexcept override;

		void set_color(ColorDef color) noexcept override;

        explicit Text(std::string_view path);
};

#endif //PROJECT_TEXT_HEADER

