#pragma once

#include "IDamageable.h"
#include <string>

class Player : public IDamageable {

public:
	Player();

	// IDamageable
	void Damage(int) override;
	bool IsDead() const override;

private:
	int m_maxHP;
	int m_HP;
	std::string m_name;

};