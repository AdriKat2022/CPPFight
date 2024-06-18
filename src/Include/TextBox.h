#pragma once

#include "IDrawable.h"
#include "Dialogue.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <sstream>

class TextBox : public IDrawable {
	
public:
	TextBox();

	void SetVisible(const bool);
	void Show();
	void Hide();
	void SetDialogue(Dialogue& dialogue);
	void SetString(const std::string string);
	void SetPosition(float x, float y);
	void ShowNext();
	void Update(); // For animations


	// IDrawable
	void Draw(sf::RenderWindow&) const override;


private:
	bool m_isVisible;
	Dialogue* m_currentDialogue;
	sf::Color m_backgroundColor;
	sf::Vector2f m_position;
	sf::Vector2f m_size = {300, 200};
	std::string m_string;
	sf::Text text;
	sf::RectangleShape background_text;
	sf::Font undertale_font;

};