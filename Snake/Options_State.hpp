#pragma once
#include "IState.hpp"
#include "Static_Graphic.h"

class Options_State :
	public IState
{
public:

	Options_State(IContext* ctx);

	virtual void ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue);
	virtual void UpdateState();
	virtual void RenderState(sf::RenderWindow& window);
private:

	// TODO These are also used in other states. Need to centralize this information. 
	const sf::Color DARK_COLOR{ 15, 56, 15 };
	const sf::Color MID_COLOR{ 48, 98, 48 };
	const sf::Color LIGHT_COLOR{ 139, 172, 15 };
	const sf::Color BRIGHT_COLOR{ 155, 188, 15 };
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	sf::Vector2<sf::Color> m_idleTextColor{ BRIGHT_COLOR, DARK_COLOR };
	sf::Vector2<sf::Color> m_ActiveTextColor{ MID_COLOR, DARK_COLOR };


	const sf::Vector2u WINDOW_SIZE;
};

