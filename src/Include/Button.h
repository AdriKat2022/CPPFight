#pragma once

#include "MouseData.h"
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
	Button(const sf::Vector2f& position, const sf::Texture& texture, const std::function<void()>& OnClickEvent, sf::Vector2i dimensions = { 1, 1 }, bool scaleOnHover = true);
	Button(const sf::Vector2f& position, const std::string& texturePath, const std::function<void()>& OnClickEvent, sf::Vector2i dimensions = { 1, 1 }, bool scaleOnHover = true);
	Button(const sf::Vector2f& position, const std::string& text, int textSize, const std::function<void()>& OnClickEvent, bool changeColorOnHover = true);

	void Update(const sf::RenderWindow& renderWindow, float deltaTime = 0.01f);
	void Draw(sf::RenderWindow& window) const override;

	void OnClick() const;
	void SetOnClickEvent(const std::function<void()>& OnClickEvent);

	void SetEnabled(bool active) override;
	void SetVisible(bool visible);

private:
	void HandleStates(const sf::RenderWindow & renderWindow);
	void ScaleButton(float deltaTime);
	void SetState(ButtonState state);


	// This should be in the IDrawable class, we got no time to refactor it
	// Or better, two derived classes : one for texture and one for text
	std::string m_textToDisplay; 
	sf::Font m_font;
	sf::Text m_text;

	std::function<void()> m_OnClickEvent = nullptr;

	ButtonState m_state = ButtonState::Idle;
	float m_scaleSpeed = 1.0f;
	float m_targetScale = 1.f;
	bool m_isDisabled = false;
	bool m_isVisible = true;
	bool m_scaleOnHover = true;
	bool m_changeColorOnHover = true;
	bool m_hasText = false;
};