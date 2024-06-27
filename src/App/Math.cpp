#include "Math.hpp"

float Math::length(sf::Vector2f a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

sf::Vector2f Math::normalize(sf::Vector2f a)
{
    return a / length(a);
}

sf::Vector2f Math::setLength(sf::Vector2f a, float t)
{
    return Math::normalize(a) * t;
}

sf::Vector2f Math::limit(sf::Vector2f a, float t)
{
    float length = Math::length(a);
    if (length > t)
    {
        return Math::setLength(a, t);
    }
    return a;
}

sf::Vector2f Math::randomPosition(sf::IntRect limit)
{
    return { Math::randomf(limit.left, limit.width),  Math::randomf(limit.top, limit.height) };
}

float Math::randomf(float min, float max)
{
    return min + (float)rand() / (float)(RAND_MAX / (max - min));
}

int Math::random(int min, int max)
{
    return rand() % max + min;
}

float Math::lerp(float a, float b, float t)
{
    return t * (b - a) + a;
}

float Math::unlerp(float a, float b, float x)
{
    return (x - a) / (b - a);
}

sf::Vector2f operator+=(sf::Vector2f a, float b)
{
    a.x += b;
    a.y += b;
    return a;
}

sf::Vector2f operator+(sf::Vector2f a, float b)
{
    return { a.x + b, a.y + b };
}

sf::Vector2f operator-(sf::Vector2f a, float b)
{
    return { a.x - b, a.y - b };
}

sf::Vector2f operator/(sf::Vector2f a, sf::Vector2f b)
{
    return { a.x / b.x, a.y / b.y };
}