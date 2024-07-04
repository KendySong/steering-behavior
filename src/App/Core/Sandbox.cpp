#include <iostream>

#include "Application.hpp"
#include "Sandbox.hpp"
#include "../Math.hpp"

#include "../../Config.hpp"

void Sandbox::init()
{
	p_config = Config::instance();
	m_target = Agent(sf::Vector2f(
		Math::random(0, p_config->Width),
		Math::random(0, p_config->Height)
	));

	m_agents.reserve(p_config->numberAgent);
	for (size_t i = 0; i < p_config->numberAgent; i++)
	{
		m_agents.emplace_back(Agent(Math::randomPosition({0, 0, p_config->Width, p_config->Height})));
	}
}

void Sandbox::update()
{
	m_mousePosition = Application::instance()->getMousePos();	
	this->moveTarget();

	for (size_t i = 0; i < m_agents.size(); i++)
	{
		if (p_config->separate)
		{
			m_agents[i].separate(m_agents);
		}

		switch (p_config->mode)
		{
		case Mode::Seek:
			m_agents[i].seek(m_mousePosition);
			break;

		case Mode::Flee:
			m_agents[i].flee(m_mousePosition);			
			break;

		case Mode::Pursuit:
			m_agents[i].pursuit(&m_target);			
			break;

		case Mode::FlowField:
			m_agents[i].move(m_flowField.getDirection(m_agents[i].position));
			break;
		}
		
	}

	/*
	switch (p_config->mode)
	{
	case Mode::Seek:
		for (size_t i = 0; i < m_agents.size(); i++)
		{
			m_agents[i].seek(m_mousePosition);
		}
		
		break;

	case Mode::Flee:
		for (size_t i = 0; i < m_agents.size(); i++)
		{
			m_agents[i].flee(m_mousePosition);
		}
		break;

	case Mode::Pursuit:
		for (size_t i = 0; i < m_agents.size(); i++)
		{
			m_agents[i].pursuit(&m_target);
		}
		break;

	case Mode::FlowField:
		for (size_t i = 0; i < m_agents.size(); i++)
		{
			m_agents[i].move(m_flowField.getDirection(m_agents[i].position));
		}		
		break;
	}
	*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		for (size_t i = 0; i < m_agents.size(); i++)
		{
			m_agents[i].position = sf::Vector2f(Math::randomPosition({ 0, 0, p_config->Width, p_config->Height }));
			m_agents[i].velocity = sf::Vector2f();
		}	
	}
}

void Sandbox::render(sf::RenderTarget& renderTarget)
{
	for (Agent agent : m_agents)
	{
		agent.draw(renderTarget);
	}

	switch (p_config->mode)
	{
	case Mode::Pursuit:
		m_target.draw(renderTarget);
		break;

	case Mode::FlowField:
		if (p_config->drawField)
		{
			for (size_t i = 0; i < m_flowField.arrows.size(); i++)
			{
				renderTarget.draw(m_flowField.arrows[i]);
			}
			renderTarget.draw(m_flowField.grid);
		}		
		break;
	}
}

void Sandbox::moveTarget()
{
	m_target.velocity = sf::Vector2f(50, -50);
	m_target.position += sf::Vector2f(50, -50) * Application::instance()->getDeltaTime();
	m_target.body.setPosition(m_target.position);
	m_target.setVertices();
	if (m_target.position.x > p_config->Width - 2 * p_config->Radius)
	{
		m_target.position.x = 0 + p_config->Radius;
	}

	if (m_target.position.y < 0)
	{
		m_target.position.y = p_config->Height - 2 * p_config->Radius;
	}
}