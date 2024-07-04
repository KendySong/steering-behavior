#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Config.hpp"

struct Agent
{
public :
	Agent() = default;
	Agent(sf::Vector2f position);
	void move(sf::Vector2f dir);
	void seek(sf::Vector2f target);
	void flee(sf::Vector2f target);
	void pursuit(Agent* target);
	void separate(std::vector<Agent>& group);
	void cohere(std::vector<Agent>& group);
	void setVertices();
	void draw(sf::RenderTarget& target);
	sf::Vector2f getCenter();

	sf::CircleShape body;
	sf::Vector2f position;

	sf::Vector2f velocity;
	sf::VertexArray velRay;
	sf::VertexArray seekRay;

private :
	void adjustPosition();

	Config* p_config;
	sf::Vector2f m_seek;
};