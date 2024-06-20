#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "Agent.hpp"

class Sandbox
{
public:
    Sandbox() = default;
    void init();
    void update();
    void render(sf::RenderTarget& renderTarget);

private:
    std::vector<Agent> m_agents;
    sf::Vector2f m_mousePosition;
    Config* p_config;
};