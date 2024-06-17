#include "Button.h"
#include "Configs.h"

#include <iostream>

Button::Button(Context* context, const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions, std::function<void(Context*)> OnClickEvent) :
	IDrawable(position, texture, dimensions),
	m_context(context),
	m_OnClickEvent(OnClickEvent),
	m_scaleSpeed(Config::BUTTON_SCALE_SPEED)
{}

Button::Button(Context* context, const sf::Vector2f& position, const std::string& texturePath, sf::Vector2i dimensions, std::function<void(Context*)> OnClickEvent) :
	IDrawable(position, texturePath, dimensions),
	m_context(context),
	m_OnClickEvent(OnClickEvent),
	m_scaleSpeed(Config::BUTTON_SCALE_SPEED)
{}


void Button::Update(sf::RenderWindow& renderWindow, float deltaTime)
{
	if (!m_isActive)
	{
		SetState(ButtonState::Disabled);
		return;
	}

	HandleStates(renderWindow);
	RenderButton(deltaTime);
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

void Button::RenderButton(float deltaTime)
{
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

void Button::OnClick(sf::Vector2f position)
{
	if (m_isActive && m_OnClickEvent)
	{
		m_OnClickEvent(m_context);
	}
}

void Button::SetOnClickEvent(std::function<void(Context*)> OnClickEvent)
{
	m_OnClickEvent = OnClickEvent;
}

void Button::SetState(ButtonState state) {
	m_state = state;
}
