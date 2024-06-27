#include "FlowField.hpp"
#include "Math.hpp"

FlowField::FlowField()
{
	p_config = Config::instance();
	
	m_case = sf::Vector2f(p_config->Width, p_config->Height) / p_config->flowSize;
	sf::Vector2f caseCenter = m_case / 2.0f;

	//Init the vector field
	arrows.reserve(p_config->flowSize.x * p_config->flowSize.y);
	for (size_t y = 0; y < p_config->flowSize.y; y++)
	{
		for (size_t x = 0; x < p_config->flowSize.x; x++)
		{
			sf::VertexArray vector(sf::Lines, 2);
			vector[0] = sf::Vertex(sf::Vector2f(
				caseCenter.x + x * m_case.x,
				caseCenter.y + y * m_case.y
			), sf::Color::Blue);

			/*
			float angle = Math::randomf(0, 2*M_PI);
			sf::Vector2f randomVec(cos(angle), sin(angle));
			vector[1] = sf::Vertex(vector[0].position + randomVec * 20.0f);
			*/

			sf::Vector2f normalized = (vector[0].position / sf::Vector2f(p_config->Width, p_config->Height) * 2.0f) - 1;
			float angle = atan2(y, x);
			sf::Vector2f randomVec(normalized.y, -normalized.x);
			vector[1] = sf::Vertex(vector[0].position + randomVec * 20.0f);

			arrows.push_back(vector);
			vectors.push_back(randomVec);
		}
	}

	//Init the grid
	grid = sf::VertexArray(sf::Lines, 2 * (p_config->flowSize.y + p_config->flowSize.x));
	int i = 1;
	int offset = 0;
	for (size_t y = 0; y < p_config->flowSize.y * 2 - 1; y += 2)
	{
		grid[y] = sf::Vector2f(0, i * m_case.y);
		grid[y + 1] = sf::Vector2f(p_config->Width, i * m_case.y);
		i++;
	}

	offset = i*2;
	i = 1;
	for (size_t x = 0; x < p_config->flowSize.x * 2 - 2; x += 2)
	{
		grid[offset + x] = sf::Vector2f(i * m_case.x, 0);
		grid[offset + x + 1] = sf::Vector2f(i * m_case.x, p_config->Height);
		i++;
	}
}

sf::Vector2f FlowField::getDirection(const sf::Vector2f& position)
{
	sf::Vector2f coordinatef = position / m_case;
	return vectors[(int)coordinatef.y * p_config->flowSize.x + (int)coordinatef.x] * p_config->flowForce;
}
