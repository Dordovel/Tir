#ifndef PROJECT_SPRITE_INTERFACE
#define PROJECT_SPRITE_INTERFACE

#include "./idrawable.hpp"
#include "./itransform.hpp"
#include "./iintersect.hpp"


class ISptire : public IDrawable,
                public ITransform,
                public IStatic,
                public IIntersect
{
	public:
		virtual void set_origin(float x, float y) noexcept = 0;
        virtual Vector2f get_origin() const noexcept = 0;

		virtual ~ISptire() = default;
};

#endif //PROJECT_SPRITE_INTERFACE
