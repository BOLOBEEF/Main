#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <queue>
#include <iomanip>
using namespace std;
using namespace sf;

// custom math functions
#include "customMath.cpp"


// SETTINGS



// Global runtime variables
RenderWindow window = { VideoMode::getDesktopMode(), "SFML"};
Vector2u windowSize = window.getSize();
Vector2f center = Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);


int main()
{
	// Local runtime variables

	Clock dtClock;
	float dt = 0.0f;


	// load texture and sprite
	Texture texture;
	texture.loadFromFile("Main/Assets/Preview.png");
	Sprite sprite = Sprite(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);


	Event event;
	while (window.isOpen())
	{
		// close window
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			// Event loop for player input

		}

		dt = dtClock.restart().asSeconds();

		// Game logic
		Vector2f mousePos = Vector2f(Mouse::getPosition(window));
		sprite.setPosition(Damp(sprite.getPosition().x, mousePos.x, 1000.0f , dt), Damp(sprite.getPosition().y, mousePos.y, 1000.0f , dt));
		//sprite.setPosition(mousePos);


		window.clear();

		// Draw objects
		window.draw(sprite);

		window.display();
	}
	return 0;
}