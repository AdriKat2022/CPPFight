#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>

class Clickable
{
public:
	virtual bool IsInBounds(sf::Vector2i position);
	virtual void OnClick(sf::Vector2i position) = 0;


private:
	Game* m_gameContext;
};