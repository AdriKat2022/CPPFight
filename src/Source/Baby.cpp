#include "Baby.h"
#include <format>
#include <iostream>


Baby::Baby()
{
	// Load sounds
	m_cryingSoundBuffer.loadFromFile(FilePaths::SOUND_BABY_CRYING);
	m_happySoundBuffer.loadFromFile(FilePaths::SOUND_BABY_LAUGHING);

	// Load fonts
	m_font.loadFromFile(FilePaths::FONT_DAMAGE);
	m_statsFont.loadFromFile(FilePaths::FONT_STATS);

	// Load the baby name and happiness text
	m_happinessNotificationText.setFont(m_font);
	m_babyName.setFont(m_statsFont);
	m_babyName.setCharacterSize(15);
	m_babyName.setString(Config::DEFAULT_BABY_NAME);
	m_babyName.setPosition({
		static_cast<float>(Config::WINDOW_WIDTH) - Anchors::BABY_NAME_FROM_BOTTOM_RIGHT[0] - m_babyName.getGlobalBounds().width/2,
		static_cast<float>(Config::WINDOW_HEIGHT) - Anchors::BABY_NAME_FROM_BOTTOM_RIGHT[1]
		});

	m_babyName.setFillColor(sf::Color::White);

	// Happiness meter
	m_background_happiness_baby.setFillColor(sf::Color::Magenta);
	m_happiness_bar_baby.setFillColor(sf::Color::Green);
	m_background_happiness_baby.setSize({
		Sizes::BABY_HAPPINESS_BAR_BG[0],
		Sizes::BABY_HAPPINESS_BAR_BG[1]
		});
	m_background_happiness_baby.setPosition({
		static_cast<float>(Config::WINDOW_WIDTH) - Anchors::BABY_HAPPINESS_BAR_FROM_BOTTOM_RIGHT_BG[0] - m_background_happiness_baby.getGlobalBounds().width / 2,
		static_cast<float>(Config::WINDOW_HEIGHT) - Anchors::BABY_HAPPINESS_BAR_FROM_BOTTOM_RIGHT_BG[1] - m_background_happiness_baby.getGlobalBounds().height
		});
	m_happiness_bar_baby.setSize({
		Sizes::BABY_HAPPINESS_BAR[0],
		Sizes::BABY_HAPPINESS_BAR[1]
		});
	m_happiness_bar_baby.setPosition({
		static_cast<float>(Config::WINDOW_WIDTH) - Anchors::BABY_HAPPINESS_BAR_FROM_BOTTOM_RIGHT[0] - m_happiness_bar_baby.getGlobalBounds().width / 2,
		static_cast<float>(Config::WINDOW_HEIGHT) - Anchors::BABY_HAPPINESS_BAR_FROM_BOTTOM_RIGHT[1] - m_happiness_bar_baby.getGlobalBounds().height
			});

	// Happiness Mult Text
	m_currentDamageMultText.setString(std::format("{}{}", Config::HAPPINESS_MULT_PRE_TEXT, GetMult()));
	m_currentDamageMultText.setFont(m_statsFont);
	m_currentDamageMultText.setCharacterSize(15);
	m_currentDamageMultText.setPosition({
		Anchors::BABY_HAPPINESS_MULT_TEXT_FROM_TOP_RIGHT[0],
		Anchors::BABY_HAPPINESS_MULT_TEXT_FROM_TOP_RIGHT[1]
		});
	m_currentDamageMultText.setFillColor(sf::Color::White);

	// Load the sprite
	m_warningTexture.loadFromFile(FilePaths::WARNING_SIGN);
	m_warningSprite.setTexture(m_warningTexture);
	m_warningSprite.setScale(2,2);
	m_warningSprite.setColor(sf::Color::Transparent);
	m_warningSprite.setPosition({
		m_currentDamageMultText.getGlobalBounds().left + m_currentDamageMultText.getGlobalBounds().width + Anchors::BABY_WARNING_SIGN_FROM_MULT_TEXT[0],
		m_currentDamageMultText.getGlobalBounds().top + m_currentDamageMultText.getGlobalBounds().height/2 - m_warningSprite.getGlobalBounds().height/2 + Anchors::BABY_WARNING_SIGN_FROM_MULT_TEXT[1]
		});

	m_currentDamageMult = GetMult();
}

void Baby::Update(float deltaTime)
{
	AnimateTextNotification(deltaTime);
	AnimateWarning(deltaTime);
}

void Baby::Draw(sf::RenderWindow& window) const
{
	window.draw(m_background_happiness_baby);
	window.draw(m_happiness_bar_baby);

	window.draw(m_happinessNotificationText);
	window.draw(m_babyName);
	window.draw(m_currentDamageMultText);
	window.draw(m_warningSprite);
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
	if(modifier == 0) return;

	int oldHappiness = m_happinessLvl;
	m_happinessLvl += modifier;

	if (m_happinessLvl > 100)
	{
		m_happinessLvl = 100;
	}
	else if (m_happinessLvl < 0)
	{
		m_happinessLvl = 0;
	}

	MakeWarning(GetMult() - m_currentDamageMult);
	UpdateHappinessTextMult();
	MakeNotification(m_happinessLvl - oldHappiness);
	UpdateHappinessBar();

	m_currentDamageMult = GetMult();

	if (!playSound) return;

	if (modifier > 0)
	{
		m_source.setBuffer(m_happySoundBuffer);
	}
	else if (modifier < 0)
	{
		m_source.setBuffer(m_cryingSoundBuffer);
	}
	m_source.setVolume(50 * Config::GLOBAL_VOLUME_MULT);
	m_source.play();
}

int Baby::GetHappiness() const
{
	return m_happinessLvl;
}

void Baby::MakeNotification(int delta)
{
	// Redefine the text
	m_animationTextSpeed = -150;
	if (delta > 0)
	{
		m_happinessNotificationText.setString(std::format("+{}%", delta));
		m_happinessNotificationText.setFillColor(sf::Color::Green);
	}
	else if (delta < 0)
	{
		m_happinessNotificationText.setString(std::format("{}%", delta));
		m_happinessNotificationText.setFillColor(sf::Color::Red);
	}
	else
	{
		if (m_happinessLvl == 100)
		{
			m_happinessNotificationText.setString("MAX");
			m_happinessNotificationText.setFillColor(sf::Color::Green);
		}
		else if (m_happinessLvl == 0)
		{
			m_happinessNotificationText.setString("MIN");
			m_happinessNotificationText.setFillColor(sf::Color::Red);
		}
	}

	// Set text at bottom right of the screen
	m_happinessNotificationText.setPosition(
		m_background_happiness_baby.getGlobalBounds().left + m_background_happiness_baby.getGlobalBounds().width/2 - m_happinessNotificationText.getGlobalBounds().width / 2,
		m_background_happiness_baby.getGlobalBounds().top
	);
}

void Baby::UpdateHappinessTextMult()
{
	m_currentDamageMultText.setString(std::format("{}{}", Config::HAPPINESS_MULT_PRE_TEXT,GetMult()));
}

void Baby::UpdateHappinessBar()
{
	m_happiness_bar_baby.setSize({
		Sizes::BABY_HAPPINESS_BAR[0] ,
		Sizes::BABY_HAPPINESS_BAR[1] * static_cast<float>(m_happinessLvl) / 100.f
		});


	m_happiness_bar_baby.setPosition({
		static_cast<float>(Config::WINDOW_WIDTH) - Anchors::BABY_HAPPINESS_BAR_FROM_BOTTOM_RIGHT[0] - m_happiness_bar_baby.getGlobalBounds().width / 2,
		static_cast<float>(Config::WINDOW_HEIGHT) - Anchors::BABY_HAPPINESS_BAR_FROM_BOTTOM_RIGHT[1] - m_happiness_bar_baby.getGlobalBounds().height
		});
}

void Baby::MakeWarning(float deltaMult)
{
	if (GetMult() <= .25f) {
		m_currentColor = sf::Color{Colors::DANGER_COLOR[0], Colors::DANGER_COLOR[1], Colors::DANGER_COLOR[2]};
		m_nWarningLoops = 8;
		m_warningTimerReset = 0.06f;
		m_warnState = false;
		return;
	}
	
	if(deltaMult == 0) return;

	m_nWarningLoops = 8;
	m_warningTimerReset = 0.06f;
	m_warnState = false;

	if (deltaMult > 0)
		m_currentColor = sf::Color{Colors::INFO_COLOR[0], Colors::INFO_COLOR[1], Colors::INFO_COLOR[2]};
	else
		m_currentColor = sf::Color{Colors::WARNING_COLOR[0], Colors::WARNING_COLOR[1], Colors::WARNING_COLOR[2]};
	

}

void Baby::AnimateTextNotification(float deltaTime)
{
	if (m_animationTextSpeed < 0)
	{
		m_animationTextSpeed += deltaTime * 150;
		m_happinessNotificationText.move(0, deltaTime * m_animationTextSpeed);
	}
	else
		m_happinessNotificationText.setString("");
}

void Baby::AnimateWarning(float deltaTime)
{
	if (m_nWarningLoops <= 0)
		return;

	m_warningTimer -= deltaTime;

	if (m_warningTimer <= 0)
	{
		m_warningTimer = m_warningTimerReset;
		m_warnState = !m_warnState;
		m_nWarningLoops--;
		m_warningSprite.setColor(m_warnState ? m_currentColor : sf::Color::Transparent);

		if(m_nWarningLoops == 0)
			m_warningSprite.setColor(sf::Color::Transparent);
	}
	
}