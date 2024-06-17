#include "TextBox.h"

TextBox::TextBox() {
	m_position = sf::Vector2f(150, 150);
	background_text.setSize(sf::Vector2f(300, 200));
	background_text.setPosition(m_position);
	background_text.setFillColor(sf::Color::Black);

	text.setPosition(m_position);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(20);
	sf::Font undertale_font;
	undertale_font.loadFromFile("resources/Font/HachicroUndertaleBattleFontRegular-L3zlg.ttf");
	text.setFont(undertale_font);
	text.setString(dialogue.getNext());
}

void TextBox::Show() {

}

void TextBox::Hide() {

}

void TextBox::SetDialogue(const Dialogue& dialogue) {
	m_currentDialogue = dialogue;
}

void TextBox::SetString(const std::string string) {
	m_string = string;
}

void TextBox::SetPosition(int x, int y) {
	m_position.x = x;
	m_position.y = y;
}

void TextBox::ShowNext() {

}

void TextBox::Update() {

}

void TextBox::Draw(sf::RenderWindow& window) {
	sf::Font undertale_font;
	undertale_font.loadFromFile(FilePaths::UNDERTALE_FONT);
	text.setFont(undertale_font);
	text.setPosition(m_position);
	text.setCharacterSize(10);
	text.setString(m_string);
	text.setFillColor(sf::Color::White);
	//window.draw(background_text);
	window.draw(text);
}