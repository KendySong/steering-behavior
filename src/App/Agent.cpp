#include <iostream>

#include "Agent.hpp"
#include "Application.hpp"
#include "Math.hpp"

Agent::Agent(sf::Vector2f position)
{
	p_config = Config::instance();

	this->position = position;
	this->velocity = sf::Vector2f();
	body = sf::CircleShape(p_config->Radius);
	body.setPosition(position);
}

void Agent::move(sf::Vector2f dir)
{
	float deltaTime = Application::instance()->getDeltaTime();
	dir = Math::normalize(dir) * p_config->maxSpeed;

	this->velocity += dir * deltaTime;
	this->position += this->velocity * deltaTime;
	this->body.setPosition(this->position);
}

sf::Vector2f Agent::getPos()
{
	return body.getPosition() + p_config->Radius;
}