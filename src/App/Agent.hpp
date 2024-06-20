#pragma once
#include <SFML/Graphics.hpp>

struct Agent
{
public :
	Agent(sf::Vector2f position);
	void move(sf::Vector2f dir);
	sf::Vector2f getPos();

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::CircleShape body;
};