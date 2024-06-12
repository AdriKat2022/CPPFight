#pragma once

#include <SFML/Graphics.hpp>


class IDrawable {

public:
	IDrawable() = default;
	IDrawable(const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions = { 1, 0 });
	IDrawable(const sf::Vector2f& position, const std::string& spritePath, sf::Vector2i dimensions = { 1, 0 });

	virtual ~IDrawable() = default;


	virtual void Draw(sf::RenderWindow&) const;
	

	void SetDimensions(const sf::Vector2i& dimensions);
	void SwtichSprite(int xIndex, int yIndex = 0);

	// Getters
	sf::Sprite& GetSprite();

	bool IsInBoundsOfSprite(sf::Vector2f position) const;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2i m_dimensions;

	int m_xIndex = 0;
	int m_yIndex = 0;
};