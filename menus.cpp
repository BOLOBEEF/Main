
// MENUS AND UI


// Settings :



// Structs and enums


// Runtime variables
Sprite pauseMenu_mnu;
Sprite EndButton_mnu;
Sprite RetryButton_mnu;
Sprite ResumeButton_mnu;
Sprite SettingButton_mnu;


// Functions
Font font;
Text fpsDisplay;
Text End_txt, Resume_txt, Retry_txt, Pause_txt;

void InitializeMenu()
{
	font.loadFromFile("Main/Assets/Fonts/trajanpro-bold.otf");
	fpsDisplay.setFont(font);
	fpsDisplay.setCharacterSize(24);
	//Pause menu
	ApplyTexture(pauseMenu_mnu, LoadTexture::menu_box_texture, Vector2f(windowSize.x - 600, windowSize.y - 250));
	UpdateAnimation(pauseMenu_mnu, menu_box_texture);
	pauseMenu_mnu.setPosition(windowSize.x / 2, windowSize.y / 2);

	ApplyTexture(EndButton_mnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(EndButton_mnu, stone_button_0_texture);
	EndButton_mnu.setPosition((windowSize.x / 2) - 60, (windowSize.y / 2) + 70);

	ApplyTexture(RetryButton_mnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(RetryButton_mnu, stone_button_0_texture);
	RetryButton_mnu.setPosition((windowSize.x / 2) + 410, (windowSize.y / 2) + 70);

	ApplyTexture(ResumeButton_mnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(ResumeButton_mnu, stone_button_0_texture);
	ResumeButton_mnu.setPosition((windowSize.x / 2 + 170), (windowSize.y / 2) + 220);

	ApplyTexture(SettingButton_mnu, LoadTexture::SettingsButton0_texture, Vector2f(105, 105));
	UpdateAnimation(SettingButton_mnu, SettingsButton0_texture);
	SettingButton_mnu.setPosition((pauseMenu_mnu.getGlobalBounds().left + pauseMenu_mnu.getGlobalBounds().width / 2) + 485, pauseMenu_mnu.getGlobalBounds().top + 170);

	//Pause menu text
	End_txt.setFont(font);
	End_txt.setCharacterSize(50);
	End_txt.setFillColor(Color(230, 194, 0));
	End_txt.setString("END");
	End_txt.setPosition(EndButton_mnu.getGlobalBounds().left + EndButton_mnu.getGlobalBounds().width / 2, (EndButton_mnu.getGlobalBounds().top + EndButton_mnu.getGlobalBounds().height / 2) - 20);
	End_txt.setOrigin(End_txt.getLocalBounds().width / 2, End_txt.getLocalBounds().height / 2);
	End_txt.setOutlineColor(Color::Black);
	End_txt.setOutlineThickness(5);

	Retry_txt.setFont(font);
	Retry_txt.setCharacterSize(50);
	Retry_txt.setFillColor(Color(230, 194, 0));
	Retry_txt.setString("RETRY");
	Retry_txt.setPosition(RetryButton_mnu.getGlobalBounds().left + RetryButton_mnu.getGlobalBounds().width / 2, (RetryButton_mnu.getGlobalBounds().top + RetryButton_mnu.getGlobalBounds().height / 2) - 20);
	Retry_txt.setOrigin(Retry_txt.getLocalBounds().width / 2, Retry_txt.getLocalBounds().height / 2);
	Retry_txt.setOutlineColor(Color::Black);
	Retry_txt.setOutlineThickness(5);

	Resume_txt.setFont(font);
	Resume_txt.setCharacterSize(50);
	Resume_txt.setFillColor(Color(230, 194, 0));
	Resume_txt.setString("RESUME");
	Resume_txt.setPosition(ResumeButton_mnu.getGlobalBounds().left + ResumeButton_mnu.getGlobalBounds().width / 2, (ResumeButton_mnu.getGlobalBounds().top + ResumeButton_mnu.getGlobalBounds().height / 2) - 20);
	Resume_txt.setOrigin(Resume_txt.getLocalBounds().width / 2, Resume_txt.getLocalBounds().height / 2);
	Resume_txt.setOutlineColor(Color::Black);
	Resume_txt.setOutlineThickness(5);

	Pause_txt.setFont(font);
	Pause_txt.setCharacterSize(65);
	Pause_txt.setFillColor(Color(230, 194, 0));
	Pause_txt.setString("PAUSED");
	Pause_txt.setPosition((ResumeButton_mnu.getGlobalBounds().left + ResumeButton_mnu.getGlobalBounds().width / 2), (ResumeButton_mnu.getGlobalBounds().top + ResumeButton_mnu.getGlobalBounds().height / 2) - 400);
	Pause_txt.setOrigin(Pause_txt.getLocalBounds().width / 2, Pause_txt.getLocalBounds().height / 2);
	Pause_txt.setOutlineColor(Color::Black);
	Pause_txt.setOutlineThickness(5);
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
	case PAUSE_MENU:

		break;
	case WIN_MENU:

		break;
	case SETTINGS:
		// code for handling settings menu input
		break;
	case GAMEOVER:

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
	case PAUSE_MENU:

		break;
	case WIN_MENU:

		break;
	case SETTINGS:
		// code for settings menu
		break;
	case GAMEOVER:

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
	case PAUSE_MENU:
		window.draw(pauseMenu_mnu);
		window.draw(EndButton_mnu);
		window.draw(RetryButton_mnu);
		window.draw(ResumeButton_mnu);
		window.draw(SettingButton_mnu);
		window.draw(End_txt);
		window.draw(Retry_txt);
		window.draw(Resume_txt);
		window.draw(Pause_txt);
		break;
	case WIN_MENU:

		break;
	case SETTINGS:
		// code for drawing settings menu
		break;
	case GAMEOVER:

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
