#include "Enemy.h"

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