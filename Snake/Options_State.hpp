#pragma once
#include "IState.hpp"
#include "SFML/Audio.hpp"
#include "Static_Graphic.h"
#include <string>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>

class Options_State :
	public IState
{

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive& archive)
	{
		std::string m_firstNameString = "APA";
		std::string m_secNameString = "BTA";
		std::string m_thirdNameString = "OMA";
		archive(100, m_firstNameString, 50, m_secNameString, 10, m_thirdNameString); // serialize things by passing them to the archive

	}
	void encrypt_and_save();
public:

	Options_State(IContext* ctx);

	virtual void ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue);
	virtual void UpdateState();
	virtual void RenderState(sf::RenderWindow& window);

private: // private methods

	enum Direction { UP, DOWN };
	void cycleActiveSelection(Direction dir);

private:

	Static_Graphic m_selectionBorder;
	sf::Vector2f m_selectionBorderPos{ 175.f, 150.f };

	sf::Font m_menuFont;

	sf::Text m_optionsHeaderText;
	sf::Text m_resetScoresText;
	sf::Text m_muteText;
	sf::Text m_backText;

	sf::Vector2f m_optionsHeaderTextPos{180.f, 100.f};
	sf::Vector2f m_resetScoresTextPos{ 200.f, 160.f };
	sf::Vector2f m_muteTextPos{240.f, 210.f};
	sf::Vector2f m_backTextPos{265.f, 400.f};


	sf::Text* m_pActiveText;


	sf::SoundBuffer m_cycleSoundBuff;
	sf::SoundBuffer m_selectionSoundBuff;

	sf::Sound m_cycleSound;
	sf::Sound m_selectionSound;

	//bool m_bMute{ false };

	const sf::Keyboard::Key UP_CMD{ sf::Keyboard::Key::Up };
	const sf::Keyboard::Key DOWN_CMD{ sf::Keyboard::Key::Down };
	const sf::Keyboard::Key SELECT_CMD{ sf::Keyboard::Key::Enter };

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

