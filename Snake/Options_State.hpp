#pragma once
#include "IState.hpp"
#include "SFML/Audio.hpp"
#include "Static_Graphic.h"

class Options_State :
	public IState
{
public:

	Options_State(IContext* ctx);

	virtual void ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue);
	virtual void UpdateState();
	virtual void RenderState(sf::RenderWindow& window);

private: // private methods

	enum Direction { UP, DOWN };
	void cycleActiveSelection(Direction dir);

private:

	sf::Font m_menuFont;

	sf::Text m_resetScoresText;
	sf::Text m_backText;

	sf::Vector2f m_resetScoresTextPos{};
	sf::Vector2f m_backTextsPos{};


	sf::Text* m_pActiveText;


	sf::SoundBuffer m_cycleSoundBuff;
	sf::SoundBuffer m_selectionSoundBuff;

	sf::Sound m_cycleSound;
	sf::Sound m_selectionSound;

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

