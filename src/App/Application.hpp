#include <SFML/Graphics.hpp>
#include "Sandbox.hpp"

class Application
{
public :
	Application(Application&) = delete;
	static Application* instance();

	int run();
	sf::Vector2f getMousePos();
	float getDeltaTime();

private :
	Application();

	static Application* m_app;
	sf::RenderWindow* p_window;
	sf::Clock m_clkDT;
	sf::Event m_event;

	std::uint32_t m_fps;
	sf::Clock m_clkFPS;
	std::uint32_t m_lastFPS;
	
	Sandbox m_sanbdox;
	bool m_pause;
	bool m_spaceDown;
	float m_deltaTime;
	Config* p_config;
};

