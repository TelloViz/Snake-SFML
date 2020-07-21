#pragma once
#include "IState.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string>
#include <random>
#include <iterator>

#include "Snake_Controller.h"
#include "Snake_Rule_Monitor.h"
#include "Static_Graphic.h"
#include "Debug_Window.hpp"


//#define DEBUG_CONTROLS
#ifdef DEBUG_CONTROLS
namespace debug_controls
{
	sf::Keyboard::Key		KILL_CMD{ sf::Keyboard::Key::F12 };
	sf::Keyboard::Key		INC_PTS_CMD{ sf::Keyboard::Key::F11 };
}
#endif // DEBUG_CONTROLS


typedef sf::Vector2i Apple_Coord;
typedef std::uniform_int_distribution<int> stlDistribution;
typedef std::vector<Snake_Segment> Cut_Tail_Vector;


class Play_State :
	public IState
{
public: // TODO make a state machine class to handle state transitioning. a middle man between the game(context) and the states

	Play_State(IContext* ctx);
	virtual void			ProcessInputQueue(std::queue< sf::Keyboard::Key>& inputQueue);
	virtual void			UpdateState();
	virtual void			RenderState(sf::RenderWindow& window);

private:

	Debug_Window			m_debugWindow;


	Snake_Rule_Monitor		m_ruleMonitor;
	Snake_Controller		m_snkController;
	Snake				m_snake;
	enum Direction			{ NONE = 0, UP, DOWN, LEFT, RIGHT };
	Direction				m_currDir;

	int				m_score;

	sf::Font				m_hudFont;
	sf::Text				m_hudScoreLabelText;
	sf::Text				m_hudScore;
	sf::Text				m_hudLivesLabelText;
	sf::Text				m_hudLives;
	sf::Text				m_gameoverText;
	sf::Vector2f			m_gameoverTextPos;
	sf::Text				m_pressAnyKeyText;
	sf::Vector2f			m_pressAnyKeyTextPos;

	Static_Graphic			m_hudOverlay;
	Static_Graphic			m_playAreaOverlay;
	Static_Graphic			m_gridOverlay;
	
	Static_Graphic			m_snakeHeadUp;
	Static_Graphic			m_snakeHeadDown;
	Static_Graphic			m_snakeHeadLeft;
	Static_Graphic			m_snakeHeadRight;

	Static_Graphic			m_snakeBod; // possibly temp version of the snake bod art
	Static_Graphic			m_cutBod;	

	Static_Graphic*		m_currentSnakeGraphic;

	Static_Graphic			m_appleGraphic;

	Static_Graphic			m_gameoverGraphic;
	sf::Vector2f			m_gameoverGraphicPos;

	sf::FloatRect			m_playArea;
	sf::FloatRect			m_hudArea;

	sf::FloatRect			m_playAreaVP;
	sf::FloatRect			m_hudAreaVP;

	sf::View				m_hudView;
	sf::View				m_playView;

	bool					m_bShouldTransistion{ false };
	bool					m_bSelfCollisionThisFrame{ false };
	bool					m_bGameOver{ false };
	bool					m_bShouldTransitionToGameOver{ false };


	Apple_Coord			m_appleCoord;
	bool					m_bAppleCollected;
	bool					m_bSpawnApple;


	Cut_Tail_Vector		m_cutTail;

	sf::SoundBuffer m_appleGetBuff;
	sf::SoundBuffer m_boneCrashSoundBuff;
	sf::SoundBuffer m_tailCrashSoundBuff;

	sf::Sound m_appleGetSound;
	sf::Sound m_boneCrashSound;
	sf::Sound m_tailCrashSound;



	//**** Members for generating random numbers ****
	std::random_device		m_device;
	std::mt19937			m_generator;
	stlDistribution          m_distribution;
	//::::::::::::::::::::::::::::::::::::::::::::::::


	// TODO add the ability to change the key-bindings at runtime
	sf::Keyboard::Key		UP_CMD			{ sf::Keyboard::Key::W };
	sf::Keyboard::Key		UP_CMD2			{ sf::Keyboard::Key::Up };

	sf::Keyboard::Key		DOWN_CMD			{ sf::Keyboard::Key::S };
	sf::Keyboard::Key		DOWN_CMD2			{ sf::Keyboard::Key::Down };


	sf::Keyboard::Key		LEFT_CMD			{ sf::Keyboard::Key::A };
	sf::Keyboard::Key		LEFT_CMD2			{ sf::Keyboard::Key::Left };


	sf::Keyboard::Key		RIGHT_CMD			{ sf::Keyboard::Key::D };
	sf::Keyboard::Key		RIGHT_CMD2		{ sf::Keyboard::Key::Right };


	sf::Keyboard::Key		PAUSE_CMD			{ sf::Keyboard::Key::P };


	sf::Keyboard::Key		SELECT_CMD		{ sf::Keyboard::Key::Enter };
	sf::Keyboard::Key		ESC_CMD			{ sf::Keyboard::Key::Escape };


	const sf::Vector2u WINDOW_SIZE;
	sf::View m_gridView;


	// TODO These are also used in other states. Need to centralize this information. 
	const sf::Color DARK_COLOR{ 15, 56, 15 };
	const sf::Color MID_COLOR{ 48, 98, 48 };
	const sf::Color LIGHT_COLOR{ 139, 172, 15 };
	const sf::Color BRIGHT_COLOR{ 155, 188, 15 };
};   //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
