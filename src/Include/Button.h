#pragma once

#include "Clickable.h"
#include "IDrawable.h"
#include <SFML/Graphics.hpp>

class Button : public Clickable, public IDrawable
{
public:
	Button(sf::Texture& texture, sf::Vector2f position);

	void Draw(sf::RenderWindow& window) const override;


protected:
	sf::Sprite m_sprite;

};