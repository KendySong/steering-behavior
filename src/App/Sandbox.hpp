#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "Agent.hpp"
#include "FlowField.hpp"

class Sandbox
{
public:
    Sandbox() = default;
    void init();
    void update();
    void render(sf::RenderTarget& renderTarget);

private:
    void moveTarget();

    std::vector<Agent> m_agents;
 
    Agent m_target;
    sf::Vector2f m_mousePosition;
    FlowField m_flowField;

    Config* p_config;
};