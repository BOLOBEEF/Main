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

// Custom Math Functions
#include "CustomMath.cpp"

// Textures
#include "Textures.cpp"

// Animations
#include "Animations.cpp"

// Level objects
#include "LevelObjects.cpp"

// Level data
#include "LevelData.cpp"

// Game Logic
#include "GameLogic.cpp"

// Menus
#include "Menus.cpp"

// Sounds and music
#include "Audio.cpp"

// script for general testing
#include "Testing.cpp"




int main()
{
	// Initialization
	Initialize();

	// input issues: key repeat is enabled by default, which causes problems with our input handling, so we disable it
	window.setKeyRepeatEnabled(false);

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