#ifndef PROJECT_PAINTABLE_INTERFACE
#define PROJECT_PAINTABLE_INTERFACE

#include "../header/color.hpp"

class IPaintable
{
	public:

		virtual void set_color(ColorDef color) noexcept = 0;

		virtual ~IPaintable() = default;
};

#endif //PROJECT_PAINTABLE_INTERFACE
