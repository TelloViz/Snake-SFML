#include "Snake_Rule_Monitor.h"
#include <iostream>

Snake_Rule_Monitor::Snake_Rule_Monitor(unsigned x_grid_dim, unsigned y_grid_dim)
	: m_xDim{x_grid_dim}, 
	  m_yDim{y_grid_dim},
	  m_lives{3},
	  m_applesCollected{0}
{}

bool Snake_Rule_Monitor::Within_Bounds(const Snake& snake) const
{
	if (snake.front().x < m_xDim &&
		snake.front().x >= 0 &&
		snake.front().y < m_yDim  &&
		snake.front().y > 0)
		return true;
	else 
		return false;
}

bool Snake_Rule_Monitor::Within_Bounds(const Snake& snake, Direction& dir)
{
	if (snake.front().x < 0)
	{
		dir = Direction::LEFT;
	}
	else if (snake.front().x >= m_xDim)
	{
		dir = Direction::RIGHT;
	}
	else if (snake.front().y < 0)
	{
		dir = Direction::UP;
	}
	else if (snake.front().y >= m_yDim)
	{
		dir = Direction::DOWN;
	}
	else
	{
		dir = Direction::NONE;
		return false;
	}

	return true;
}

bool Snake_Rule_Monitor::Check_For_Self_Collision(const Snake& snake, sf::Vector2i& collisionPoint)
{
	auto head = snake.front();
	for (auto it = ++snake.begin(); it != snake.end(); ++it)
	{
		if (head == *it)
		{			
			collisionPoint.x = head.x;
			collisionPoint.y = head.y;
			return true;
		}
	}
	collisionPoint.x = -1;
	collisionPoint.y = -1;
	return false;
}

bool Snake_Rule_Monitor::Check_For_Collision(const Snake& snake, std::vector<sf::Vector2i> obst)
{
	for (auto i : obst)
	{
		if (snake.front() == i)
		{
			return true;
		}
	}
	return false;
}

bool Snake_Rule_Monitor::Check_For_Apple_Collision(const Snake& snake, const sf::Vector2i& appleCoord)
{
	if (snake.front().x == appleCoord.x && snake.front().y == appleCoord.y)
	{
		incrementApplesCollected();
		return true;
	}
	else return false;
}

