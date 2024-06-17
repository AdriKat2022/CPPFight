#include "IDrawable.h"

#include <iostream>

IDrawable::IDrawable(const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions, bool centerOrigin) :
	m_texture(texture),
	m_sprite(texture)
{
	m_sprite.setPosition(position);
	DefineSpriteSheet(dimensions);

	if (centerOrigin)
		CenterOrigin();
}

IDrawable::IDrawable(const sf::Vector2f& position, const std::string& spritePath, sf::Vector2i dimensions, bool centerOrigin)
{
	m_texture.loadFromFile(spritePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	DefineSpriteSheet(dimensions);

	if(centerOrigin)
		CenterOrigin();
}

void IDrawable::Draw(sf::RenderWindow& renderWindow) const
{
	renderWindow.draw(m_sprite);
}

void IDrawable::DefineSpriteSheet(const sf::Vector2i& dimensions)
{
	if (dimensions.x <= 0 || dimensions.y <= 0)
	{
		std::cout << "Warning: Dimensions cannot be negative or equal to zero. Setting to { 1, 1 }" << std::endl;

		m_dimensions = { 1, 1 };

		return;
	}

	m_dimensions = dimensions;

	SwitchSprite(m_xIndex, m_yIndex);
}

void IDrawable::SwitchSprite(int xIndex, int yIndex)
{
	std::cout << "Switching sprite to " << xIndex << ", " << yIndex << std::endl;

	m_xIndex = xIndex;
	m_yIndex = yIndex;

	// Set the texture rect
	m_sprite.setTextureRect(sf::IntRect(
		m_xIndex * m_sprite.getTexture()->getSize().x / m_dimensions.x,
		m_yIndex * m_sprite.getTexture()->getSize().y / m_dimensions.y,
		m_sprite.getTexture()->getSize().x / m_dimensions.x,
		m_sprite.getTexture()->getSize().y / m_dimensions.y
	));
	

	//std::cout << m_sprite.getTextureRect().left << ", " << m_sprite.getTextureRect().top << ", " << m_sprite.getTextureRect().width << ", " << m_sprite.getTextureRect().height << std::endl;
}

sf::Sprite& IDrawable::GetSprite()
{
	return m_sprite;
}

bool IDrawable::IsInBoundsOfSprite(sf::Vector2f position) const
{
	return m_sprite.getGlobalBounds().contains(position);
}

void IDrawable::CenterOrigin()
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}