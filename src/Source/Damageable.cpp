#include "Damageable.h"


Damageable::Damageable(int maxHP) : m_maxHP(maxHP), m_HP(maxHP) {}

int Damageable::GetHP() const {
	return m_HP;
}

void Damageable::Damage(int damage) {
	m_HP -= damage;
	if (m_HP < 0) {
		m_HP = 0;
	}
}

bool Damageable::IsDead() const
{
	return m_HP == 0;
}