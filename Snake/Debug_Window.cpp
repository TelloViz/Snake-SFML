#include "Debug_Window.hpp"
#include <iostream>
#include <string>

Debug_Window::Debug_Window()
{

	m_window.create( sf::VideoMode{300, 500}, "Debug Window", sf::Style::Titlebar | sf::Style::Close );

	if (!m_font.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh
	m_snakePosLabel.setFont(m_font);
	m_snakePosLabel.setString("(x,y) : ");
	m_snakePosLabel.setPosition(0.f, 0.f);
	m_snakePosLabel.setFillColor(sf::Color::Black);
	m_snakePosLabel.setOutlineColor(LIGHT_COLOR);
	m_snakePosLabel.setOutlineThickness(2);

	m_snakePosText.setFont(m_font);
	m_snakePosText.setString(",");
	m_snakePosText.setPosition(150.f, 0.f);
	m_snakePosText.setFillColor(sf::Color::Black);
	m_snakePosText.setOutlineColor(LIGHT_COLOR);
	m_snakePosText.setOutlineThickness(2);

	
}

void Debug_Window::update(const Debug_Info_Bundle& bundle)
{
	std::string pos{ std::to_string(bundle.snake_coord.x) + "," + std::to_string(bundle.snake_coord.y) };
	m_snakePosText.setString(pos);

	render();
}

void Debug_Window::render()
{
	m_window.clear();
	m_window.draw(m_snakePosLabel);
	m_window.draw(m_snakePosText);
	m_window.display();
}
