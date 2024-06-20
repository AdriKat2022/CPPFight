#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Configs.h"
#include "Shaker.h"

class Baby {

public:
	Baby();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window) const;

	float GetMult() const;
	int GetHappiness() const;
	void Modify(int happiness, bool playSound = true);


private:
	void UpdateHappinessTextMult();
	void UpdateHappinessBar();
	void MakeNotification(int delta);
	void MakeWarning(float deltaMult);
	void AnimateTextNotification(float deltaTime);
	void AnimateWarning(float deltaTime);

	bool m_warnState = false;

	float m_warningTimerReset = 0.14f;
	float m_warningTimer = 0.f;
	float m_currentDamageMult = 1.0f;
	float m_animationTextSpeed = 0.f;

	sf::Color m_currentColor = sf::Color::White;

	sf::Sprite m_warningSprite;
	sf::Texture m_warningTexture;

	sf::RectangleShape m_background_happiness_baby;
	sf::RectangleShape m_happiness_bar_baby;

	Shaker m_multTextShaker;
	sf::Text m_currentDamageMultText;
	sf::Text m_babyName;
	sf::Font m_statsFont;

	sf::Text m_happinessNotificationText;
	sf::Font m_font;

	sf::SoundBuffer m_happySoundBuffer;
	sf::SoundBuffer m_cryingSoundBuffer;
	sf::Sound m_source;

	int m_happinessLvl = Config::DEFAULT_BABY_START_HAPPINESS; // From 0 to 100
	int m_nWarningLoops = 4;
};