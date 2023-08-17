#pragma once
#include "IState.hpp"
#include <iostream>


class Pause_State :
	public IState
{
public:
	Pause_State(sm::IContext* ctx);
	virtual ~Pause_State();
	virtual void ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue);
	virtual void UpdateState();
	virtual void RenderState(sf::RenderWindow& window);

private:
	sf::Keyboard::Key		PAUSE_CMD{ sf::Keyboard::Key::P };
	sf::Keyboard::Key		ESC_CMD{ sf::Keyboard::Key::Escape };

	sf::Font m_pauseFont;
	sf::Text m_pauseText;

	sf::View m_pauseView;
	sf::FloatRect m_pauseAreaVP;

	bool m_bShouldTerminate;
	bool m_bShouldResume;

	// TODO These are also used in other states. Need to centralize this information. 
	const sf::Color DARK_COLOR{ 15, 56, 15 };
	const sf::Color MID_COLOR{ 48, 98, 48 };
	const sf::Color LIGHT_COLOR{ 139, 172, 15 };
	const sf::Color BRIGHT_COLOR{ 155, 188, 15 };
};   //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


