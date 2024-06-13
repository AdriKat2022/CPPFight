#include "Button.h"
#include "Configs.h"

Button::Button(const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions, void(*OnClickEvent)()) :
	IDrawable(position, texture, dimensions),
	m_OnClickEvent(OnClickEvent),
	m_scaleSpeed(Config::BUTTON_SCALE_SPEED)
{}

Button::Button(const sf::Vector2f& position, const std::string& texturePath, sf::Vector2i dimensions, void(*OnClickEvent)()) :
	IDrawable(position, texturePath, dimensions),
	m_OnClickEvent(OnClickEvent),
	m_scaleSpeed(Config::BUTTON_SCALE_SPEED)
{}


void Button::Update(GameRun& gameRun, float deltaTime)
{
	if (!IsActive())
	{
		SetState(ButtonState::Disabled);
		return;
	}

	HandleStates(gameRun);
	RenderButton(deltaTime);
}

void Button::HandleStates(const GameRun& gameRun) {
	using enum ButtonState;

	auto mousePos = gameRun.GetMousePosition();

	// Check for Hovering
	if (IsInBounds(mousePos))
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
	if (IsActive() && m_OnClickEvent)
	{
		m_OnClickEvent();
	}
}

bool Button::IsInBounds(sf::Vector2f position) const
{
	return IsInBoundsOfSprite(position);
}

void Button::SetOnClickEvent(void(*OnClickEvent)())
{
	m_OnClickEvent = OnClickEvent;
}

void Button::SetState(ButtonState state) {
	m_state = state;
}
