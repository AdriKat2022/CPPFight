#include "Button.h"
#include "Configs.h"

#include <iostream>

Button::Button(const sf::Vector2f& position, const sf::Texture& texture, const std::function<void()>& OnClickEvent, sf::Vector2i dimensions, bool scaleOnHover) :
	IDrawable(position, texture, dimensions),
	m_OnClickEvent(OnClickEvent),
	m_scaleSpeed(Config::BUTTON_SCALE_SPEED),
	m_scaleOnHover(scaleOnHover)
{}

Button::Button(const sf::Vector2f& position, const std::string& texturePath, const std::function<void()>& OnClickEvent, sf::Vector2i dimensions, bool scaleOnHover) :
	IDrawable(position, texturePath, dimensions),
	m_OnClickEvent(OnClickEvent),
	m_scaleSpeed(Config::BUTTON_SCALE_SPEED),
	m_scaleOnHover(scaleOnHover)
{}

// Make a text button rather than a texture button
Button::Button(const sf::Vector2f& position, const std::string& text, int textSize, const std::function<void()>& OnClickEvent, bool changeColorOnHover) :
	m_textToDisplay(text),
	m_OnClickEvent(OnClickEvent),
	m_scaleOnHover(false),
	m_changeColorOnHover(changeColorOnHover),
	m_hasText(true)
{
	m_font.loadFromFile(FilePaths::FONT_MAIN);
	m_text.setString(m_textToDisplay);
	m_text.setCharacterSize(textSize);
	m_text.setFillColor(sf::Color::White);
	m_text.setFont(m_font);

	m_text.setPosition({
		position.x - m_text.getGlobalBounds().width / 2,
		position.y - m_text.getGlobalBounds().height / 2
		});
}

// We would need to rename this function to something more appropriate
// Since its update needs also a renderWindow or a way to get the mouse position
void Button::Update(const sf::RenderWindow& renderWindow, float deltaTime)
{
	ScaleButton(deltaTime);

	if (m_isDisabled)
	{
		SetState(ButtonState::Disabled);
		return;
	}
	HandleStates(renderWindow);
}

void Button::Draw(sf::RenderWindow& window) const
{
	if(!m_isVisible)
		return;

	IDrawable::Draw(window);

	if(!m_hasText)
		return;

	window.draw(m_text);

}

void Button::HandleStates(const sf::RenderWindow& renderWindow) {
	using enum ButtonState;

	auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(renderWindow));

	// Check for Hovering
	if (IsInBoundsOfSprite(mousePos) || (m_hasText && m_text.getGlobalBounds().contains(mousePos)))
	{
		if (m_state != Pressed && m_state != Hover) {
			SetState(Hover);
			if(!m_hasText)
				SwitchSprite(0, 1);
		}
	}
	else
	{
		if (m_state != Idle) {
			SetState(Idle);
			if (!m_hasText)
				SwitchSprite(0, 0);
		}
		return;
	}

	// Check for click (only if hovered)
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_state == Hover)
	{
		SetState(Pressed);
	}
	else if (m_state == Pressed && !MouseData::IsMousePressed)
	{
		OnClick();
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

void Button::OnClick() const
{
	if (!m_isDisabled && m_OnClickEvent)
	{
		m_OnClickEvent();
	}
}

void Button::SetOnClickEvent(const std::function<void()>& OnClickEvent)
{
	m_OnClickEvent = OnClickEvent;
}

void Button::SetEnabled(bool active)
{
	m_isDisabled = !active;

	if(active)
	{
		SetState(ButtonState::Idle);
	}
	else
	{
		SetState(ButtonState::Disabled);
	}
}

void Button::SetVisible(bool visible)
{
	m_isVisible = visible;
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
