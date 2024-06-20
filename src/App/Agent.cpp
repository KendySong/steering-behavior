#include "Agent.hpp"
#include "Application.hpp"
#include "../Config.hpp"
#include "Math.hpp"
#include <iostream>

Agent::Agent(sf::Vector2f position)
{
	this->position = position;
	this->velocity = sf::Vector2f();
	body = sf::CircleShape(RADIUS);
	body.setPosition(position);
}

void Agent::move(sf::Vector2f dir)
{
	float deltaTime = Application::instance()->getDeltaTime();
	dir = Math::normalize(dir) * MAX_SPEED;

	this->velocity += dir * deltaTime;
	this->position += this->velocity * deltaTime;
	this->body.setPosition(this->position);
}

sf::Vector2f Agent::getPos()
{
	return body.getPosition() + RADIUS;
}