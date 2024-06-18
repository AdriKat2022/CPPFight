#include "TextBox.h"
#include "Configs.h"

TextBox::TextBox() {
	undertale_font.loadFromFile(FilePaths::FONT_MAIN);
	m_position.x = 150;
	m_position.y = 150;

	background_text.setSize(sf::Vector2f(300, 200));
	background_text.setPosition(m_position);
	background_text.setFillColor(sf::Color::Black);

	text.setPosition(m_position);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(20);
	text.setFont(undertale_font);
	text.setString(m_currentDialogue->GetNext());
	SetVisible(true);
}

void TextBox::SetVisible(const bool booleen)
{
	m_isVisible = booleen;
}

void TextBox::Show() {

}

void TextBox::Hide() {

}

void TextBox::SetDialogue(Dialogue& dialogue) {
	m_currentDialogue = &dialogue;
}

void TextBox::SetString(const std::string string) {
	m_string = string;
}

void TextBox::SetPosition(float x, float y) {
	m_position.x = x;
	m_position.y = y;
}

void TextBox::ShowNext() {

}

void TextBox::Update() {

}

void TextBox::Draw(sf::RenderWindow& window) const{
	
}