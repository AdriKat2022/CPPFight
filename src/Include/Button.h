#pragma once

#include "Clickable.h"
#include "IDrawable.h"
#include <SFML/Graphics.hpp>

class GameRun;


enum class ButtonState
{
	Idle,
	Hover,
	Pressed,
	Disabled
};


class Button : public IDrawable
{
public:
	using IDrawable::IDrawable;
	Button(const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions = { 1, 0 }, void (*OnClickEvent)() = nullptr);
	Button(const sf::Vector2f& position, const std::string& texturePath, sf::Vector2i dimensions = { 1, 0 }, void (*OnClickEvent)() = nullptr);
	

	void Update(float deltaTime = 0.1f);

	void OnClick(sf::Vector2f position);
	void SetOnClickEvent(void (*OnClickEvent)());

private:
	void HandleStates();
	void RenderButton(float deltaTime);
	void SetState(ButtonState state);


	void (*m_OnClickEvent)() = nullptr;
	ButtonState m_state = ButtonState::Idle;
	float m_scaleSpeed = 10.0f;
	float m_targetScale = 1.f;
	bool m_isActive = true;
};