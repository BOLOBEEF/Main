
// AUDIO:
// sound effects and music


// Settings :



// Structs and enums

enum MenuSoundEffect
{
	// add a type for each menu sound effect
	ButtonClick,
	ButtonSwitch,
	Back,
	Enter
	// just some tine menu sound effects
};

enum GameSoundEffect
{
	// add a type for each possible sound effect (NOT LOOPING MUSIC) we have
	Death,
	DoorOpen,
	DoorClose,
	Win
	// and so on
};

enum BackgroundMusic {
	// only for long music
	MainMenu,
	Game_Slow,
	Game_Fast,
	Game_Dark
};


// make a buffer for each possible audio file
SoundBuffer menuMusicSound;
SoundBuffer gameMusic_SlowSound;
SoundBuffer gameMusic_FastSound;
SoundBuffer gameMusic_DarkSound;
SoundBuffer StepsSound;
SoundBuffer PondStepsSound;
SoundBuffer PondFreezeSound;
SoundBuffer PondMeltSound;
SoundBuffer IceSteps_WgSound;
SoundBuffer IceSteps_FbSound;
SoundBuffer DeathSound;
SoundBuffer BoyJumpSound;
SoundBuffer GirlJumpSound;
SoundBuffer WindSound;
SoundBuffer DoorSound;
SoundBuffer ButtonSound;
SoundBuffer LeverSound;
SoundBuffer PlatformSound;
SoundBuffer LevelWinSound;
SoundBuffer LevelGameoverSound;
SoundBuffer ClockSound;
SoundBuffer DiamondCollectingSound;
// and so on

// have only one Music player and 5 sound effect players
Sound musicPlayer;
int currentSoundEffectPlayer = 0;
Sound soundEffectsPlayers[5];
// loop on those sound effect players when playing sound effects, so we can play multiple sound effects at the same time without cutting each other off, but we can only play 5 sound effects at the same time


// Functions

void InitializeAudio()
{
	menuMusicSound.loadFromFile("/Main/Assets/UsedSounds/MenuMusic.mp3");
	gameMusic_SlowSound.loadFromFile("/Main/Assets/UsedSounds/LevelMusic_slow.mp3");
	gameMusic_FastSound.loadFromFile("/Main/Assets/UsedSounds/LevelMusic_fast.mp3");
	gameMusic_DarkSound.loadFromFile("/Main/Assets/UsedSounds/LevelMusic_dark.mp3");
	StepsSound.loadFromFile("/Main/Assets/UsedSounds/Steps.mp3");
	PondStepsSound.loadFromFile("/Main/Assets/UsedSounds/PondSteps.mp3");
	PondFreezeSound.loadFromFile("/Main/Assets/UsedSounds/PondFreeze.mp3");
	PondMeltSound.loadFromFile("/Main/Assets/UsedSounds/PondMelt.mp3");
	IceSteps_WgSound.loadFromFile("/Main/Assets/UsedSounds/IceSteps_wg.mp3");//??

	DeathSound.loadFromFile("/Main/Assets/UsedSounds/Death.mp3");
	BoyJumpSound.loadFromFile("/Main/Assets/UsedSounds/Jump_fb.mp3");
	GirlJumpSound.loadFromFile("/Main/Assets/UsedSounds/Jump_wg.mp3");
	WindSound.loadFromFile("/Main/Assets/UsedSounds/Wind.mp3");
	DoorSound.loadFromFile("/Main/Assets/UsedSounds/Door.mp3");
	ButtonSound.loadFromFile("/Main/Assets/UsedSounds/Button.mp3");
	LeverSound.loadFromFile("/Main/Assets/UsedSounds/Lever.mp3");
	PlatformSound.loadFromFile("/Main/Assets/UsedSounds/Platform.mp3");
	LevelWinSound.loadFromFile("/Main/Assets/UsedSounds/LevelWin.mp3");
	LevelGameoverSound.loadFromFile("/Main/Assets/UsedSounds/LevelGameOver.mp3");
	ClockSound.loadFromFile("/Main/Assets/UsedSounds/Clock.mp3");
	DiamondCollectingSound.loadFromFile("/Main/Assets/UsedSounds/DiamondCollecting.mp3");
	// load all buffers here
}

void PlayMusic(BackgroundMusic music) {
	bool validMusic = true;

	switch (music)
	{
	case MainMenu:
		musicPlayer.setBuffer(menuMusicSound);
		break;
	case Game_Slow:
		break;
	case Game_Fast:
		break;
	case Game_Dark:
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
		break;
	case ButtonSwitch:
		break;
	case Back:
		break;
	case Enter:
		break;
	default:
		cout << "Invalid sound effect" << endl;
		break;
	}
}



void PlayGameSoundEffect(GameSoundEffect soundEffect) {
	switch (soundEffect)
	{
	case Death:
		break;
	case DoorOpen:
		break;
	case DoorClose:
		break;
	case Win:
		break;
	default:
		cout << "Invalid sound effect" << endl;
		break;
	}
}
