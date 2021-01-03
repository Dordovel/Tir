#ifndef PROJECT_STATIC_INTERFACE
#define PROJECT_STATIC_INTERFACE

struct RectF;

class IStatic
{
    public:
        virtual RectF get_global_bounds() const noexcept = 0;
        virtual Vector2f get_position() const noexcept = 0;

        virtual ~IStatic() = default;
};

#endif //PROJECT_STATIC_INTERFACE
