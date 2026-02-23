// this class monitors the play state for any game related state changes or rule violations

#pragma once
#include "Snake.h"
#include <vector>


class Snake_Rule_Monitor
{
public:

	enum class Direction { NONE = 0, UP, DOWN, LEFT, RIGHT };

	Snake_Rule_Monitor() = default;
	Snake_Rule_Monitor(unsigned x_grid_dim, unsigned y_grid_dim);

	bool Within_Bounds(const Snake& snake) const;
	bool Within_Bounds(const Snake& snake, Snake_Rule_Monitor::Direction& dir);

	bool Check_For_Self_Collision(const Snake& snake, sf::Vector2i& collisionPoint);
	bool Check_For_Collision(const Snake& snake, std::vector<sf::Vector2i> obst);
	bool Check_For_Apple_Collision(const Snake& snake, const sf::Vector2i& appleCoord);

	unsigned Lives_Left() const { return m_lives; }

	unsigned Num_Apples_Collected() const { return m_applesCollected; }

	void Increment_Lives() { ++m_lives; }
	void Decrement_Lives() { --m_lives; }
private: // private methods

	void incrementApplesCollected() { ++m_applesCollected; }


private:
	unsigned m_xDim;
	unsigned m_yDim;

	unsigned m_lives;

	unsigned m_applesCollected;

};

