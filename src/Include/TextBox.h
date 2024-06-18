#pragma once

#include "IDrawable.h"
#include "Dialogue.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <sstream>


class TextBox {
	
public:
	TextBox();

	void SetVisible(const bool);
	void Show() const;
	void Hide() const;
	void SetDialogue(Dialogue& dialogue);
	void SetString(const std::string& string);
	void SetPosition(float x, float y);
	void ShowNext();
	void Update();
	
	void Draw(sf::RenderWindow&) const;

	bool IsFinished() const;

private:
	size_t m_remainingDialogues = 0;
	bool m_isVisible;
	bool m_hasClickedAfterFinish = false;
	Dialogue* m_currentDialogue;
	sf::Color m_backgroundColor;
	sf::Vector2f m_position;
	sf::Vector2f m_size = {300, 200};
	std::string m_string;
	sf::Text m_text;
	sf::RectangleShape m_background_text;
	sf::Font m_undertale_font;

};