#include "Enemy.h"


Enemy::Enemy(const EnemyData& enemyData) :
	Damageable(enemyData.Health),
	m_name(enemyData.Name),
	m_attackPower(enemyData.Attack),
	m_speed(enemyData.Speed),
	m_defense(enemyData.Defense),
	m_spritePath(enemyData.SpritePath)
{}

Enemy::Enemy(const EnemyData* enemyData) :
	Damageable(enemyData->Health),
	m_name(enemyData->Name),
	m_attackPower(enemyData->Attack),
	m_speed(enemyData->Speed),
	m_defense(enemyData->Defense),
	m_spritePath(enemyData->SpritePath)
{}

const std::string& Enemy::GetName() const
{
	return m_name;
}

int Enemy::GetAttackPower() const
{
	return m_attackPower;
}

int Enemy::GetSpeed() const
{
	return m_speed;
}

const std::string& Enemy::GetSpritePath() const
{
	return m_spritePath;
}
