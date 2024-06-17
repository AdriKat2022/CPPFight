#pragma once

#include "IDrawable.h"
#include "Dialogue.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <sstream>

class TextBox : public IDrawable {
	
public:
	TextBox();


	void Show();
	void Hide();
	void SetDialogue(const Dialogue& dialogue);
	void SetString(const std::string string);
	void SetPosition(int x, int y);
	void ShowNext();
	void Update(); // For animations


	// IDrawable
	void Draw(sf::RenderWindow&) override;


private:
	bool m_isVisible;
	Dialogue* m_currentDialogue;
	sf::Color m_backgroundColor;
	sf::Vector2i m_position;
	sf::Vector2i m_size = {300, 200};
	std::string m_string;
	sf::Text text;
	//sf::RectangleShape background_text;

};