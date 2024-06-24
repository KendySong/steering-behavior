#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "App/Mode.hpp"

class Config
{
public :
    static Config* instance();

    int numberAgent       = 40;
    float maxSpeed        = 800;
    float maxForce        = 400;
    Mode  mode            = Mode::Seek;
    sf::Vector2f flowSize = sf::Vector2f(16, 9);
    float flowForce       = 400;
    bool  drawField       = true;

    const float Radius = 10;
    
    const std::uint32_t Width  = 1280;
    const std::uint32_t Height = 720;

private :
    Config() = default;
    static Config* p_config;
};