#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../Config.hpp"

class FlowField
{
public :
    FlowField();
    sf::Vector2f getDirection(const sf::Vector2f& position);

    sf::VertexArray grid;
    std::vector<sf::Vector2f> vectors;
    std::vector<sf::VertexArray> arrows;

private :
    sf::Vector2f m_case;
    Config* p_config;
};