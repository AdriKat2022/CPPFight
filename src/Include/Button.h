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
	Button(Context* context, const sf::Vector2f& position, const sf::Texture& texture, sf::Vector2i dimensions = { 1, 1 }, std::function<void(Context*)> OnClickEvent = nullptr);
	Button(Context* context, const sf::Vector2f& position, const std::string& texturePath, sf::Vector2i dimensions = { 1, 1 }, std::function<void(Context*)> OnClickEvent = nullptr);
	

	void Update(sf::RenderWindow& renderWindow, float deltaTime = 0.01f);

	void OnClick(sf::Vector2f position);
	void SetOnClickEvent(std::function<void(Context*)> OnClickEvent);

private:
	void HandleStates(const sf::RenderWindow & renderWindow);
	void RenderButton(float deltaTime);
	void SetState(ButtonState state);


	Context* m_context = nullptr;
	std::function<void(Context*)> m_OnClickEvent = nullptr;

	ButtonState m_state = ButtonState::Idle;
	float m_scaleSpeed = 10.0f;
	float m_targetScale = 1.f;
	bool m_isActive = true;
};