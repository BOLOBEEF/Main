
// TEXTURES


// Settings :



// Structs and enums


// ALL SPRITE TEXTURES MUST BE GLOBAL
// so they are always store and never deleted


enum LoadTexture
{
	PLAYER_FIRE,
	TRIANGLE,
	TRIANGLE_ROTATED,
	RECTANGLE
};


// only initialize one texture for every image, multiple sprites can use the same texture and setTextureRect independently
Texture menuBackground;
Texture playerTexture;
Texture triangleTexture;
Texture cubeTexture;


// Functions


// menu and gameLogic scripts should apply their textures using this script
// maybe divide it into a menu version and a gamelogic version for clarity

// set size of sprite in pixels
void SetSpriteSize(Sprite& sprite, Vector2f size, bool rotate = false) {
	Vector2f scale = Vector2f(size.x / sprite.getLocalBounds().width, size.y / sprite.getLocalBounds().height);
	sprite.setScale((rotate ? -scale.x : scale.x), scale.y);
}


void FlipSprite(Sprite& sprite) {
	Vector2f scale = sprite.getScale();
	sprite.setScale(-scale.x, scale.y);
}

void ApplyTexture(Sprite& sprite, LoadTexture texture, Vector2f size, Vector2f scale = Vector2f(1, 1)) {
	switch (texture)
	{
	case PLAYER_FIRE:
		//
		break;

	case TRIANGLE:
		sprite.setTexture(triangleTexture);
		sprite.setColor(Color::White);
		SetSpriteSize(sprite, size);
		break;

	case TRIANGLE_ROTATED:
		sprite.setTexture(triangleTexture);
		sprite.setColor(Color::White);
		SetSpriteSize(sprite, size, true);
		break;

	case RECTANGLE:
		sprite.setTexture(cubeTexture);
		sprite.setColor(Color::White);
		SetSpriteSize(sprite, size);
		break;

	default:
		cout << "Invalid texture" << endl;
		return;
		break;
	}
}

void InitializeMenuTextures() {
	// load menu textures
	// menuBackground.load......
}

void InitializeGameTextures() {
	// load game textures
	// playerTexture.load......

	triangleTexture.loadFromFile("Main/Assets/Textures/Triangle.png");
	cubeTexture.loadFromFile("Main/Assets/Textures/Cube.png");
}


void InitializeTextures()
{
	// load all texture here
	// this functions maybe called again if reloading the textures is needed

	// divide the process into functions
	InitializeMenuTextures();
	InitializeGameTextures();
}

