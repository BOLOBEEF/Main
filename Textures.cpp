
// TEXTURES


// Settings :



// Structs and enums


// ALL SPRITE TEXTURES MUST BE GLOBAL
// so they are always store and never deleted


enum LoadTexture
{
	PLAYER_FIRE,
	TRIANGLE,
	TRIANGLE_ROTATED
};


// only initialize one texture for every image, multiple sprites can use the same texture and setTextureRect independently
Texture menuBackground;
Texture playerTexture;
Texture triangleTexture;


// Functions

void InitializeMenuTextures() {
	// load menu textures
	// menuBackground.load......
}

void InitializeGameTextures() {
	// load game textures
	// playerTexture.load......
	
	triangleTexture.loadFromFile("Main/Assets/Textures/Triangle.png");
}


// menu and gameLogic scripts should apply their textures using this script
// maybe divide it into a menu version and a gamelogic version for clarity

void ApplyTexture(Sprite& sprite, LoadTexture texture) {
	switch (texture)
	{
	case PLAYER_FIRE:
		//
		break;

	case TRIANGLE:
		sprite.setTexture(triangleTexture);
		sprite.setColor(Color::White);
		sprite.setScale(0.1f, 0.1f);
		break;

	case TRIANGLE_ROTATED:
		sprite.setTexture(triangleTexture);
		sprite.setColor(Color::White);
		sprite.setScale(-0.1f, 0.1f);
		break;

	default:
		cout << "Invalid texture" << endl;
		break;
	}
}


void InitializeTextures()
{
	// load all texture here
	// this functions maybe called again if reloading the textures is needed

	// divide the process into functions
	InitializeMenuTextures();
	InitializeGameTextures();
}
