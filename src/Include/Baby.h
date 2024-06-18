#pragma once

#include <SFML/Audio.hpp>
#include "Configs.h"

class Baby {

public:
	Baby();

	float GetMult() const;
	int GetHappiness() const;
	void Modify(int happiness, bool playSound = true);

private:

	sf::SoundBuffer m_happySoundBuffer;
	sf::SoundBuffer m_cryingSoundBuffer;
	sf::Sound m_happySound;
	sf::Sound m_cryingSound;

	int m_happinessLvl = Config::DEFAULT_BABY_START_HAPPINESS; // From 0 to 100
};