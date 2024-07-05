#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "App/Simulation/Mode.hpp"

class Config
{
public :
    static Config* instance();

    int numberAgent       = 40;
    float maxSpeed        = 100;
    float maxForce        = 50;
    Mode  mode            = Mode::Seek;
    sf::Vector2f flowSize = sf::Vector2f(16, 9);
    float flowForce       = 1500;
    bool  drawField       = true;
    float neighborDist    = 450;
    bool  separate        = true;
    float separateForce   = 10;
    bool  cohere          = true;
    float cohereForce     = 10;
    bool  align = true;
    float alignForce = 10;

    const float Radius = 10;
    float simulationSpeed = 2;
    
    const int Width  = 1600;
    const int Height = 900;

private :
    Config() = default;
    static Config* p_config;
};