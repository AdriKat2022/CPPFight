#pragma once

#include <SFML/Graphics.hpp>


class IDrawable {

public:
	virtual ~IDrawable() = default;

	virtual void Draw(sf::RenderWindow&) const = 0;


protected:
	sf::Sprite m_sprite;

};