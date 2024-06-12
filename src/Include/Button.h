#pragma once

#include "Clickable.h"
#include "IDrawable.h"
#include <SFML/Graphics.hpp>

class Button : public Clickable, public IDrawable
{
public:
	using IDrawable::IDrawable;

	void SetActive(bool isActive);
	bool IsActive() const;

private:
	bool m_isActive = true;

};