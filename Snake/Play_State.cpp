#include "Play_State.hpp"
#include "Pause_State.hpp"
#include "Game_Over_State.hpp"


Play_State::Play_State(IContext* ctx)

// *******************Play State Initialization of Members*******************************
	: IState(ctx),
	WINDOW_SIZE{ 600, 650 },
	m_ruleMonitor{ 30, 30 },
	m_snakeHeadUp{ "Snake_Head_Up.png" },
	m_snakeHeadDown{ "Snake_Head_Down.png" },
	m_snakeHeadLeft{ "Snake_Head_Left.png" },
	m_snakeHeadRight{ "Snake_Head_Right.png" },
	m_currentSnakeGraphic{ &m_snakeHeadUp },
	m_snakeBod{ "Snake_Bod.png" },
	m_cutBod{ "Bone.png" },
	m_appleGraphic{ "Apple.png" },
	m_gameoverGraphic{ "GameOverLogo.png" },
	m_gameoverGraphicPos{ sf::Vector2f{100.f, 150.f} },
	m_gameoverTextPos{175.f, 200.f},
	m_pressAnyKeyTextPos{ sf::Vector2f{180.f, 270.f} },
	m_playArea{ sf::FloatRect{0.f, 50.f, 600.f, 600.f} },
	m_hudArea{ sf::FloatRect{0.f, 0.f, 600.f, 50.f} },
	m_hudOverlay{ "Score_Header.png" },
	m_playAreaOverlay{ "Play_Area_Overlay.png" },
	m_gridOverlay{ "Grid_Overlay.png" },
	m_playView(sf::FloatRect{ 0, 0, 600, 600 }),
	m_playAreaVP{ sf::FloatRect{0.f,1 - 600.f / 650.f,1.f,600.f / 650.f} },
	m_hudView{ sf::FloatRect {0.f, 0.f, 600.f, 50.f} },
	m_hudAreaVP{ sf::FloatRect{0.f, 0.f, 1.f,50.f / 650.f} },
	m_currDir{ NONE },
	m_appleCoord{ sf::Vector2i{0,0} },
	m_bAppleCollected{ false },
	m_bSpawnApple{true},
	m_generator{ m_device() },
	m_distribution{0, 29}															// range matches grid range 30x30 0-indexed grid
//:::::::::::::::::::: END INIT OF MEMBERS ::::::::::::::::::::::::::::::::::::::::::::::::

// ******************* Constructor Body ***************************************************
{
	// ***** INIT WINDOW FOR PLAY_STATE ********
	//RequestWindowTranslation(0, -50);
	RequestWindowResize(WINDOW_SIZE);
	m_playView.setViewport(m_playAreaVP);
	m_hudView.setViewport(m_hudAreaVP);
	// ::::::::::::::::::::::::::::::::::::::::::

	// ******** INIT SNAKE **********************
	m_snkController.Make_Snake(m_snake, Snake_Segment{ 14, 14 }); // init snake
	/*m_snake.push_back(Snake_Segment{14, 15});
	m_snake.push_back(Snake_Segment{14, 16});
	m_snake.push_back(Snake_Segment{13, 16});
	m_snake.push_back(Snake_Segment{12,16});
	m_snake.push_back(Snake_Segment{12,15});
	m_snake.push_back(Snake_Segment{12, 14});
	m_snake.push_back(Snake_Segment{12,13});
	m_snake.push_back(Snake_Segment{12,12});
	m_snake.push_back(Snake_Segment{13,12});
	m_snake.push_back(Snake_Segment{ 14,12 });*/

	// :::::::::::::::::::::::::::::::::::::::::::::::


	// :::::::::::::::::::::::::::::: Temporary Score Label Init Code ::::::::::::::::::::::::::::::::::::::::::::::	
	if (!m_hudFont.loadFromFile("whitrabt.ttf")) std::cout << "failed to load font" << std::endl; // TODO, definitely remove this from happening every frame yeesh
	m_hudScoreLabelText.setFont(m_hudFont);
	m_hudScoreLabelText.setString("Score: ");
	m_hudScoreLabelText.setPosition(10.f, 10.f);
	m_hudScoreLabelText.setFillColor(BRIGHT_COLOR);
	m_hudScoreLabelText.setOutlineColor(DARK_COLOR);
	m_hudScoreLabelText.setOutlineThickness(2);
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


	// :::::::::::::::::::::::::::::: Temporary Score Text Init Code ::::::::::::::::::::::::::::::::::::::::::::::	
	m_hudScore.setFont(m_hudFont);
	m_hudScore.setString("0");
	m_hudScore.setPosition(120.f, 10.f);
	m_hudScore.setFillColor(BRIGHT_COLOR);
	m_hudScore.setOutlineColor(DARK_COLOR);
	m_hudScore.setOutlineThickness(2);
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


	// :::::::::::::::::::::::::::::: Temporary Lives Label Init Code ::::::::::::::::::::::::::::::::::::::::::::::	
	m_hudLivesLabelText.setFont(m_hudFont);
	m_hudLivesLabelText.setString("Lives: ");
	m_hudLivesLabelText.setPosition(455.f, 10.f);
	m_hudLivesLabelText.setFillColor(BRIGHT_COLOR);
	m_hudLivesLabelText.setOutlineColor(DARK_COLOR);
	m_hudLivesLabelText.setOutlineThickness(2);
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	// :::::::::::::::::::::::::::::: Temporary Lives Text Init Code ::::::::::::::::::::::::::::::::::::::::::::::	
	m_hudLives.setFont(m_hudFont);
	m_hudLives.setString("-");
	m_hudLives.setPosition(565.f, 10.f);
	m_hudLives.setFillColor(BRIGHT_COLOR);
	m_hudLives.setOutlineColor(DARK_COLOR);
	m_hudLives.setOutlineThickness(2);
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	// :::::::::::::::::::::::::::::: Temporary Game Over Text Init Code ::::::::::::::::::::::::::::::::::::::::::::::	
	m_gameoverText.setFont(m_hudFont);
	m_gameoverText.setCharacterSize(50);
	m_gameoverText.setString("GAME OVER");
	m_gameoverText.setFillColor(BRIGHT_COLOR);
	m_gameoverText.setOutlineColor(DARK_COLOR);
	m_gameoverText.setOutlineThickness(2);
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	// :::::::::::::::::::::::::::::: Temporary Press Any Key... Text Init Code ::::::::::::::::::::::::::::::::::::::::::::::	
	m_pressAnyKeyText.setFont(m_hudFont);
	m_pressAnyKeyText.setCharacterSize(30);
	m_pressAnyKeyText.setString("Press any key...");
	m_pressAnyKeyText.setFillColor(BRIGHT_COLOR);
	m_pressAnyKeyText.setOutlineColor(DARK_COLOR);
	m_pressAnyKeyText.setOutlineThickness(2);
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::




}
//:::::::::::::::::::: END CTOR BODY::::::::::::::::::::::::::::::::::::::::::::::::


void Play_State::ProcessInputQueue(std::queue<sf::Keyboard::Key>& inputQueue)
{
	// in the event of no events, leave procedure
	if (inputQueue.empty()) return;

	auto inputKey = inputQueue.front(); // use an intermediate variable so I don't have to call front() too many times

	if (m_bGameOver && inputKey)
	{
		if (m_bGameOver)
		{
			m_bShouldTransitionToGameOver = true;
		}
	}
     if (inputKey == UP_CMD || inputKey == UP_CMD2)
     {
		if (m_currDir != UP && m_currDir != DOWN) m_currDir = UP;
     }
	else if (inputKey == DOWN_CMD || inputKey == DOWN_CMD2)
	{
		if (m_currDir != DOWN && m_currDir != UP) m_currDir = DOWN;
	}
	else if (inputKey == LEFT_CMD || inputKey == LEFT_CMD2)
	{
		if (m_currDir != LEFT && m_currDir != RIGHT) m_currDir = LEFT;
	}
	else if (inputKey == RIGHT_CMD || inputKey == RIGHT_CMD2)
	{
		if (m_currDir != RIGHT && m_currDir != LEFT) m_currDir = RIGHT;
	}	
	
	if (inputKey == PAUSE_CMD)
	{
		RequestStatePushTransition(new Pause_State(m_pContext));
	}
	if (inputKey == ESC_CMD)
	{
		RequestProgramTermination();
	}

#ifdef DEBUG_CONTROLS
	if (inputKey == KILL_CMD)
	{
		m_ruleMonitor.Decrement_Lives();
	}
	if (inputKey == INC_PTS_CMD)
	{
		m_score++;
	}
#endif // DEBUG_CONTROLS


	inputQueue.pop(); // clear out the processed input
}

void Play_State::UpdateState()
{
	if (m_bShouldTransitionToGameOver)
	{
		//sf::Time sleepTime = sf::seconds(2.f);
		//sf::sleep(sleepTime);
		RequestStateTransition(new Game_Over_State{m_pContext, m_score});
	}

	m_hudLives.setString(std::to_string(m_ruleMonitor.Lives_Left()));
	
	if (!m_ruleMonitor.Lives_Left()) // out of lives, signal game over
	{
		m_bGameOver = true;
	}


	if (!m_bGameOver)
	{
		// ********************* Snake Movement Update Code ***************************
		switch (m_currDir)
		{
		case Play_State::NONE:
			break;
		case Play_State::UP:
			m_currentSnakeGraphic = &m_snakeHeadUp;
			m_snkController.Move_Up(m_snake);
			break;
		case Play_State::DOWN:
			m_currentSnakeGraphic = &m_snakeHeadDown;
			m_snkController.Move_Down(m_snake);
			break;
		case Play_State::LEFT:
			m_currentSnakeGraphic = &m_snakeHeadLeft;
			m_snkController.Move_Left(m_snake);
			break;
		case Play_State::RIGHT:
			m_currentSnakeGraphic = &m_snakeHeadRight;
			m_snkController.Move_Right(m_snake);
			break;
		}

		m_currentSnakeGraphic->setPosition(sf::Vector2f{ m_snake.front().x * 20.f, m_snake.front().y * 20.f });

		// :::::::::::::::::::::: END SNAKE MOVEMENT UPDATE CODE :::::::::::::::::::::::::::::::::::::
		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::



		// ******************** Check for self collision **********************
		sf::Vector2i collisionPoint;
		if (m_ruleMonitor.Check_For_Self_Collision(m_snake, collisionPoint))
		{
			auto headIter{ m_snake.begin() };
			std::advance(headIter, 1);
			auto bodyIter{ headIter };
			Snake::iterator cutPoint = std::find(bodyIter, m_snake.end(), collisionPoint);
			if (cutPoint != std::end(m_snake))
			{
				while (m_snake.back() != *cutPoint)
				{
					m_cutTail.push_back(m_snake.back());
					m_snake.pop_back();
				}
				// Now back() should refer to "cutpoint" so we should pop that too
				m_cutTail.push_back(m_snake.back());
				m_snake.pop_back();
			}
			m_ruleMonitor.Decrement_Lives();
			m_bSelfCollisionThisFrame = true;
		}
		else m_bSelfCollisionThisFrame = false;
		// :::::::::::::::::::::::::::::: END CHECK FOR SELF COLLISION ::::::::::::::::::::::::::::
		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::




		// ********** Check for collision with bones ******************
		// the second condition in the if aims to ensure that 2 lives aren't lost for evey tail piece collided with
		// otherwise you hit the tail and lose a life, it turns to bone and then you lose a life from hitting the bone too
		if (m_ruleMonitor.Check_For_Collision(m_snake, m_cutTail) 
			&& !m_bSelfCollisionThisFrame)
		{
			m_ruleMonitor.Decrement_Lives();
		}
		// ::::::::::: END CHECK FOR COLLISION WITH BONES :::::::::::::::::::::::::
		// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


		// **************** Check whether Snake is within bounds or not *******************
		if (!m_ruleMonitor.Within_Bounds(m_snake))
		{
			Snake_Rule_Monitor::Direction dir{ Snake_Rule_Monitor::Direction::NONE };
			m_ruleMonitor.Within_Bounds(m_snake, dir);
			switch (dir)
			{
			case Snake_Rule_Monitor::Direction::UP:
				m_snkController.Teleport_Snake_Head(m_snake, m_snake.front().x, 30);
				break;
			case Snake_Rule_Monitor::Direction::DOWN:
				m_snkController.Teleport_Snake_Head(m_snake, m_snake.front().x, -1);

				break;
			case Snake_Rule_Monitor::Direction::LEFT:
				m_snkController.Teleport_Snake_Head(m_snake, 30, m_snake.front().y);

				break;
			case Snake_Rule_Monitor::Direction::RIGHT:
				m_snkController.Teleport_Snake_Head(m_snake, -1, m_snake.front().y);

				break;
			}

		}
		// ::::::::::: END WITHIN BOUNDS :::::::::::::::::::::::::::::::::::::::::::::::::::
		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::



		// ******************* Check for Apple Collision *****************************
		if (m_ruleMonitor.Check_For_Apple_Collision(m_snake, m_appleCoord))
		{
			m_snkController.Extend_Snake(m_snake);
			m_bSpawnApple = true;
			m_score = m_ruleMonitor.Num_Apples_Collected();
			m_hudScore.setString(std::to_string(m_score));
		}
		// **************** Spawn new apple if needed ******************************
		if (m_bSpawnApple)
		{
			m_appleCoord.x = m_distribution(m_generator);
			m_appleCoord.y = m_distribution(m_generator);
			m_appleGraphic.setPosition(sf::Vector2f{ m_appleCoord.x * 20.f, m_appleCoord.y * 20.f });
			m_bSpawnApple = false;
		}
		// :::::::::::::::::::::::: END APPLE BUSINESS :::::::::::::::::::::::::::::::
		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	}


	m_debugWindow.update(Debug_Info_Bundle{m_snake.front()});


#ifdef DEBUG_OUTPUT
	std::cout << "Snake(x,y) : " << "(" << m_snake.front().x << ", " << m_snake.front().y << ")" << std::endl;
#endif // DEBUG_OUTPUT

}

void Play_State::RenderState(sf::RenderWindow& window)
{	
	window.clear(BRIGHT_COLOR);

	// ***********Draw Stuff in Play Area*************
	window.setView(m_playView);
	window.draw(m_gridOverlay);

	if (!m_bSpawnApple)	window.draw(m_appleGraphic);

	for (auto it = std::next(m_snake.begin()); it != m_snake.end(); ++it)
	{
		m_snakeBod.setPosition(sf::Vector2f{ it->x * 20.f, it->y * 20.f });
		window.draw(m_snakeBod);
	}
	for (auto it : m_cutTail)
	{
		m_cutBod.setPosition(sf::Vector2f{ it.x * 20.f, it.y * 20.f });
		window.draw(m_cutBod);
	}
	window.draw(*m_currentSnakeGraphic);
	if (m_bGameOver)
	{
		m_gameoverGraphic.setPosition(m_gameoverGraphicPos);
		window.draw(m_gameoverGraphic);
		m_gameoverText.setPosition(m_gameoverTextPos);
		window.draw(m_gameoverText);
		m_pressAnyKeyText.setPosition(m_pressAnyKeyTextPos);
		window.draw(m_pressAnyKeyText);
	}
	//:::::::::::::::::::::::::::::::::::::::::::::::

	// **********Draw Stuff in Score Hud**************
	window.setView(m_hudView);
	window.draw(m_hudOverlay);
	window.draw(m_hudScoreLabelText);
	window.draw(m_hudScore);
	window.draw(m_hudLivesLabelText);
	window.draw(m_hudLives);
	//::::::::::::::::::::::::::::::::::::::::::::::::

	window.display();
}
