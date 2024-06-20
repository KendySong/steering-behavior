#include <iostream>

#include "Application.hpp"
#include "Sandbox.hpp"

#include "Math.hpp"

#include "../Config.hpp"

void Sandbox::init()
{
	m_agents.reserve(NB_AGENTS);
	for (size_t i = 0; i < NB_AGENTS; i++)
	{
		m_agents.emplace_back(Agent(sf::Vector2f(WIDTH/2, HEIGHT/2)));
	}
}

void Sandbox::update()
{
	m_mousePosition = Application::instance()->getMousePos();
	sf::Vector2f dir = m_mousePosition - m_agents[0].position - m_agents[0].velocity;
	m_agents[0].move(dir);


}

void Sandbox::render(sf::RenderTarget& renderTarget)
{
	for (Agent agent : m_agents)
	{
		renderTarget.draw(agent.body);
	}
}