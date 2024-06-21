#pragma once
#include <SFML/Graphics.hpp>
#include "../Config.hpp"

struct Agent
{
public :
	Agent(sf::Vector2f position);
	void move(sf::Vector2f dir);
	void seek(sf::Vector2f target);
	void flee(sf::Vector2f target);
	sf::Vector2f getCenter();

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::CircleShape body;
	sf::VertexArray ray;

private :
	void setVertices();

	Config* p_config;
};