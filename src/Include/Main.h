#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Clickable;
class IDrawable;
class GameRun;



int main();

void ManageEvents(sf::RenderWindow& window, sf::Event& event);

std::unique_ptr<GameRun> NewRun(sf::RenderWindow & renderWindow);

void Update(GameRun& gameRun, float deltaTime);
void UpdateRun(GameRun& gameRun, float deltaTime);
void AddClickable(std::shared_ptr<Clickable> clickable);
void AddDrawable(std::shared_ptr<IDrawable> drawable);
void LoadEnemiesData();
void ExampleFunction();
void Render(const GameRun & game, sf::RenderWindow& window);
void CreateMenuButton(const std::string& spritePath, sf::Vector2f position, void (*OnClickEvent)());