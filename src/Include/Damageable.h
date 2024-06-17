#pragma once

class Damageable
{
public:
	explicit Damageable(int maxHP);
	virtual ~Damageable() = default;


	int GetHP() const;
	int GetMaxHP() const;

	// Could be overriden by derived classes (e.g. to add some (sound)effects)
	virtual void Damage(int);
	virtual bool IsDead() const;


private:
	int m_maxHP;
	int m_HP;

};