#include "Baby.h"

Baby::Baby() {
	// Create the baby
}

float Baby::GetMult() const
{
	return 0.0f;
}

void Baby::Modify(int modifier)
{
	m_happinessLvl += modifier;
}
