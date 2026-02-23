#include "Pause_State.hpp"


Pause_State::Pause_State(sm::IContext* ctx)

// ************* Pause_State init of members ***************************
	: IState{ctx},
	m_pauseView(sf::FloatRect{ 0, 0, 600, 600 }),
	m_pauseAreaVP{ sf::FloatRect{0.f,1 - 600.f / 650.f,1.f,600.f / 650.f} },
	m_bShouldTerminate{ false },
	m_bShouldResume{false}
//:::::::::::::::::::: END INIT OF MEMBERS ::::::::::::::::::::::::::::::::::::::::::::::::

// ******************* Constructor Body ***************************************************

{
	std::cout << "You have entered pause state..." << std::endl;

	m_pauseView.setViewport(m_pauseAreaVP);	

	// ***************** This code needs to be encapsulated somewhere else
	if (!m_pauseFont.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh
	m_pauseText.setFont(m_pauseFont);
	m_pauseText.setString("--Paused--");
	m_pauseText.setPosition(215.f, 175.f);
	m_pauseText.setFillColor(BRIGHT_COLOR);
	m_pauseText.setOutlineColor(DARK_COLOR);
	m_pauseText.setOutlineThickness(2);
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}
//:::::::::::::::::::: END CTOR BODY::::::::::::::::::::::::::::::::::::::::::::::::


Pause_State::~Pause_State()
{
	std::cout << "You are now leaving Pause_State..." << std::endl;
}

void Pause_State::ProcessInputQueue(std::queue<sf::Keyboard::Key>& inputQueue)
{

	// in the event of no events, leave procedure
	if (inputQueue.empty()) return;

	auto inputKey = inputQueue.front(); // use an intermediate variable so I don't have to call front() too many times
	
	if (inputKey == PAUSE_CMD)
	{
		m_bShouldResume = true;
	}
	else if (inputKey == ESC_CMD)
	{
		m_bShouldTerminate = true;
	}

	inputQueue.pop(); // clear out the processed input
}

void Pause_State::UpdateState()
{
	if(m_bShouldTerminate) RequestProgramTermination();
	if(m_bShouldResume) RequestStatePopTransition();

}

void Pause_State::RenderState(sf::RenderWindow& window)
{
	window.clear(BRIGHT_COLOR);
	
	// *************** Set view for drawing pause related things************************
	window.setView(m_pauseView);
	window.draw(m_pauseText);
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	
	
	window.display();
}
