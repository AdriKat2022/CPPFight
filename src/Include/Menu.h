#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Context;
class Button;
class IDrawable;

// A menu holds buttons and sprites that are all drawn to the screen when the menu is active (and Draw() is called)
// Draw() should be called every frame to update the menu, since buttons have animations and the menu could be animated (with serveral sprites)
// Buttons can be clicked and have an OnClickEvent that is called when the button is clicked
class Menu {

public:
	Menu();

	void AddButton(const std::string& spritePath, sf::Vector2f position, std::function<void(Context*)> OnClickEvent, Context* context);
	void AddSprite(const std::string& spritePath, sf::Vector2f position, sf::Vector2i dimensions = { 1, 1 }, bool centerOrigin = true);

	void Draw(sf::RenderWindow& window) const;

	void SetActive(bool isActive);
	bool IsActive() const;

private:

	bool m_isActive = false;

	std::vector<std::shared_ptr<Button>> m_buttons;
	std::vector<std::shared_ptr<IDrawable>> m_drawables;
};