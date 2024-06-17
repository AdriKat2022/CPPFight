#pragma once

#include "EnemyData.h"
#include "Damageable.h"
#include "Dialogue.h"
#include <string>
#include <vector>

class Enemy : public Damageable {

public:
	explicit Enemy(const EnemyData&);
	explicit Enemy(const EnemyData*);
	Enemy(const std::string& name, int health, int damage);

	const std::string& GetName() const;
	int GetAttackPower() const;

private:
	std::string m_name;
	int m_attackPower;

	std::vector<Dialogue> m_dialogues;

};