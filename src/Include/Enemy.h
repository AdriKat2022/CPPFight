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

	const std::string& GetName() const;
	int GetAttackPower() const;
	int GetSpeed() const;
	const std::string& GetSpritePath() const;

private:
	const std::string m_name;
	int m_attackPower;
	int m_speed;
	int m_defense;
	const std::string m_spritePath;

	std::vector<Dialogue> m_dialogues;

};