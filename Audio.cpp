
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
	BoyDeath,
	GirlDeath,
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
SoundBuffer BoyDeathSoundSound;
SoundBuffer GirlDeathSound;
// and so on

// have only one Music player and 5 sound effect players
Sound musicPlayer;
int currentSoundEffectPlayer = 0;
Sound soundEffectsPlayers[5];
// loop on those sound effect players when playing sound effects, so we can play multiple sound effects at the same time without cutting each other off, but we can only play 5 sound effects at the same time


// Functions

void InitializeAudio()
{
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
	case BoyDeath:
		break;
	case GirlDeath:
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
