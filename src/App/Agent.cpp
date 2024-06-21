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
	ray = sf::VertexArray(sf::Lines, 2);
	this->setVertices();
}

void Agent::move(sf::Vector2f dir)
{
	float deltaTime = Application::instance()->getDeltaTime();

	this->velocity += dir * deltaTime;

	this->position += this->velocity * deltaTime;
	body.setPosition(this->position);
	this->setVertices();
}

void Agent::seek(sf::Vector2f target)
{
	sf::Vector2f desired = Math::setLength(target - this->getCenter(), p_config->maxSpeed);
	this->move(Math::limit(desired - this->velocity, p_config->maxForce));
}

void Agent::flee(sf::Vector2f target)
{
	sf::Vector2f desired = Math::setLength(target - this->getCenter(), p_config->maxSpeed);
	this->move(-Math::limit(desired - this->velocity, p_config->maxForce));
}

sf::Vector2f Agent::getCenter()
{
	return this->position + p_config->Radius;
}

void Agent::setVertices()
{
	ray[0] = sf::Vertex(this->getCenter());
	ray[1] = sf::Vertex(this->getCenter() + Math::setLength(this->velocity, 30));
}