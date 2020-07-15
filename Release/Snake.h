/* This file describes a Snake. A snake is simply a container that holds snake segments. Snake segments are essentially just coordinates that represent
	a single segment of the snake. These coordinates can be used directly in a grid system or in a conversion to screen pixels*/


#pragma once
#include <list>
#include <iterator>
#include <SFML/System/Vector2.hpp>





typedef sf::Vector2i Snake_Segment;

typedef std::list<Snake_Segment> Snake;

