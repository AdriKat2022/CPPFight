#include "IDrawable.h"

#include <iostream>

IDrawable::IDrawable(const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions) :
	m_texture(texture),
	m_sprite(texture)
{
	m_sprite.setPosition(position);
	SetDimensions(dimensions);
}

IDrawable::IDrawable(const sf::Vector2f& position, const std::string& spritePath, sf::Vector2i dimensions)
{
	sf::Texture texture;
	texture.loadFromFile(spritePath);
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position);
	SetDimensions(dimensions);
}

void IDrawable::Draw(sf::RenderWindow& renderWindow) const
{
	renderWindow.draw(m_sprite);
}

void IDrawable::SetDimensions(const sf::Vector2i& dimensions)
{
	if (dimensions.x < 0 || dimensions.y < 0 || (dimensions.x == 0 && dimensions.y == 0))
	{
		std::cout << "Warning: Dimensions cannot be negative or both equal to zero. Setting to { 1, 0 }" << std::endl;

		m_dimensions = { 1, 0 };

		return;
	}

	m_dimensions = dimensions;
}

void IDrawable::SwtichSprite(int xIndex, int yIndex)
{
	m_xIndex = xIndex;
	m_yIndex = yIndex;

	m_sprite.setTextureRect(sf::IntRect(
		m_xIndex / m_dimensions.x * m_texture.getSize().x,
		m_yIndex / m_dimensions.y * m_texture.getSize().y,
		(m_xIndex+1) / m_dimensions.x * m_texture.getSize().x,
		(m_xIndex+1) / m_dimensions.x * m_texture.getSize().y
	));
}

sf::Sprite& IDrawable::GetSprite()
{
	return m_sprite;
}

bool IDrawable::IsInBoundsOfSprite(sf::Vector2f position) const
{
	return m_sprite.getGlobalBounds().contains(position);
}