#include "Button.h"

bool Button::IsInBounds(sf::Vector2f position) const
{
	return m_isActive && GetSprite()->getGlobalBounds().contains(position);
}


void Button::SetActive(bool isActive)
{
	m_isActive = isActive;
}

bool Button::IsActive() const
{
	return m_isActive;
}
