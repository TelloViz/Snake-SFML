/* This file defines a class that is used to manipulate the snake data structure. You provide any snake object to the Snake_Controller and it can
perform a command on your snake object */



#pragma once
#include "IReceiver.hpp"
#include <list>
#include <iterator>
#include <SFML/System/Vector2.hpp>


typedef		sf::Vector2i				Snake_Segment;
typedef		std::list<Snake_Segment>		Snake;


class Snake_Controller : public IReceiver
{
	enum Direction { NONE = 0, UP, DOWN, LEFT, RIGHT };

public:
	Snake_Controller();	

	void Make_Snake(Snake& snake, Snake_Segment head);

     void Extend_Snake(Snake& snake);

     void Teleport_Snake_Head(Snake& snake, int x_coord, int y_coord);


	///////////////////////////////////////////////////////////
    /// \brief Calculates and fills snake object with new coordinates in the upward direction
    /// input:  snake : Snake& (the snake object to alter)
    /// output: none
    ////////////////////////////////////////////////////////////
	void Move_Up(Snake& snake);

     ///////////////////////////////////////////////////////////
    /// \brief Calculates and fills snake object with new coordinates in the downward direction
    /// input:  snake : Snake& (the snake object to alter)
    /// output: none
    ////////////////////////////////////////////////////////////
	void Move_Down(Snake& snake);

     ///////////////////////////////////////////////////////////
    /// \brief Calculates and fills snake object with new coordinates in the Leftward direction
    /// input:  snake : Snake& (the snake object to alter)
    /// output: none
    ////////////////////////////////////////////////////////////
	void Move_Left(Snake& snake);

     ///////////////////////////////////////////////////////////
     /// \brief Calculates and fills snake object with new coordinates in the Rightward direction
     /// input:  snake : Snake& (the snake object to alter)
     /// output: none
     ////////////////////////////////////////////////////////////
	void Move_Right(Snake& snake);


	// Use these to move just one snake segment
	void Move_Up(Snake_Segment& segment);
	void Move_Down(Snake_Segment& segment);
	void Move_Left(Snake_Segment& segment);
	void Move_Right(Snake_Segment& segment);

	void Move_Snake(Snake& snake,Direction newDir);

private:
	const sf::Vector2i DEFAULT_SNAKE_POS{0, 0};
};

