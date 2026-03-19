
// TEXTURES


// Settings :



// Structs and enums


// ALL SPRITE TEXTURES MUST BE GLOBAL
// so they are always store and never deleted

// only initialize one texture for every image, multiple sprites can use the same texture and setTextureRect independently
Texture menuBackground;
Texture playerTexture;


// Functions

void InitializeMenuTextures() {
	// load menu textures
	// menuBackground.load......
	// apply those textures to their corresponding sprites
}

void InitializeGameTextures() {
	// load menu textures
	// playerTexture.load......
	// apply those textures to their corresponding sprites
	playerTexture.loadFromFile("C:/Users/PC/Downloads/SFML Template/sfml-github/ConsoleApplication1/Main/Assets/Preview.png");
	player.setTexture(playerTexture);
	player.setOrigin(player.getLocalBounds().width / 2.0f, player.getLocalBounds().height / 2.0f);
}


void InitializeTextures()
{
	// load all texture here
	// this functions maybe called again if reloading the textures is needed

	// divide the process into functions
	InitializeMenuTextures();
	InitializeGameTextures();
}
