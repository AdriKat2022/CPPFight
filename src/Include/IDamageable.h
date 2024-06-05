#pragma once

class IDamageable
{
public:
	virtual ~IDamageable() = default;

	virtual void Damage(int) = 0;
	virtual bool IsDead() const = 0 ;
};