#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Configs.h"

class Baby {

public:
	Baby();

	float GetMult() const;
	int GetHappiness() const;
	void Modify(int happiness, bool playSound = true);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window) const;

private:

	void ResetNotification(int delta);
	void AnimateTextNotification(float deltaTime);


	float m_animationTextSpeed = 0.f;

	sf::Text m_happinessText;
	sf::Font m_font;

	sf::SoundBuffer m_happySoundBuffer;
	sf::SoundBuffer m_cryingSoundBuffer;
	sf::Sound m_source;

	int m_happinessLvl = Config::DEFAULT_BABY_START_HAPPINESS; // From 0 to 100
};