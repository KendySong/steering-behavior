#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>

class Math
{
public :
	static float length(sf::Vector2f a);
	static sf::Vector2f setLength(sf::Vector2f a, float t);
	static sf::Vector2f normalize(sf::Vector2f a);
	static sf::Vector2f limit(sf::Vector2f a, float t);
	static float randomf(float min, float max);
	static int random(int min, int max);
	static float lerp(float a, float b, float t);
	static float unlerp(float a, float b, float t);
};

sf::Vector2f operator+=(sf::Vector2f a, float b);
sf::Vector2f operator+(sf::Vector2f a, float b);
sf::Vector2f operator/(sf::Vector2f a, sf::Vector2f b);