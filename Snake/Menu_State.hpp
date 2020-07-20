#pragma once
#include "IState.hpp"
#include "Static_Graphic.h"
#include <iostream>



class Menu_State :
	public IState
{
public: // TODO make a state machine class to handle state transitioning. a middle man between the game(context) and the states

	Menu_State(IContext* ctx);
	virtual void ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue);
	virtual void UpdateState();
	virtual void RenderState(sf::RenderWindow& window);



private:
	bool m_bShouldTransistion{ false };
	const sf::Keyboard::Key TRANSITION_CMD{ sf::Keyboard::Key::Space };
	const sf::Keyboard::Key ESC_CMD{ sf::Keyboard::Key::Escape };
	const sf::Keyboard::Key UP_CMD{ sf::Keyboard::Key::Up };
	const sf::Keyboard::Key DOWN_CMD{ sf::Keyboard::Key::Down };
	const sf::Keyboard::Key SELECT_CMD{ sf::Keyboard::Key::Enter };


	sf::RectangleShape m_background;
	Static_Graphic m_logoGraphic;
	Static_Graphic m_borderGraphic;
	sf::Font m_menuFont;


	sf::Text m_menuText;
	sf::Text m_startText;
	sf::Text m_optionsText;
	sf::Text m_quitText;

	

	// TODO These are also used in other states. Need to centralize this information. 
	const sf::Color DARK_COLOR{ 15, 56, 15 };
	const sf::Color MID_COLOR{ 48, 98, 48 };
	const sf::Color LIGHT_COLOR{ 139, 172, 15 };
	const sf::Color BRIGHT_COLOR{ 155, 188, 15 };
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


	sf::Vector2<sf::Color> m_idleText{BRIGHT_COLOR, DARK_COLOR};
	sf::Vector2<sf::Color> m_activeText{DARK_COLOR, BRIGHT_COLOR};


	const sf::Vector2u WINDOW_SIZE;



};

