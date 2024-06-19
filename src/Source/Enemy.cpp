#include "Enemy.h"


Enemy::Enemy(const EnemyData& enemyData) :
	Damageable(enemyData.Health),
	m_name(enemyData.Name),
	m_attackPower(enemyData.Attack),
	m_speed(enemyData.Speed),
	m_defense(enemyData.Defense)
{}

Enemy::Enemy(const EnemyData* enemyData) :
	Damageable(enemyData->Health),
	m_name(enemyData->Name),
	m_attackPower(enemyData->Attack),
	m_speed(enemyData->Speed),
	m_defense(enemyData->Defense)
{}

Enemy::Enemy(const std::string& name, int health, int damage) :
	Damageable(health),
	m_name(name),
	m_attackPower(damage)
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
