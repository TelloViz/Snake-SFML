#pragma once
#include "IState.hpp"

#include "SFML/Audio.hpp"

#include "Static_Graphic.h"
#include <iostream>




class Menu_State :
	public IState
{
public: // TODO make a state machine class to handle state transitioning. a middle man between the game(context) and the states

	Menu_State(sm::IContext* ctx);
	virtual void ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue);
	virtual void UpdateState();
	virtual void RenderState(sf::RenderWindow& window);

private: // private methods
	enum Direction { UP, DOWN };
	void cycleActiveSelection(Direction dir);

private:
	bool m_bShouldTransistion{ false };
	enum Transition_To{NONE, PLAY, OPTIONS, QUIT} m_transitionTo;


	const sf::Keyboard::Key UP_CMD{ sf::Keyboard::Key::Up };
	const sf::Keyboard::Key DOWN_CMD{ sf::Keyboard::Key::Down };
	const sf::Keyboard::Key SELECT_CMD{ sf::Keyboard::Key::Enter };


	Static_Graphic m_logoGraphic;
	Static_Graphic m_borderGraphic;
	Static_Graphic m_selectionBorder;

	sf::Vector2f m_selectionBorderPos{ 390.f, 300.f };

	sf::Font m_menuFont;

	sf::Text m_menuText;
	sf::Text m_startText;
	sf::Text m_optionsText;
	sf::Text m_quitText;

	sf::Text* m_pActiveText;

	sf::Vector2f m_menuTextPos{ 95.f, 500.f };
	sf::Vector2f m_startTextPos{ 250.f, 325.f };
	sf::Vector2f m_optionsTextPos{235.f, 375.f};
	sf::Vector2f m_quitTextPos{ 250.f, 425.f };
	

	// TODO These are also used in other states. Need to centralize this information. 
	const sf::Color DARK_COLOR{ 15, 56, 15 };
	const sf::Color MID_COLOR{ 48, 98, 48 };
	const sf::Color LIGHT_COLOR{ 139, 172, 15 };
	const sf::Color BRIGHT_COLOR{ 155, 188, 15 };
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	sf::Vector2<sf::Color> m_idleTextColor{BRIGHT_COLOR, DARK_COLOR};
	sf::Vector2<sf::Color> m_ActiveTextColor{MID_COLOR, DARK_COLOR};


	const sf::Vector2u WINDOW_SIZE;

	sf::SoundBuffer m_cycleSoundBuff;
	sf::SoundBuffer m_selectionSoundBuff;

	sf::Sound m_cycleSound;
	sf::Sound m_selectionSound;




};

