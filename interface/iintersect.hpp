#ifndef PROJECT_INTERSECT_INTERFACE
#define PROJECT_INTERSECT_INTERFACE

#include "./istatic.hpp"

struct Vector2f;

class IIntersect
{
    public:
        virtual bool intersect(const IStatic* const object) const noexcept = 0;
        virtual bool intersect(const IStatic& object) const noexcept = 0;

        virtual bool intersect(const Vector2f&  object) const noexcept = 0;
        virtual bool intersect(float x, float y) const noexcept = 0;

    virtual ~IIntersect() = default;
};

#endif //PROJECT_INTERSECT_INTERFACE
