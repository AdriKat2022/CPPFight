#include "Baby.h"

Baby::Baby() {
	// Create the baby
}

float Baby::GetMult() const
{
	if (m_happinessLvl < 0) {
		//Erreur?
		return 0.0f;
	}
	else if (m_happinessLvl<10)
	{
		return 0.25f;
	}
	else if (m_happinessLvl < 20)
	{
		return 0.5f;
	}
	else if (m_happinessLvl < 30)
	{
		return 1.0f;
	}
	else if (m_happinessLvl< 40)
	{
		return 1.25f;
	}
	else if (m_happinessLvl< 50)
	{
		return 1.5f;
	}
	else if (m_happinessLvl < 60)
	{
		return 1.75f;
	}
	else if (m_happinessLvl < 70)
	{
		return 2.0f;
	}
	else if (m_happinessLvl < 80)
	{
		return 2.25f;
	}
	else if (m_happinessLvl < 90)
	{
		return 2.5f;
	}
	else 
	{
		return 3.0f;
	}
}

void Baby::Modify(int modifier)
{
	m_happinessLvl += modifier;
}
