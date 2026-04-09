
// AUDIO:
// sound effects and music


// Settings :



// Structs and enums




enum MenuSoundEffect
{
	// add a type for each menu sound effect
	ButtonClick,
	Back,
	Enter
	// just some tine menu sound effects
};

enum GameSoundEffect
{
	// add a type for each possible sound effect (NOT LOOPING MUSIC) we have

	//index[o]
	GameOver,
	Win,

	//index[1]--> boy, index[2] -->girl
	Walking_boy,
	Walking_girl,
	IceSteps_Fb,
	IceSteps_Wg,
	Pondsteps_boy,
	Pondsteps_girl,
	Death,
	BoyJump,
	GirlJump,
	 
	//index[3]
	Door,
	Lever,
	Platform,

	//index[4]
	pondFreeze,
	PondMelt,
	Wind,

	//index[5]
	DiamondCollect
	// and so on
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

SoundBuffer StepsSound;//->
SoundBuffer IceSteps_WgSound;//->
SoundBuffer IceSteps_FbSound;//->
SoundBuffer PondStepsSound;//->
SoundBuffer DeathSound;//->
SoundBuffer BoyJumpSound;//->
SoundBuffer GirlJumpSound;//->

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
// and so on

// have only one Music player and 5 sound effect players
Sound musicPlayer;

int currentSoundEffectPlayer = 0;

Sound soundEffectsPlayers[6]; 
Sound Clock;
Sound Button;

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
	IceSteps_WgSound.loadFromFile("/Main/Assets/UsedSounds/IceSteps_wg.mp3");
	IceSteps_FbSound.loadFromFile("/Main/Assets/UsedSounds/IceSteps_fb.mp3");
	DeathSound.loadFromFile("/Main/Assets/UsedSounds/Death.mp3");
	BoyJumpSound.loadFromFile("/Main/Assets/UsedSounds/Jump_fb.mp3");
	GirlJumpSound.loadFromFile("/Main/Assets/UsedSounds/Jump_wg.mp3");

	PondFreezeSound.loadFromFile("/Main/Assets/UsedSounds/PondFreeze.mp3");
	PondMeltSound.loadFromFile("/Main/Assets/UsedSounds/PondMelt.mp3");
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
		musicPlayer.setVolume(100.0f);
		break;
	case Game_Slow:
		musicPlayer.setBuffer(gameMusic_SlowSound);
		musicPlayer.setVolume(100.0f);
		break;
	case Game_Fast:
		musicPlayer.setBuffer(gameMusic_FastSound);
		musicPlayer.setVolume(100.0f);
		break;
	case Game_Dark:
		musicPlayer.setBuffer(gameMusic_DarkSound);
		musicPlayer.setVolume(100.0f);
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
		break;
	case Back:
		Button.setBuffer(ButtonSound);
		break;
	case Enter:
		Button.setBuffer(ButtonSound);
		break;
	default:
		cout << "Invalid sound effect" << endl;
		break;
	}
}

void PlayGameSoundEffect(GameSoundEffect soundEffect) {
	for (int i = 0; i < 6; i++)
	{
		soundEffectsPlayers[i].setVolume(100.0f);
	}

	switch (soundEffect)
	{
	case GameOver:
		soundEffectsPlayers[0].setBuffer(LevelGameoverSound);

		break;
	case Win:
		soundEffectsPlayers[0].setBuffer(LevelWinSound);
		break;

	case Walking_boy:
		soundEffectsPlayers[1].setBuffer(StepsSound);
		break;
	case Walking_girl:
		soundEffectsPlayers[2].setBuffer(StepsSound);
		break;
	case IceSteps_Fb:
		soundEffectsPlayers[1].setBuffer(IceSteps_FbSound);
		break;
	case IceSteps_Wg:
		soundEffectsPlayers[2].setBuffer(IceSteps_WgSound);
		break;
	case Pondsteps_boy:
		soundEffectsPlayers[1].setBuffer(PondStepsSound);
		break;
	case Pondsteps_girl:
		soundEffectsPlayers[2].setBuffer(PondStepsSound);
		break;
	case Death:
		soundEffectsPlayers[1].setBuffer(DeathSound);
		soundEffectsPlayers[2].setBuffer(DeathSound);
		break;
	case BoyJump:
		soundEffectsPlayers[1].setBuffer(BoyJumpSound);
		break;
	case GirlJump:
		soundEffectsPlayers[2].setBuffer(GirlJumpSound);
		break;

	case Door:
		soundEffectsPlayers[3].setBuffer(DoorSound);
		break;
	case Lever:
		soundEffectsPlayers[3].setBuffer(LeverSound);
		break;
	case Platform:
		soundEffectsPlayers[3].setBuffer(PlatformSound);
		break;

	case pondFreeze:
		soundEffectsPlayers[4].setBuffer(PondFreezeSound);
		break;
	case PondMelt:
		soundEffectsPlayers[4].setBuffer(PondMeltSound);
		break;
	case Wind:
		soundEffectsPlayers[4].setBuffer(WindSound);
		break;
	case DiamondCollect:
		soundEffectsPlayers[5].setBuffer(DiamondCollectingSound);
		break;
	default:
		cout << "Invalid sound effect" << endl;
		break;
	}
}