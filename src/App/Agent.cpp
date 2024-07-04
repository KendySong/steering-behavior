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
	velRay	= sf::VertexArray(sf::Lines, 2);
	seekRay = sf::VertexArray(sf::Lines, 2);
	this->setVertices();
}

void Agent::move(sf::Vector2f dir)
{
	float deltaTime = Application::instance()->getDeltaTime();

	this->velocity += dir * deltaTime;
	this->velocity = Math::limit(this->velocity, p_config->maxSpeed);

	this->position += this->velocity * deltaTime;

	adjustPosition();
	body.setPosition(this->position);
	this->setVertices();
}

void Agent::seek(sf::Vector2f target)
{
	sf::Vector2f desired = Math::setLength(target - this->getCenter(), p_config->maxSpeed);
	m_seek = Math::limit(desired - this->velocity, p_config->maxForce);
	this->move(this->m_seek);
}

void Agent::flee(sf::Vector2f target)
{
	sf::Vector2f desired = Math::setLength(target - this->getCenter(), p_config->maxSpeed);
	m_seek = Math::limit(desired - this->velocity, p_config->maxForce);
	this->move(-m_seek);
}

void Agent::pursuit(Agent* target)
{
	this->seek(target->getCenter() + target->velocity);
}

void Agent::separate(std::vector<Agent>& group)
{
	int count = 0;
	sf::Vector2f separation(0, 0);
	
	for (size_t i = 0; i < group.size(); i++)
	{
		sf::Vector2f dir = this->getCenter() - group[i].getCenter();
		float distance = Math::length(dir);

		if (distance < p_config->neighborDist && this != &group[i])
		{
			count++;
			separation += dir * 1.0f / distance;
		}
	}

	if (count == 0)
	{
		return;
	}

	this->move(separation);
}

void Agent::cohere(std::vector<Agent>& group)
{
	for (size_t i = 0; i < group.size(); i++)
	{
		if (Math::distance(group[i].getCenter(), this->getCenter()) > p_config->neighborDist)
		{
			//Rapproch
		}
	}

}

sf::Vector2f Agent::getCenter()
{
	return this->position + p_config->Radius;
}

void Agent::setVertices()
{
	sf::Vector2f center = this->getCenter();
	velRay[0] = sf::Vertex(center, sf::Color::Red);
	velRay[1] = sf::Vertex(center + Math::setLength(this->velocity, 30), sf::Color::Red);

	seekRay[0] = sf::Vertex(center, sf::Color::Green);
	seekRay[1] = sf::Vertex(center + Math::setLength(m_seek, 30), sf::Color::Green);
}

void Agent::draw(sf::RenderTarget& target)
{
	target.draw(body);
	target.draw(velRay);
	target.draw(seekRay);
}

void Agent::adjustPosition()
{
	position.x = position.x < 0 ? position.x = p_config->Width - 2 * p_config->Radius : position.x > p_config->Width - 2 * p_config->Radius ? 0 : position.x;
	position.y = position.y < 0 ? position.x = p_config->Height - 2 * p_config->Radius : position.y > p_config->Height - 2 * p_config->Radius ? 2 * p_config->Radius : position.y;
}