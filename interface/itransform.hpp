#ifndef PROJECT_TRANSFORM_INTERFACE
#define PROJECT_TRANSFORM_INTERFACE

struct Vector2f;

class ITransform
{
	public:
		virtual void set_scale(float x, float y) noexcept = 0;

		virtual void set_position(float x, float y) noexcept = 0;
		virtual void set_position(Vector2f pos) noexcept = 0;

        virtual void move(float x, float y) noexcept = 0;
        virtual void move(Vector2f pos) noexcept = 0;

		virtual void set_rotation(float angle) noexcept = 0;
        virtual float get_rotation() const noexcept = 0;

		virtual ~ITransform() = default;
};

#endif //PROJECT_TRANSFORM_INTERFACE

