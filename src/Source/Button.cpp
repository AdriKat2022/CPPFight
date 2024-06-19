#include "Button.h"
#include "Configs.h"

#include <iostream>

Button::Button(const sf::Vector2f& position, const sf::Texture& texture, std::function<void()> OnClickEvent, sf::Vector2i dimensions, bool scaleOnHover) :
	IDrawable(position, texture, dimensions),
	m_OnClickEvent(OnClickEvent),
	m_scaleSpeed(Config::BUTTON_SCALE_SPEED),
	m_scaleOnHover(scaleOnHover)
{}

Button::Button(const sf::Vector2f& position, const std::string& texturePath, std::function<void()> OnClickEvent, sf::Vector2i dimensions, bool scaleOnHover) :
	IDrawable(position, texturePath, dimensions),
	m_OnClickEvent(OnClickEvent),
	m_scaleSpeed(Config::BUTTON_SCALE_SPEED),
	m_scaleOnHover(scaleOnHover)
{}

// Make a text button rather than a texture button
Button::Button(const sf::Vector2f & position, const std::string& text, std::function<void()> OnClickEvent, bool changeColorOnHover) :
	m_textToDisplay(text),
	m_OnClickEvent(OnClickEvent),
	m_scaleOnHover(false),
	m_changeColorOnHover(changeColorOnHover),
	m_hasText(true)
{
	Move(position);
	m_font.loadFromFile(FilePaths::FONT_MAIN);
	m_text.setString(m_textToDisplay);
	m_text.setFillColor(sf::Color::White);
	m_text.setFont(m_font);
}

// We would need to rename this function to something more appropriate
// Since its update needs also a renderWindow or a way to get the mouse position
void Button::Update(sf::RenderWindow& renderWindow, float deltaTime)
{
	if (!m_isActive)
	{
		SetState(ButtonState::Disabled);
		return;
	}

	HandleStates(renderWindow);
	ScaleButton(deltaTime);
}

void Button::Draw(sf::RenderWindow& window) const
{
	IDrawable::Draw(window);

	if(!m_hasText)
		return;

	window.draw(m_text);

}

void Button::HandleStates(const sf::RenderWindow& renderWindow) {
	using enum ButtonState;

	auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(renderWindow));

	// Check for Hovering
	if (IsInBoundsOfSprite(mousePos))
	{
		if (m_state != Pressed && m_state != Hover) {
			SetState(Hover);
			SwitchSprite(0, 1);
		}
	}
	else
	{
		if (m_state != Idle) {
			SetState(Idle);
			SwitchSprite(0, 0);
		}
		return;
	}

	// Check for click (only if hovered)
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_state == Hover)
	{
		SetState(Pressed);
	}
	else if (m_state == Pressed && !Clickable::IsMousePressed)
	{
		OnClick(mousePos);
		SetState(Hover);
	}
}

void Button::ScaleButton(float deltaTime)
{
	if(!m_scaleOnHover)
		return;

	switch (m_state)
	{
	using enum ButtonState;
	case Idle:
		m_targetScale = Config::BUTTON_TARGET_SCALE_IDLE;
		break;
	case Hover:
		m_targetScale = Config::BUTTON_TARGET_SCALE_HOVER;
		break;
	case Pressed:
		m_targetScale = Config::BUTTON_TARGET_SCALE_PRESSED;
		break;
	case Disabled:
		m_targetScale = Config::BUTTON_TARGET_SCALE_DISABLED;
		break;
	default:

		break;
	}

	auto currentScale = GetSprite().getScale().x;
	auto newScale = currentScale + (m_targetScale - currentScale) * deltaTime * m_scaleSpeed;

	GetSprite().setScale(newScale, newScale);
}

void Button::OnClick(sf::Vector2f position) const
{
	if (m_isActive && m_OnClickEvent)
	{
		m_OnClickEvent();
	}
}

void Button::SetOnClickEvent(std::function<void()> OnClickEvent)
{
	m_OnClickEvent = OnClickEvent;
}

void Button::SetActive(bool active)
{
	m_isActive = active;
	if(active)
	{
		SetState(ButtonState::Idle);
	}
	else
	{
		SetState(ButtonState::Disabled);
	}
}

void Button::SetState(ButtonState state) {
	m_state = state;

	if (m_state == ButtonState::Hover && m_changeColorOnHover)
	{
		m_text.setFillColor(sf::Color::Yellow);
	}
	else
	{
		m_text.setFillColor(sf::Color::White);
	}
}
