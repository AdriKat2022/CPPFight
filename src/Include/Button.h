#pragma once

#include "Clickable.h"
#include "IDrawable.h"
#include <SFML/Graphics.hpp>
#include <functional>

class GameRun;
class Context;

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
	Button(const sf::Vector2f& position, const sf::Texture& texture, std::function<void()> OnClickEvent, sf::Vector2i dimensions = { 1, 1 }, bool scaleOnHover = true);
	Button(const sf::Vector2f& position, const std::string& texturePath, std::function<void()> OnClickEvent, sf::Vector2i dimensions = { 1, 1 }, bool scaleOnHover = true);
	

	void Update(sf::RenderWindow& renderWindow, float deltaTime = 0.01f);

	void OnClick(sf::Vector2f position);
	void SetOnClickEvent(std::function<void()> OnClickEvent);

private:
	void HandleStates(const sf::RenderWindow & renderWindow);
	void ScaleButton(float deltaTime);
	void SetState(ButtonState state);


	std::function<void()> m_OnClickEvent = nullptr;

	ButtonState m_state = ButtonState::Idle;
	float m_scaleSpeed = 1.0f;
	float m_targetScale = 1.f;
	bool m_isActive = true;
	bool m_scaleOnHover = true;
};