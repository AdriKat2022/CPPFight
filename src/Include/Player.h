#pragma once

#include "Damageable.h"
#include "IDrawable.h"
#include <string>

class Player : public Damageable, public IDrawable {

public:
	Player() = default;
	explicit Player(const std::string& playerName, int maxHP);

	void Draw(sf::RenderWindow&) const override;

	const std::string& GetName() const;
	void SetName(std::string);

private:
	std::string m_name;
};