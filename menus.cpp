
// MENUS AND UI


// Settings :



// Structs and enums


// Runtime variables
Sprite pauseMenu_mnu;
Sprite EndButton_mnu;
Sprite ResumeButton_mnu;
Sprite RetryButton_mnu;

// Functions
Font font;
Text fpsDisplay;

void InitializeMenu()
{
	font.loadFromFile("Main/Assets/Fonts/ContrailOne-Regular.ttf");
	fpsDisplay.setFont(font);
	fpsDisplay.setCharacterSize(24);
	//Pause menu
	ApplyTexture(pauseMenu_mnu, LoadTexture::menu_box_texture, Vector2f(windowSize.x - 600, windowSize.y - 250), Vector2f(1, 1), true);
	pauseMenu_mnu.setPosition(windowSize.x / 2, windowSize.y / 2);

	ApplyTexture(EndButton_mnu, LoadTexture::stone_button_0_texture, Vector2f(1000, 250), Vector2f(1, 1), true);
	EndButton_mnu.setPosition(windowSize.x / 2, (windowSize.y / 2) + 100);
	// code for initializing menu variables and objects
	// for example load sprites, set up text objects, etc.
}


void HandleMenuInput(Event event)
{
	switch (gameState)
	{
	case MAIN_MENU:
		// code for handling main menu input
		break;
	case SETTINGS:
		// code for handling settings menu input
		break;
	case GAME:
		// code for handling game UI input
		break;
	default:
		break;
	}
}

void OnUpdatedGameStateMenu() {
	// do stuff here exactly when the gameState is changed
}

void UpdateUI()
{
	switch (gameState)
	{
	case MAIN_MENU:
		// code for main menu
		break;
	case SETTINGS:
		// code for settings menu
		break;
	case GAME:
		// code for game UI
		break;
	default:
		break;
	}
}

void DrawUI()
{
	// draw only, no need for window.clear or window.display

	switch (gameState)
	{
	case MAIN_MENU:
		// code for drawing main menu
		window.draw(pauseMenu_mnu);
		window.draw(EndButton_mnu);
		break;
	case SETTINGS:
		// code for drawing settings menu
		break;
	case GAME:
		// code for drawing game UI
		break;
	default:
		break;
	}

	fpsDisplay.setString(to_string((int)round(1.0f / dt)));
	window.draw(fpsDisplay);
}
