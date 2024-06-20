#pragma once
#include <SFML/Graphics.hpp>

class Math
{
public :
	static float length(sf::Vector2f a);
	static sf::Vector2f normalize(sf::Vector2f a);
};

sf::Vector2f operator+=(sf::Vector2f a, float b);
sf::Vector2f operator+(sf::Vector2f a, float b);