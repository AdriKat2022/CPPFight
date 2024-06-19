#include "TextBox.h"
#include "Configs.h"

TextBox::TextBox()
{
	m_undertale_font.loadFromFile(FilePaths::FONT_MAIN);
	m_position.x = 150;
	m_position.y = 150;

	m_background_text.setSize(sf::Vector2f(300, 200));
	m_background_text.setPosition(m_position);
	m_background_text.setFillColor(sf::Color::Black);

	m_text.setPosition(m_position);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(20);
	m_text.setFont(m_undertale_font);
	SetVisible(true);
}

void TextBox::SetVisible(const bool booleen)
{
	m_isVisible = booleen;
}

void TextBox::Show() const
{
	// No need for now
}

void TextBox::Hide() const
{
	// No need for now
}

void TextBox::SetDialogue(Dialogue& dialogue) {
	m_currentDialogue = &dialogue;
	m_remainingDialogues = dialogue.GetSize();
}

void TextBox::SetString(const std::string& string) {
	m_string = string;
}

void TextBox::SetPosition(float x, float y) {
	m_position.x = x;
	m_position.y = y;
}

void TextBox::ShowNext()
{
	if (m_remainingDialogues == 0)
	{
		m_text.setString("");
		m_hasClickedAfterFinish = true;
		return;
	}

	// Show next dialogue
	m_text.setString(m_currentDialogue->GetNext());
	m_remainingDialogues--;
}

void TextBox::Update()
{
	if (sf::Mouse::Button::Left == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		ShowNext();
	}
}

void TextBox::Draw(sf::RenderWindow& window) const
{
	window.draw(m_background_text);
	window.draw(m_text);
}

bool TextBox::IsFinished() const
{
	return m_remainingDialogues == 0 && m_hasClickedAfterFinish;
}