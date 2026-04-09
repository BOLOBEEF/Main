
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
	RECTANGLE,
	GROUND
};


// only initialize one texture for every image, multiple sprites can use the same texture and setTextureRect independently
Texture menuBackground;
Texture playerTexture;
Texture triangleTexture;
Texture cubeTexture;
Texture groundTexture;

// char assets textures
Texture death_smoke;
Texture diamonds;
Texture fire_glow;
Texture fire_head_jumping;
Texture fire_head_rising;
Texture fire_ice_steps;
Texture fire_idle_body;
Texture fire_idle_head;
Texture fire_running;
Texture fire_stairs;
Texture fire_head_falling;
Texture water_body_idle;
Texture water_glow;
Texture water_head_falling;
Texture water_head_idle;
Texture water_head_jump;
Texture water_head_rising;
Texture water_ice_steps;
Texture water_running;
Texture water_stairs;

// map objects textures
Texture movingbox;
Texture snow_flat;
Texture snow_slope_right_slide_down;
Texture snow_slope_left_slide_down;
Texture pusher_block;
Texture fire_door_open;
Texture water_door_open;
Texture fire_block;
Texture fire_block_right;
Texture fire_block_left;
Texture lever_stick;
Texture bar;
Texture bar_cap_right;
Texture bar_cap_left;
Texture ramp_1;
Texture water_block_right;
Texture fire_block_left;
Texture water_block;
Texture slider_dot;
Texture slider_light_on;

//menu assets textures
Texture BackButton0;
Texture BackButtonFull0;
Texture Diamond0;
Texture Diamond1;
Texture Diamond2;
Texture Diamond3;
Texture DiamondDark0;
Texture DiamondDar1;
Texture DiamondDark2;
Texture DiamondDark3;
Texture DiamondPuzzle0;
Texture DiamondPuzzle1;
Texture DiamondPuzzle2;
Texture DiamondPuzzle3;
Texture DiamondSpeed0;
Texture DiamondSpeed1;
Texture DiamondSpeed2;
Texture DiamondSpeed3;
Texture FxButton0;
Texture FxButton1;
Texture GoldLock0;
Texture Lock0;
Texture MusicButton0;
Texture MusicButton1;
Texture MuteButton0;
Texture MuteButton1;
Texture SettingsButton0;
Texture sound_icon;



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
	case GROUND:
		sprite.setTexture(groundTexture);
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
	groundTexture.loadFromFile("Main/Assets/Textures/Ground.png");
	groundTexture.setRepeated(true);
}


void InitializeTextures()
{
	// load all texture here
	// this functions maybe called again if reloading the textures is needed

	 death_smoke.loadFromFile("death smoke.png");
	 diamonds.loadFromFile("diamonds.png");
	 fire_glow.loadFromFile("fire glow.png");
	 fire_head_jumping.loadFromFile("fire head jumping.png");
	 fire_head_rising.loadFromFile("fire head rising.png"); 
	 fire_ice_steps.loadFromFile("fire ice steps.png"); 
    fire_idle_body.loadFromFile("fire idle body.png");
	 fire_idle_head.loadFromFile("fire idle head.png");
	 fire_running.loadFromFile("fire running.png");
	fire_stairs.loadFromFile("fire stairs.png");
	fire_head_falling.loadFromFile("firehead falling.png");
	 water_body_idle.loadFromFile("water body idle.png");
	 water_glow.loadFromFile("water glow.png");
	 water_head_falling.loadFromFile("water head falling.png");
	 water_head_idle.loadFromFile("water head idle.png");
	 water_head_jump.loadFromFile("water head jump.png");
	 water_head_rising.loadFromFile("water head rising.png");
	 water_ice_steps.loadFromFile("water ice steps.png");
	 water_running.loadFromFile("water running.png");
	 water_stairs.loadFromFile("water stairs.png");
	  BackButton0.loadFromFile("BackButton0000.png");
	  BackButtonFull0.loadFromFile("BackButtonFull0000.png");
	  Diamond0.loadFromFile("Diamond0000.png");
	  Diamond1.loadFromFile("Diamond0001.png");
	  Diamond2.loadFromFile("Diamond0002.png");
	  Diamond3.loadFromFile("Diamond0003.png");
	  DiamondDark0;
	  DiamondDar1;
	  DiamondDark2;
	  DiamondDark3;
	  DiamondPuzzle0;
	  DiamondPuzzle1;
	  DiamondPuzzle2;
	  DiamondPuzzle3;
	  DiamondSpeed0;
	  DiamondSpeed1;
	  DiamondSpeed2;
	  DiamondSpeed3;
	  FxButton0;
	  FxButton1;
	  GoldLock0;
	  Lock0;
	  MusicButton0;
	  MusicButton1;
	  MuteButton0;
	  MuteButton1;
	  SettingsButton0;
	  sound_icon;





	// divide the process into functions
	InitializeMenuTextures();
	InitializeGameTextures();
}

