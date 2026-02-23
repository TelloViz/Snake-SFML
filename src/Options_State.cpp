#include "Options_State.hpp"
#include <fstream>
#include <iostream>


void Options_State::encrypt_and_save()
{
	std::ofstream out_stream{ "highscore.txt", std::ofstream::binary };
	cereal::BinaryOutputArchive out_archive(out_stream); // Create an output archive

	std::string firstNameString = "APA";
	std::string secNameString = "BTA";
	std::string thirdNameString = "OMA";

	out_archive(100, firstNameString, 50, secNameString, 10, thirdNameString);

}


Options_State::Options_State(sm::IContext* ctx)
	: IState{ctx}, 
	m_pActiveText{&m_resetScoresText}, 
	m_selectionBorder{ "Options_Selection_Box.png" }
{

	
	m_selectionBorder.setPosition(m_selectionBorderPos);


	if (!m_menuFont.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh

	m_optionsHeaderText.setFont(m_menuFont);
	m_optionsHeaderText.setCharacterSize(35);
	m_optionsHeaderText.setString("Options Menu");
	m_optionsHeaderText.setPosition(m_optionsHeaderTextPos);
	m_optionsHeaderText.setFillColor(m_idleTextColor.x);
	m_optionsHeaderText.setOutlineColor(m_idleTextColor.y);
	m_optionsHeaderText.setOutlineThickness(2);

	m_resetScoresText.setFont(m_menuFont);
	m_resetScoresText.setString("reset scores");
	m_resetScoresText.setPosition(m_resetScoresTextPos);
	m_resetScoresText.setFillColor(m_idleTextColor.x);
	m_resetScoresText.setOutlineColor(m_idleTextColor.y);
	m_resetScoresText.setOutlineThickness(2);

	m_muteText.setFont(m_menuFont);
	m_muteText.setString("un/mute");
	m_muteText.setPosition(m_muteTextPos);
	m_muteText.setFillColor(m_idleTextColor.x);
	m_muteText.setOutlineColor(m_idleTextColor.y);
	m_muteText.setOutlineThickness(2);

	m_backText.setFont(m_menuFont);
	m_backText.setString("back");
	m_backText.setPosition(m_backTextPos);
	m_backText.setFillColor(m_idleTextColor.x);
	m_backText.setOutlineColor(m_idleTextColor.y);
	m_backText.setOutlineThickness(2);

	if (!m_cycleSoundBuff.loadFromFile("SoundEffect7.ogg")) std::cout << "Failed to load sound 7" << std::endl; // TODO find or make my own sounds so I'm not infringing BM
	if (!m_selectionSoundBuff.loadFromFile("SoundEffect8.ogg")) std::cout << "Failed to load sound 8" << std::endl;

	m_cycleSound.setBuffer(m_cycleSoundBuff);
	m_selectionSound.setBuffer(m_selectionSoundBuff);

	m_cycleSound.setLoop(false);
	m_selectionSound.setLoop(false);

	m_pActiveText->setFillColor(m_ActiveTextColor.x);
	m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
}

void Options_State::ProcessInputQueue(std::queue<sf::Keyboard::Key>& inputQueue)
{
	// in the event of no events, leave procedure
	if (inputQueue.empty()) return;

	auto inputKey = inputQueue.front();

	if (inputKey == UP_CMD)
	{
		if (!RequestMuteStatus()) m_cycleSound.play();
		cycleActiveSelection(UP);
	}

	if (inputKey == DOWN_CMD)
	{
		if (!RequestMuteStatus()) m_cycleSound.play();
		cycleActiveSelection(DOWN);
	}

	if (inputKey == SELECT_CMD)
	{

		if (m_pActiveText == &m_muteText)
		{
			if (!RequestMuteStatus()) m_selectionSound.play();
			RequestMute();
		}
		else if (m_pActiveText == &m_resetScoresText)
		{
			if (!RequestMuteStatus()) m_selectionSound.play();
			encrypt_and_save();
		}		
		else if (m_pActiveText == &m_backText)
			{
				if(!RequestMuteStatus()) m_selectionSound.play();
				sf::sleep(sf::seconds(1));
				RequestStatePopTransition();
			}
		

	}

	inputQueue.pop();
}

void Options_State::UpdateState()
{
}

void Options_State::RenderState(sf::RenderWindow& window)
{
	window.clear(BRIGHT_COLOR);
	window.draw(m_optionsHeaderText);
	window.draw(m_selectionBorder);
	window.draw(m_resetScoresText);
	window.draw(m_muteText);
	window.draw(m_backText);
	window.display();
}

void Options_State::cycleActiveSelection(Direction dir)
{

	m_pActiveText->setFillColor(m_idleTextColor.x);
	m_pActiveText->setOutlineColor(m_idleTextColor.y);

	switch (dir)
	{
	case Options_State::UP:


		if (m_pActiveText == &m_resetScoresText)
		{
			m_pActiveText = &m_backText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);

		}
		else if (m_pActiveText == &m_muteText)
		{
			m_pActiveText = &m_resetScoresText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
		}
		else if (m_pActiveText == &m_backText)
		{
			m_pActiveText = &m_muteText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
		}
		else if (m_pActiveText == &m_muteText)
		{

		}
		break;
	case Options_State::DOWN:

		if (m_pActiveText == &m_resetScoresText)
		{
			m_pActiveText = &m_muteText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);

		}
		else if (m_pActiveText == &m_muteText)
		{
			m_pActiveText = &m_backText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
		}
		else if (m_pActiveText == &m_backText)
		{
			m_pActiveText = &m_resetScoresText;
			m_pActiveText->setFillColor(m_ActiveTextColor.x);
			m_pActiveText->setOutlineColor(m_ActiveTextColor.y);
		}
		break;
	}



}