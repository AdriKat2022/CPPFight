#pragma once

#include <SFML/Graphics.hpp>


class IDrawable {

public:
	virtual ~IDrawable() = default;

	virtual void Draw(sf::RenderWindow&) = 0;
};