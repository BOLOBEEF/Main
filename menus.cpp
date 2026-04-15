
// MENUS AND UI


// Settings :



// Structs and enums


// Runtime variables
GameState PreviousMenu_State = MAIN_MENU;
RectangleShape Dimmed_Backgriund;
//float Current_mnu = ( Stone_mnu.getPosition().y);
//float Target_mnu =  Stone_mnu.getPosition().y + 1000;
Sprite Stone_mnu;
Sprite SettingButton_mnu;
Sprite EndButton_Pausemnu;
Sprite RetryButton_Pausemnu;
Sprite ResumeButton_Pausemnu;
Sprite PauseIcon_mnu;
//Vector2f Current_Up_mnu = Vector2f(windowSize.x / 2, windowSize.y / 2 + 850);
Vector2f Target_up_mnu = Vector2f(windowSize.x / 2, windowSize.y / 2);
Vector2f Target_Down_mnu = Vector2f(windowSize.x / 2, windowSize.y / 2 + 1000);
Vector2f Current_position_mnu = Target_Down_mnu;
Vector2f Current_Target;
//Sprite PressedResumeButton_Pausemnu;

Sprite GameOverbuttons_mnu[3];
Sprite ContinueButton_Winmnu;

Font font;
Text fpsDisplay;
Text End_Pausetxt, Resume_Pausetxt, Retry_Pausetxt, Pause_txt;
Text Menu_GOVERtxt, Retry_GOVERtxt, Skip_GOVERtxt, GameOver_txt;
Text Continue_Wintxt;


// Functions
bool MouseInput_mnu(Event event, Sprite& ButtonClicked, LoadTexture Currnet_texture_enum, LoadTexture Desired_texture_enum, MenuSoundEffect Sound_Played_mnu,GameState state_mnu)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			UpdateAnimation(ButtonClicked, Desired_texture_enum);
			//Damp(Current_mnu, Target_mnu, 200, dt);
			PlayMenuSoundEffect(Sound_Played_mnu);
		}
	}
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			UpdateAnimation(ButtonClicked, Currnet_texture_enum);
			UpdateGameState(state_mnu);
		}
	}
	return true;
}

bool PauseMenu_Movement(Vector2f Desired_Target)
{
	Current_Target = Desired_Target;
	Current_position_mnu = Damp(Current_position_mnu, Current_Target, 5, dt);
	EndButton_Pausemnu.setPosition(Vector2f((windowSize.x / 2) - 35, (windowSize.y / 2) + 70) + Current_position_mnu - center);
	RetryButton_Pausemnu.setPosition(Vector2f((windowSize.x / 2) + 435, (windowSize.y / 2) + 70) + Current_position_mnu - center);
	ResumeButton_Pausemnu.setPosition(Vector2f((windowSize.x / 2 + 205), (windowSize.y / 2) + 220) + Current_position_mnu - center);
	SettingButton_mnu.setPosition(Vector2f(Stone_mnu.getPosition().x + 485, Stone_mnu.getPosition().y - 240));
	End_Pausetxt.setPosition(Vector2f(EndButton_Pausemnu.getGlobalBounds().left + EndButton_Pausemnu.getGlobalBounds().width / 2, (EndButton_Pausemnu.getGlobalBounds().top + EndButton_Pausemnu.getGlobalBounds().height / 2) - 20));
	Retry_Pausetxt.setPosition(Vector2f(RetryButton_Pausemnu.getGlobalBounds().left + RetryButton_Pausemnu.getGlobalBounds().width / 2, (RetryButton_Pausemnu.getGlobalBounds().top + RetryButton_Pausemnu.getGlobalBounds().height / 2) - 20));
	Resume_Pausetxt.setPosition(Vector2f(ResumeButton_Pausemnu.getGlobalBounds().left + ResumeButton_Pausemnu.getGlobalBounds().width / 2, (ResumeButton_Pausemnu.getGlobalBounds().top + ResumeButton_Pausemnu.getGlobalBounds().height / 2) - 20));
	Pause_txt.setPosition(Vector2f((ResumeButton_Pausemnu.getGlobalBounds().left + ResumeButton_Pausemnu.getGlobalBounds().width / 2), (ResumeButton_Pausemnu.getGlobalBounds().top + ResumeButton_Pausemnu.getGlobalBounds().height / 2) - 400));
	Stone_mnu.setPosition(Current_position_mnu);
	if (Current_position_mnu == Desired_Target)
	{
		return false;
	}
}
bool WinMenu_Movement(Vector2f Desired_Target)
{
	Current_Target = Desired_Target;
	Current_position_mnu = Damp(Current_position_mnu, Current_Target, 5, dt);
	Stone_mnu.setPosition(Current_position_mnu);
	ContinueButton_Winmnu.setPosition(Vector2f((windowSize.x / 2) + 270, (windowSize.y / 2) + 200) + Current_position_mnu - center);
	Continue_Wintxt.setPosition((ContinueButton_Winmnu.getGlobalBounds().left + ContinueButton_Winmnu.getGlobalBounds().width / 2), (ContinueButton_Winmnu.getGlobalBounds().top + ContinueButton_Winmnu.getGlobalBounds().height / 2) - 5);
	if (Current_position_mnu == Desired_Target)
	{
		return false;
	}
}
bool GameoverMenu_Movement(Vector2f Desired_Target)
{
	Current_Target = Desired_Target;
	Current_position_mnu = Damp(Current_position_mnu, Current_Target, 5, dt);
	Stone_mnu.setPosition(Current_position_mnu);
	int x_shift_mnu = 350;
	for (int i = 0; i < 3; i++)
	{
		GameOverbuttons_mnu[i].setPosition(Vector2f(((windowSize.x / 2) + x_shift_mnu + 200), ((windowSize.y / 2) + 145)) + Current_position_mnu - center);
		x_shift_mnu -= 350;
	}
	Menu_GOVERtxt.setPosition((GameOverbuttons_mnu[2].getGlobalBounds().left + GameOverbuttons_mnu[2].getGlobalBounds().width / 2), (GameOverbuttons_mnu[2].getGlobalBounds().top + GameOverbuttons_mnu[2].getGlobalBounds().height / 2) - 15);
	Retry_GOVERtxt.setPosition((GameOverbuttons_mnu[1].getGlobalBounds().left + GameOverbuttons_mnu[1].getGlobalBounds().width / 2), (GameOverbuttons_mnu[1].getGlobalBounds().top + GameOverbuttons_mnu[1].getGlobalBounds().height / 2) - 15);
	Skip_GOVERtxt.setPosition((GameOverbuttons_mnu[0].getGlobalBounds().left + GameOverbuttons_mnu[0].getGlobalBounds().width / 2) + 30, (GameOverbuttons_mnu[0].getGlobalBounds().top + GameOverbuttons_mnu[0].getGlobalBounds().height / 2) - 10);
	GameOver_txt.setPosition((GameOverbuttons_mnu[1].getGlobalBounds().left + GameOverbuttons_mnu[1].getGlobalBounds().width / 2), (GameOverbuttons_mnu[1].getGlobalBounds().top + GameOverbuttons_mnu[1].getGlobalBounds().height / 2) - 270);
	if (Current_position_mnu == Desired_Target)
	{
		return false;
	}
}
void InitializeMenu()
{
	font.loadFromFile("Main/Assets/Fonts/trajanpro-bold.otf");
	fpsDisplay.setFont(font);
	fpsDisplay.setCharacterSize(24);

	//Dimmed Background
	Dimmed_Backgriund.setSize(Vector2f(window.getSize().x, window.getSize().y));
	Dimmed_Backgriund.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);
	Dimmed_Backgriund.setFillColor(Color(0, 0, 0, 180));

	//Pause menu
	ApplyTexture(Stone_mnu, LoadTexture::menu_box_texture, Vector2f(windowSize.x - 600, windowSize.y - 250));
	UpdateAnimation(Stone_mnu, menu_box_texture);
	Stone_mnu.setPosition(windowSize.x / 2, windowSize.y / 2);

	ApplyTexture(PauseIcon_mnu, LoadTexture::pause_icon_texture, Vector2f(75, 75));
	UpdateAnimation(PauseIcon_mnu, pause_icon_texture);
	PauseIcon_mnu.setPosition(windowSize.x / 2 + 820, windowSize.y / 2 - 500);

	ApplyTexture(EndButton_Pausemnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(EndButton_Pausemnu, stone_button_0_texture);
	EndButton_Pausemnu.setPosition((windowSize.x / 2) - 35, (windowSize.y / 2) + 70);

	ApplyTexture(RetryButton_Pausemnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(RetryButton_Pausemnu, stone_button_0_texture);
	RetryButton_Pausemnu.setPosition((windowSize.x / 2) + 435, (windowSize.y / 2) + 70);

	ApplyTexture(ResumeButton_Pausemnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(ResumeButton_Pausemnu, stone_button_0_texture);
	ResumeButton_Pausemnu.setPosition((windowSize.x / 2 + 205), (windowSize.y / 2) + 220);

	ApplyTexture(SettingButton_mnu, LoadTexture::SettingsButton0_texture, Vector2f(105, 105));
	UpdateAnimation(SettingButton_mnu, SettingsButton0_texture);
	SettingButton_mnu.setPosition((Stone_mnu.getGlobalBounds().left + Stone_mnu.getGlobalBounds().width / 2) + 485, Stone_mnu.getGlobalBounds().top + 170);

	//Game Over menu

	// stone background has already set
	int x_shift_mnu = 350;
	for (int i = 0; i < 3; i++)
	{
		ApplyTexture(GameOverbuttons_mnu[i], LoadTexture::stone_button_0_texture, Vector2f(680, 150));
		UpdateAnimation(GameOverbuttons_mnu[i], stone_button_0_texture);
		GameOverbuttons_mnu[i].setPosition(((windowSize.x / 2) + x_shift_mnu + 200), ((windowSize.y / 2) + 145));
		x_shift_mnu -= 350;
	}

	//Win Menu 

	// stone background has already set

	ApplyTexture(ContinueButton_Winmnu, LoadTexture::stone_button_0_texture, Vector2f(950, 170));
	UpdateAnimation(ContinueButton_Winmnu, stone_button_0_texture);
	ContinueButton_Winmnu.setPosition((windowSize.x / 2) + 270, (windowSize.y / 2) + 200);

	//Pause menu text
	End_Pausetxt.setFont(font);
	End_Pausetxt.setCharacterSize(50);
	End_Pausetxt.setFillColor(Color(230, 194, 0));
	End_Pausetxt.setString("END");
	End_Pausetxt.setPosition(EndButton_Pausemnu.getGlobalBounds().left + EndButton_Pausemnu.getGlobalBounds().width / 2, (EndButton_Pausemnu.getGlobalBounds().top + EndButton_Pausemnu.getGlobalBounds().height / 2) - 20);
	End_Pausetxt.setOrigin(End_Pausetxt.getLocalBounds().width / 2, End_Pausetxt.getLocalBounds().height / 2);
	End_Pausetxt.setOutlineColor(Color::Black);
	End_Pausetxt.setOutlineThickness(5);

	Retry_Pausetxt.setFont(font);
	Retry_Pausetxt.setCharacterSize(50);
	Retry_Pausetxt.setFillColor(Color(230, 194, 0));
	Retry_Pausetxt.setString("RETRY");
	Retry_Pausetxt.setPosition(RetryButton_Pausemnu.getGlobalBounds().left + RetryButton_Pausemnu.getGlobalBounds().width / 2, (RetryButton_Pausemnu.getGlobalBounds().top + RetryButton_Pausemnu.getGlobalBounds().height / 2) - 20);
	Retry_Pausetxt.setOrigin(Retry_Pausetxt.getLocalBounds().width / 2, Retry_Pausetxt.getLocalBounds().height / 2);
	Retry_Pausetxt.setOutlineColor(Color::Black);
	Retry_Pausetxt.setOutlineThickness(5);

	Resume_Pausetxt.setFont(font);
	Resume_Pausetxt.setCharacterSize(50);
	Resume_Pausetxt.setFillColor(Color(230, 194, 0));
	Resume_Pausetxt.setString("RESUME");
	Resume_Pausetxt.setPosition(ResumeButton_Pausemnu.getGlobalBounds().left + ResumeButton_Pausemnu.getGlobalBounds().width / 2, (ResumeButton_Pausemnu.getGlobalBounds().top + ResumeButton_Pausemnu.getGlobalBounds().height / 2) - 20);
	Resume_Pausetxt.setOrigin(Resume_Pausetxt.getLocalBounds().width / 2, Resume_Pausetxt.getLocalBounds().height / 2);
	Resume_Pausetxt.setOutlineColor(Color::Black);
	Resume_Pausetxt.setOutlineThickness(5);

	Pause_txt.setFont(font);
	Pause_txt.setCharacterSize(65);
	Pause_txt.setFillColor(Color(230, 194, 0));
	Pause_txt.setString("PAUSED");
	Pause_txt.setPosition((ResumeButton_Pausemnu.getGlobalBounds().left + ResumeButton_Pausemnu.getGlobalBounds().width / 2), (ResumeButton_Pausemnu.getGlobalBounds().top + ResumeButton_Pausemnu.getGlobalBounds().height / 2) - 400);
	Pause_txt.setOrigin(Pause_txt.getLocalBounds().width / 2, Pause_txt.getLocalBounds().height / 2);
	Pause_txt.setOutlineColor(Color::Black);
	Pause_txt.setOutlineThickness(5);

	//GameOver menu Text
	Menu_GOVERtxt.setFont(font);
	Menu_GOVERtxt.setCharacterSize(50);
	Menu_GOVERtxt.setFillColor(Color(230, 194, 0));
	Menu_GOVERtxt.setString("MENU");
	Menu_GOVERtxt.setPosition((GameOverbuttons_mnu[2].getGlobalBounds().left + GameOverbuttons_mnu[2].getGlobalBounds().width / 2), (GameOverbuttons_mnu[2].getGlobalBounds().top + GameOverbuttons_mnu[2].getGlobalBounds().height / 2) - 15);
	Menu_GOVERtxt.setOrigin(Menu_GOVERtxt.getLocalBounds().width / 2, Menu_GOVERtxt.getLocalBounds().height / 2);
	Menu_GOVERtxt.setOutlineColor(Color::Black);
	Menu_GOVERtxt.setOutlineThickness(5);

	Retry_GOVERtxt.setFont(font);
	Retry_GOVERtxt.setCharacterSize(50);
	Retry_GOVERtxt.setFillColor(Color(230, 194, 0));
	Retry_GOVERtxt.setString("RETRY");
	Retry_GOVERtxt.setPosition((GameOverbuttons_mnu[1].getGlobalBounds().left + GameOverbuttons_mnu[1].getGlobalBounds().width / 2), (GameOverbuttons_mnu[1].getGlobalBounds().top + GameOverbuttons_mnu[1].getGlobalBounds().height / 2) - 15);
	Menu_GOVERtxt.setPosition((GameOverbuttons_mnu[2].getGlobalBounds().left + GameOverbuttons_mnu[2].getGlobalBounds().width / 2), (GameOverbuttons_mnu[2].getGlobalBounds().top + GameOverbuttons_mnu[2].getGlobalBounds().height / 2) - 15);
	Retry_GOVERtxt.setOrigin(Retry_GOVERtxt.getLocalBounds().width / 2, Retry_GOVERtxt.getLocalBounds().height / 2);
	Retry_GOVERtxt.setOutlineColor(Color::Black);
	Retry_GOVERtxt.setOutlineThickness(5);

	Skip_GOVERtxt.setFont(font);
	Skip_GOVERtxt.setCharacterSize(50);
	Skip_GOVERtxt.setFillColor(Color(230, 194, 0));
	Skip_GOVERtxt.setString("SKIP");
	Skip_GOVERtxt.setPosition((GameOverbuttons_mnu[0].getGlobalBounds().left + GameOverbuttons_mnu[0].getGlobalBounds().width / 2) + 30, (GameOverbuttons_mnu[0].getGlobalBounds().top + GameOverbuttons_mnu[0].getGlobalBounds().height / 2) - 10);
	Skip_GOVERtxt.setOrigin(Retry_GOVERtxt.getLocalBounds().width / 2, Retry_GOVERtxt.getLocalBounds().height / 2);
	Skip_GOVERtxt.setOutlineColor(Color::Black);
	Skip_GOVERtxt.setOutlineThickness(5);

	GameOver_txt.setFont(font);
	GameOver_txt.setCharacterSize(65);
	GameOver_txt.setFillColor(Color(230, 194, 0));
	GameOver_txt.setString("GAMEOVER");
	GameOver_txt.setPosition((GameOverbuttons_mnu[1].getGlobalBounds().left + GameOverbuttons_mnu[1].getGlobalBounds().width / 2), (GameOverbuttons_mnu[1].getGlobalBounds().top + GameOverbuttons_mnu[1].getGlobalBounds().height / 2) - 270);
	GameOver_txt.setOrigin(GameOver_txt.getLocalBounds().width / 2, GameOver_txt.getLocalBounds().height / 2);
	GameOver_txt.setOutlineColor(Color::Black);
	GameOver_txt.setOutlineThickness(5);

	//Win Menu Text
	Continue_Wintxt.setFont(font);
	Continue_Wintxt.setCharacterSize(50);
	Continue_Wintxt.setFillColor(Color(230, 194, 0));
	Continue_Wintxt.setString("CONTINUE");
	Continue_Wintxt.setPosition((ContinueButton_Winmnu.getGlobalBounds().left + ContinueButton_Winmnu.getGlobalBounds().width / 2), (ContinueButton_Winmnu.getGlobalBounds().top + ContinueButton_Winmnu.getGlobalBounds().height / 2) - 5);
	Continue_Wintxt.setOrigin(Continue_Wintxt.getLocalBounds().width / 2, GameOver_txt.getLocalBounds().height / 2);
	Continue_Wintxt.setOutlineColor(Color::Black);
	Continue_Wintxt.setOutlineThickness(5);

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
	case LEVEL_MENU:

		break;
	case PAUSE_MENU:
		MouseInput_mnu(event, ResumeButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME);
		if (MouseInput_mnu(event, RetryButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME))
		{
			//call function reset
		}
		MouseInput_mnu(event, EndButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU);
		MouseInput_mnu(event, SettingButton_mnu, SettingsButton0_texture, SettingsButton0_texture, ButtonClick, SETTINGS);
		//Damp(Current_mnu, Target_mnu, 200, dt);
		break;
	case WIN_MENU:
		MouseInput_mnu(event, ContinueButton_Winmnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU);
		break;
	case SETTINGS:
		// code for handling settings menu input
		break;
	case GAMEOVER:
		MouseInput_mnu(event, GameOverbuttons_mnu[0], stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU);
		MouseInput_mnu(event, GameOverbuttons_mnu[2], stone_button_0_texture, stone_button_1_texture, ButtonClick, MAIN_MENU);
		if (MouseInput_mnu(event, GameOverbuttons_mnu[1], stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME))
		{
			//call function reset
		}
		break;
	case GAME:
		// code for handling game UI input
		MouseInput_mnu(event, PauseIcon_mnu, pause_icon_texture, pause_icon_texture, ButtonClick, PAUSE_MENU);
		break;
	default:
		break;
	}
}

void OnUpdatedGameStateMenu() {
	// do stuff here exactly when the gameState is changed

	switch (gameState)
	{
	case MAIN_MENU:
		break;
	case LEVEL_MENU:
		break;
	case PAUSE_MENU:
		break;
	case WIN_MENU:
		break;
	case SETTINGS:
		break;
	case GAMEOVER:
		break;
	case GAME:
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
		GameoverMenu_Movement(Target_Down_mnu);
		break;
	case LEVEL_MENU:
		if (PreviousMenu_State == GAMEOVER)
		{
			GameoverMenu_Movement(Target_Down_mnu);
		}
		else if (PreviousMenu_State == PAUSE_MENU)
		{
			PauseMenu_Movement(Target_Down_mnu);
		}
		else if (PreviousMenu_State == WIN_MENU)
		{
			WinMenu_Movement(Target_Down_mnu);
		}
		break;
	case PAUSE_MENU:
		PreviousMenu_State = PAUSE_MENU;
		PauseMenu_Movement(Target_up_mnu);
		break;
	case WIN_MENU:
		PreviousMenu_State = WIN_MENU;
		WinMenu_Movement(Target_up_mnu);
		break;
	case SETTINGS:
		// code for settings menu
		break;
	case GAMEOVER:
		PreviousMenu_State = GAMEOVER;
		GameoverMenu_Movement(Target_up_mnu);
		break;
	case GAME:
		// code for game UI
		//GameoverMenu_Movement(Target_Down_mnu);
		//PauseMenu_Movement(Target_Down_mnu);
		if (PreviousMenu_State == GAMEOVER)
		{
			GameoverMenu_Movement(Target_Down_mnu);
		}
		else if (PreviousMenu_State == PAUSE_MENU)
		{
			PauseMenu_Movement(Target_Down_mnu);
		}
		else if (PreviousMenu_State == WIN_MENU)
		{
			WinMenu_Movement(Target_Down_mnu);
		}
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
		if (Current_position_mnu != Target_Down_mnu)
		{

			if (PreviousMenu_State == GAMEOVER)
			{
				window.draw(Stone_mnu);
				for (int i = 0; i < 3; i++)
				{
					window.draw(GameOverbuttons_mnu[i]);
				}
				window.draw(Menu_GOVERtxt);
				window.draw(Retry_GOVERtxt);
				window.draw(Skip_GOVERtxt);
				window.draw(GameOver_txt);
			}
		}
		//draw the things of the Main menu down here

		break;
	case LEVEL_MENU:
		if (Current_position_mnu != Target_Down_mnu)
		{

			if (PreviousMenu_State == GAMEOVER)
			{
				window.draw(Stone_mnu);
				for (int i = 0; i < 3; i++)
				{
					window.draw(GameOverbuttons_mnu[i]);
				}
				window.draw(Menu_GOVERtxt);
				window.draw(Retry_GOVERtxt);
				window.draw(Skip_GOVERtxt);
				window.draw(GameOver_txt);
			}
			else if (PreviousMenu_State == PAUSE_MENU)
			{
				window.draw(Stone_mnu);
				window.draw(EndButton_Pausemnu);
				window.draw(RetryButton_Pausemnu);
				window.draw(ResumeButton_Pausemnu);
				window.draw(SettingButton_mnu);
				window.draw(End_Pausetxt);
				window.draw(Retry_Pausetxt);
				window.draw(Resume_Pausetxt);
				window.draw(Pause_txt);
			}
			else if (PreviousMenu_State == WIN_MENU)
			{
				window.draw(Stone_mnu);
				window.draw(ContinueButton_Winmnu);
				window.draw(Continue_Wintxt);
			}
		}
		//draw the things of the level menu down here

		break;

	case PAUSE_MENU:
		DrawGame(true);
		window.draw(Dimmed_Backgriund);
		window.draw(Stone_mnu);
		window.draw(EndButton_Pausemnu);
		window.draw(RetryButton_Pausemnu);
		window.draw(ResumeButton_Pausemnu);
		window.draw(SettingButton_mnu);
		window.draw(End_Pausetxt);
		window.draw(Retry_Pausetxt);
		window.draw(Resume_Pausetxt);
		window.draw(Pause_txt);
		break;

	case WIN_MENU:
		DrawGame(true);
		window.draw(Dimmed_Backgriund);
		window.draw(Stone_mnu);
		window.draw(ContinueButton_Winmnu);
		window.draw(Continue_Wintxt);
		break;

	case SETTINGS:
		// code for drawing settings menu
		DrawGame(true);
		window.draw(Dimmed_Backgriund);
		if (Current_position_mnu != Target_Down_mnu)
		{

			if (PreviousMenu_State == PAUSE_MENU)
			{
				window.draw(Stone_mnu);
				window.draw(EndButton_Pausemnu);
				window.draw(RetryButton_Pausemnu);
				window.draw(ResumeButton_Pausemnu);
				window.draw(SettingButton_mnu);
				window.draw(End_Pausetxt);
				window.draw(Retry_Pausetxt);
				window.draw(Resume_Pausetxt);
				window.draw(Pause_txt);
			}
		}
		break;

	case GAMEOVER:
		DrawGame(true);
		window.draw(Dimmed_Backgriund);
		window.draw(Stone_mnu);
		for (int i = 0; i < 3; i++)
		{
			window.draw(GameOverbuttons_mnu[i]);
		}
		window.draw(Menu_GOVERtxt);
		window.draw(Retry_GOVERtxt);
		window.draw(Skip_GOVERtxt);
		window.draw(GameOver_txt);
		break;

	case GAME:
		// code for drawing game UI
		window.draw(PauseIcon_mnu);
		if (Current_position_mnu != Target_Down_mnu)
		{

			if (PreviousMenu_State == GAMEOVER)
			{
				window.draw(Stone_mnu);
				for (int i = 0; i < 3; i++)
				{
					window.draw(GameOverbuttons_mnu[i]);
				}
				window.draw(Menu_GOVERtxt);
				window.draw(Retry_GOVERtxt);
				window.draw(Skip_GOVERtxt);
				window.draw(GameOver_txt);
			}
			else if (PreviousMenu_State == PAUSE_MENU)
			{
				window.draw(Stone_mnu);
				window.draw(EndButton_Pausemnu);
				window.draw(RetryButton_Pausemnu);
				window.draw(ResumeButton_Pausemnu);
				window.draw(SettingButton_mnu);
				window.draw(End_Pausetxt);
				window.draw(Retry_Pausetxt);
				window.draw(Resume_Pausetxt);
				window.draw(Pause_txt);
			}
			else if (PreviousMenu_State == WIN_MENU)
			{
				window.draw(Stone_mnu);
				window.draw(ContinueButton_Winmnu);
				window.draw(Continue_Wintxt);
			}
		}
		break;
	default:
		break;
	}

	fpsDisplay.setString(to_string((int)round(1.0f / dt)));
	window.draw(fpsDisplay);
}
