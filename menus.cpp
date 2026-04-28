
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

// Runtime variables
float dimingSpeed, dimPercentage = 0;
float fadeSpeed = 155, fadePercentage = 0;
float holdSpeed = 40, holdLimit = 50;
//Why hold? -> because when I make the fade transition, I change the game state when alpha becomes 255, so the pause menu won't move until this case, it will move when we start decrementing the alpha
//which is not like the original game


GameState PreviousMenu_State = MAIN_MENU;
GameState FadeTransitionMenuState = MAIN_MENU;
RectangleShape Dimmed_Background;
RectangleShape FadingTransitionBackground;

Vector2f Target_up_mnu = Vector2f(windowSize.x / 2, windowSize.y / 2);
Vector2f Target_Down_mnu = Vector2f(windowSize.x / 2, windowSize.y / 2 + 1000);
Vector2f Current_position_mnu = Target_Down_mnu;
Vector2f Current_position_Settings_mnu = Target_Down_mnu;
Vector2f Current_Target;

Sprite Stone_mnu;
Sprite SettingButton_mnu;
Sprite EndButton_Pausemnu;
Sprite RetryButton_Pausemnu;
Sprite ResumeButton_Pausemnu;
Sprite PauseIcon_mnu;
Sprite MainMenuBackground_mnu;
Sprite GameName_mnu;
Sprite PlayButton_mnu;
Sprite CreditsButton_mnu;
Sprite ExitButton_mnu;
Sprite IdleFbBodymnu;
Sprite IdleFbHeadmnu;
Sprite IdleWgBodymnu;
Sprite IdleWgHeadmnu;

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

//gameover
Sprite GameOverbuttons_mnu[3];


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
Sprite cursorAndpointerSprite;

int finalScore = 0;
// Functions

void forceMainMenuDraw(bool forcedraw)
{
	if (!forcedraw) return;
	else
	{
		window.draw(MainMenuBackground_mnu);
		window.draw(GameName_mnu);
		window.draw(PlayButton_mnu);
		window.draw(CreditsButton_mnu);
		window.draw(ExitButton_mnu);
		window.draw(SettingButton_mnu);
		window.draw(IdleFbBodymnu);
		window.draw(IdleFbHeadmnu);
		window.draw(IdleWgBodymnu);
		window.draw(IdleWgHeadmnu);
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
bool MuteSound(Event event, Sprite& ButtonClicked, LoadTexture Unmuted ,LoadTexture Muted, MenuSoundEffect Sound_Played_mnu, bool SoundOn)
{
	
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !isSoundButtonClicked_MainToSetting)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			ApplyTexture(ButtonClicked, Muted, Vector2f(113, 109));
			ButtonClicked.setScale(1.25, 1.25);
			isSoundButtonClicked_MainToSetting = true;
		}
	}
	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && isSoundButtonClicked_MainToSetting)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			ApplyTexture(ButtonClicked, Unmuted, Vector2f(113, 109));
			ButtonClicked.setScale(1.25, 1.25);
			isSoundButtonClicked_MainToSetting = false;
		}
	}
	return true;
}
bool MuteMusic(Event event, Sprite& ButtonClicked, LoadTexture Unmuted ,LoadTexture Muted, MenuSoundEffect Sound_Played_mnu, bool MusicOn)
{
	
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !isMusicButtonClicked_MainToSetting)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			ApplyTexture(ButtonClicked, Muted, Vector2f(113, 109));
			ButtonClicked.setScale(1.25, 1.25);
			isMusicButtonClicked_MainToSetting = true;
		}
	}
	else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && isMusicButtonClicked_MainToSetting)
	{
		if (ButtonClicked.getGlobalBounds().contains(mousePosition))
		{
			ApplyTexture(ButtonClicked, Unmuted, Vector2f(113, 109));
			ButtonClicked.setScale(1.25, 1.25);
			isMusicButtonClicked_MainToSetting = false;
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
	SettingButton_mnu.setPosition(Vector2f(Stone_mnu.getPosition().x + 485, Stone_mnu.getPosition().y - 240));
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
	levelDiamond_Winmnu.setPosition(Vector2f(windowSize.x / 2 + 748, windowSize.y / 2 - 95) + Current_position_mnu - center);

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
	Current_position_Settings_mnu = Damp(Current_position_Settings_mnu, Current_Target, 25, dt);
	if (fromMain)
	{
		SettingsMenuBox_MainToSetting.setPosition(Current_position_Settings_mnu);
		SoundButton_MainToSetting.setPosition(Vector2f(700, 530) + Current_position_Settings_mnu - center);
		MusicButton_MainToSetting.setPosition(Vector2f(1200, 530) + Current_position_Settings_mnu - center);
		OkButton_MainToSetting.setPosition(Vector2f(1155, 750) + Current_position_Settings_mnu - center);
		OkButtontxt_MainToSetting.setPosition(Vector2f(903, 720) + Current_position_Settings_mnu - center);
	}
	else
	{
		SettingsMenuBox_PauseToSetting.setPosition(Current_position_Settings_mnu);
		SoundButton_PauseToSetting.setPosition(Vector2f(700, 530) + Current_position_Settings_mnu - center);
		MusicButton_PauseToSetting.setPosition(Vector2f(1200, 530) + Current_position_Settings_mnu - center);
		OkButton_PauseToSetting.setPosition(Vector2f(1155, 750) + Current_position_Settings_mnu - center);
		OkButtontxt_PauseToSetting.setPosition(Vector2f(903, 720) + Current_position_Settings_mnu - center);
	}
	// I Will Handle this After You finish Settings Menu
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
	Dimmed_Background.setSize(Vector2f(window.getSize().x, window.getSize().y));
	Dimmed_Background.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);

	//fading Transition Background
	FadingTransitionBackground.setSize(Vector2f(window.getSize().x, window.getSize().y));
	FadingTransitionBackground.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);

	//Main menu
	ApplyTexture(MainMenuBackground_mnu, LoadTexture::main_menu_background_texture, Vector2f(windowSize.x, windowSize.y));	
	MainMenuBackground_mnu.setPosition(windowSize.x / 2 ,windowSize.y / 2);	

	if (gameState == MAIN_MENU)
	{
		ApplyTexture(SettingButton_mnu, LoadTexture::SettingsButton0_texture, Vector2f(120, 120));
		SettingButton_mnu.setPosition(150, 860);
	}

	ApplyTexture(GameName_mnu, LoadTexture::game_name_texture, Vector2f(860, 270));
	GameName_mnu.setPosition(windowSize.x / 2, windowSize.y / 2 - 200);

	ApplyTexture(PlayButton_mnu, LoadTexture::PlayButton_texture, Vector2f(240, 160));
	PlayButton_mnu.setPosition(windowSize.x / 2, windowSize.y / 2 + 40);
	
	ApplyTexture(CreditsButton_mnu, LoadTexture::CreditsButton_Texture, Vector2f(260, 173));
	CreditsButton_mnu.setPosition(windowSize.x / 2 + 350, windowSize.y / 2 + 150);

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

	//Settings from main
	menu_box.setSmooth(true);
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
	if (gameState == PAUSE_MENU)
	{
		ApplyTexture(SettingButton_mnu, LoadTexture::SettingsButton0_texture, Vector2f(105, 105));
		SettingButton_mnu.setPosition((Stone_mnu.getGlobalBounds().left + Stone_mnu.getGlobalBounds().width / 2) + 485, Stone_mnu.getGlobalBounds().top + 170);
	}
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
	RatingCheck(true, true, true);

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
	Levels_GOVERtxt.setPosition((GameOverbuttons_mnu[0].getGlobalBounds().left + GameOverbuttons_mnu[0].getGlobalBounds().width / 2) , (GameOverbuttons_mnu[0].getGlobalBounds().top + GameOverbuttons_mnu[0].getGlobalBounds().height / 2) - 10);
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

	// code for initializing menu variables and objects
	// for example load sprites, set up text objects, etc.
}

void HandleMenuInput(Event event)
{

	switch (gameState)
	{
	case MAIN_MENU:
		// code for handling main menu input
		MouseInput_mnu(event, SettingButton_mnu, SettingsButton0_texture, SettingsButton0_texture, ButtonClick, SETTINGS, false);
		MouseInput_mnu(event, PlayButton_mnu, PlayButton_texture, PlayButton_texture, ButtonClick, GAME, true);
		MouseInput_mnu(event, CreditsButton_mnu, CreditsButton_Texture, CreditsButton_Texture, ButtonClick, CREDITS, false);
		if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			if (ExitButton_mnu.getGlobalBounds().contains(mousePosition))
			{
				window.close();
			}
		}
		break;
	case LEVEL_MENU:

		break;
	case PAUSE_MENU:
		MouseInput_mnu(event, ResumeButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME, false, Resume_Pausetxt);
		if (MouseInput_mnu(event, RetryButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME, true, Retry_Pausetxt))
		{
			RestartGame();
		}
		MouseInput_mnu(event, EndButton_Pausemnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU, true, End_Pausetxt);
		MouseInput_mnu(event, SettingButton_mnu, SettingsButton0_texture, SettingsButton0_texture, No_Sound_Buttons, SETTINGS, false);
		break;
	case WIN_MENU:
		MouseInput_mnu(event, ContinueButton_Winmnu, stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU, true, Continue_Wintxt);
		break;
	case SETTINGS:
		// code for handling settings menu input
		if (Settings_from_MainMenu)
		{
			MuteSound(event, SoundButton_MainToSetting, MuteButton0_texture, MuteButton1_texture, ButtonClick, isSoundButtonClicked_MainToSetting);
			MuteMusic(event, MusicButton_MainToSetting, MusicButton0_texture, MusicButton1_texture, ButtonClick, isMusicButtonClicked_MainToSetting);
			MouseInput_mnu(event, OkButton_MainToSetting, stone_button_0_texture, stone_button_1_texture, No_Sound_Buttons, MAIN_MENU, false, OkButtontxt_MainToSetting);
		}
		else
		{
			MuteSound(event, SoundButton_PauseToSetting, MuteButton0_texture, MuteButton1_texture, ButtonClick, isSoundButtonClicked_PauseToSetting);
			MuteMusic(event, MusicButton_PauseToSetting, MusicButton0_texture, MusicButton1_texture, ButtonClick, isMusicButtonClicked_PauseToSetting);
			MouseInput_mnu(event, OkButton_PauseToSetting, stone_button_0_texture, stone_button_1_texture, No_Sound_Buttons, PAUSE_MENU, false, OkButtontxt_PauseToSetting);
		}
		break;
	case GAMEOVER:
		MouseInput_mnu(event, GameOverbuttons_mnu[0], stone_button_0_texture, stone_button_1_texture, ButtonClick, LEVEL_MENU, true, Levels_GOVERtxt);
		MouseInput_mnu(event, GameOverbuttons_mnu[2], stone_button_0_texture, stone_button_1_texture, ButtonClick, MAIN_MENU, true, Menu_GOVERtxt);
		if (MouseInput_mnu(event, GameOverbuttons_mnu[1], stone_button_0_texture, stone_button_1_texture, ButtonClick, GAME, true, Retry_GOVERtxt))
		{
			RestartGame();
		}
		break;
	case GAME:
		// code for handling game UI input
		MouseInput_mnu(event, PauseIcon_mnu, pause_icon_texture, pause_icon_texture, No_Sound_Buttons, PAUSE_MENU, false);
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
		PlayMusic(MainMenu);
		break;
	case PAUSE_MENU:
		musicPlayer.stop();
		break;
	case WIN_MENU:
		musicPlayer.stop();
		PlayGameSoundEffect(Win_sound);
		break;
	case SETTINGS:
		break;
	case GAMEOVER:
		musicPlayer.stop();
		PlayGameSoundEffect(GameOver_sound);
		break;
	case GAME:
		PlayMusic(Game_Slow);
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
		MainMenuSettings = true;
		UpdateAnimation(IdleFbHeadmnu, fire_idle_head_texture);
		UpdateAnimation(IdleWgHeadmnu, water_head_idle_texture);
		if (LastWasSettings)
		{
			SettingMenu_Movement(Target_Down_mnu, true);
			currentDimState = DimmingDown;
		}
		else if (PreviousMenu_State == GAMEOVER)
		{
			GameoverMenu_Movement(Target_Down_mnu);
			currentDimState = DimmingDown;
		}
		Settings_from_MainMenu = true;
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
		MainMenuSettings = false;
		PauseMenu_Movement(Target_up_mnu);
		if (LastWasSettings)
		{
			SettingMenu_Movement(Target_Down_mnu, false);
		}
		currentDimState = DimmingUp;
		Settings_from_MainMenu = false;
		break;
	case WIN_MENU:
		PreviousMenu_State = WIN_MENU;
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
		//PreviousMenu_State = SETTINGS;
		if (MainMenuSettings)
		{
			SettingMenu_Movement(Target_up_mnu, true);
			currentDimState = DimmingUp;
		}
		else
		{
			SettingMenu_Movement(Target_up_mnu, false);
		}
		LastWasSettings = true;
		// code for settings menu
		break;
	case GAMEOVER:
		PreviousMenu_State = GAMEOVER;
		GameoverMenu_Movement(Target_up_mnu);
		currentDimState = DimmingUp;
		break;
	case GAME:
		// code for game UI
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
		currentDimState = DimmingDown;
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
	Dimmed_Background.setFillColor(Color(0, 0, 0, dimPercentage));

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
		window.draw(SettingButton_mnu);
		window.draw(IdleFbBodymnu);
		window.draw(IdleFbHeadmnu);
		window.draw(IdleWgBodymnu);
		window.draw(IdleWgHeadmnu);
		window.draw(Dimmed_Background);
		
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
				window.draw(Levels_GOVERtxt);
				window.draw(GameOver_txt);
			}
		}
		if (Current_position_Settings_mnu != Target_Down_mnu)
		{
			if (LastWasSettings)
			{
				window.draw(SettingsMenuBox_MainToSetting);
				window.draw(SoundButton_MainToSetting);
				window.draw(MusicButton_MainToSetting);
				window.draw(OkButton_MainToSetting);
				window.draw(OkButtontxt_MainToSetting);
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
				window.draw(Levels_GOVERtxt);
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
		window.draw(Dimmed_Background);
		window.draw(Stone_mnu);
		window.draw(EndButton_Pausemnu);
		window.draw(RetryButton_Pausemnu);
		window.draw(ResumeButton_Pausemnu);
		window.draw(SettingButton_mnu);
		window.draw(End_Pausetxt);
		window.draw(Retry_Pausetxt);
		window.draw(Resume_Pausetxt);
		window.draw(Pause_txt);
		if (Current_position_Settings_mnu != Target_Down_mnu)
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
		window.draw(Dimmed_Background);
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
		window.draw(Dimmed_Background);
		if (MainMenuSettings && PreviousMenu_State != PAUSE_MENU)
		{
			window.draw(MainMenuBackground_mnu);
			window.draw(GameName_mnu);
			window.draw(PlayButton_mnu);
			window.draw(CreditsButton_mnu);
			window.draw(ExitButton_mnu);
			window.draw(SettingButton_mnu);
			window.draw(IdleFbBodymnu);
			window.draw(IdleFbHeadmnu);
			window.draw(IdleWgBodymnu);
			window.draw(IdleWgHeadmnu);

			window.draw(SettingsMenuBox_MainToSetting);
			window.draw(SoundButton_MainToSetting);
			window.draw(MusicButton_MainToSetting);
			window.draw(OkButton_MainToSetting);
			window.draw(OkButtontxt_MainToSetting);
		}
		else if (PreviousMenu_State == PAUSE_MENU)
		{
			DrawGame(true);
			cout << "t3baaaaaaaaaaaaaaaaan\n";
			window.draw(Stone_mnu);
			window.draw(EndButton_Pausemnu);
			window.draw(RetryButton_Pausemnu);
			window.draw(ResumeButton_Pausemnu);
			window.draw(SettingButton_mnu);
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
		window.draw(Dimmed_Background);
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
		window.draw(Dimmed_Background);
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
				window.draw(Levels_GOVERtxt);
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
		}
		break;
	default:
		break;
	}
	
	if (currentFadeState != NoFading)
	{
		window.draw(FadingTransitionBackground);
	}
	window.draw(cursorAndpointerSprite);
	fpsDisplay.setString(to_string((int)round(1.0f / dt)));
	window.draw(fpsDisplay);
}
