#ifndef PROJECT_DRAWABLE_INTERFACE
#define PROJECT_DRAWABLE_INTERFACE

class GraphicObject;

class IDrawable
{
	public:
		virtual GraphicObject get_object() const noexcept = 0;
		virtual ~IDrawable() = default;
};

#endif //PROJECT_DRAWABLE_INTERFACE
