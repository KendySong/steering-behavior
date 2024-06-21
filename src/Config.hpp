#pragma once
#include <cstdint>

class Config
{
public :
    static Config* instance();

    float maxSpeed = 800;
    float maxForce = 400;
    bool useSteer = true;

    const int NbAgents = 1;
    const float Radius = 10;
    
    const std::uint32_t Width = 1280;
    const std::uint32_t Height = 720;

private :
    Config();
    static Config* p_config;
};