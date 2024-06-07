#pragma once

#include "Damageable.h"
#include <string>

class Player : public Damageable {

public:
	explicit Player(const std::string& playerName, int maxHP);

	const std::string& GetName() const;

private:
	std::string m_name;
};