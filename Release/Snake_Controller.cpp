#include "Snake_Controller.h"
#include <iostream>

Snake_Controller::Snake_Controller()
{
}

void Snake_Controller::Make_Snake(Snake& snake, Snake_Segment head)
{
	snake.clear();
	snake.push_back(head);
	std::cout << "A snake has been created from Make_Snake" << std::endl;
}

void Snake_Controller::Extend_Snake(Snake& snake)
{
	snake.push_back(Snake_Segment(sf::Vector2i{snake.back().x, snake.back().y}));
	
}

void Snake_Controller::Teleport_Snake_Head(Snake& snake, int x_coord, int y_coord)
{
	snake.front().x = x_coord;
	snake.front().y = y_coord;
}

void Snake_Controller::Move_Up(Snake& snake)
{
	//std::cout << "Move_Up called from inside snake controller at " << this << std::endl;
	Move_Snake(snake, Direction::UP);

}

void Snake_Controller::Move_Down(Snake& snake)
{
	//std::cout << "Move_Down called from inside snake controller at " << this << std::endl;
	Move_Snake(snake, Direction::DOWN);

}
 
void Snake_Controller::Move_Left(Snake& snake)
{
	//std::cout << "Move_Left called from inside snake controller at " << this << std::endl;
	Move_Snake(snake, Direction::LEFT);

}

void Snake_Controller::Move_Right(Snake& snake)
{
	//std::cout << "Move_Right called from inside snake controller at " << this << std::endl;
	Move_Snake(snake, Direction::RIGHT);

}

void Snake_Controller::Move_Up(Snake_Segment& segment)
{
	--segment.y;
}

void Snake_Controller::Move_Down(Snake_Segment& segment)
{
	++segment.y;
}

void Snake_Controller::Move_Left(Snake_Segment& segment)
{
	--segment.x;
}

void Snake_Controller::Move_Right(Snake_Segment& segment)
{
	++segment.x;
}

void Snake_Controller::Move_Snake(Snake& snake, Direction newDir)
{
	sf::Vector2i prevHeadPos{ snake.front() };
	sf::Vector2i prevTailPos;
	sf::Vector2i prevTailPos2;
	switch (newDir)
	{
	case Snake_Controller::NONE:
		break;
	case Snake_Controller::UP:
		Move_Up(snake.front());
		break;
	case Snake_Controller::DOWN:
		Move_Down(snake.front());
		break;
	case Snake_Controller::LEFT:
		Move_Left(snake.front());

		break;
	case Snake_Controller::RIGHT:
		Move_Right(snake.front());
		break;
	}

	if (snake.size() > 1) // snake has a body (not only a head)
	{
		auto it = ++snake.begin();
		prevTailPos = *it;
		*it = prevHeadPos;
		++it;
		// the for loop updates all snake body segments to be the former position of the segment in front of it
		while(it != snake.end())
		{
			prevTailPos2 = *it;
			*it = prevTailPos;
			prevTailPos = prevTailPos2;
			++it;

		}

		//for (auto current = snake.rend(); current != snake.rbegin(); /* Do nothing */)
		//{
		//	++current; // Unfortunately, you now need this here
		//	current->x = std::prev(current)->x;
		//	current->y = std::prev(current)->y;
		//}
	}

	

	
}