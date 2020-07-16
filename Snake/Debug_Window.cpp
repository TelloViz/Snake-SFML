#include "Debug_Window.hpp"
#include <iostream>
#include <string>

Debug_Window::Debug_Window()
{

	m_window.create( sf::VideoMode{300, 500}, "Debug Window", sf::Style::Titlebar | sf::Style::Close );

	m_window.setPosition(sf::Vector2i{ 0, 0 });




	if (!m_font.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh
	m_snakePosLabel.setFont(m_font);
	m_snakePosLabel.setString("Snake(x,y): ");
	m_snakePosLabel.setPosition(m_snakePosLabelPos);
	m_snakePosLabel.setFillColor(sf::Color::Black);
	m_snakePosLabel.setOutlineColor(LIGHT_COLOR);
	m_snakePosLabel.setOutlineThickness(2);

	m_snakePosText.setFont(m_font);
	m_snakePosText.setString(",");
	m_snakePosText.setPosition(m_snakePosTextPos);
	m_snakePosText.setFillColor(sf::Color::Black);
	m_snakePosText.setOutlineColor(LIGHT_COLOR);
	m_snakePosText.setOutlineThickness(2);

	m_applePosLabel.setFont(m_font);
	m_applePosLabel.setString("Apple(x,y): ");
	m_applePosLabel.setPosition(m_applePosLabelPos);
	m_applePosLabel.setFillColor(sf::Color::Black);
	m_applePosLabel.setOutlineColor(LIGHT_COLOR);
	m_applePosLabel.setOutlineThickness(2);

	m_applePosText.setFont(m_font);
	m_applePosText.setString(",");
	m_applePosText.setPosition(m_applePosTextPos);
	m_applePosText.setFillColor(sf::Color::Black);
	m_applePosText.setOutlineColor(LIGHT_COLOR);
	m_applePosText.setOutlineThickness(2);

	m_scoreLabel.setFont(m_font);
	m_scoreLabel.setString("Score: ");
	m_scoreLabel.setPosition(m_scoreLabelPos);
	m_scoreLabel.setFillColor(sf::Color::Black);
	m_scoreLabel.setOutlineColor(LIGHT_COLOR);
	m_scoreLabel.setOutlineThickness(2);

	m_scoreText.setFont(m_font);
	m_scoreText.setString(",");
	m_scoreText.setPosition(m_scoreTextPos);
	m_scoreText.setFillColor(sf::Color::Black);
	m_scoreText.setOutlineColor(LIGHT_COLOR);
	m_scoreText.setOutlineThickness(2);

	m_applesCollectedLabel.setFont(m_font);
	m_applesCollectedLabel.setString("Apples: ");
	m_applesCollectedLabel.setPosition(m_applesCollectedLabelPos);
	m_applesCollectedLabel.setFillColor(sf::Color::Black);
	m_applesCollectedLabel.setOutlineColor(LIGHT_COLOR);
	m_applesCollectedLabel.setOutlineThickness(2);

	m_applesCollectedText.setFont(m_font);
	m_applesCollectedText.setString(",");
	m_applesCollectedText.setPosition(m_applesCollectedTextPos);
	m_applesCollectedText.setFillColor(sf::Color::Black);
	m_applesCollectedText.setOutlineColor(LIGHT_COLOR);
	m_applesCollectedText.setOutlineThickness(2);

	m_directionLabel.setFont(m_font);
	m_directionLabel.setString("Dir: ");
	m_directionLabel.setPosition(m_directionLabelPos);
	m_directionLabel.setFillColor(sf::Color::Black);
	m_directionLabel.setOutlineColor(LIGHT_COLOR);
	m_directionLabel.setOutlineThickness(2);

	m_directionText.setFont(m_font);
	m_directionText.setString(",");
	m_directionText.setPosition(m_directionTextPos);
	m_directionText.setFillColor(sf::Color::Black);
	m_directionText.setOutlineColor(LIGHT_COLOR);
	m_directionText.setOutlineThickness(2);
	
}

void Debug_Window::update(const Debug_Info_Bundle& bundle)
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Request for closing the window
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
	std::string pos{ std::to_string(bundle.snake_coord.x) + "," + std::to_string(bundle.snake_coord.y) };
	m_snakePosText.setString(pos);

	pos = { std::to_string(bundle.apple_coord.x) + "," + std::to_string(bundle.apple_coord.y) };
	m_applePosText.setString(pos);

	std::string coll{ std::to_string(bundle.apples_collected) };
	m_applesCollectedText.setString(coll);

	std::string sc{ std::to_string(bundle.score)  };
	m_scoreText.setString(sc);

	switch (bundle.direction)
	{
	case Direction::UP:
		m_directionText.setString("Up");
		break;
	case Direction::DOWN:
		m_directionText.setString("Down");

		break;
	case Direction::LEFT:
		m_directionText.setString("Left");

		break;
	case Direction::RIGHT:
		m_directionText.setString("Right");

		break;
	}

	render();
}

void Debug_Window::render()
{
	m_window.clear();
	m_window.draw(m_snakePosLabel);
	m_window.draw(m_snakePosText);

	m_window.draw(m_applePosLabel);
	m_window.draw(m_applePosText);

	m_window.draw(m_scoreLabel);
	m_window.draw(m_scoreText);

	m_window.draw(m_applesCollectedLabel);
	m_window.draw(m_applesCollectedText);

	m_window.draw(m_directionLabel);
	m_window.draw(m_directionText);
	m_window.display();
}

