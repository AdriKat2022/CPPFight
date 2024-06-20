#include "TextBox.h"
#include "Configs.h"
#include <iostream>

TextBox::TextBox(const sf::Vector2f& position)
{
	m_undertale_font.loadFromFile(FilePaths::FONT_MAIN);
	
	m_textBoxBackground.setSize({Anchors::TEXT_BOX_SIZE[0], Anchors::TEXT_BOX_SIZE[1]});
	m_textBoxBackground.setFillColor(sf::Color::Black);
	m_textBoxBackground.setOutlineColor(sf::Color::White);
	m_textBoxBackground.setOutlineThickness(10);
	m_textBoxBackground.setPosition({
		position.x - m_textBoxBackground.getGlobalBounds().width / 2,
		position.y - m_textBoxBackground.getGlobalBounds().height / 2
		});
	
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(20);
	m_text.setFont(m_undertale_font);
	SetVisible(false);
}

void TextBox::SetVisible(const bool booleen)
{
	m_isVisible = booleen;
}

void TextBox::Show()
{
	std::cout << "TextBox visible" << std::endl;
	m_isVisible = true;
}

void TextBox::Hide()
{
	std::cout << "TextBox hidden" << std::endl;
	m_isVisible = false;
}

void TextBox::SetDialogue(Dialogue& dialogue) {
	m_currentDialogue = &dialogue;
	m_remainingDialogues = dialogue.GetSize();

	std::cout << "Setup dialogue" << std::endl;
	if (m_remainingDialogues > 0)
	{
		m_hasClickedAfterFinish = false;
		ShowNext();
	}
}


void TextBox::ShowNext()
{
	std::cout << "Showing next" << std::endl;

	if (m_remainingDialogues == 0)
	{
		m_text.setString("");
		m_hasClickedAfterFinish = true;
		Hide();
		return;
	}

	// Show next dialogue
	m_text.setString(m_currentDialogue->GetNext());
	m_text.setPosition({
		m_textBoxBackground.getPosition().x + m_textBoxBackground.getGlobalBounds().width / 2 - m_text.getGlobalBounds().width / 2,
		m_textBoxBackground.getPosition().y + m_textBoxBackground.getGlobalBounds().height / 2 - m_text.getGlobalBounds().height / 2
		});
	m_remainingDialogues--;
}

void TextBox::Update(float deltaTime)
{
	if (m_textBoxLocked)
		return;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !m_lastFrameClick)
	{
		m_lastFrameClick = true;
		ShowNext();
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		m_lastFrameClick = false;
	}
}

void TextBox::Draw(sf::RenderWindow& window) const
{
	if(!m_isVisible)
		return;

	window.draw(m_textBoxBackground);
	window.draw(m_text);
}

void TextBox::LockTextBox(bool lock)
{
	m_textBoxLocked = lock;
}

bool TextBox::IsFinished() const
{
	return m_remainingDialogues == 0 && m_hasClickedAfterFinish;
}