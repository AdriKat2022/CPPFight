#pragma once

#include "IDamageable.h"
#include "Dialogue.h"
#include <string>
#include <vector>

class Enemy : public IDamageable {

public:
	Enemy(std::string name, int health, int damage);
	~Enemy();

	std::string GetName() const;

	// IDamageable
	void Damage(int);
	bool IsDead() const;

private:
	int m_maxHealth;
	int m_health;
	int m_power;

	std::string m_name;
	std::vector<Dialogue> m_dialogues;

};