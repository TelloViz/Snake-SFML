#include "Menu_State.hpp"



Menu_State::Menu_State(IContext* ctx) 
	: IState(ctx),
	WINDOW_SIZE{ sf::Vector2u{600, 600} },
	m_logoGraphic{"Snake_Logo.png"},
	m_borderGraphic{"Menu_Border.png"},
	m_selectionBorder{"Selection_Box.png"}, // reusing score display box for now
	m_pActiveText{&m_startText}
{
	RequestWindowResize(WINDOW_SIZE);

	// :::::::::::::::::::::::::::::: Temporary Logo Init Code ::::::::::::::::::::::::::::::::::::::::::::::
	m_logoGraphic.setPosition(sf::Vector2f{ 47.f, 45.f }); // TODO make this less temporary
	m_logoGraphic.scale(sf::Vector2f{ 1.5f, 1.5f });
	
	//m_selectionBorder.scale(sf::Vector2f{.5f, .5f});
	m_selectionBorder.rotate(90);
	m_selectionBorder.setPosition(m_selectionBorderPos);

	
	if (!m_menuFont.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh
	
	m_startText.setFont(m_menuFont);
	m_startText.setString("Start");
	m_startText.setPosition(m_startTextPos);
	m_startText.setFillColor(m_idleTextColor.x);
	m_startText.setOutlineColor(m_idleTextColor.y);
	m_startText.setOutlineThickness(2);

	m_optionsText.setFont(m_menuFont);
	m_optionsText.setString("Options");
	m_optionsText.setPosition(m_optionsTextPos);
	m_optionsText.setFillColor(m_idleTextColor.x);
	m_optionsText.setOutlineColor(m_idleTextColor.y);
	m_optionsText.setOutlineThickness(2);

	m_quitText.setFont(m_menuFont);
	m_quitText.setString("Quit");
	m_quitText.setPosition(m_quitTextPos);
	m_quitText.setFillColor(m_idleTextColor.x);
	m_quitText.setOutlineColor(m_idleTextColor.y);
	m_quitText.setOutlineThickness(2);


	m_pActiveText->setFillColor(m_ActiveTextColor.x);
	m_pActiveText->setOutlineColor(m_ActiveTextColor.y);

	if (!m_cycleSoundBuff.loadFromFile("SoundEffect7.ogg")) std::cout << "Failed to load sound 7" << std::endl; // TODO find or make my own sounds so I'm not infringing BM
	if (!m_selectionSoundBuff.loadFromFile("SoundEffect8.ogg")) std::cout << "Failed to load sound 8" << std::endl;

	m_cycleSound.setBuffer(m_cycleSoundBuff);
	m_selectionSound.setBuffer(m_selectionSoundBuff);

	m_cycleSound.setLoop(false);
	m_selectionSound.setLoop(false);

}

void Menu_State::ProcessInputQueue(std::queue<sf::Keyboard::Key> &inputQueue)
{
	// TODO determine if a queue will hold up the game for too long if many keys are provided by the system at once
	
	// in the event of no events, leave procedure
	if (inputQueue.empty()) return;	

	auto inputKey = inputQueue.front();
	
	if (inputKey == UP_CMD)
	{
		m_cycleSound.play();
		cycleActiveSelection(UP);
	}

	if (inputKey == DOWN_CMD)
	{
		m_cycleSound.play();
		cycleActiveSelection(DOWN);
	}

	if (inputKey == SELECT_CMD)
	{
		m_selectionSound.play();
		sf::sleep(sf::seconds(1));
		m_bShouldTransistion = true;
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

void Menu_State::UpdateState()
{
	if (m_bShouldTransistion) 
	{
		switch (m_transitionTo)
		{
		case Menu_State::PLAY:
			RequestPlayAgain();
			break;
		case Menu_State::OPTIONS:
			RequestOptions();
			break;
		case Menu_State::QUIT:
			RequestProgramTermination();
			break;
		}
	} 
}

void Menu_State::RenderState(sf::RenderWindow& window)
{	
	window.clear(BRIGHT_COLOR);
	window.draw(m_borderGraphic);
	window.draw(m_selectionBorder);
	window.draw(m_menuText);
	window.draw(m_startText);
	window.draw(m_quitText);
	window.draw(m_optionsText);
	window.draw(m_logoGraphic);
	window.display();
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
