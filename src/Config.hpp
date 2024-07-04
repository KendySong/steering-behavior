#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "App/Mode.hpp"

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
    float neighborDist    = 50;
    bool  separate        = true;
    float separateForce   = 1;

    const float Radius = 10;
    float simulationSpeed = 2;
    
    const int Width  = 1600;
    const int Height = 900;

private :
    Config() = default;
    static Config* p_config;
};