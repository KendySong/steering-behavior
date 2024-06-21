#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "Application.hpp"
#include "../Config.hpp"

Application* Application::m_app = nullptr;
Application::Application()
{   
    m_fps = 0;
    m_lastFPS = 0;
    m_deltaTime = 0;
    p_config = Config::instance();
    p_window = new sf::RenderWindow(sf::VideoMode(p_config->Width, p_config->Height), "Steering behavior");
    ImGui::SFML::Init(*p_window);
    m_sanbdox.init();
}

int Application::run()
{
    //Main loop
    while (p_window->isOpen())
    {
        while (p_window->pollEvent(m_event))
        {
            ImGui::SFML::ProcessEvent(*p_window, m_event);
            if (m_event.type == sf::Event::Closed)
            {
                p_window->close();
            }
        }

        //Count FPS
        m_fps++;
        if (m_clkFPS.getElapsedTime().asSeconds() >= 1)
        {
            m_lastFPS = m_fps;
            m_clkFPS.restart();
            m_fps = 0;
        }

        //Update
        sf::Time& deltaTime = m_clkDT.getElapsedTime();
        ImGui::SFML::Update(*p_window, deltaTime);
        m_deltaTime = deltaTime.asSeconds();
        m_sanbdox.update();
        m_clkDT.restart();

        ImGui::Begin("Info");
            ImGui::Text("%i FPS", m_lastFPS);
            ImGui::SliderFloat("Max speed", &p_config->maxSpeed, 1, 300);
            ImGui::SliderFloat("Max force", &p_config->maxForce, 1, 300);
            ImGui::Checkbox("Steer", &p_config->useSteer);
        ImGui::End();

        //Render
        p_window->clear();
        m_sanbdox.render(*p_window);
        ImGui::SFML::Render(*p_window);
        p_window->display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

Application* Application::instance()
{
    if (m_app == nullptr)
    {
        m_app = new Application();
    }
    return m_app;
}

sf::Vector2f Application::getMousePos()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*p_window);
    return { (float)mousePos.x, (float)mousePos.y };
}

float Application::getDeltaTime()
{
    return m_deltaTime;
}