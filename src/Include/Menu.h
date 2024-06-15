#pragma once

#include "IDrawable.h"


class Context;
class Button;


class Menu : public IDrawable {

public:
	Menu() = default;

	void AddButton(const std::string& spritePath, sf::Vector2f position, void (*OnClickEvent)(Context& context));
	void AddSprite(const std::string& spritePath, sf::Vector2f position, sf::Vector2i dimensions = { 1, 0 });

	void Draw(sf::RenderWindow& window) const override;

	void SetActive(bool isActive);
	bool IsActive() const;

private:

	bool m_isActive = false;

	std::vector<std::shared_ptr<Button>> m_buttons;
	std::vector<std::shared_ptr<IDrawable>> m_drawables;
};