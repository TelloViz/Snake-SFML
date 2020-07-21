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

	if (!m_cycleSoundBuff.loadFromFile("SoundEffect7.ogg")) std::cout << "Failed to load sound 7" << std::endl; // TODO find or make my own sounds so I'm not infringing BM
	if (!m_selectionSoundBuff.loadFromFile("SoundEffect8.ogg")) std::cout << "Failed to load sound 8" << std::endl;

	m_cycleSound.setBuffer(m_cycleSoundBuff);
	m_selectionSound.setBuffer(m_selectionSoundBuff);

	m_cycleSound.setLoop(false);
	m_selectionSound.setLoop(false);
}

void Options_State::ProcessInputQueue(std::queue<sf::Keyboard::Key>& inputQueue)
{
	// in the event of no events, leave procedure
	if (inputQueue.empty()) return;

	auto inputKey = inputQueue.front();

	if (inputKey == UP_CMD)
	{
		m_cycleSound.play();
	}

	if (inputKey == DOWN_CMD)
	{
		m_cycleSound.play();
	}

	if (inputKey == SELECT_CMD)
	{
		//RequestStatePopTransition(); if select "back"
	}

	inputQueue.pop();
}

void Options_State::UpdateState()
{
}

void Options_State::RenderState(sf::RenderWindow& window)
{
}

void Options_State::cycleActiveSelection(Direction dir)
{

	m_pActiveText->setFillColor(m_idleTextColor.x);
	m_pActiveText->setOutlineColor(m_idleTextColor.y);

	switch (dir)
	{
	case Menu_State::UP:


		if (m_pActiveText == &m_startText)
		{
			m_pActiveText = &m_quitText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);

		}
		else if (m_pActiveText == &m_optionsText)
		{
			m_pActiveText = &m_startText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
		}
		else if (m_pActiveText == &m_quitText)
		{
			m_pActiveText = &m_optionsText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
		}
		break;
	case Menu_State::DOWN:

		if (m_pActiveText == &m_startText)
		{
			m_pActiveText = &m_optionsText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);

		}
		else if (m_pActiveText == &m_optionsText)
		{
			m_pActiveText = &m_quitText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
		}
		else if (m_pActiveText == &m_quitText)
		{
			m_pActiveText = &m_startText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
		}
		break;
	}



}