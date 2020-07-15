#include "Game_Over_State.hpp"
#include "Play_State.hpp"
#include <iostream>

Game_Over_State::Game_Over_State(IContext* ctx, int score)
	: IState{ctx},
	m_score{ score },
	m_bInitialsNeeded{false},
	m_rankToReplace{NONE},
	m_gameoverGraphic{"GameOverLogo.png"},
	m_gameoverGraphicPos{ sf::Vector2f{100.f, 200.f} },
	m_gridOverlay{ "Grid_Overlay.png" },
	m_scoreDisplayGraphic{"Score_Display_Box.png"},
	m_scoreDisplayGraphicPos{ sf::Vector2f{100.f, 75.f} },
	m_scoreArea{ sf::FloatRect{0.f, 50.f, 600.f, 600.f} },
	m_headerArea{ sf::FloatRect{0.f, 0.f, 600.f, 50.f} },
	m_headerOverlay{ "Score_Header.png" },
	m_scoreView(sf::FloatRect{ 0, 0, 600, 600 }),
	m_scoreAreaVP{ sf::FloatRect{0.f,1 - 600.f / 650.f,1.f,600.f / 650.f} },
	m_headerView{ sf::FloatRect {0.f, 0.f, 600.f, 50.f} },
	m_headerAreaVP{ sf::FloatRect{0.f, 0.f, 1.f,50.f / 650.f} },
	m_firstPlaceLabelPos{ sf::Vector2f{125.f, 100.f} },
	m_secPlaceLabelPos{ sf::Vector2f{125.f, 200.f} },
	m_thirdPlaceLabelPos{ sf::Vector2f{125.f, 300.f} },
	m_firstScoreTextPos{ sf::Vector2f{200, 100.f} },
	m_secScoreTextPos{ sf::Vector2f{200.f, 200.f} },
	m_thirdScoreTextPos{ sf::Vector2f{200.f, 300.f} },
	m_toContinueTextPos{ sf::Vector2f{125.f,400.f} },
	m_toQuitTextPos{ sf::Vector2f{200.f,435.f} },
	m_firstNameTextPos{ sf::Vector2f{300.f, 100.f} },
	m_secNameTextPos{ sf::Vector2f{300.f, 200.f} },
	m_thirdNameTextPos{ sf::Vector2f{300.f, 300.f} },
	m_enterInitialsText1Pos{ sf::Vector2f{155.f, 400.f} },
	m_enterInitialsText2Pos{ sf::Vector2f{123.f, 425.f} },
	m_enterInitialsText3Pos{ sf::Vector2f{195.f, 450.f} }
{


	// init views
	{ 
	m_scoreView.setViewport(m_scoreAreaVP);
	m_headerView.setViewport(m_headerAreaVP);
	}

	// init labels and text
	{
		if (!m_gameoverFont.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh
		m_finalScoreLabel.setFont(m_gameoverFont);
		m_finalScoreLabel.setString("Final Score: ");
		m_finalScoreLabel.setPosition(10.f, 10.f);
		m_finalScoreLabel.setFillColor(BRIGHT_COLOR);
		m_finalScoreLabel.setOutlineColor(DARK_COLOR);
		m_finalScoreLabel.setOutlineThickness(2);
		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

		m_scoreValueString.setFont(m_gameoverFont);
		m_scoreValueString.setString("-");
		m_scoreValueString.setPosition(225.f, 10.f);
		m_scoreValueString.setFillColor(BRIGHT_COLOR);
		m_scoreValueString.setOutlineColor(DARK_COLOR);
		m_scoreValueString.setOutlineThickness(2);


		m_firstPlaceLabel.setFont(m_gameoverFont);
		m_firstPlaceLabel.setString("1st: ");
		m_firstPlaceLabel.setPosition(m_firstPlaceLabelPos);
		m_firstPlaceLabel.setFillColor(BRIGHT_COLOR);
		m_firstPlaceLabel.setOutlineColor(DARK_COLOR);
		m_firstPlaceLabel.setOutlineThickness(2);

		m_secPlaceLabel.setFont(m_gameoverFont);
		m_secPlaceLabel.setString("2nd: ");
		m_secPlaceLabel.setPosition(m_secPlaceLabelPos);
		m_secPlaceLabel.setFillColor(BRIGHT_COLOR);
		m_secPlaceLabel.setOutlineColor(DARK_COLOR);
		m_secPlaceLabel.setOutlineThickness(2);

		m_thirdPlaceLabel.setFont(m_gameoverFont);
		m_thirdPlaceLabel.setString("3rd: ");
		m_thirdPlaceLabel.setPosition(m_thirdPlaceLabelPos);
		m_thirdPlaceLabel.setFillColor(BRIGHT_COLOR);
		m_thirdPlaceLabel.setOutlineColor(DARK_COLOR);
		m_thirdPlaceLabel.setOutlineThickness(2);

		m_firstScoreText.setFont(m_gameoverFont);
		m_firstScoreText.setString("-");
		m_firstScoreText.setPosition(m_firstScoreTextPos);
		m_firstScoreText.setFillColor(BRIGHT_COLOR);
		m_firstScoreText.setOutlineColor(DARK_COLOR);
		m_firstScoreText.setOutlineThickness(2);

		m_secScoreText.setFont(m_gameoverFont);
		m_secScoreText.setString("-");
		m_secScoreText.setPosition(m_secScoreTextPos);
		m_secScoreText.setFillColor(BRIGHT_COLOR);
		m_secScoreText.setOutlineColor(DARK_COLOR);
		m_secScoreText.setOutlineThickness(2);

		m_thirdScoreText.setFont(m_gameoverFont);
		m_thirdScoreText.setString("-");
		m_thirdScoreText.setPosition(m_thirdScoreTextPos);
		m_thirdScoreText.setFillColor(BRIGHT_COLOR);
		m_thirdScoreText.setOutlineColor(DARK_COLOR);
		m_thirdScoreText.setOutlineThickness(2);


		m_toContinueText.setFont(m_gameoverFont);
		m_toContinueText.setString("[space] to play again");
		m_toContinueText.setPosition(m_toContinueTextPos);
		m_toContinueText.setFillColor(BRIGHT_COLOR);
		m_toContinueText.setOutlineColor(DARK_COLOR);
		m_toContinueText.setOutlineThickness(2);

		m_toQuitText.setFont(m_gameoverFont);
		m_toQuitText.setString("[esc] to quit");
		m_toQuitText.setPosition(m_toQuitTextPos);
		m_toQuitText.setFillColor(BRIGHT_COLOR);
		m_toQuitText.setOutlineColor(DARK_COLOR);
		m_toQuitText.setOutlineThickness(2);

		m_firstNameText.setFont(m_gameoverFont);
		m_firstNameText.setPosition(m_firstNameTextPos);
		m_firstNameText.setFillColor(BRIGHT_COLOR);
		m_firstNameText.setOutlineColor(DARK_COLOR);
		m_firstNameText.setOutlineThickness(2);

		m_secNameText.setFont(m_gameoverFont);
		m_secNameText.setPosition(m_secNameTextPos);
		m_secNameText.setFillColor(BRIGHT_COLOR);
		m_secNameText.setOutlineColor(DARK_COLOR);
		m_secNameText.setOutlineThickness(2);

		m_thirdNameText.setFont(m_gameoverFont);
		m_thirdNameText.setPosition(m_thirdNameTextPos);
		m_thirdNameText.setFillColor(BRIGHT_COLOR);
		m_thirdNameText.setOutlineColor(DARK_COLOR);
		m_thirdNameText.setOutlineThickness(2);

		m_enterInitialsText1.setFont(m_gameoverFont);
		m_enterInitialsText1.setCharacterSize(20);
		m_enterInitialsText1.setString("[UP][DOWN] : Cycle Letters");
		m_enterInitialsText1.setPosition(m_enterInitialsText1Pos);
		m_enterInitialsText1.setFillColor(BRIGHT_COLOR);
		m_enterInitialsText1.setOutlineColor(DARK_COLOR);
		m_enterInitialsText1.setOutlineThickness(2);

		m_enterInitialsText2.setFont(m_gameoverFont);
		m_enterInitialsText2.setCharacterSize(20);
		m_enterInitialsText2.setString("[LEFT][RIGHT] : Cycle Initial");
		m_enterInitialsText2.setPosition(m_enterInitialsText2Pos);
		m_enterInitialsText2.setFillColor(BRIGHT_COLOR);
		m_enterInitialsText2.setOutlineColor(DARK_COLOR);
		m_enterInitialsText2.setOutlineThickness(2);

		m_enterInitialsText3.setFont(m_gameoverFont);
		m_enterInitialsText3.setCharacterSize(20);
		m_enterInitialsText3.setString("[ENTER] : Finish");
		m_enterInitialsText3.setPosition(m_enterInitialsText3Pos);
		m_enterInitialsText3.setFillColor(BRIGHT_COLOR);
		m_enterInitialsText3.setOutlineColor(DARK_COLOR);
		m_enterInitialsText3.setOutlineThickness(2);
	}
	
	// load and decrypt save data
	{
		load_and_decrypt();
		m_firstNameText.setString(m_firstNameString);
		m_secNameText.setString(m_secNameString);
		m_thirdNameText.setString(m_thirdNameString);
	}
	
	m_scoreDisplayGraphic.setPosition(m_scoreDisplayGraphicPos);

	if (m_score > m_first)
	{
		m_third = m_second;
		m_second = m_first;
		m_first = m_score;
		m_bInitialsNeeded = true;
		m_rankToReplace = FIRST;
		m_pRankToEdit = m_firstInitials;

		m_secNameString = m_firstNameString;

		m_thirdNameString = m_secNameString;



	}
	else if (m_score > m_second)
	{
		m_third = m_second;
		m_thirdNameText = m_secNameText;
		m_second = m_score;
		m_bInitialsNeeded = true;
		//clearInitials(SECOND);
		m_rankToReplace = SECOND;
		m_pRankToEdit = m_secInitials;

		m_thirdNameString = m_secNameString;
	}
	else if (m_score > m_third)
	{
		m_third = m_score;
		m_bInitialsNeeded = true;
		//clearInitials(THIRD);
		m_rankToReplace = THIRD;
		m_pRankToEdit = m_thirdInitials;
	}


	m_scoreValueString.setString(std::to_string(m_score));
	m_firstScoreText.setString(std::to_string(m_first));
	m_secScoreText.setString(std::to_string(m_second));
	m_thirdScoreText.setString(std::to_string(m_third));
} // ::: END CTOR:::::

Game_Over_State::~Game_Over_State()
{
	

}

void Game_Over_State::ProcessInputQueue(std::queue<sf::Keyboard::Key>& inputQueue)
{
	// in the event of no events, leave procedure
	if (inputQueue.empty()) return;

	auto inputKey = inputQueue.front(); // use an intermediate variable so I don't have to call front() too many times
	if (inputKey == ESC_CMD)
	{
		// TODO: Instead, set a flag signaling the desire to quit, we can then intercept for a "do you really want to"
		if (!m_bInitialsNeeded)
		{
			encrypt_and_save();
			RequestProgramTermination();
		}
	}
	if (!m_bInitialsNeeded && inputKey == CONT_CMD)
	{
		m_bPlayAgain = true;
	}

	if (m_bInitialsNeeded && inputKey == UP_CMD)
	{
		incrementSlotValue(m_pRankToEdit[m_currentSlot]);
	}
	else if (m_bInitialsNeeded && inputKey == DOWN_CMD)
	{
		decrementSlotValue(m_pRankToEdit[m_currentSlot]);

	}
	else if (m_bInitialsNeeded && inputKey == LEFT_CMD)
	{
		decrementSlot(m_currentSlot);
	}
	else if (m_bInitialsNeeded && inputKey == RIGHT_CMD)
	{
		incrementSlot(m_currentSlot);
	}

	if (m_bInitialsNeeded && inputKey == CONFIRM_CMD)
	{
		m_bInitialsNeeded = false;
	}


	inputQueue.pop(); // clear out the processed input
}

void Game_Over_State::UpdateState()
{		

	if (m_bInitialsNeeded)
	{
		switch (m_rankToReplace)
		{
		case Game_Over_State::FIRST:
			if (m_bFirstUpdate)
			{
				m_secNameString = m_firstNameString;
				m_secNameText.setString(m_secNameString);
				m_thirdNameString = m_secNameString;
				m_thirdNameText.setString(m_thirdNameString);
				m_firstNameString = { m_firstInitials };
				m_firstNameText.setString(m_firstNameString);
			}
			else
			{
				m_firstNameString = m_firstInitials;
				m_firstNameText.setString(m_firstNameString);
			}
			break;


		case Game_Over_State::SECOND:
			if (m_bFirstUpdate)
			{
				m_thirdNameString = m_secNameString;
				m_thirdNameText.setString(m_thirdNameString);
				m_secNameString = { m_secInitials };
				m_secNameText.setString(m_secNameString);
			}
			else
			{
				m_secNameString = m_secInitials;
				m_secNameText.setString(m_secNameString);
			}
			break;
		case Game_Over_State::THIRD:
			if (m_bFirstUpdate)
			{
				m_thirdNameString = { m_thirdInitials };
				m_thirdNameText.setString(m_thirdNameString);
			}
			else
			{
				m_thirdNameString = m_thirdInitials;
				m_thirdNameText.setString(m_thirdNameString);
			}
			break;
		}
	}

	if (m_bPlayAgain)
	{
		encrypt_and_save();
		RequestStateTransition(new Play_State{ m_pContext });
	}

	
}

void Game_Over_State::RenderState(sf::RenderWindow& window)
{
	
	window.clear(BRIGHT_COLOR);

	// **********Draw Stuff in Header**************
	window.setView(m_headerView);
	window.draw(m_headerOverlay);
	window.draw(m_finalScoreLabel);
	window.draw(m_scoreValueString);
    
	//::::::::::::::::::::::::::::::::::::::::::::::::

	// ***********Draw Stuff in Play Area*************
	window.setView(m_scoreView);
	if (m_bFirstRender)
	{
		//m_scoreDisplayGraphic.setPosition(m_scoreDisplayGraphicPos);
	}
	window.draw(m_gridOverlay);
	window.draw(m_scoreDisplayGraphic);
	window.draw(m_firstPlaceLabel);
	window.draw(m_firstScoreText);
	window.draw(m_firstNameText);
	window.draw(m_secPlaceLabel);
	window.draw(m_secScoreText);
	window.draw(m_secNameText);
	window.draw(m_thirdPlaceLabel);
	window.draw(m_thirdScoreText);
	window.draw(m_thirdNameText);
	if (m_bInitialsNeeded)
	{
		window.draw(m_enterInitialsText1);
		window.draw(m_enterInitialsText2);
		window.draw(m_enterInitialsText3);
	}
	else
	{
		window.draw(m_toContinueText);
		window.draw(m_toQuitText);
	}
	window.display();
	m_bFirstRender = false;
}

void Game_Over_State::encrypt_and_save()
{
	std::ofstream out_stream{ "highscore.txt", std::ofstream::binary };
	cereal::BinaryOutputArchive out_archive(out_stream); // Create an output archive

	m_firstNameString = m_firstNameText.getString();
	m_secNameString = m_secNameText.getString();
	m_thirdNameString = m_thirdNameText.getString();

	out_archive(m_first, m_firstNameString, m_second, m_secNameString, m_third, m_thirdNameString);

}

void Game_Over_State::load_and_decrypt()
{
	try
	{
		std::ifstream in_stream{ "highscore.txt", std::ofstream::binary };
		cereal::BinaryInputArchive in_archive(in_stream); // Create an output archive
		m_firstNameString = m_firstNameText.getString();
		m_secNameString = m_secNameText.getString();
		m_thirdNameString = m_thirdNameText.getString();

		in_archive(m_first, m_firstNameString, m_second, m_secNameString, m_third, m_thirdNameString);
	}
	catch(...)
	{
		std::cerr << "Exception caught in load_and_decrypt()!"  << std::endl;
	}
}

void Game_Over_State::clearInitials(Game_Over_State::Rank rank)
{
	
	switch (rank)
	{
	case Game_Over_State::FIRST:
		m_firstNameText.setString("___");
		m_currentSlot = SLOT1;
		break;
	case Game_Over_State::SECOND:
		m_secNameText.setString("___");
		m_currentSlot = SLOT2;
		break;
	case Game_Over_State::THIRD:
		m_thirdNameText.setString("___");
		m_currentSlot = SLOT3;
		break;
	default:
		break;
	}
}

void Game_Over_State::incrementSlot(Letter_Slot& slot)
{
	switch (slot)
	{
	case Game_Over_State::SLOT1:
		slot = SLOT2;
		break;
	case Game_Over_State::SLOT2:
		slot = SLOT3;
		break;
	case Game_Over_State::SLOT3:
		slot = SLOT1;
		break;
	}
}

void Game_Over_State::decrementSlot(Letter_Slot& slot)
{
	switch (slot)
	{
	case Game_Over_State::SLOT1:
		slot = SLOT3;
		break;
	case Game_Over_State::SLOT2:
		slot = SLOT1;
		break;
	case Game_Over_State::SLOT3:
		slot = SLOT2;
		break;
	}
}

void Game_Over_State::incrementSlotValue(char& incChar)
{
	if (incChar == 'Z') incChar = 'a';
	else if (incChar == 'z') incChar = '.';
	else if (incChar == '.') incChar = '-';
	else if (incChar == '-') incChar = '_';
	else if (incChar == '_') incChar = ' ';
	else if (incChar == ' ') incChar = 'A';
	else ++incChar;
}

void Game_Over_State::decrementSlotValue(char& incChar)
{
	if (incChar == 'a') incChar = 'Z';
	else if (incChar == '.') incChar = 'z';
	else if (incChar == '-') incChar = '.';
	else if (incChar == '_') incChar = '-';
	else if (incChar == ' ') incChar = '_';
	else if (incChar == 'A') incChar = ' ';
	else --incChar;
}

