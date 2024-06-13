#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Clickable;
class IDrawable;
class Game;



int main();

void ManageEvents(sf::RenderWindow& window, sf::Event& event);

std::unique_ptr<Game> NewRun(sf::RenderWindow & renderWindow);

void Update(Game& game, float deltaTime);
void UpdateRun(Game& game, float deltaTime);
void AddClickable(std::shared_ptr<Clickable> clickable);
void AddDrawable(std::shared_ptr<IDrawable> drawable);
void LoadEnemiesData();
void ExampleFunction();
void Render(const Game & game, sf::RenderWindow& window);
void CreateMenuButton(const std::string& spritePath, sf::Vector2f position, void (*OnClickEvent)());