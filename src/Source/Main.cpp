#include <Game.h>
#include <iostream>

int main() {
	std::cout << "Starting !" << std::endl;

	// Create a window to pass to game
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");


	sf::Texture texture;
	texture.loadFromFile("resources/Sprites/C.png");
	sf::Sprite sprite(texture);
	sprite.setScale(4,4);


	// Create a new game
	Game game(&window);


	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
			else if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else if(event.key.code == sf::Keyboard::Space) {
					sprite.move({8,5});
				}
			}
		}

		game.Run();
		game.Render();
		//window.clear();
		window.draw(sprite);
		window.display();
	}
}