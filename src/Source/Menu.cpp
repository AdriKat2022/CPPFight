#include "Menu.h"
#include "Button.h"

void Menu::AddButton(const std::string& spritePath, sf::Vector2f position, void(*OnClickEvent)(Context& context))
{
	auto button = std::make_shared<Button>(position, spritePath, sf::Vector2i(1, 0), OnClickEvent);
	m_buttons.push_back(button);
}

void Menu::AddSprite(const std::string& spritePath, sf::Vector2f position, sf::Vector2i dimensions)
{

}

void Menu::Draw(sf::RenderWindow& window) const
{
	if (!IsActive())
		return;
	
	for (const auto& button : m_buttons) {
		button->Draw(window);
		button->Update();
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
