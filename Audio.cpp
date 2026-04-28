
// AUDIO:
float MAinMenu_BackGround_Music = 40.0f;
float GAME_BackGround_Music = 30.0f;
float ButtonSound_Value = 40.0f;

// sound effects and music


// Settings :



// Structs and enums

enum MenuSoundEffect
{
	// add a type for each menu sound effect
	ButtonClick,
	Back,
	Enter,
	No_Sound_Buttons
	// just some tine menu sound effects
};

enum GameSoundEffect
{
	// add a type for each possible sound effect (NOT LOOPING MUSIC) we have

	//index[o]
	GameOver_sound,
	Win_sound,

	//index[1]--> boy, index[2] -->girl
	Walking_boy_sound,
	Walking_girl_sound,
	IceSteps_Fb_sound,
	IceSteps_Wg_sound,
	Pondsteps_boy_sound,
	Pondsteps_girl_sound,
	Death_sound,
	BoyJump_sound,
	GirlJump_sound,

	//index[3]
	Door_sound,
	Lever_sound,
	Platform_sound,

	//index[4]
	pondFreeze_sound,
	PondMelt_sound,
	Wind_sound,

	//index[5]
	DiamondCollect_sound,
	// and so on

	EndDiamond_sound,
	EndTaskPassAndFail_sound
};

enum BackgroundMusic {
	// only for long music
	MainMenu,
	Game_Slow,
	Game_Fast,
	Game_Dark,
};


// make a buffer for each possible audio file
SoundBuffer menuMusicSound;
SoundBuffer gameMusic_SlowSound;
SoundBuffer gameMusic_FastSound;
SoundBuffer gameMusic_DarkSound;

SoundBuffer StepsSound;
SoundBuffer IceSteps_WgSound;
SoundBuffer IceSteps_FbSound;
SoundBuffer PondStepsSound;
SoundBuffer DeathSound;
SoundBuffer BoyJumpSound;
SoundBuffer GirlJumpSound;

SoundBuffer PondFreezeSound;
SoundBuffer PondMeltSound;
SoundBuffer WindSound;
SoundBuffer DoorSound;
SoundBuffer ButtonSound;
SoundBuffer LeverSound;
SoundBuffer PlatformSound;
SoundBuffer LevelWinSound;
SoundBuffer LevelGameoverSound;
SoundBuffer ClockSound;
SoundBuffer DiamondCollectingSound;

SoundBuffer EndDiamondSoundBF;
SoundBuffer EndTaskPassAndFailSoundBF;
// and so on

// have only one Music player and 5 sound effect players
Sound musicPlayer;

int currentSoundEffectPlayer = 0;

Sound soundEffectsPlayers[6];
//Sound Clock;
Sound Button;
Sound EndDiamondSound;
Sound EndTaskPassAndFailSound;


// loop on those sound effect players when playing sound effects, so we can play multiple sound effects at the same time without cutting each other off, but we can only play 5 sound effects at the same time


// Functions

void InitializeAudio()
{
	menuMusicSound.loadFromFile("Main/Assets/Sounds/MenuMusic.mp3");

	gameMusic_SlowSound.loadFromFile("Main/Assets/Sounds/LevelMusic_slow.mp3");
	gameMusic_FastSound.loadFromFile("Main/Assets/Sounds/LevelMusic_fast.mp3");
	gameMusic_DarkSound.loadFromFile("Main/Assets/Sounds/LevelMusic_dark.mp3");

	StepsSound.loadFromFile("Main/Assets/Sounds/Steps.mp3");
	PondStepsSound.loadFromFile("Main/Assets/Sounds/PondSteps.mp3");
	IceSteps_WgSound.loadFromFile("Main/Assets/Sounds/IceSteps_wg.mp3");
	IceSteps_FbSound.loadFromFile("Main/Assets/Sounds/IceSteps_fb.mp3");
	DeathSound.loadFromFile("Main/Assets/Sounds/Death.mp3");
	BoyJumpSound.loadFromFile("Main/Assets/Sounds/Jump_fb.mp3");
	GirlJumpSound.loadFromFile("Main/Assets/Sounds/Jump_wg.mp3");

	PondFreezeSound.loadFromFile("Main/Assets/Sounds/PondFreeze.mp3");
	PondMeltSound.loadFromFile("Main/Assets/Sounds/PondMelt.mp3");
	WindSound.loadFromFile("Main/Assets/Sounds/Wind.mp3");
	DoorSound.loadFromFile("Main/Assets/Sounds/Door.mp3");
	ButtonSound.loadFromFile("Main/Assets/Sounds/Button.mp3");
	LeverSound.loadFromFile("Main/Assets/Sounds/Lever.mp3");
	PlatformSound.loadFromFile("Main/Assets/Sounds/Platform.mp3");
	LevelWinSound.loadFromFile("Main/Assets/Sounds/LevelWin.mp3");
	LevelGameoverSound.loadFromFile("Main/Assets/Sounds/LevelGameOver.mp3");
	ClockSound.loadFromFile("Main/Assets/Sounds/Clock.mp3");
	DiamondCollectingSound.loadFromFile("Main/Assets/Sounds/DiamondCollecting.mp3");

	EndDiamondSoundBF.loadFromFile("Main/Assets/Sounds/EndDiamond.mp3");
	EndTaskPassAndFailSoundBF.loadFromFile("Main/Assets/Sounds/EndTaskPass&Fail.mp3");

	for (int i = 0; i < 6; i++)
	{
		soundEffectsPlayers[i].setVolume(40.0f);
	}
}

void PlayMusic(BackgroundMusic music) {
	bool validMusic = true;

	switch (music)
	{
	case MainMenu:
		musicPlayer.setBuffer(menuMusicSound);
		musicPlayer.setVolume(MAinMenu_BackGround_Music);
		break;
	case Game_Slow:
		musicPlayer.setBuffer(gameMusic_SlowSound);
		musicPlayer.setVolume(GAME_BackGround_Music);
		break;
	case Game_Fast:
		musicPlayer.setBuffer(gameMusic_FastSound);
		musicPlayer.setVolume(GAME_BackGround_Music);
		break;
	case Game_Dark:
		musicPlayer.setBuffer(gameMusic_DarkSound);
		musicPlayer.setVolume(GAME_BackGround_Music);
		break;
	default:
		cout << "Invalid background music" << endl;
		validMusic = false;
		break;
	}


	if (validMusic) {
		musicPlayer.setLoop(true);
		musicPlayer.play();
	}
}

// play menu sound effects
void PlayMenuSoundEffect(MenuSoundEffect soundEffect) {
	switch (soundEffect)
	{
	case ButtonClick:
		Button.setBuffer(ButtonSound);
		Button.setVolume(ButtonSound_Value);
		Button.play();
		break;
	case Back:
		Button.setBuffer(ButtonSound);
		Button.setVolume(ButtonSound_Value);
		Button.play();
		break;
	case Enter:
		Button.setBuffer(ButtonSound);
		Button.setVolume(ButtonSound_Value);
		Button.play();
		break;
	case No_Sound_Buttons:
		// no sound played
		break;
	default:
		cout << "Invalid sound effect" << endl;
		break;
	}
}

void PlayGameSoundEffect(GameSoundEffect soundEffect, bool loop = false) {
	// if loop -> set loop to true and start playing
	// if not looping a sound that should be looped -> stop that sound

	switch (soundEffect)
	{
	case GameOver_sound:
		soundEffectsPlayers[0].setBuffer(LevelGameoverSound);
		soundEffectsPlayers[0].setLoop(false);
		soundEffectsPlayers[0].play();
		break;
	case Win_sound:
		soundEffectsPlayers[0].setBuffer(LevelWinSound);
		soundEffectsPlayers[0].setLoop(false);
		soundEffectsPlayers[0].play();
		break;

	case Walking_boy_sound:
		soundEffectsPlayers[1].setBuffer(StepsSound);
		soundEffectsPlayers[1].setLoop(loop);
		if (loop)
			soundEffectsPlayers[1].play();
		else 
			soundEffectsPlayers[1].stop();
		
		break;
	case Walking_girl_sound:
		soundEffectsPlayers[2].setBuffer(StepsSound);
		soundEffectsPlayers[2].setLoop(loop);
		if (loop)
			soundEffectsPlayers[2].play();
		else
			soundEffectsPlayers[2].stop();

		break;
	case IceSteps_Fb_sound:
		soundEffectsPlayers[1].setBuffer(IceSteps_FbSound);
		soundEffectsPlayers[1].setLoop(loop);
		if (loop)
			soundEffectsPlayers[1].play();
		else
			soundEffectsPlayers[1].stop();
		break;
	case IceSteps_Wg_sound:
		soundEffectsPlayers[2].setBuffer(IceSteps_WgSound);
		soundEffectsPlayers[2].setLoop(loop);
		if (loop)
			soundEffectsPlayers[2].play();
		else
			soundEffectsPlayers[2].stop();
		break;
	case Pondsteps_boy_sound:
		soundEffectsPlayers[1].setBuffer(PondStepsSound);
		soundEffectsPlayers[1].setLoop(loop);
		if (loop)
			soundEffectsPlayers[1].play();
		else
			soundEffectsPlayers[1].stop();
		break;
	case Pondsteps_girl_sound:
		soundEffectsPlayers[2].setBuffer(PondStepsSound);
		soundEffectsPlayers[2].setLoop(loop);
		if (loop)
			soundEffectsPlayers[2].play();
		else
			soundEffectsPlayers[2].stop();
		break;
	case Death_sound:
		soundEffectsPlayers[1].setBuffer(DeathSound);
		soundEffectsPlayers[2].setBuffer(DeathSound);
		soundEffectsPlayers[1].setLoop(false);
		soundEffectsPlayers[1].play();
		break;
	case BoyJump_sound:
		soundEffectsPlayers[1].setBuffer(BoyJumpSound);
		soundEffectsPlayers[1].setLoop(false);
		soundEffectsPlayers[1].play();
		break;
	case GirlJump_sound:
		soundEffectsPlayers[2].setBuffer(GirlJumpSound);
		soundEffectsPlayers[2].setLoop(false);
		soundEffectsPlayers[2].play();
		break;

	case Door_sound:
		soundEffectsPlayers[3].setBuffer(DoorSound);
		soundEffectsPlayers[3].setLoop(false);
		soundEffectsPlayers[3].play();
		break;
	case Lever_sound:
		soundEffectsPlayers[3].setBuffer(LeverSound);
		soundEffectsPlayers[3].setLoop(false);
		soundEffectsPlayers[3].play();
		break;
	case Platform_sound:
		soundEffectsPlayers[3].setBuffer(PlatformSound);
		soundEffectsPlayers[3].setLoop(false);
		soundEffectsPlayers[3].play();
		break;

	case pondFreeze_sound:
		soundEffectsPlayers[4].setBuffer(PondFreezeSound);
		soundEffectsPlayers[4].setLoop(false);
		soundEffectsPlayers[4].play();
		break;
	case PondMelt_sound:
		soundEffectsPlayers[4].setBuffer(PondMeltSound);
		soundEffectsPlayers[4].setLoop(false);
		soundEffectsPlayers[4].play();
		break;
	case Wind_sound:
		soundEffectsPlayers[4].setBuffer(WindSound);
		soundEffectsPlayers[4].setLoop(false);
		soundEffectsPlayers[4].setLoop(loop);
		if (loop)
			soundEffectsPlayers[4].play();
		else
			soundEffectsPlayers[4].stop();
		break;
	case DiamondCollect_sound:
		soundEffectsPlayers[5].setBuffer(DiamondCollectingSound);
		soundEffectsPlayers[5].setLoop(false);
		soundEffectsPlayers[5].play();
		break;
	case EndDiamond_sound:
		EndDiamondSound.setBuffer(EndDiamondSoundBF);
		EndDiamondSound.setLoop(false);
		EndDiamondSound.setVolume(100.0f);
		EndDiamondSound.play();
		break;
	case EndTaskPassAndFail_sound:
		EndTaskPassAndFailSound.setBuffer(EndTaskPassAndFailSoundBF);
		EndTaskPassAndFailSound.setLoop(false);
		EndTaskPassAndFailSound.setVolume(100.0f);
		EndTaskPassAndFailSound.play();
		break;
	default:
		cout << "Invalid sound effect" << endl;
		break;
	}
}