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

// Global variables that are used across multiple files and functions
#include "Globals.cpp"

// script for general testing
#include "Testing.cpp"

// Custom Math Functions
#include "CustomMath.cpp"

// Game Logic
#include "GameLogic.cpp"

// Animations
#include "Animations.cpp"

// Textures
#include "Textures.cpp"


// Level objects
#include "LevelObjects.cpp"

// Level data
#include "LevelData.cpp"

// Menus
#include "Menus.cpp"

// Sounds and music
#include "Audio.cpp"




int main()
{
	// Initialization
	Initialize();


	Event event;
	while (window.isOpen())
	{
		// close window
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();


			else
			{
				HandleInput(event);
			}
		}

		// game updates 
		UpdateGlobals();



		window.clear();

		Draw();

		window.display();
	}
	return 0;
}