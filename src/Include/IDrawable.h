#pragma once

#include <SFML/Graphics.hpp>


class IDrawable {

public:
	IDrawable() = default;
	IDrawable(const sf::Vector2f& position, const sf::Texture& texture);
	IDrawable(const sf::Vector2f& position, const std::string& spritePath);

	virtual ~IDrawable() = default;


	virtual void Draw(sf::RenderWindow&) const;

	// Getters
	sf::Sprite& GetSprite();

	bool IsInBoundsOfSprite(sf::Vector2f position) const;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};