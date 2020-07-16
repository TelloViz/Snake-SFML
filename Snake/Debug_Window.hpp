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
	int direction{ 0 };
	sf::Vector2i apple_coord{ 0,0 };
	int score{ 0 };
	unsigned apples_collected{ 0 };

};


class Debug_Window
{
	enum Direction { NONE = 0, UP, DOWN, LEFT, RIGHT };


public:
	Debug_Window();

	

	void update(const Debug_Info_Bundle& bundle);
private:

	void render();

	sf::RenderWindow	m_window;

	sf::Font			m_font;
	
	sf::Text			m_snakePosLabel;
	sf::Vector2f		m_snakePosLabelPos{ 0.f, 0.f };

	sf::Text			m_snakePosText;
	sf::Vector2f		m_snakePosTextPos{ 200.f, 0.f };

	sf::Text			m_directionLabel;
	sf::Vector2f		m_directionLabelPos{ 0.f, 50.f };

	sf::Text			m_directionText;
	sf::Vector2f		m_directionTextPos{ 125.f, 50.f };

	sf::Text			m_applePosLabel;
	sf::Vector2f		m_applePosLabelPos{0.f, 100.f};

	sf::Text			m_applePosText;
	sf::Vector2f		m_applePosTextPos{ 200.f, 100.f };

	sf::Text			m_scoreLabel;
	sf::Vector2f		m_scoreLabelPos{ 0.f, 150.f };

	sf::Text			m_scoreText;
	sf::Vector2f		m_scoreTextPos{150.f, 150.f};

	sf::Text			m_applesCollectedLabel;
	sf::Vector2f		m_applesCollectedLabelPos{0.f, 200.f};

	sf::Text			m_applesCollectedText;
	sf::Vector2f		m_applesCollectedTextPos{125.f, 200.f};

	
	


	// TODO These are also used in other states. Need to centralize this information. 
	const sf::Color DARK_COLOR{ 15, 56, 15 };
	const sf::Color MID_COLOR{ 48, 98, 48 };
	const sf::Color LIGHT_COLOR{ 139, 172, 15 };
	const sf::Color BRIGHT_COLOR{ 155, 188, 15 };
};   //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


