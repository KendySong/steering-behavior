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