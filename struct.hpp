#include "./header/sprite.hpp"
#include "./types.hpp"

struct Target
{
    Sprite sprite;
    bool isLife = false;
    TYPE type;
};

struct CannonBall
{
    Sprite* sprite = nullptr;
	GunBallType type;
};

struct Gun
{
	CannonBall* ball = nullptr;
    float angle = 0;
};
