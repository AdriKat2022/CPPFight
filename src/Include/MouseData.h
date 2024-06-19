#pragma once

#include <SFML/Graphics.hpp>

// not ideal, but it's a quick way to get the mouse data
class MouseData
{
public:
	static bool IsMousePressed;
	static sf::Vector2f MousePosition;
};