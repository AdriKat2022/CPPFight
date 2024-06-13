#include "Clickable.h"

bool Clickable::IsMousePressed = false;

void Clickable::SetActive(bool isActive) {
	m_isActive = isActive;
}

bool Clickable::IsActive() const {
	return m_isActive;
}	