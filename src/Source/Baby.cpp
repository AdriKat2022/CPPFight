#include "Baby.h"
#include <format>


Baby::Baby()
{
	m_cryingSoundBuffer.loadFromFile(FilePaths::SOUND_BABY_CRYING);
	m_happySoundBuffer.loadFromFile(FilePaths::SOUND_BABY_LAUGHING);

	m_font.loadFromFile(FilePaths::FONT_DAMAGE);
	m_happinessText.setFont(m_font);
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

	ResetNotification(m_happinessLvl - oldHappiness);

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

void Baby::Update(float deltaTime)
{
	AnimateTextNotification(deltaTime);
}

void Baby::Draw(sf::RenderWindow& window) const
{
	window.draw(m_happinessText);
}

void Baby::ResetNotification(int delta)
{
	// Set text at bottom right of the screen
	m_happinessText.setPosition(
		static_cast<float>(Config::WINDOW_WIDTH - 150),
		static_cast<float>(Config::WINDOW_HEIGHT - 200)
	);

	m_animationTextSpeed = -150;
	if (delta > 0)
	{
		m_happinessText.setString(std::format("+{}%", delta));
		m_happinessText.setFillColor(sf::Color::Green);
	}
	else if (delta < 0)
	{
		m_happinessText.setString(std::format("{}%", delta));
		m_happinessText.setFillColor(sf::Color::Red);
	}
	else
	{
		if (m_happinessLvl == 100)
		{
			m_happinessText.setString("MAX");
			m_happinessText.setFillColor(sf::Color::Green);
		}
		else if (m_happinessLvl == 0)
		{
			m_happinessText.setString("MIN");
			m_happinessText.setFillColor(sf::Color::Red);
		}
	}
}

void Baby::AnimateTextNotification(float deltaTime)
{
	if (m_animationTextSpeed < 0)
	{
		m_animationTextSpeed += deltaTime * 100;
		m_happinessText.move(0, deltaTime * m_animationTextSpeed);
	}
	else
		m_happinessText.setString("");
}