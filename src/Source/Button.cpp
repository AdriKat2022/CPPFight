#include "Button.h"


void Button::SetActive(bool isActive)
{
	m_isActive = isActive;
}

bool Button::IsActive() const
{
	return m_isActive;
}
