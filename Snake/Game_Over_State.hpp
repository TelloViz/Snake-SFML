#pragma once

#include "IState.hpp"
#include "Static_Graphic.h"

#include <iostream>
#include <fstream>
#include <math.h>

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>


class Game_Over_State :
	public IState
{
	enum Rank { NONE = 0, FIRST, SECOND, THIRD };

public:
	Game_Over_State(IContext* ctx, int score);
	~Game_Over_State();
	virtual void ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue);
	virtual void UpdateState();
	virtual void RenderState(sf::RenderWindow& window);

private: // private methods


	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive& archive)
	{
		m_firstNameString = m_firstNameText.getString() ;
		m_secNameString = m_secNameText.getString();
		m_thirdNameString = m_thirdNameText.getString();
		archive(m_first, m_firstNameString, m_second, m_secNameString, m_third, m_thirdNameString); // serialize things by passing them to the archive


	}
	void encrypt_and_save();
	void load_and_decrypt();

	void clearInitials(Game_Over_State::Rank rank);

private:
	int				m_score;
	int				m_first{ 7 };
	int				m_second{ 5 };
	int				m_third{ 1 };

	bool					m_bInitialsNeeded;
	Rank					m_rankToReplace;

	sf::Text				m_firstNameText;
	sf::Text				m_secNameText;
	sf::Text				m_thirdNameText;

	std::string			m_firstNameString;
	std::string			m_secNameString;
	std::string			m_thirdNameString;

	sf::Vector2f			m_firstNameTextPos;
	sf::Vector2f			m_secNameTextPos;
	sf::Vector2f			m_thirdNameTextPos;


	sf::Text				m_firstScoreText;
	sf::Text				m_secScoreText;
	sf::Text				m_thirdScoreText;

	sf::Vector2f			m_firstScoreTextPos;
	sf::Vector2f			m_secScoreTextPos;
	sf::Vector2f			m_thirdScoreTextPos;


	sf::Font				m_gameoverFont;
	sf::Text				m_gameoverLabel;
	sf::Text				m_finalScoreLabel;
	sf::Text				m_firstPlaceLabel;
	sf::Text				m_secPlaceLabel;
	sf::Text				m_thirdPlaceLabel;

	sf::Vector2f			m_firstPlaceLabelPos;
	sf::Vector2f			m_secPlaceLabelPos;
	sf::Vector2f			m_thirdPlaceLabelPos;


	sf::Text				m_scoreValueString;

	sf::Text				m_toContinueText;
	sf::Vector2f			m_toContinueTextPos;

	sf::Text				m_toQuitText;
	sf::Vector2f			m_toQuitTextPos;

	sf::Text				m_enterInitialsText1;
	sf::Vector2f			m_enterInitialsText1Pos;

	sf::Text				m_enterInitialsText2;
	sf::Vector2f			m_enterInitialsText2Pos;

	sf::Text				m_enterInitialsText3;
	sf::Vector2f			m_enterInitialsText3Pos;

	Static_Graphic			m_gameoverGraphic;
	sf::Vector2f			m_gameoverGraphicPos;

	Static_Graphic			m_scoreDisplayGraphic;
	sf::Vector2f			m_scoreDisplayGraphicPos;

	Static_Graphic			m_gridOverlay;

	Static_Graphic			m_headerOverlay;

	bool					m_bFirstRender{ true };
	bool					m_bFirstUpdate{ true };
	bool					m_bPlayAgain{ false };
	bool					m_bTerminate{ false };

	sf::FloatRect			m_scoreArea;
	sf::FloatRect			m_headerArea;

	sf::FloatRect			m_scoreAreaVP;
	sf::FloatRect			m_headerAreaVP;

	sf::View				m_headerView;
	sf::View				m_scoreView;


	sf::Keyboard::Key		ESC_CMD{ sf::Keyboard::Key::Escape };
	sf::Keyboard::Key		CONT_CMD{ sf::Keyboard::Key::Space };
	sf::Keyboard::Key		UP_CMD{ sf::Keyboard::Key::Up };
	sf::Keyboard::Key		DOWN_CMD{ sf::Keyboard::Key::Down };
	sf::Keyboard::Key		LEFT_CMD{ sf::Keyboard::Key::Left };
	sf::Keyboard::Key		RIGHT_CMD{ sf::Keyboard::Key::Right };
	sf::Keyboard::Key		CONFIRM_CMD{ sf::Keyboard::Key::Enter };

	char					m_firstInitials[4] = {'_', '_', '_', 0};
	char					m_secInitials[4] = { '_', '_', '_', 0 };
	char					m_thirdInitials[4] = { '_', '_', '_', 0 };
	char*				m_pRankToEdit;

	enum Letter_Slot{ SLOT1 = 0, SLOT2, SLOT3};
	Letter_Slot			m_currentSlot{ SLOT1 };
	unsigned				m_slot1Letter;
	unsigned				m_slot2Letter;
	unsigned				m_slot3Letter;

	void					incrementSlot(Letter_Slot& slot);
	void					decrementSlot(Letter_Slot& slot);


	void					incrementSlotValue(char& incChar);
	void					decrementSlotValue(char& incChar);


	// TODO These are also used in other states. Need to centralize this information. 
	const sf::Color DARK_COLOR{ 15, 56, 15 };
	const sf::Color MID_COLOR{ 48, 98, 48 };
	const sf::Color LIGHT_COLOR{ 139, 172, 15 };
	const sf::Color BRIGHT_COLOR{ 155, 188, 15 };
};   //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


