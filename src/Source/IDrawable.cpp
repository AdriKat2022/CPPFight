#include "IDrawable.h"

IDrawable::IDrawable(const sf::Vector2f& position, const sf::Texture& texture) :
	m_texture(texture),
	m_sprite(texture)
{
	m_sprite.setPosition(position);
}

IDrawable::IDrawable(const sf::Vector2f& position, const std::string& spritePath)
{
	sf::Texture texture;
	texture.loadFromFile(spritePath);
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position);
}

void IDrawable::Draw(sf::RenderWindow& renderWindow) const
{
	renderWindow.draw(m_sprite);
}

sf::Sprite& IDrawable::GetSprite()
{
	return m_sprite;
}

bool IDrawable::IsInBoundsOfSprite(sf::Vector2f position) const
{
	return m_sprite.getGlobalBounds().contains(position);
}