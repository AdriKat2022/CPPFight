#pragma once

#include <SFML/Graphics.hpp>

// A drawable object is an object that can be drawn to the screen
// It has a sprite but also a position and a texture
// The sprite can be animated with a sprite sheet
// If the sprite sheet dimensions are defined and the texture (or the path) is passed as an argument is a sprite sheet, the function SwitchSprite can be called to switch the sprite
class IDrawable {

public:
	IDrawable() = default;
	IDrawable(const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions = { 1, 0 }, bool centerOrigin = true);
	IDrawable(const sf::Vector2f& position, const std::string& spritePath, sf::Vector2i dimensions = { 1, 0 }, bool centerOrigin = true);
	virtual ~IDrawable() = default;


	virtual void Draw(sf::RenderWindow&) const;
	

	void DefineSpriteSheet(const sf::Vector2i& dimensions);
	void SwitchSprite(int xIndex, int yIndex = 0);

	// Getters
	sf::Sprite& GetSprite();

	bool IsInBoundsOfSprite(sf::Vector2f position) const;

private:

	void CenterOrigin();

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2i m_dimensions;

	int m_xIndex = 0;
	int m_yIndex = 0;
};