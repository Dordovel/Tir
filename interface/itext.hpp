#ifndef PROJECT_TEXT_INTERFACE
#define PROJECT_TEXT_INTERFACE

#include "./idrawable.hpp"
#include "./itransform.hpp"
#include "./iintersect.hpp"
#include "./ipaintable.hpp"

#include <string_view>


class IText : public IDrawable,
                public ITransform,
                public IStatic,
                public IPaintable,
				public IIntersect
{
	public:

		virtual void set_text(std::string_view str) noexcept = 0;

		virtual std::string get_text() const noexcept = 0;

		virtual ~IText() = default;
};

#endif //PROJECT_TEXT_INTERFACE
