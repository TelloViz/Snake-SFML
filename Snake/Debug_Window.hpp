#pragma once
#include <SFML/Graphics.hpp>

#define DEBUG_WINDOW_DEBUG_OUTPUT

/*
#ifdef DEBUG_WINDOW_DEBUG_OUTPUT
		// use this wherever you need to conceal debug code for the window itself
#endif // DEBUG_WINDOW_DEBUG_OUTPUT
*/


/* Debug_Window expects a Debug_Info_Bundle every frame for accurate output */
struct Debug_Info_Bundle
{
	sf::Vector2i snake_coord{0,0};
};


class Debug_Window
{
public:
	Debug_Window();

	

	void update(const Debug_Info_Bundle& bundle);
private:

	void render();

	sf::RenderWindow	m_window;

	sf::Font			m_font;
	
	sf::Text			m_snakePosLabel;
	sf::Vector2f		m_snakePosLabelPos;

	sf::Text			m_snakePosText;
	sf::Vector2f		m_snakePosTextPos;
	


	// TODO These are also used in other states. Need to centralize this information. 
	const sf::Color DARK_COLOR{ 15, 56, 15 };
	const sf::Color MID_COLOR{ 48, 98, 48 };
	const sf::Color LIGHT_COLOR{ 139, 172, 15 };
	const sf::Color BRIGHT_COLOR{ 155, 188, 15 };
};   //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


