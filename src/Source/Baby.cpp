#include "Baby.h"

Baby::Baby() {
	m_cryingSoundBuffer.loadFromFile(FilePaths::SOUND_BABY_CRYING);
	m_happySoundBuffer.loadFromFile(FilePaths::SOUND_BABY_LAUGHING);
}

float Baby::GetMult() const
{
	if (m_happinessLvl < 0) {
		//Erreur?
		return 0.0f;
	}
	else if (m_happinessLvl < 10)
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
	else if (m_happinessLvl < 40)
	{
		return 1.25f;
	}
	else if (m_happinessLvl < 50)
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
	else if (m_happinessLvl < 100)
	{
		return 3.0f;
	}
	else
	{
		return 3.5f;
	}
}

void Baby::Modify(int modifier, bool playSound)
{
	m_happinessLvl += modifier;

	if (m_happinessLvl > 100)
	{
		m_happinessLvl = 100;
	}
	else if (m_happinessLvl < 0)
	{
		m_happinessLvl = 0;
	}

	if (!playSound) return;

	if (modifier > 0)
	{
		// Play happy sound
	}
	else if (modifier < 0)
	{
		// Play sad sound
	}
}

int Baby::GetHappiness() const
{
	return m_happinessLvl;
}