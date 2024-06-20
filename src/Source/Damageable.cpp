#include "Damageable.h"


Damageable::Damageable(int maxHP) : m_maxHP(maxHP), m_HP(maxHP) {}

int Damageable::GetHP() const {
	return m_HP;
}

int Damageable::GetMaxHP() const {
	return m_maxHP;
}

void Damageable::setMaxHP(const int HP)
{
	m_maxHP = HP;
}

void Damageable::Damage(int damage) {
	m_HP -= damage;
	if (m_HP < 0) {
		m_HP = 0;
	}
	if (m_HP > m_maxHP)
	{
		m_HP = m_maxHP;
	}
}

bool Damageable::IsDead() const
{
	return m_HP == 0;
}