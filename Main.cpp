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


		window.clear();

		// Draw objects
		window.draw(sprite);

		window.display();
	}
	return 0;
}