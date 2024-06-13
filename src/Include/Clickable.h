#pragma once

#include "GameRun.h"
#include <SFML/Graphics.hpp>

class Clickable
{
public:
	static bool IsMousePressed;

	virtual ~Clickable() = default;

	virtual bool IsInBounds(sf::Vector2f position) const = 0;
	virtual void OnClick(sf::Vector2f position) = 0;

	virtual void Update(GameRun& gameRun, float deltaTime) = 0;

	void SetActive(bool isActive);
	bool IsActive() const;


private:
	bool m_isActive = true;

};