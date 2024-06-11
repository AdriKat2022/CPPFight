#pragma once

#include "Damageable.h"
#include "IDrawable.h"
#include <string>

class Player : public Damageable, public IDrawable {

public:
	explicit Player(const std::string& playerName, int maxHP);

	void Draw(sf::RenderWindow&) const override;

	const std::string& GetName() const;

private:
	std::string m_name;
};