#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>

class Clickable
{
public:
	virtual ~Clickable() = default;

	virtual bool IsInBounds(sf::Vector2f position) = 0;
	virtual void OnClick(sf::Vector2f position) = 0;
};