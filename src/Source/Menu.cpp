#include "Menu.h"
#include "Button.h"
#include <iostream>


void Menu::AddButton(const std::string& textToDisplay, sf::Vector2f position, [[maybe_unused]] int textSize, std::function<void()> OnClickEvent)
{
	auto button = std::make_shared<Button>(position, textToDisplay, OnClickEvent, true);
	m_buttons.push_back(button);
}

void Menu::AddButton(const std::string& spritePath, sf::Vector2f position, std::function<void()> OnClickEvent)
{
	auto button = std::make_shared<Button>(position, spritePath, OnClickEvent, sf::Vector2i(1, 2), true);
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

void Menu::SetButtonsActive(bool active) const
{
	for (const auto& button : m_buttons) {
		button->SetActive(active);
	}
}
