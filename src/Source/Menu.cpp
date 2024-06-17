#include "Menu.h"
#include "Button.h"
#include <iostream>


Menu::Menu()
{
	SetActive(true);
}

void Menu::AddButton(const std::string& spritePath, sf::Vector2f position, std::function<void(Context*)> OnClickEvent, Context* context)
{
	auto button = std::make_shared<Button>(context, position, spritePath, sf::Vector2i(1, 2), OnClickEvent);
	m_buttons.push_back(button);
}

void Menu::AddSprite(const std::string& spritePath, sf::Vector2f position, sf::Vector2i dimensions, bool centerOrigin)
{
	auto sprite = std::make_shared<IDrawable>(position, spritePath, dimensions, centerOrigin);
	m_drawables.push_back(sprite);
}

void Menu::Draw(sf::RenderWindow& window) const
{
	if (!IsActive())
		return;
	
	for (const auto& drawable : m_drawables) {
		drawable->Draw(window);
	}
	for (const auto& button : m_buttons) {
		button->Draw(window);
		button->Update(window);
	}
}

void Menu::SetActive(bool isActive)
{
	m_isActive = isActive;
}

bool Menu::IsActive() const
{
	return m_isActive;
}
