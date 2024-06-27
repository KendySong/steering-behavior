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
    m_pause = false;
    m_spaceDown = false;
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
            if (m_event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
            {
                p_window->close();
            }

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                m_spaceDown = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_spaceDown)
            {
                m_pause = !m_pause;
                m_spaceDown = true;
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

        if (!m_pause)
        {
            m_sanbdox.update();
        }    

        m_clkDT.restart();

        ImGui::Begin("Info");
            ImGui::Text("%i FPS", m_lastFPS);
            ImGui::DragFloat("Simulation speed", &p_config->simulationSpeed, 0.5f, 0, 100);
            ImGui::SliderFloat("Max speed", &p_config->maxSpeed, 1, 3000);
            ImGui::SliderFloat("Max force", &p_config->maxForce, 1, 3000);
            
            if (ImGui::BeginCombo("Agent Mode", modeString(p_config->mode)))
            {
                for (size_t i = 0; i < static_cast<int>(Mode::Count); i++)
                {
                    bool isSelect = i == static_cast<int>(p_config->mode);
                    if (ImGui::Selectable(modeString(static_cast<Mode>(i)), isSelect))
                    {
                        p_config->mode = static_cast<Mode>(i);
                    }

                    if (isSelect)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            if (p_config->mode == Mode::FlowField)
            {
                ImGui::DragFloat("Flow force", &p_config->flowForce, 0.5f, 1, 500);
                ImGui::Checkbox("Draw field", &p_config->drawField);
            }

            ImGui::SetNextItemOpen(true, ImGuiCond_Always);
            if (ImGui::TreeNode("Commands"))
            {
                ImGui::TextUnformatted("[R] : Reset agents position\n[Space] : Pause the simulation\n[ESC] : Quit the simulation");
                ImGui::TreePop();
            }           
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
    return m_deltaTime * p_config->simulationSpeed;
}