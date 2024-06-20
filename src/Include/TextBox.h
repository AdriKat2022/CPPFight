#pragma once

#include "IDrawable.h"
#include "Dialogue.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <sstream>


class TextBox {
	
public:
	explicit TextBox(const sf::Vector2f& position);

	void SetVisible(const bool);
	void Show();
	void Hide();
	void SetDialogue(Dialogue& dialogue);
	void ShowNext();
	void Update(float deltaTime);
	
	void Draw(sf::RenderWindow&) const;

	void LockTextBox(bool lock);

	bool IsFinished() const;

private:
	size_t m_remainingDialogues = 0;

	bool m_lastFrameClick = false;
	bool m_isVisible = false;
	bool m_hasClickedAfterFinish = true;
	bool m_textBoxLocked = true;

	Dialogue* m_currentDialogue;
	sf::Color m_backgroundColor;
	sf::Vector2f m_size = {300, 200};
	std::string m_string;
	sf::Text m_text;
	sf::RectangleShape m_textBoxBackground;
	sf::Font m_undertale_font;

};