#include "Menu.h"
#include "Button.h"
#include <iostream>


void Menu::AddButton(const std::string& spritePath, sf::Vector2f position, std::function<void()> OnClickEvent)
{
	auto button = std::make_shared<Button>(position, spritePath, OnClickEvent, sf::Vector2i(1, 2));
	m_buttons.push_back(button);
}

void Menu::AddSprite(const std::string& spritePath, sf::Vector2f position, sf::Vector2i dimensions, bool centerOrigin)
{
	auto sprite = std::make_shared<IDrawable>(position, spritePath, dimensions, centerOrigin);
	m_drawables.push_back(sprite);
}

void Menu::Draw(sf::RenderWindow& window) const
{
	for (const auto& drawable : m_drawables) {
		drawable->Draw(window);
	}
	for (const auto& button : m_buttons) {
		button->Draw(window);
		button->Update(window);
	}
}
