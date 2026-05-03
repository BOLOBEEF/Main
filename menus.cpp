
// MENUS AND UI


// Settings :



// Structs and enums

enum FadeState 
{
	NoFading,
	FadingUp,
	FadingDown
};
FadeState currentFadeState = NoFading;

enum DimState
{
	NoDimming,
	DimmingUp,
	DimmingDown
};
DimState currentDimState = NoDimming;

enum settingDimState
{
	NoSettingsDimming,

	PauseToSettingsDimmingUp,
	MainTo_SettingsOtCredits_DimmingUp,

	PauseToSettingsDimmingDown,
	MainTo_SettingsOrCredits_DimmingDown
};
settingDimState currentSettingsDimState = NoSettingsDimming;

// Runtime variables
float dimingSpeed, dimPercentage = 0;
float settingAndCredits_DimmingSpeed, settingsAndCreditsDimPercentage = 0;
float fadeSpeed = 155, fadePercentage = 0;
float holdSpeed = 40, holdLimit = 50;
//Why hold? -> because when I make the fade transition, I change the game state when alpha becomes 255, so the pause menu won't move until this case, it will move when we start decrementing the alpha
//which is not like the original game

int Minutes_clock = 0, Seconds_clock = 0;
int tenth_min = 0, unit_min = 0;
int tenth_sec = 0, unit_sec = 0;
float totalTimePassed = 0;
float clockTikingSpeed = 0;

TutorialTxt temporary_txt;


GameState FadeTransitionMenuState = MAIN_MENU;
RectangleShape Game_Dimmed_Background;
RectangleShape settingsAndCredits_Dimmed_Background;
RectangleShape FadingTransitionBackground;

Vector2f Target_up_mnu = Vector2f(windowSize.x / 2, windowSize.y / 2);
Vector2f Target_Down_mnu = Vector2f(windowSize.x / 2, windowSize.y / 2 + 1000);
Vector2f Current_position_mnu = Target_Down_mnu;
Vector2f Current_position_SettingsOrCredits_mnu = Target_Down_mnu;
Vector2f Current_Target;

Sprite Stone_mnu;
Sprite clockTiking_game;
Sprite SettingButton_Pausemnu;
Sprite EndButton_Pausemnu;
Sprite RetryButton_Pausemnu;
Sprite ResumeButton_Pausemnu;
Sprite PauseIcon_mnu;

//main menu
Sprite MainMenuBackground_mnu;
Sprite GameName_mnu;
Sprite PlayButton_mnu;
Sprite CreditsButton_mnu;
Sprite ExitButton_mnu;
Sprite SettingsButton_Mainmnu;
Sprite IdleFbBodymnu;
Sprite IdleFbHeadmnu;
Sprite IdleWgBodymnu;
Sprite IdleWgHeadmnu;
//Sprite dustAnimation;

//settings from main
Sprite SoundButton_MainToSetting;
Sprite MusicButton_MainToSetting;
Sprite OkButton_MainToSetting;
Sprite SettingsMenuBox_MainToSetting;
bool isSoundButtonClicked_MainToSetting = false;
bool isMusicButtonClicked_MainToSetting = false;

//settings from pause
Sprite SoundButton_PauseToSetting;
Sprite MusicButton_PauseToSetting;
Sprite OkButton_PauseToSetting;
Sprite SettingsMenuBox_PauseToSetting;
bool isSoundButtonClicked_PauseToSetting = false;
bool isMusicButtonClicked_PauseToSetting = false;

//Level menu
Sprite LevelMenuBackground_mnu;
Sprite LevelMenuBox_mnu[2][3];
Sprite DiamondLevel_mnu[2][3];
Sprite LevelSelection_mnu[2][3];
Sprite LevelEntry_mnu[2][3];
Sprite BackButtonLevel_mnu;
Text LevelNumber_mnu[2][3];
Text LevelTimeRate[2][3];

//gameover
Sprite GameOverbuttons_mnu[3];

//Credits
Sprite BackButtonCredits_mnu;
Sprite CreditsMenuBox_mnu;

Sprite ContinueButton_Winmnu;
Sprite MaleAndFemale_icon_Winmnu;
Sprite diamondRating_icon_Winmnu;
Sprite timerRating_icon_Winmnu;
Sprite arrowIcon_Winmnu;
Sprite levelDiamond_Winmnu;
Sprite checkOrCrossMaleOrFemale_icon_Winmnu, checkOrCrossDiamonds_icon_Winmnu, checkOrCrossTimer_icon_Winmnu;
float ratingOrder = 0, ratingOrder_Speed = 200;
bool MaleAndFemale_turn = false, diamondRating_turn = false, timerRating_turn = false, levelAndArrowIcon_turn = false;
bool isMaleAndFemaleSoundPlayed = false, isdiamondSoundPlayed = false, istimerSoundPlayed = false, islevelAndArrowSoundPlayed = false;
bool MainMenuSettings = true, LastWasSettings = false;

bool Settings_from_MainMenu = true;

//because i want to play the sounds of each rating once in the game loop not to rerun it each iteration 


Font font;
Text fpsDisplay;
Text End_Pausetxt, Resume_Pausetxt, Retry_Pausetxt, Pause_txt;
Text Menu_GOVERtxt, Retry_GOVERtxt, Levels_GOVERtxt, GameOver_txt;
Text Continue_Wintxt;
Text NoText; // to use it as a default value in the MouseInput_mnu function
// cursor Variables
Text OkButtontxt_MainToSetting;
Text OkButtontxt_PauseToSetting;
Text stopwatch_txt;
Text MenusandSoundsCredits_txt[2], GamelogicCredits_txt[4], AnimationandTexturesCredits_txt[2];

Sprite cursorAndpointerSprite;

int finalScore = 0;
// Functions
void initializeTutorialText()
{
	temporary_txt.text.setString("\nUSE THE ARROW KEYS\n    TO MOVE FIREBOY\n");
	temporary_txt.text.setPosition(430, 900);
	gameTutorials.Add(temporary_txt);

	temporary_txt.text.setString("\nUSE A.W.D\nTO MOVE WATERGIRL\n");
	temporary_txt.text.setPosition(430, 750);
	gameTutorials.Add(temporary_txt);

	temporary_txt.text.setString("\n\t\t\t\t  NEVER MIX FIRE & WATER!  \t\t\t\t\n         \n");
	temporary_txt.text.setPosition(1146, 870);
	gameTutorials.Add(temporary_txt);

	temporary_txt.text.setString("\nGREEN GOO\n    \tHURTS THEM BOTH\t\t\t\t\t\n\n");
	temporary_txt.text.setPosition(1200, 650);
	gameTutorials.Add(temporary_txt);

	temporary_txt.text.setString("PRESS SPACE TO OPEN THE LEVER\n\t\t   LEVERS REMAIN AS\n\t\t    YOU LEAVE THEM\n");
	temporary_txt.text.setPosition(500, 610);
	gameTutorials.Add(temporary_txt);

	temporary_txt.text.setString("\nBUTTONS HOWEVER\n\t\t\t     MUST BE HELD\n");
	temporary_txt.text.setPosition(670, 430);
	gameTutorials.Add(temporary_txt);

	temporary_txt.text.setString("\nTHEY CAN PUSH\n\t\t      BOXES AROUND\n");
	temporary_txt.text.setPosition(1465, 250);
	gameTutorials.Add(temporary_txt);

	temporary_txt.text.setString("\nDONT'T FORGET TO\nGRAB SOME\nDIAMONDS!\n\n");
	temporary_txt.text.setPosition(350, 100);
	gameTutorials.Add(temporary_txt);

	temporary_txt.text.setString("\nOPEN THE FINISH DOORS\nBY STANDING IN FRONT OF THEM.\n");
	temporary_txt.text.setPosition(windowSize.x / 2 + 70, 95);
	gameTutorials.Add(temporary_txt);

	for (int i = 0; i < gameTutorials.count; i++)
	{
		gameTutorials.elements[i].Initialize(font);
	}
}
void UpdateTimeCounters() {
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			LevelTimeRate[i][j].setString("Time : " + to_string(levelProgress[i * 3 + j].lowestTime));
		}
	}
}
void changeCursorColor(Event event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		UpdateAnimation(cursorAndpointerSprite, pointer_texture);
	}
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		UpdateAnimation(cursorAndpointerSprite, cursor_texture);
	}
}
void RatingCheck(bool maleAndFemale_case = false, bool DiamondCollection_case = false, bool BeforeTimeOut_case = false)
{
	int numberOfChecks = 0;
	if (maleAndFemale_case == true)
	{
		ApplyTexture(checkOrCrossMaleOrFemale_icon_Winmnu, LoadTexture::tick_icon_texture, Vector2f(90, 90));
		UpdateAnimation(checkOrCrossMaleOrFemale_icon_Winmnu, tick_icon_texture);
		checkOrCrossMaleOrFemale_icon_Winmnu.setPosition(windowSize.x / 2 - 205, windowSize.y / 2 - 195);
		numberOfChecks += 1;
	}
	else if (maleAndFemale_case == false)
	{
		ApplyTexture(checkOrCrossMaleOrFemale_icon_Winmnu, LoadTexture::x_icon_texture, Vector2f(75, 75));
		UpdateAnimation(checkOrCrossMaleOrFemale_icon_Winmnu, x_icon_texture);
		checkOrCrossMaleOrFemale_icon_Winmnu.setPosition(windowSize.x / 2 - 205, windowSize.y / 2 - 190);
	}

	if (DiamondCollection_case == true)
	{
		ApplyTexture(checkOrCrossDiamonds_icon_Winmnu, LoadTexture::tick_icon_texture, Vector2f(90, 90));
		UpdateAnimation(checkOrCrossDiamonds_icon_Winmnu, tick_icon_texture);
		checkOrCrossDiamonds_icon_Winmnu.setPosition(windowSize.x / 2 - 205, windowSize.y / 2 - 85);
		numberOfChecks += 1;
	}
	else if (DiamondCollection_case == false)
	{
		ApplyTexture(checkOrCrossDiamonds_icon_Winmnu, LoadTexture::x_icon_texture, Vector2f(75, 75));
		UpdateAnimation(checkOrCrossDiamonds_icon_Winmnu, x_icon_texture);
		checkOrCrossDiamonds_icon_Winmnu.setPosition(windowSize.x / 2 - 205, windowSize.y / 2 - 85);
	}

	if (BeforeTimeOut_case == true)
	{
		ApplyTexture(checkOrCrossTimer_icon_Winmnu, LoadTexture::tick_icon_texture, Vector2f(90, 90));
		UpdateAnimation(checkOrCrossTimer_icon_Winmnu, tick_icon_texture);
		checkOrCrossTimer_icon_Winmnu.setPosition(windowSize.x / 2 - 205, windowSize.y / 2);
		numberOfChecks += 1;
	}
	else if (BeforeTimeOut_case == false)
	{
		ApplyTexture(checkOrCrossTimer_icon_Winmnu, LoadTexture::x_icon_texture, Vector2f(75, 75));
		UpdateAnimation(checkOrCrossTimer_icon_Winmnu, x_icon_texture);
		checkOrCrossTimer_icon_Winmnu.setPosition(windowSize.x / 2 - 205, windowSize.y / 2 + 20);
	}
	finalScore = numberOfChecks;
}

bool MouseInput_mnu(Event event, Sprite& ButtonClicked, LoadTexture Currnet_texture_enum, LoadTexture Desired_texture_enum, MenuSoundEffect Sound_Played_mnu, GameState state_mnu, bool fadeTransition, Text& buttonText = NoText)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			UpdateAnimation(ButtonClicked, Desired_texture_enum);
			buttonText.setScale(0.97, 0.97);
			return true;
		}
	}
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			UpdateAnimation(ButtonClicked, Currnet_texture_enum);
			buttonText.setScale(1, 1);
			PlayMenuSoundEffect(Sound_Played_mnu);
			if (fadeTransition)
			{
				if (currentFadeState == NoFading)
				{
					currentFadeState = FadingUp;
					FadeTransitionMenuState = state_mnu;
				}
			}
			else if(!fadeTransition) UpdateGameState(state_mnu);
			
			return true;
		}
		else
		{
			UpdateAnimation(ButtonClicked, Currnet_texture_enum);
			buttonText.setScale(1, 1);
			UpdateAnimation(cursorAndpointerSprite, cursor_texture);
		}
	}

	return false;
}
bool MuteSound(Event event, Sprite& ButtonClicked, Sprite& SameButton, LoadTexture Unmuted ,LoadTexture Muted, MenuSoundEffect Sound_Played_mnu, bool SoundOn)
{
	
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !isSoundButtonClicked_MainToSetting)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			ApplyTexture(ButtonClicked, Muted, Vector2f(113, 109));
			ApplyTexture(SameButton, Muted, Vector2f(113, 109));
			ButtonClicked.setScale(1.25, 1.25);
			SameButton.setScale(1.25, 1.25);
			isSoundButtonClicked_MainToSetting = true;
			MuteAudio();
		}
	}
	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && isSoundButtonClicked_MainToSetting)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			ApplyTexture(ButtonClicked, Unmuted, Vector2f(113, 109));
			ApplyTexture(SameButton, Unmuted, Vector2f(113, 109));
			ButtonClicked.setScale(1.25, 1.25);
			SameButton.setScale(1.25, 1.25);
			isSoundButtonClicked_MainToSetting = false;
			UnmuteAudio();
		}
	}
	return true;
}
bool MuteMusic(Event event, Sprite& ButtonClicked, Sprite& SameButton, LoadTexture Unmuted ,LoadTexture Muted, MenuSoundEffect Sound_Played_mnu, bool MusicOn)
{
	
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !isMusicButtonClicked_MainToSetting)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			ApplyTexture(ButtonClicked, Muted, Vector2f(113, 109));
			ApplyTexture(SameButton, Muted, Vector2f(113, 109));
			ButtonClicked.setScale(1.25, 1.25);
			SameButton.setScale(1.25, 1.25);
			isMusicButtonClicked_MainToSetting = true;
			MuteMusic();
		}
	}
	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && isMusicButtonClicked_MainToSetting)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			ApplyTexture(ButtonClicked, Unmuted, Vector2f(113, 109));
			ApplyTexture(SameButton, Unmuted, Vector2f(113, 109));
			ButtonClicked.setScale(1.25, 1.25);
			SameButton.setScale(1.25, 1.25);
			isMusicButtonClicked_MainToSetting = false;
			UnmuteMusic();
		}
	}
	return true;
}

void PauseMenu_Movement(Vector2f Desired_Target)
{
	Current_Target = Desired_Target;
	Current_position_mnu = Damp(Current_position_mnu, Current_Target, 25, dt);
	Stone_mnu.setPosition(Current_position_mnu);
	EndButton_Pausemnu.setPosition(Vector2f((windowSize.x / 2) - 35, (windowSize.y / 2) + 70) + Current_position_mnu - center);
	RetryButton_Pausemnu.setPosition(Vector2f((windowSize.x / 2) + 435, (windowSize.y / 2) + 70) + Current_position_mnu - center);
	ResumeButton_Pausemnu.setPosition(Vector2f((windowSize.x / 2 + 205), (windowSize.y / 2) + 220) + Current_position_mnu - center);
	SettingButton_Pausemnu.setPosition(Vector2f(Stone_mnu.getPosition().x + 485, Stone_mnu.getPosition().y - 240));
	End_Pausetxt.setPosition(Vector2f(EndButton_Pausemnu.getGlobalBounds().left + EndButton_Pausemnu.getGlobalBounds().width / 2, (EndButton_Pausemnu.getGlobalBounds().top + EndButton_Pausemnu.getGlobalBounds().height / 2) - 20));
	Retry_Pausetxt.setPosition(Vector2f(RetryButton_Pausemnu.getGlobalBounds().left + RetryButton_Pausemnu.getGlobalBounds().width / 2, (RetryButton_Pausemnu.getGlobalBounds().top + RetryButton_Pausemnu.getGlobalBounds().height / 2) - 20));
	Resume_Pausetxt.setPosition(Vector2f(ResumeButton_Pausemnu.getGlobalBounds().left + ResumeButton_Pausemnu.getGlobalBounds().width / 2, (ResumeButton_Pausemnu.getGlobalBounds().top + ResumeButton_Pausemnu.getGlobalBounds().height / 2) - 20));
	Pause_txt.setPosition(Vector2f((ResumeButton_Pausemnu.getGlobalBounds().left + ResumeButton_Pausemnu.getGlobalBounds().width / 2), (ResumeButton_Pausemnu.getGlobalBounds().top + ResumeButton_Pausemnu.getGlobalBounds().height / 2) - 400));
}
void WinMenu_Movement(Vector2f Desired_Target)
{
	Current_Target = Desired_Target;
	Current_position_mnu = Damp(Current_position_mnu, Current_Target, 25, dt);
	Stone_mnu.setPosition(Current_position_mnu);
	ContinueButton_Winmnu.setPosition(Vector2f((windowSize.x / 2) + 270, (windowSize.y / 2) + 200) + Current_position_mnu - center);
	MaleAndFemale_icon_Winmnu.setPosition(Vector2f(windowSize.x / 2 - 330, windowSize.y / 2 - 190) + Current_position_mnu - center);
	diamondRating_icon_Winmnu.setPosition(Vector2f(windowSize.x / 2 - 330, windowSize.y / 2 - 80) + Current_position_mnu - center);
	timerRating_icon_Winmnu.setPosition(Vector2f(windowSize.x / 2 - 330, windowSize.y / 2 + 20) + Current_position_mnu - center);
	arrowIcon_Winmnu.setPosition(Vector2f(windowSize.x / 2, windowSize.y / 2 - 95) + Current_position_mnu - center);
	levelDiamond_Winmnu.setPosition(Vector2f(windowSize.x / 2 + 225, windowSize.y / 2 - 95) + Current_position_mnu - center);

	checkOrCrossMaleOrFemale_icon_Winmnu.setPosition(Vector2f(windowSize.x / 2 - 205, windowSize.y / 2 - 190) + Current_position_mnu - center);
	checkOrCrossDiamonds_icon_Winmnu.setPosition(Vector2f(windowSize.x / 2 - 205, windowSize.y / 2 - 90) + Current_position_mnu - center);
	checkOrCrossTimer_icon_Winmnu.setPosition(Vector2f(windowSize.x / 2 - 205, windowSize.y / 2 + 15) + Current_position_mnu - center);

	if (levelAndArrowIcon_turn)
	{
		ApplyTexture(arrowIcon_Winmnu, LoadTexture::arrow_icon1_texture, Vector2f(150, 100));
		UpdateAnimation(arrowIcon_Winmnu, arrow_icon1_texture);
		arrowIcon_Winmnu.setPosition(Vector2f(windowSize.x / 2, windowSize.y / 2 - 95) + Current_position_mnu - center);
		if (finalScore == 1)
		{
			ApplyTexture(levelDiamond_Winmnu, LoadTexture::diamonds_purple_texture, Vector2f(150, 150));
			UpdateAnimation(levelDiamond_Winmnu, diamonds_purple_texture);
			levelDiamond_Winmnu.setPosition(Vector2f(windowSize.x / 2 + 225, windowSize.y / 2 - 95) + Current_position_mnu - center);
		}
		else if (finalScore == 2)
		{
			ApplyTexture(levelDiamond_Winmnu, LoadTexture::diamonds_orange_texture, Vector2f(150, 150));
			UpdateAnimation(levelDiamond_Winmnu, diamonds_orange_texture);
			levelDiamond_Winmnu.setPosition(Vector2f(windowSize.x / 2 + 225, windowSize.y / 2 - 95) + Current_position_mnu - center);
		}
		else if (finalScore == 3)
		{
			ApplyTexture(levelDiamond_Winmnu, LoadTexture::diamonds_green_texture, Vector2f(150, 150));
			UpdateAnimation(levelDiamond_Winmnu, diamonds_green_texture);
			levelDiamond_Winmnu.setPosition(Vector2f(windowSize.x / 2 + 225, windowSize.y / 2 - 95) + Current_position_mnu - center);
		}
	}
	Continue_Wintxt.setPosition((ContinueButton_Winmnu.getGlobalBounds().left + ContinueButton_Winmnu.getGlobalBounds().width / 2), (ContinueButton_Winmnu.getGlobalBounds().top + ContinueButton_Winmnu.getGlobalBounds().height / 2) - 5);
}
void GameoverMenu_Movement(Vector2f Desired_Target)
{
	Current_Target = Desired_Target;
	Current_position_mnu = Damp(Current_position_mnu, Current_Target, 25, dt);
	Stone_mnu.setPosition(Current_position_mnu);
	int x_shift_mnu = 350;
	for (int i = 0; i < 3; i++)
	{
		GameOverbuttons_mnu[i].setPosition(Vector2f(((windowSize.x / 2) + x_shift_mnu + 200), ((windowSize.y / 2) + 145)) + Current_position_mnu - center);
		x_shift_mnu -= 350;
	}
	Menu_GOVERtxt.setPosition((GameOverbuttons_mnu[2].getGlobalBounds().left + GameOverbuttons_mnu[2].getGlobalBounds().width / 2), (GameOverbuttons_mnu[2].getGlobalBounds().top + GameOverbuttons_mnu[2].getGlobalBounds().height / 2) - 15);
	Retry_GOVERtxt.setPosition((GameOverbuttons_mnu[1].getGlobalBounds().left + GameOverbuttons_mnu[1].getGlobalBounds().width / 2), (GameOverbuttons_mnu[1].getGlobalBounds().top + GameOverbuttons_mnu[1].getGlobalBounds().height / 2) - 15);
	Levels_GOVERtxt.setPosition((GameOverbuttons_mnu[0].getGlobalBounds().left + GameOverbuttons_mnu[0].getGlobalBounds().width / 2), (GameOverbuttons_mnu[0].getGlobalBounds().top + GameOverbuttons_mnu[0].getGlobalBounds().height / 2) - 10);
	GameOver_txt.setPosition((GameOverbuttons_mnu[1].getGlobalBounds().left + GameOverbuttons_mnu[1].getGlobalBounds().width / 2), (GameOverbuttons_mnu[1].getGlobalBounds().top + GameOverbuttons_mnu[1].getGlobalBounds().height / 2) - 270);
}
void SettingMenu_Movement(Vector2f Desired_Target, bool fromMain)
{
	Current_Target = Desired_Target;
	Current_position_SettingsOrCredits_mnu = Damp(Current_position_SettingsOrCredits_mnu, Current_Target, 25, dt);
	if (fromMain)
	{
		SettingsMenuBox_MainToSetting.setPosition(Current_position_SettingsOrCredits_mnu);
		SoundButton_MainToSetting.setPosition(Vector2f(700, 530) + Current_position_SettingsOrCredits_mnu - center);
		MusicButton_MainToSetting.setPosition(Vector2f(1200, 530) + Current_position_SettingsOrCredits_mnu - center);
		OkButton_MainToSetting.setPosition(Vector2f(1155, 750) + Current_position_SettingsOrCredits_mnu - center);
		OkButtontxt_MainToSetting.setPosition(Vector2f(903, 710) + Current_position_SettingsOrCredits_mnu - center);
	}
	else
	{
		SettingsMenuBox_PauseToSetting.setPosition(Current_position_SettingsOrCredits_mnu);
		SoundButton_PauseToSetting.setPosition(Vector2f(700, 530) + Current_position_SettingsOrCredits_mnu - center);
		MusicButton_PauseToSetting.setPosition(Vector2f(1200, 530) + Current_position_SettingsOrCredits_mnu - center);
		OkButton_PauseToSetting.setPosition(Vector2f(1155, 750) + Current_position_SettingsOrCredits_mnu - center);
		OkButtontxt_PauseToSetting.setPosition(Vector2f(903, 710) + Current_position_SettingsOrCredits_mnu - center);
	}
	// I Will Handle this After You finish Settings Menu
}
void CreditsMenu_Movement(Vector2f Desired_Target)
{
	Current_Target = Desired_Target;
	Current_position_SettingsOrCredits_mnu = Damp(Current_position_SettingsOrCredits_mnu, Current_Target, 25, dt);
	CreditsMenuBox_mnu.setPosition(Current_position_SettingsOrCredits_mnu);
	BackButtonCredits_mnu.setPosition(Vector2f(534, 790) + Current_position_SettingsOrCredits_mnu - center);
	MenusandSoundsCredits_txt[0].setPosition(Vector2f(520, 250) + Current_position_SettingsOrCredits_mnu - center);
	MenusandSoundsCredits_txt[1].setPosition(Vector2f(430, 320) + Current_position_SettingsOrCredits_mnu - center);
	AnimationandTexturesCredits_txt[0].setPosition(Vector2f(975, 700) + Current_position_SettingsOrCredits_mnu - center);
	AnimationandTexturesCredits_txt[1].setPosition(Vector2f(920, 770) + Current_position_SettingsOrCredits_mnu - center);
	GamelogicCredits_txt[0].setPosition(Vector2f(830, 420) + Current_position_SettingsOrCredits_mnu - center);
	GamelogicCredits_txt[1].setPosition(Vector2f(815, 490) + Current_position_SettingsOrCredits_mnu - center);
	GamelogicCredits_txt[2].setPosition(Vector2f(765, 540) + Current_position_SettingsOrCredits_mnu - center);
	GamelogicCredits_txt[3].setPosition(Vector2f(730, 590) + Current_position_SettingsOrCredits_mnu - center);
}

void InitializeMenu()
{
	font.loadFromFile("Main/Assets/Fonts/trajanpro-bold.otf");
	fpsDisplay.setFont(font);
	fpsDisplay.setCharacterSize(24);

	//Cursor 
	CursorAndPointer.setSmooth(true);
	ApplyTexture(cursorAndpointerSprite, LoadTexture::cursor_texture, Vector2f(45, 30));
	UpdateAnimation(cursorAndpointerSprite, cursor_texture);

	//Dimmed Background
	Game_Dimmed_Background.setSize(Vector2f(window.getSize().x, window.getSize().y));
	Game_Dimmed_Background.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);

	//Setting Dimmed Background
	settingsAndCredits_Dimmed_Background.setSize(Vector2f(window.getSize().x, window.getSize().y));
	settingsAndCredits_Dimmed_Background.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);

	//fading Transition Background
	FadingTransitionBackground.setSize(Vector2f(window.getSize().x, window.getSize().y));
	FadingTransitionBackground.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);

	//clock
	clock_timer.setSmooth(true);
	ApplyTexture(clockTiking_game, LoadTexture::clock_timer_texture, Vector2f(310, 112));
	clockTiking_game.setPosition(windowSize.x / 2, (windowSize.y / 2) - 483);


	//Main menu
	main_menu_background.setSmooth(true);
	ApplyTexture(MainMenuBackground_mnu, LoadTexture::main_menu_background_texture, Vector2f(windowSize.x, windowSize.y));	
	MainMenuBackground_mnu.setPosition(windowSize.x / 2 ,windowSize.y / 2);	

	SettingsButton0.setSmooth(true);
	ApplyTexture(SettingsButton_Mainmnu, LoadTexture::SettingsButton0_texture, Vector2f(120, 120));
	SettingsButton_Mainmnu.setPosition(150, 860);

	game_name.setSmooth(true);
	ApplyTexture(GameName_mnu, LoadTexture::game_name_texture, Vector2f(860, 270));
	GameName_mnu.setPosition(windowSize.x / 2, windowSize.y / 2 - 200);

	PlayButton.setSmooth(true);
	ApplyTexture(PlayButton_mnu, LoadTexture::PlayButton_texture, Vector2f(240, 160));
	PlayButton_mnu.setPosition(windowSize.x / 2, windowSize.y / 2 + 40);
	
	//dust.setSmooth(true);
	//ApplyTexture(dustAnimation, LoadTexture::dust_texture, Vector2f(2240, 98));
	//dustAnimation.setPosition(windowSize.x / 2 + 10, windowSize.y / 2 + 40);

	CreditsButton.setSmooth(true);
	ApplyTexture(CreditsButton_mnu, LoadTexture::CreditsButton_Texture, Vector2f(260, 173));
	CreditsButton_mnu.setPosition(windowSize.x / 2 + 350, windowSize.y / 2 + 150);

	ExitButton.setSmooth(true);
	ApplyTexture(ExitButton_mnu, LoadTexture::ExitButton_texture, Vector2f(240, 160));
	ExitButton_mnu.setPosition(windowSize.x / 2 - 350, windowSize.y / 2 + 150);

	ApplyTexture(IdleFbBodymnu, LoadTexture::fire_idle_body_texture, Vector2f(130, 172));
	IdleFbBodymnu.setScale(1.5, 1.5);
	IdleFbBodymnu.setPosition(windowSize.x / 2 - 100, windowSize.y / 2 + 390);

	ApplyTexture(IdleFbHeadmnu, LoadTexture::fire_idle_head_texture, Vector2f(2470, 300), Vector2f(1, 1), true, false);
	IdleFbHeadmnu.setScale(1.25, 1.25);
	IdleFbHeadmnu.setPosition(windowSize.x / 2 + 1362, windowSize.y / 2 + 390);

	ApplyTexture(IdleWgBodymnu, LoadTexture::water_body_idle_texture, Vector2f(1100, 200));
	IdleWgBodymnu.setScale(1.5, 1.5);
	IdleWgBodymnu.setPosition(windowSize.x / 2 + 100, windowSize.y / 2 + 390);

	ApplyTexture(IdleWgHeadmnu, LoadTexture::water_head_idle_texture, Vector2f(2470, 300), Vector2f(1, 1), true, false);
	IdleWgHeadmnu.setScale(1.25, 1.25);
	IdleWgHeadmnu.setPosition(windowSize.x / 2 + 2456, windowSize.y / 2 + 390);
	
	//Level menu
	LevelMenuBackground.setSmooth(true);
	ApplyTexture(LevelMenuBackground_mnu, LoadTexture::LevelMenuBackground_texture, Vector2f(windowSize.x, windowSize.y));
	LevelMenuBackground_mnu.setOrigin(LevelMenuBackground_mnu.getGlobalBounds().width / 2, LevelMenuBackground_mnu.getGlobalBounds().height / 2);
	LevelMenuBackground_mnu.setPosition(windowSize.x / 2, windowSize.y / 2);

	LevelMenuBox.setSmooth(true);
	Diamond0.setSmooth(true);
	SliderLightOn.setSmooth(true);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ApplyTexture(LevelMenuBox_mnu[i][j], LoadTexture::LevelMenuBox_Texture, Vector2f(500, 500));
			LevelMenuBox_mnu[i][j].setPosition(490 + (j * 500), 280 + (i * 500));

			ApplyTexture(DiamondLevel_mnu[i][j], LoadTexture::Diamond0_texture, Vector2f(69, 80));
			DiamondLevel_mnu[i][j].setPosition(500 + (j * 500), 280 + (i * 500));

			LevelNumber_mnu[i][j].setFont(font);
			LevelNumber_mnu[i][j].setCharacterSize(40);
			LevelNumber_mnu[i][j].setFillColor(Color(230, 194, 0));
			LevelNumber_mnu[i][j].setPosition(425 + (j * 500), 150 + (i * 500));
			LevelNumber_mnu[i][j].setOutlineColor(Color::Black);
			LevelNumber_mnu[i][j].setOutlineThickness(5);

			LevelTimeRate[i][j].setFont(font);
			LevelTimeRate[i][j].setCharacterSize(40);
			LevelTimeRate[i][j].setFillColor(Color(230, 194, 0));
			LevelTimeRate[i][j].setPosition(350 + (j * 500), 350 + (i * 500));
			LevelTimeRate[i][j].setOutlineColor(Color::Black);
			LevelTimeRate[i][j].setOutlineThickness(5);

			ApplyTexture(LevelSelection_mnu[i][j], LoadTexture::SliderLightOn_texture, Vector2f(55, 57));
			LevelSelection_mnu[i][j].setPosition(510 + (j * 500), 284 + (i * 500));
			LevelSelection_mnu[i][j].setScale(5.5, 5.5);
			
			ApplyTexture(LevelEntry_mnu[i][j], LoadTexture::LevelEntry_texture, Vector2f(85, 85));
			LevelEntry_mnu[i][j].setPosition(501 + (j * 500), 300 + (i * 500));
			LevelEntry_mnu[i][j].setScale(0.8, 0.8);
		}
	}

	ApplyTexture(BackButtonLevel_mnu, LoadTexture::BackButtonFull0_texture, Vector2f(259, 98));
	BackButtonLevel_mnu.setScale(1.1, 1.1);
	BackButtonLevel_mnu.setPosition(165, 525);

	//Credits menu
	ApplyTexture(CreditsMenuBox_mnu, LoadTexture::menu_box_texture, Vector2f(windowSize.x - 600, windowSize.y - 250));
	
	ApplyTexture(BackButtonCredits_mnu, LoadTexture::BackButtonFull0_texture, Vector2f(700, 170));
	BackButtonCredits_mnu.setScale(1.1, 1.1);

	//Settings from main
	menu_box.setSmooth(true);
	MuteButton0.setSmooth(true);
	MuteButton1.setSmooth(true);
	MusicButton0.setSmooth(true);
	MusicButton1.setSmooth(true);

	ApplyTexture(SettingsMenuBox_MainToSetting, LoadTexture::menu_box_texture, Vector2f(windowSize.x - 600, windowSize.y - 250));
	UpdateAnimation(SettingsMenuBox_MainToSetting, menu_box_texture);
	SettingsMenuBox_MainToSetting.setPosition(windowSize.x / 2, windowSize.y / 2);

	ApplyTexture(SoundButton_MainToSetting, LoadTexture::MuteButton0_texture, Vector2f(113, 109));
	SoundButton_MainToSetting.setScale(1.25, 1.25);
	
	ApplyTexture(MusicButton_MainToSetting, LoadTexture::MusicButton0_texture, Vector2f(113, 109));
	MusicButton_MainToSetting.setScale(1.25, 1.25);

	stone_button.setSmooth(true);
	ApplyTexture(OkButton_MainToSetting, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(OkButton_MainToSetting, stone_button_0_texture);
	OkButton_MainToSetting.setPosition(windowSize.x / 2, windowSize.y / 2);

	OkButtontxt_MainToSetting.setFont(font);
	OkButtontxt_MainToSetting.setCharacterSize(50);
	OkButtontxt_MainToSetting.setFillColor(Color(230, 194, 0));
	OkButtontxt_MainToSetting.setString("OK");
	OkButtontxt_MainToSetting.setOutlineColor(Color::Black);
	OkButtontxt_MainToSetting.setOutlineThickness(5);

	//setting from pause
	ApplyTexture(SettingsMenuBox_PauseToSetting, LoadTexture::menu_box_texture, Vector2f(windowSize.x - 600, windowSize.y - 250));
	UpdateAnimation(SettingsMenuBox_PauseToSetting, menu_box_texture);
	SettingsMenuBox_PauseToSetting.setPosition(windowSize.x / 2, windowSize.y / 2);

	ApplyTexture(SoundButton_PauseToSetting, LoadTexture::MuteButton0_texture, Vector2f(113, 109));
	SoundButton_PauseToSetting.setScale(1.25, 1.25);

	ApplyTexture(MusicButton_PauseToSetting, LoadTexture::MusicButton0_texture, Vector2f(113, 109));
	MusicButton_PauseToSetting.setScale(1.25, 1.25);

	ApplyTexture(OkButton_PauseToSetting, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(OkButton_PauseToSetting, stone_button_0_texture);
	OkButton_PauseToSetting.setPosition(windowSize.x / 2, windowSize.y / 2);

	OkButtontxt_PauseToSetting.setFont(font);
	OkButtontxt_PauseToSetting.setCharacterSize(50);
	OkButtontxt_PauseToSetting.setFillColor(Color(230, 194, 0));
	OkButtontxt_PauseToSetting.setString("OK");
	OkButtontxt_PauseToSetting.setOutlineColor(Color::Black);
	OkButtontxt_PauseToSetting.setOutlineThickness(5);

	//Pause menu
	ApplyTexture(Stone_mnu, LoadTexture::menu_box_texture, Vector2f(windowSize.x - 600, windowSize.y - 250));
	UpdateAnimation(Stone_mnu, menu_box_texture);
	Stone_mnu.setPosition(windowSize.x / 2, windowSize.y / 2);

	pause_icon.setSmooth(true);
	ApplyTexture(PauseIcon_mnu, LoadTexture::pause_icon_texture, Vector2f(65, 65));
	PauseIcon_mnu.setPosition(windowSize.x / 2 + 830, windowSize.y / 2 - 505);

	ApplyTexture(EndButton_Pausemnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(EndButton_Pausemnu, stone_button_0_texture);
	EndButton_Pausemnu.setPosition((windowSize.x / 2) - 35, (windowSize.y / 2) + 70);

	ApplyTexture(RetryButton_Pausemnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(RetryButton_Pausemnu, stone_button_0_texture);
	RetryButton_Pausemnu.setPosition((windowSize.x / 2) + 435, (windowSize.y / 2) + 70);

	ApplyTexture(ResumeButton_Pausemnu, LoadTexture::stone_button_0_texture, Vector2f(700, 170));
	UpdateAnimation(ResumeButton_Pausemnu, stone_button_0_texture);
	ResumeButton_Pausemnu.setPosition((windowSize.x / 2 + 205), (windowSize.y / 2) + 220);

	ApplyTexture(SettingButton_Pausemnu, LoadTexture::SettingsButton0_texture, Vector2f(105, 105));
	SettingButton_Pausemnu.setPosition((Stone_mnu.getGlobalBounds().left + Stone_mnu.getGlobalBounds().width / 2) + 485, Stone_mnu.getGlobalBounds().top + 170);

	//Game Over menu

	// stone background has been already set
	int x_shift_mnu = 350;
	for (int i = 0; i < 3; i++)
	{
		ApplyTexture(GameOverbuttons_mnu[i], LoadTexture::stone_button_0_texture, Vector2f(680, 150));
		UpdateAnimation(GameOverbuttons_mnu[i], stone_button_0_texture);
		GameOverbuttons_mnu[i].setPosition(((windowSize.x / 2) + x_shift_mnu + 200), ((windowSize.y / 2) + 145));
		x_shift_mnu -= 350;
	}

	//Win Menu 

	// stone background has been already set
	ApplyTexture(ContinueButton_Winmnu, LoadTexture::stone_button_0_texture, Vector2f(950, 170));
	UpdateAnimation(ContinueButton_Winmnu, stone_button_0_texture);
	ContinueButton_Winmnu.setPosition((windowSize.x / 2) + 270, (windowSize.y / 2) + 200);

	finished_icon.setSmooth(true);
	ApplyTexture(MaleAndFemale_icon_Winmnu, LoadTexture::finished_icon_texture, Vector2f(125, 145));
	UpdateAnimation(MaleAndFemale_icon_Winmnu, finished_icon_texture);
	MaleAndFemale_icon_Winmnu.setPosition(windowSize.x / 2 - 330, windowSize.y / 2 - 190);

	rating_diamonds.setSmooth(true);
	ApplyTexture(diamondRating_icon_Winmnu, LoadTexture::rating_diamonds_texture, Vector2f(110, 90));
	UpdateAnimation(diamondRating_icon_Winmnu, rating_diamonds_texture);
	diamondRating_icon_Winmnu.setPosition(windowSize.x / 2 - 330, windowSize.y / 2 - 80);

	rating_timer.setSmooth(true);
	ApplyTexture(timerRating_icon_Winmnu, LoadTexture::rating_timer_texture, Vector2f(135, 100));
	UpdateAnimation(timerRating_icon_Winmnu, rating_diamonds_texture);
	timerRating_icon_Winmnu.setPosition(windowSize.x / 2 - 330, windowSize.y / 2 + 20);

	arrow_icon0.setSmooth(true);
	arrow_icon1.setSmooth(true);
	ApplyTexture(arrowIcon_Winmnu, LoadTexture::arrow_icon0_texture, Vector2f(150, 100));
	UpdateAnimation(arrowIcon_Winmnu, arrow_icon0_texture);
	arrowIcon_Winmnu.setPosition(windowSize.x / 2, windowSize.y / 2 - 80);

	diamonds_green.setSmooth(true);
	diamonds_orange.setSmooth(true);
	diamonds_purple.setSmooth(true);
	ApplyTexture(levelDiamond_Winmnu, LoadTexture::diamonds_green_idle_texture, Vector2f(1195, 150));
	UpdateAnimation(levelDiamond_Winmnu, diamonds_green_idle_texture);
	levelDiamond_Winmnu.setPosition(windowSize.x / 2 + 748, windowSize.y / 2 - 95);
	
	x_icon.setSmooth(true);
	tick_icon.setSmooth(true);



	//RatingCheck(true, true, false);

	//Clock Text
	stopwatch_txt.setFont(font);
	stopwatch_txt.setCharacterSize(50);
	stopwatch_txt.setFillColor(Color(230, 194, 0));
	stopwatch_txt.setPosition((clockTiking_game.getGlobalBounds().left + clockTiking_game.getGlobalBounds().width / 2) - 66, (clockTiking_game.getGlobalBounds().top + clockTiking_game.getGlobalBounds().height / 2) - 60);
	stopwatch_txt.setOrigin((stopwatch_txt.getLocalBounds().width / 2), stopwatch_txt.getLocalBounds().height / 2);
	stopwatch_txt.setOutlineColor(Color::Black);
	stopwatch_txt.setOutlineThickness(5);

	//Tutorial Text

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

	Levels_GOVERtxt.setFont(font);
	Levels_GOVERtxt.setCharacterSize(50);
	Levels_GOVERtxt.setFillColor(Color(230, 194, 0));
	Levels_GOVERtxt.setString("LEVELS");
	Levels_GOVERtxt.setPosition((GameOverbuttons_mnu[0].getGlobalBounds().left + GameOverbuttons_mnu[0].getGlobalBounds().width / 2), (GameOverbuttons_mnu[0].getGlobalBounds().top + GameOverbuttons_mnu[0].getGlobalBounds().height / 2) - 10);
	Levels_GOVERtxt.setOrigin(Retry_GOVERtxt.getLocalBounds().width / 2, Retry_GOVERtxt.getLocalBounds().height / 2);
	Levels_GOVERtxt.setOutlineColor(Color::Black);
	Levels_GOVERtxt.setOutlineThickness(5);

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

	//Credits Menu Text
	MenusandSoundsCredits_txt[0].setString("Menus & Sounds");
	MenusandSoundsCredits_txt[1].setString("Ali Elsha3r - Omar Ayman");
	for (int i = 0; i < 2; i++)
	{
		MenusandSoundsCredits_txt[i].setFont(font);
		MenusandSoundsCredits_txt[i].setCharacterSize(35);
		MenusandSoundsCredits_txt[i].setFillColor(Color(230, 194, 0));
		MenusandSoundsCredits_txt[i].setOutlineColor(Color::Black);
		MenusandSoundsCredits_txt[i].setOutlineThickness(5);
	}

	GamelogicCredits_txt[0].setString("Game Logic");
	GamelogicCredits_txt[1].setString("Omar Ahmed");
	GamelogicCredits_txt[2].setString("Stephano Ashraf");
	GamelogicCredits_txt[3].setString("Osama Abdelmomen");
	for (int i = 0; i < 4; i++)
	{
		GamelogicCredits_txt[i].setFont(font);
		GamelogicCredits_txt[i].setCharacterSize(40);
		GamelogicCredits_txt[i].setFillColor(Color(230, 194, 0));
		GamelogicCredits_txt[i].setOutlineColor(Color::Black);
		GamelogicCredits_txt[i].setOutlineThickness(5);
	}
	
	AnimationandTexturesCredits_txt[0].setString("Animation & Textures");
	AnimationandTexturesCredits_txt[1].setString("Ahmed Manie3 - Ali Shokry");
	for (int i = 0; i < 2; i++)
	{
		AnimationandTexturesCredits_txt[i].setFont(font);
		AnimationandTexturesCredits_txt[i].setCharacterSize(35);
		AnimationandTexturesCredits_txt[i].setFillColor(Color(230, 194, 0));
		AnimationandTexturesCredits_txt[i].setOutlineColor(Color::Black);
		AnimationandTexturesCredits_txt[i].setOutlineThickness(5);
	}

	//Level Menu Text
	LevelNumber_mnu[0][0].setString("LEVEL 1");
	LevelNumber_mnu[0][1].setString("LEVEL 2");
	LevelNumber_mnu[0][2].setString("LEVEL 3");
	LevelNumber_mnu[1][0].setString("LEVEL 4");
	LevelNumber_mnu[1][1].setString("LEVEL 5");
	LevelNumber_mnu[1][2].setString("LEVEL 6");

	UpdateTimeCounters();

	PauseMenu_Movement(Target_Down_mnu);
	WinMenu_Movement(Target_Down_mnu);
	GameoverMenu_Movement(Target_Down_mnu);

	ApplyTexture(levelDiamond_Winmnu, LoadTexture::diamonds_purple_texture, Vector2f(150, 150));
	UpdateAnimation(levelDiamond_Winmnu, diamonds_purple_texture);
	SetSpriteOriginToCenter(levelDiamond_Winmnu, true);
	// code for initializing menu variables and objects
	// for example load sprites, set up text objects, etc.
}

void HandleMenuInput(Event event)
{

	switch (gameState)
	{
	case MAIN_MENU:
		// code for handling main menu input
		MouseInput_mnu(event, SettingsButton_Mainmnu, SettingsButton0_texture, SettingsButton0_texture, ButtonClick, SETTINGS, false);
		MouseInput_mnu(event, PlayButton_mnu, PlayButton_texture, PlayButton_texture, ButtonClick, LEVEL_MENU, true);
		MouseInput_mnu(event, CreditsButton_mnu, CreditsButton_Texture, CreditsButton_Texture, ButtonClick, CREDITS, false);
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			if (ExitButton_mnu.getGlobalBounds().contains(mousePosition))
			{
				window.close();
			}
		}
		break;
	case LEVEL_MENU:
		MouseInput_mnu(event, BackButtonLevel_mnu, BackButtonFull0_texture, BackButtonFull0_texture, ButtonClick, MAIN_MENU, true);

		arrowIcon_Winmnu.setTexture(arrow_icon0);
		levelDiamond_Winmnu.setTexture(diamonds_green);
		levelDiamond_Winmnu.setTextureRect(IntRect(0, 0, 128, 128));
		ratingOrder = 0;
		MaleAndFemale_turn = false;
		diamondRating_turn = false;
		timerRating_turn = false;
		levelAndArrowIcon_turn = false;
		isMaleAndFemaleSoundPlayed = false;
		isdiamondSoundPlayed = false;
		istimerSoundPlayed = false;
		islevelAndArrowSoundPlayed = false;
		WinMenu_Movement(Target_Down_mnu);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (MouseInput_mnu(event, LevelEntry_mnu[i][j], LevelEntry_texture, LevelEntry_texture, ButtonClick, GAME, true))
				{
					currentLevel.SetLevel(j + i * 3);
				}

			}
		}
		break;
	case PAUSE_MENU:
		MouseInput_mnu(event, ResumeButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME, false, Resume_Pausetxt);
		if (MouseInput_mnu(event, RetryButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME, true, Retry_Pausetxt))
		{
			totalTimePassed = 0;
			currentLevel.ResetLevel();
		}
		if (MouseInput_mnu(event, EndButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU, true, End_Pausetxt))
		{
			totalTimePassed = 0;
		}
		MouseInput_mnu(event, SettingButton_Pausemnu, SettingsButton0_texture, SettingsButton0_texture, No_Sound_Buttons, SETTINGS, false);
		break;
	case WIN_MENU:
		if (MouseInput_mnu(event, ContinueButton_Winmnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU, true, Continue_Wintxt))
		{
			totalTimePassed = 0;
		}
		break;
	case SETTINGS:
		// code for handling settings menu input
		if (Settings_from_MainMenu)
		{
			MuteSound(event, SoundButton_MainToSetting, SoundButton_PauseToSetting, MuteButton0_texture, MuteButton1_texture, ButtonClick, isSoundButtonClicked_MainToSetting);
			MuteMusic(event, MusicButton_MainToSetting, MusicButton_PauseToSetting, MusicButton0_texture, MusicButton1_texture, ButtonClick, isMusicButtonClicked_MainToSetting);
			MouseInput_mnu(event, OkButton_MainToSetting, stone_button_0_texture, stone_button_1_texture, ButtonClick, MAIN_MENU, false, OkButtontxt_MainToSetting);
		}
		else
		{
			MuteSound(event, SoundButton_PauseToSetting, SoundButton_MainToSetting, MuteButton0_texture, MuteButton1_texture, ButtonClick, isSoundButtonClicked_PauseToSetting);
			MuteMusic(event, MusicButton_PauseToSetting, MusicButton_MainToSetting, MusicButton0_texture, MusicButton1_texture, ButtonClick, isMusicButtonClicked_PauseToSetting);
			MouseInput_mnu(event, OkButton_PauseToSetting, stone_button_0_texture, stone_button_1_texture, ButtonClick, PAUSE_MENU, false, OkButtontxt_PauseToSetting);
		}
		break;
	case GAMEOVER:
		if(MouseInput_mnu(event, GameOverbuttons_mnu[0], stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU, true, Levels_GOVERtxt))
		{
			totalTimePassed = 0;
		}
		if (MouseInput_mnu(event, GameOverbuttons_mnu[2], stone_button_0_texture, stone_button_1_texture, ButtonClick, MAIN_MENU, true, Menu_GOVERtxt))
		{
			totalTimePassed = 0;
		}
		if (MouseInput_mnu(event, GameOverbuttons_mnu[1], stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME, true, Retry_GOVERtxt))
		{
			totalTimePassed = 0;
		}
		break;
	case GAME:
		// code for handling game UI input
		MouseInput_mnu(event, PauseIcon_mnu, pause_icon_texture, pause_icon_texture, No_Sound_Buttons, PAUSE_MENU, false);
		break;
	case CREDITS:
		MouseInput_mnu(event, BackButtonCredits_mnu, BackButtonFull0_texture, BackButtonFull0_texture, ButtonClick, MAIN_MENU, false);
		break;
	default:
		break;
	}
	changeCursorColor(event);
}

void OnUpdatedGameStateMenu() {
	// do stuff here exactly when the gameState is changed

	switch (gameState)
	{
	case MAIN_MENU:
		PlayMusic(MainMenu);
		break;
	case LEVEL_MENU:
		UpdateTimeCounters();
		PlayMusic(MainMenu);
		break;
	case PAUSE_MENU:
		PauseMusic();
		break;
	case WIN_MENU:
		PauseMusic();
		PlayGameSoundEffect(Win_sound);

		break;
	case SETTINGS:
		break;
	case CREDITS:
		PauseMusic();
		break;
	case GAMEOVER:
		PauseMusic();
		PlayGameSoundEffect(GameOver_sound);
		break;
	case GAME:
		gameTutorials = TutorialTxtList();
		if (currentLevel.currentLevelIndex == 0)
		{
			initializeTutorialText();
		}
		if (currentLevel.currentLevelIndex == 2)
		{
			PlayMusic(Game_Fast);
		}
		else
		{
			PlayMusic(Game_Slow);
		}
		break;
	default:
		break;
	}
}

void UpdateUI()
{
	//clock logic
	totalTimePassed += clockTikingSpeed * dt;

	Minutes_clock = (int)totalTimePassed / 60;
	Seconds_clock = (int)totalTimePassed % 60;

	unit_sec = Seconds_clock % 10;
	tenth_sec = Seconds_clock / 10;

	unit_min = Minutes_clock % 10;
	tenth_min = Minutes_clock / 10;

	stopwatch_txt.setString(to_string(tenth_min) + to_string(unit_min) + ':' + to_string(tenth_sec) + to_string(unit_sec));

	switch (gameState)
	{
	case MAIN_MENU:
		// code for main menu
		clockTikingSpeed = 0;
		MainMenuSettings = true;
		UpdateAnimation(IdleFbHeadmnu, fire_idle_head_texture);
		UpdateAnimation(IdleWgHeadmnu, water_head_idle_texture);
		//UpdateAnimation(dustAnimation, dust_texture);
		if (LastWasSettings)
		{
			SettingMenu_Movement(Target_Down_mnu, true);
			currentSettingsDimState = MainTo_SettingsOrCredits_DimmingDown;
		}
		else if (lastGameState == GAMEOVER)
		{
			GameoverMenu_Movement(Target_Down_mnu);
			currentDimState = DimmingDown;
		}
		else if (lastGameState == CREDITS)
		{
			CreditsMenu_Movement(Target_Down_mnu);
			currentSettingsDimState = MainTo_SettingsOrCredits_DimmingDown;
		}
		Settings_from_MainMenu = true;
		break;
	case LEVEL_MENU:
		clockTikingSpeed = 0;
		if (lastGameState == GAMEOVER)
		{
			GameoverMenu_Movement(Target_Down_mnu);
		}
		else if (lastGameState == PAUSE_MENU)
		{
			PauseMenu_Movement(Target_Down_mnu);
		}
		else if (lastGameState == WIN_MENU)
		{
			WinMenu_Movement(Target_Down_mnu);
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (levelProgress[j + i * 3].isCompleted && levelProgress[j + i * 3].collectedGems && levelProgress[j + i * 3].finishedOnTime)
				{
					ApplyTexture(DiamondLevel_mnu[i][j], LoadTexture::Diamond3_texture, Vector2f(69, 80));
				}
				else if (levelProgress[j + i * 3].isCompleted && (levelProgress[j + i * 3].collectedGems || levelProgress[j + i * 3].finishedOnTime))
				{
					ApplyTexture(DiamondLevel_mnu[i][j], LoadTexture::Diamond2_texture, Vector2f(69, 80));
				}
				else if (levelProgress[j + i * 3].isCompleted)
				{
					ApplyTexture(DiamondLevel_mnu[i][j], LoadTexture::Diamond1_texture, Vector2f(69, 80));
				}
			}
		}
		break;
	case PAUSE_MENU:
		clockTikingSpeed = 0;
		lastGameState = PAUSE_MENU;
		MainMenuSettings = false;
		PauseMenu_Movement(Target_up_mnu);
		if (LastWasSettings)
		{
			SettingMenu_Movement(Target_Down_mnu, false);
			currentSettingsDimState = PauseToSettingsDimmingDown;
		}
		currentDimState = DimmingUp;
		Settings_from_MainMenu = false;
		break;
	case WIN_MENU:
		RatingCheck(currentLevel.GetCurrentProgress().isCompleted, currentLevel.GetCurrentProgress().collectedGems, currentLevel.GetCurrentProgress().finishedOnTime);
		clockTikingSpeed = 0;
		lastGameState = WIN_MENU;
		WinMenu_Movement(Target_up_mnu);
		currentDimState = DimmingUp;

		ratingOrder += ratingOrder_Speed * dt;
		if (ratingOrder >= 600)
		{
			ratingOrder = 600;
			if (levelAndArrowIcon_turn == false) // do this one time only
				InitializeOneTimeAnimations(); // to reset clock of diamond animation

			levelAndArrowIcon_turn = true;
			ApplyTexture(arrowIcon_Winmnu, LoadTexture::arrow_icon1_texture, Vector2f(150, 100));
			UpdateAnimation(arrowIcon_Winmnu, arrow_icon1_texture);
			arrowIcon_Winmnu.setPosition(windowSize.x / 2, windowSize.y / 2 - 95);
			if (!islevelAndArrowSoundPlayed)
			{
				PlayGameSoundEffect(EndDiamond_sound);
				islevelAndArrowSoundPlayed = true;
			}
		}
		else if (ratingOrder >= 500)
		{
			timerRating_turn = true;
			if (!istimerSoundPlayed)
			{
				PlayGameSoundEffect(EndTaskPassAndFail_sound);
				istimerSoundPlayed = true;
			}
		}
		else if (ratingOrder >= 400)
		{
			diamondRating_turn = true;
			if (!isdiamondSoundPlayed)
			{
				PlayGameSoundEffect(EndTaskPassAndFail_sound);
				isdiamondSoundPlayed = true;
			}
		}
		else if (ratingOrder >= 300)
		{
			MaleAndFemale_turn = true;
			if (!isMaleAndFemaleSoundPlayed)
			{
				PlayGameSoundEffect(EndTaskPassAndFail_sound);
				isMaleAndFemaleSoundPlayed = true;
			}
		}

		break;
	case SETTINGS:
		clockTikingSpeed = 0;
		if (MainMenuSettings)
		{
			SettingMenu_Movement(Target_up_mnu, true);
			currentSettingsDimState = MainTo_SettingsOtCredits_DimmingUp;
		}
		else
		{
			SettingMenu_Movement(Target_up_mnu, false);
			currentSettingsDimState = PauseToSettingsDimmingUp;
		}
		LastWasSettings = true;
		
		// code for settings menu
		break;
	case GAMEOVER:
		clockTikingSpeed = 0;
		lastGameState = GAMEOVER;
		GameoverMenu_Movement(Target_up_mnu);
		currentDimState = DimmingUp;
		break;
	case GAME:
		// code for game UI
		for (int i = 0; i < gameTutorials.count; i++)
		{
			gameTutorials.elements[i].Update(fireBoy, waterGirl);
		}

		clockTikingSpeed = 1;
		if (lastGameState == GAMEOVER)
		{
			GameoverMenu_Movement(Target_Down_mnu);
		}
		else if (lastGameState == PAUSE_MENU)
		{
			PauseMenu_Movement(Target_Down_mnu);
		}
		else if (lastGameState == WIN_MENU)
		{
			WinMenu_Movement(Target_Down_mnu);
		}
		currentDimState = DimmingDown;
		break;
	case CREDITS:
		lastGameState = CREDITS;
		clockTikingSpeed = 0;
		CreditsMenu_Movement(Target_up_mnu);
		currentSettingsDimState = MainTo_SettingsOtCredits_DimmingUp;
		LastWasSettings = false;
		break;
	default:
		break;
	}

	if (currentFadeState == FadingUp)
	{
		fadePercentage += fadeSpeed * dt;
		if (fadePercentage >= 255)
		{
			fadePercentage = 255;
			UpdateGameState(FadeTransitionMenuState);
			holdLimit -= holdSpeed * dt;
			if (holdLimit <= 0)
			{
				currentFadeState = FadingDown;
				holdLimit = 50;
			}
		}
	}
	else if (currentFadeState == FadingDown)
	{
		fadePercentage -= fadeSpeed * dt;
		if (fadePercentage <= 0)
		{
			fadePercentage = 0;
			currentFadeState = NoFading;
		}
	}
	FadingTransitionBackground.setFillColor(Color(0, 0, 0, fadePercentage));

	if (currentDimState == DimmingUp)
	{
		dimingSpeed = 155;
		dimPercentage += dimingSpeed * dt;
		if (dimPercentage >= 150)
		{
			dimPercentage = 150;
			currentDimState = NoDimming;
		}
	}
	else if (currentDimState == DimmingDown)
	{
		dimingSpeed = 190;
		dimPercentage -= dimingSpeed * dt;
		if (dimPercentage <= 0)
		{
			dimPercentage = 0;
			currentDimState = NoDimming;
		}
	}

	if (currentSettingsDimState == PauseToSettingsDimmingUp)
	{
		settingAndCredits_DimmingSpeed = 35.0f;
		settingsAndCreditsDimPercentage += settingAndCredits_DimmingSpeed * dt;
		if (settingsAndCreditsDimPercentage >= 60)
		{
			settingsAndCreditsDimPercentage = 60;
			currentSettingsDimState = NoSettingsDimming;
		}
	}
	else if (currentSettingsDimState == PauseToSettingsDimmingDown)
	{
		settingAndCredits_DimmingSpeed = 55.0f;
		settingsAndCreditsDimPercentage -= settingAndCredits_DimmingSpeed * dt;
		if (settingsAndCreditsDimPercentage <= 0)
		{
			settingsAndCreditsDimPercentage = 0;
			currentSettingsDimState = NoSettingsDimming;
		}
	}
	else if (currentSettingsDimState == MainTo_SettingsOtCredits_DimmingUp)
	{
		settingAndCredits_DimmingSpeed = 155.0f;
		settingsAndCreditsDimPercentage += settingAndCredits_DimmingSpeed * dt;
		if (settingsAndCreditsDimPercentage >= 150)
		{
			settingsAndCreditsDimPercentage = 150;
			currentSettingsDimState = NoSettingsDimming;
		}
	}
	else if (currentSettingsDimState == MainTo_SettingsOrCredits_DimmingDown)
	{
		settingAndCredits_DimmingSpeed = 190.0f;
		settingsAndCreditsDimPercentage -= settingAndCredits_DimmingSpeed * dt;
		if (settingsAndCreditsDimPercentage <= 0)
		{
			settingsAndCreditsDimPercentage = 0;
			currentSettingsDimState = NoSettingsDimming;
		}
	}

	Game_Dimmed_Background.setFillColor(Color(0, 0, 0, dimPercentage + settingsAndCreditsDimPercentage));
	settingsAndCredits_Dimmed_Background.setFillColor(Color(0, 0, 0, settingsAndCreditsDimPercentage));
	cursorAndpointerSprite.setPosition(mousePosition + Vector2f(21, 13));
}

void DrawUI()
{
	// draw only, no need for window.clear or window.display
	switch (gameState)
	{
	case MAIN_MENU:
		// code for drawing main menu
		window.draw(MainMenuBackground_mnu);
		window.draw(GameName_mnu);
		window.draw(PlayButton_mnu);
		window.draw(CreditsButton_mnu);
		window.draw(ExitButton_mnu);
		window.draw(SettingsButton_Mainmnu);
		window.draw(IdleFbBodymnu);
		window.draw(IdleFbHeadmnu);
		window.draw(IdleWgBodymnu);
		window.draw(IdleWgHeadmnu);
		//window.draw(dustAnimation);

		window.draw(settingsAndCredits_Dimmed_Background);
		
		if (Current_position_SettingsOrCredits_mnu != Target_Down_mnu)
		{
			if (LastWasSettings)
			{
				window.draw(SettingsMenuBox_MainToSetting);
				window.draw(SoundButton_MainToSetting);
				window.draw(MusicButton_MainToSetting);
				window.draw(OkButton_MainToSetting);
				window.draw(OkButtontxt_MainToSetting);
			}
			else if (lastGameState == CREDITS)
			{
				window.draw(CreditsMenuBox_mnu);
				window.draw(BackButtonCredits_mnu);
				for (int i = 0; i < 2; i++)
				{
					window.draw(MenusandSoundsCredits_txt[i]);
				}
				for (int i = 0; i < 4; i++)
				{
					window.draw(GamelogicCredits_txt[i]);
				}
				for (int i = 0; i < 2; i++)
				{
					window.draw(AnimationandTexturesCredits_txt[i]);
				}
			}
		}
		
		
		//draw the things of the Main menu down here

		break;
	case LEVEL_MENU:
		window.draw(LevelMenuBackground_mnu);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				window.draw(LevelEntry_mnu[i][j]);
				window.draw(LevelMenuBox_mnu[i][j]);
				if (DiamondLevel_mnu[i][j].getGlobalBounds().contains(mousePosition))
				{
					window.draw(LevelSelection_mnu[i][j]);
				}
				window.draw(DiamondLevel_mnu[i][j]);
				window.draw(LevelNumber_mnu[i][j]);
				if (levelProgress[j + i * 3].isCompleted)
				{
					window.draw(LevelTimeRate[i][j]);
				}
			}
		}
		window.draw(BackButtonLevel_mnu);
		if (Current_position_mnu != Target_Down_mnu)
		{

			if (lastGameState == GAMEOVER)
			{
				window.draw(Stone_mnu);
				for (int i = 0; i < 3; i++)
				{
					window.draw(GameOverbuttons_mnu[i]);
				}
				window.draw(Menu_GOVERtxt);
				window.draw(Retry_GOVERtxt);
				window.draw(Levels_GOVERtxt);
				window.draw(GameOver_txt);
			}
			else if (lastGameState == PAUSE_MENU)
			{
				window.draw(Stone_mnu);
				window.draw(EndButton_Pausemnu);
				window.draw(RetryButton_Pausemnu);
				window.draw(ResumeButton_Pausemnu);
				window.draw(SettingButton_Pausemnu);
				window.draw(End_Pausetxt);
				window.draw(Retry_Pausetxt);
				window.draw(Resume_Pausetxt);
				window.draw(Pause_txt);
			}
			else if (lastGameState == WIN_MENU)
			{
				window.draw(Stone_mnu);
				window.draw(ContinueButton_Winmnu);
				window.draw(MaleAndFemale_icon_Winmnu);
				window.draw(diamondRating_icon_Winmnu);
				window.draw(timerRating_icon_Winmnu);
				window.draw(arrowIcon_Winmnu);
				window.draw(levelDiamond_Winmnu);
				window.draw(checkOrCrossMaleOrFemale_icon_Winmnu);
				window.draw(checkOrCrossDiamonds_icon_Winmnu);
				window.draw(checkOrCrossTimer_icon_Winmnu);
				window.draw(Continue_Wintxt);
			}
		}
		//draw the things of the level menu down here

		break;

	case PAUSE_MENU:
		DrawGame(true);
		window.draw(clockTiking_game);
		window.draw(stopwatch_txt);
		window.draw(Game_Dimmed_Background);
		window.draw(Stone_mnu);
		window.draw(EndButton_Pausemnu);
		window.draw(RetryButton_Pausemnu);
		window.draw(ResumeButton_Pausemnu);
		window.draw(SettingButton_Pausemnu);
		window.draw(End_Pausetxt);
		window.draw(Retry_Pausetxt);
		window.draw(Resume_Pausetxt);
		window.draw(Pause_txt);
		if (Current_position_SettingsOrCredits_mnu != Target_Down_mnu)
		{
			if (LastWasSettings)
			{

				window.draw(SettingsMenuBox_PauseToSetting);
				window.draw(SoundButton_PauseToSetting);
				window.draw(MusicButton_PauseToSetting);
				window.draw(OkButton_PauseToSetting);
				window.draw(OkButtontxt_PauseToSetting);
			}
		}
		break;

	case WIN_MENU:
		DrawGame(true);
		window.draw(clockTiking_game);
		window.draw(stopwatch_txt);
		window.draw(Game_Dimmed_Background);
		window.draw(Stone_mnu);
		window.draw(ContinueButton_Winmnu);
		window.draw(MaleAndFemale_icon_Winmnu);
		window.draw(diamondRating_icon_Winmnu);
		window.draw(timerRating_icon_Winmnu);
		window.draw(arrowIcon_Winmnu);
		window.draw(levelDiamond_Winmnu);
		if (levelAndArrowIcon_turn)
		{
			window.draw(checkOrCrossMaleOrFemale_icon_Winmnu);
			window.draw(checkOrCrossDiamonds_icon_Winmnu);
			window.draw(checkOrCrossTimer_icon_Winmnu);
		}
		else if (timerRating_turn)
		{
			window.draw(checkOrCrossMaleOrFemale_icon_Winmnu);
			window.draw(checkOrCrossDiamonds_icon_Winmnu);
			window.draw(checkOrCrossTimer_icon_Winmnu);
		}
		else if (diamondRating_turn)
		{
			window.draw(checkOrCrossMaleOrFemale_icon_Winmnu);
			window.draw(checkOrCrossDiamonds_icon_Winmnu);
		}
		else if (MaleAndFemale_turn)
		{
			window.draw(checkOrCrossMaleOrFemale_icon_Winmnu);
		}
		window.draw(Continue_Wintxt);
		break;

	case SETTINGS:
		if (MainMenuSettings && lastGameState != PAUSE_MENU)
		{
			window.draw(MainMenuBackground_mnu);
			window.draw(GameName_mnu);
			window.draw(PlayButton_mnu);
			window.draw(CreditsButton_mnu);
			window.draw(ExitButton_mnu);
			window.draw(SettingsButton_Mainmnu);
			window.draw(IdleFbBodymnu);
			window.draw(IdleFbHeadmnu);
			window.draw(IdleWgBodymnu);
			window.draw(IdleWgHeadmnu);
			window.draw(settingsAndCredits_Dimmed_Background);

			window.draw(SettingsMenuBox_MainToSetting);
			window.draw(SoundButton_MainToSetting);
			window.draw(MusicButton_MainToSetting);
			window.draw(OkButton_MainToSetting);
			window.draw(OkButtontxt_MainToSetting);
		}
		else if (lastGameState == PAUSE_MENU)
		{
			DrawGame(true);
			window.draw(clockTiking_game);
			window.draw(stopwatch_txt);
			window.draw(Game_Dimmed_Background);
			window.draw(Stone_mnu);
			window.draw(EndButton_Pausemnu);
			window.draw(RetryButton_Pausemnu);
			window.draw(ResumeButton_Pausemnu);
			window.draw(SettingButton_Pausemnu);
			window.draw(End_Pausetxt);
			window.draw(Retry_Pausetxt);
			window.draw(Resume_Pausetxt);
			window.draw(Pause_txt);

			window.draw(SettingsMenuBox_PauseToSetting);
			window.draw(SoundButton_PauseToSetting);
			window.draw(MusicButton_PauseToSetting);
			window.draw(OkButton_PauseToSetting);
			window.draw(OkButtontxt_PauseToSetting);
		}
		
		break;

	case GAMEOVER:
		DrawGame(true);
		window.draw(clockTiking_game);
		window.draw(stopwatch_txt);
		window.draw(Game_Dimmed_Background);
		window.draw(Stone_mnu);
		for (int i = 0; i < 3; i++)
		{
			window.draw(GameOverbuttons_mnu[i]);
		}
		window.draw(Menu_GOVERtxt);
		window.draw(Retry_GOVERtxt);
		window.draw(Levels_GOVERtxt);
		window.draw(GameOver_txt);
		break;

	case GAME:
		// code for drawing game UI
		window.draw(PauseIcon_mnu);
		window.draw(clockTiking_game);
		window.draw(stopwatch_txt);
		// gameTutorials is drawn in the actual DrawGame function
		window.draw(Game_Dimmed_Background);
		if (Current_position_mnu != Target_Down_mnu)
		{

			if (lastGameState == GAMEOVER)
			{
				window.draw(Stone_mnu);
				for (int i = 0; i < 3; i++)
				{
					window.draw(GameOverbuttons_mnu[i]);
				}
				window.draw(Menu_GOVERtxt);
				window.draw(Retry_GOVERtxt);
				window.draw(Levels_GOVERtxt);
				window.draw(GameOver_txt);
			}
			else if (lastGameState == PAUSE_MENU)
			{
				window.draw(Stone_mnu);
				window.draw(EndButton_Pausemnu);
				window.draw(RetryButton_Pausemnu);
				window.draw(ResumeButton_Pausemnu);
				window.draw(SettingButton_Pausemnu);
				window.draw(End_Pausetxt);
				window.draw(Retry_Pausetxt);
				window.draw(Resume_Pausetxt);
				window.draw(Pause_txt);
			}
		}
		break;

	case CREDITS:
		
		window.draw(MainMenuBackground_mnu);
		window.draw(GameName_mnu);
		window.draw(PlayButton_mnu);
		window.draw(CreditsButton_mnu);
		window.draw(ExitButton_mnu);
		window.draw(SettingsButton_Mainmnu);
		window.draw(IdleFbBodymnu);
		window.draw(IdleFbHeadmnu);
		window.draw(IdleWgBodymnu);
		window.draw(IdleWgHeadmnu);
		
		window.draw(settingsAndCredits_Dimmed_Background);
		
		window.draw(CreditsMenuBox_mnu);
		window.draw(BackButtonCredits_mnu);
			for (int i = 0; i < 2; i++)
			{
				window.draw(MenusandSoundsCredits_txt[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				window.draw(GamelogicCredits_txt[i]);
			}
			for (int i = 0; i < 2; i++)
			{
				window.draw(AnimationandTexturesCredits_txt[i]);
			}
		break;
	default:
		break;
	}
	
	window.draw(cursorAndpointerSprite);
	if (currentFadeState != NoFading)
	{
		window.draw(FadingTransitionBackground);
	}
	fpsDisplay.setString(to_string((int)round(1.0f / dt)));
	window.draw(fpsDisplay);
}
