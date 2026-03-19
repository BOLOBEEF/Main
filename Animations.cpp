
// MENUS AND UI


// Settings :



// Structs and enums


// Runtime variables
// Ex: clocks and timers for animations



// Functions

void InitializeAnimations()
{
	// code for initializing menu variables and objects
	// for example initialize timers or counters
}


void HandleAnimationsInput(Event event)
{
	// if ever needed you can check for input events here

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

void UpdateAnimations()
{
	// update animations here

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
