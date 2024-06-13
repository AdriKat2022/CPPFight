#pragma once

#include "Clickable.h"
#include "IDrawable.h"
#include <SFML/Graphics.hpp>

class Game;


enum class ButtonState
{
	Idle,
	Hover,
	Pressed,
	Disabled
};


class Button : public Clickable, public IDrawable
{
public:
	using IDrawable::IDrawable;
	Button(const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions = { 1, 0 }, void (*OnClickEvent)() = nullptr);
	Button(const sf::Vector2f& position, const std::string& texturePath, sf::Vector2i dimensions = { 1, 0 }, void (*OnClickEvent)() = nullptr);
	

	void Update(Game& game, float deltaTime) override;


	// Clickable
	void OnClick(sf::Vector2f position) override;
	bool IsInBounds(sf::Vector2f position) const override;

	void SetOnClickEvent(void (*OnClickEvent)());

private:
	void HandleStates(const Game& game);
	void RenderButton(float deltaTime);
	void SetState(ButtonState state);

	void (*m_OnClickEvent)() = nullptr;

	ButtonState m_state = ButtonState::Idle;

	float m_scaleSpeed = 10.0f;
	float m_targetScale = 1.f;
};