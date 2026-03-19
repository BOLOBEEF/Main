
// MENUS AND UI


// Settings :



// Structs and enums


// Runtime variables
Texture texture;



// Functions

void InitializeMenu()
{
	// code for initializing menu variables and objects
	// for example load sprites, set up text objects, etc.
	texture.loadFromFile("Main/Assets/Preview.png");
	player.setTexture(texture);
	player.setOrigin(player.getLocalBounds().width / 2.0f, player.getLocalBounds().height / 2.0f);
	player.setScale(0.2f, 0.2f);
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
}
