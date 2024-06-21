#include <iostream>

#include "Application.hpp"
#include "Sandbox.hpp"

#include "Math.hpp"

#include "../Config.hpp"

void Sandbox::init()
{
	p_config = Config::instance();
	m_agents.reserve(p_config->NbAgents);
	for (size_t i = 0; i < p_config->NbAgents; i++)
	{
		m_agents.emplace_back(Agent(sf::Vector2f(p_config->Width /2, p_config->Height/2)));
	}
}

void Sandbox::update()
{
	m_mousePosition = Application::instance()->getMousePos();	

	if (p_config->useSteer)
	{
		m_agents[0].seek(m_mousePosition);
	}
	else
	{
		m_agents[0].flee(m_mousePosition);
		//m_agents[0].move(250.0f * Math::normalize(m_mousePosition - m_agents[0].getCenter()));
	}
}

void Sandbox::render(sf::RenderTarget& renderTarget)
{
	for (Agent agent : m_agents)
	{
		renderTarget.draw(agent.body); 
		renderTarget.draw(agent.ray);
	}
}
