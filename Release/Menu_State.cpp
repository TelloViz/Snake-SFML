#include "Menu_State.hpp"
#include <iostream>
#include "Play_State.hpp"

Menu_State::Menu_State(IContext* ctx) 
	: IState(ctx),
	WINDOW_SIZE{ sf::Vector2u{600, 600} },
	m_logoGraphic{"W:\\Summer20\\Snake\\Snake\\Snake\\Snake_Logo.png"},
	m_borderGraphic{"Menu_Border.png"}
	
{
	RequestWindowResize(WINDOW_SIZE);

	// :::::::::::::::::::::::::::::: Temporary Logo Init Code ::::::::::::::::::::::::::::::::::::::::::::::
	m_logoGraphic.setPosition(sf::Vector2f{ 47.f, 45.f }); // TODO make this less temporary
	m_logoGraphic.scale(sf::Vector2f{ 1.5f, 1.5f });
	
	
	
	if (!m_menuFont.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh
	m_menuText.setFont(m_menuFont);
	m_menuText.setString("Press space to continue...");
	m_menuText.setPosition(95, 500);
	m_menuText.setFillColor(BRIGHT_COLOR);
	m_menuText.setOutlineColor(DARK_COLOR);
	m_menuText.setOutlineThickness(2);
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	
}

void Menu_State::ProcessInputQueue(std::queue<sf::Keyboard::Key> &inputQueue)
{
	// TODO determine if a queue will hold up the game for too long if many keys are provided by the system at once
	
	// in the event of no events, leave procedure
	if (inputQueue.empty()) return;	

	auto inputKey = inputQueue.front();
	if (inputQueue.front() == ESC_CMD) RequestProgramTermination();
	else if (inputQueue.front() == TRANSITION_CMD) m_bShouldTransistion = true;
	inputQueue.pop();
}

void Menu_State::UpdateState()
{
	if (m_bShouldTransistion) { RequestStateTransition(new  Play_State(m_pContext)); } // then signal transition to next state (to playing state in this case)
}

void Menu_State::RenderState(sf::RenderWindow& window)
{	
	window.clear(BRIGHT_COLOR);
	window.draw(m_borderGraphic);
	window.draw(m_menuText);
	window.draw(m_logoGraphic);
	window.display();
}
