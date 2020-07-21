#include "Options_State.hpp"
#include <iostream>

Options_State::Options_State(IContext* ctx) : IState{ctx}
{
	if (!m_menuFont.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh

	m_resetScoresText.setFont(m_menuFont);
	m_resetScoresText.setString("reset scores");
	m_resetScoresText.setPosition(m_resetScoresTextPos);
	m_resetScoresText.setFillColor(m_idleTextColor.x);
	m_resetScoresText.setOutlineColor(m_idleTextColor.y);
	m_resetScoresText.setOutlineThickness(2);

	m_backText.setFont(m_menuFont);
	m_backText.setString("back");
	m_backText.setPosition(m_backTextsPos);
	m_backText.setFillColor(m_idleTextColor.x);
	m_backText.setOutlineColor(m_idleTextColor.y);
	m_backText.setOutlineThickness(2);
}

void Options_State::ProcessInputQueue(std::queue<sf::Keyboard::Key>& inputQueue)
{
	// in the event of no events, leave procedure
	if (inputQueue.empty()) return;

	auto inputKey = inputQueue.front();

	if (inputKey == UP_CMD)
	{
		
	}

	if (inputKey == DOWN_CMD)
	{
		
	}

	if (inputKey == SELECT_CMD)
	{
		if (m_pActiveText == &m_startText)
		{
			m_transitionTo = PLAY;
		}
		else if (m_pActiveText == &m_optionsText)
		{
			m_transitionTo = OPTIONS;

		}
		else if (m_pActiveText == &m_quitText)
		{
			m_transitionTo = QUIT;

		}
	}

	inputQueue.pop();
}

void Options_State::UpdateState()
{
}

void Options_State::RenderState(sf::RenderWindow& window)
{
}
