
// S


// Settings :



// Structs and enums


// ALL SPRITE S MUST BE GLOBAL
// so they are always store and never deleted


enum LoadTexture
{
	PLAYER_FIRE,
	TRIANGLE,
	TRIANGLE_ROTATED,


	FLAME_POND,
	WATER_POND,
	TOXIC_POND,

	RECTANGLE,
	GROUND,

	// char assets s
	death_smoke_texture,
	diamondsh_texture,
	fire_glow_texture,
	fire_head_jumping_texture,
	fire_head_rising_texture,
	fire_ice_steps_texture,
	fire_idle_body_texture,
	fire_idle_head_texture,
	fire_running_texture,
	fire_stairs_texture,
	fire_head_falling_texture,
	water_body_idle_texture,
	water_glow_texture,
	water_head_falling_texture,
	water_head_idle_texture,
	water_head_jump_texture,
	water_head_rising_texture,
	water_ice_steps_texture,
	water_running_texture,
	water_stairs_texture,

	// map objects s
	movingbox_texture,
	snow_flat_texture,
	snow_slope_right_side_down_texture,
	snow_slope_left_side_down_texture,
	pusher_block_texture,
	fire_door_open_texture,
	water_door_open_texture,
	fire_pond_texture,
	fire_pond_right_texture,
	fire_pond_left_texture,
	lever_stick_texture,
	bar_texture,
	bar_cap_right_texture,
	bar_cap_left_texture,
	ramp_1_texture,
	water_pond_right_texture,
	water_pond_texture,
	water_pond_left_texture,
	slider_dot_texture,
	slider_light_on_texture,

	//menu assets s
	BackButton0_texture,
	BackButtonFull0_texture,
	Diamond0_texture,
	Diamond1_texture,
	Diamond2_texture,
	Diamond3_texture,
	DiamondDark0_texture,
	DiamondDar1_texture,
	DiamondDark2_texture,
	DiamondDark3_texture,
	DiamondPuzzle0_texture,
	DiamondPuzzle1_texture,
	DiamondPuzzle2_texture,
	DiamondPuzzle3_texture,
	DiamondSpeed0_texture,
	DiamondSpeed1_texture,
	DiamondSpeed2_texture,
	DiamondSpeed3_texture,
	FxButton0_texture,
	FxButton1_texture,
	GoldLock0_texture,
	Lock0_texture,
	MusicButton0_texture,
	MusicButton1_texture,
	MuteButton0_texture,
	MuteButton1_texture,
	SettingsButton0_texture,
	sound_icon_texture,

};


// only initialize one texture for every image, multiple sprites can use the same texture and setTextureRect independently
Texture menuBackground;
Texture playerTexture;
Texture triangleTexture;

Texture firePondTexture, waterPondTexture, toxicPondTexture;

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
Texture snow_slope_right_side_down;
Texture snow_slope_left_side_down;
Texture pusher_block;
Texture fire_door_open;
Texture water_door_open;
Texture fire_pond;
Texture fire_pond_right;
Texture fire_pond_left;
Texture lever_stick;
Texture bar;
Texture bar_cap_right;
Texture bar_cap_left;
Texture ramp_1;
Texture water_pond_right;
Texture water_pond;
Texture water_pond_left;
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

void SetSpriteOriginToCenter(Sprite& sprite, bool dontMove = false) {
	FloatRect bounds = sprite.getLocalBounds();
	Vector2f oldOrigin = sprite.getOrigin();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	if (dontMove) sprite.move(-Vector2f((oldOrigin.x - bounds.width / 2.0f) * sprite.getScale().x, (oldOrigin.y - bounds.height / 2.0f) * sprite.getScale().y));
}


void ApplyTexture(Sprite& sprite, LoadTexture texture, Vector2f size, Vector2f scale = Vector2f(1, 1)) {
	bool isValid = true;
	bool centerOrigin = true;
	bool flip = false;
	
	switch (texture)
	{
	case PLAYER_FIRE:
		//
		break;

	case TRIANGLE:
		sprite.setTexture(triangleTexture);
		sprite.setColor(Color::White);
		break;

	case TRIANGLE_ROTATED:
		sprite.setTexture(triangleTexture);
		sprite.setColor(Color::White);
		flip = true;
		break;

	case RECTANGLE:
		sprite.setTexture(cubeTexture);
		sprite.setColor(Color::White);
		break;
	case FLAME_POND:
		sprite.setTexture(firePondTexture);
		sprite.setColor(Color::Red);
		sprite.setScale(0.1f, 0.1f);
		break;
	case WATER_POND:
		sprite.setTexture(waterPondTexture);
		sprite.setColor(Color::Blue);
		sprite.setScale(0.1f, 0.1f);
		break;
	case TOXIC_POND:
		sprite.setTexture(toxicPondTexture);
		sprite.setColor(Color::Green);
		sprite.setScale(0.1f, 0.1f);

	case GROUND:
		sprite.setTexture(groundTexture);
		centerOrigin = false;
		break;

	default:
		cout << "Invalid texture" << endl;
		isValid = false;
		return;
		break;
	}

	if (!isValid) return;
	if (centerOrigin) SetSpriteOriginToCenter(sprite, true);
	if (flip)
		SetSpriteSize(sprite, size, true);
	else
		SetSpriteSize(sprite, size);
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

	 death_smoke.loadFromFile("Main\\Assets\\Animations\\characters assets\\death smoke.png");
	 diamonds.loadFromFile("Main\\Assets\\Animations\\characters assets\\diamonds.png");
	 fire_glow.loadFromFile("Main\\Assets\\Animations\\characters assets\\fire glow.png");
	 fire_head_jumping.loadFromFile("Main\\Assets\\Animations\\characters assets\\fire head jumping.png");
	 fire_head_rising.loadFromFile("Main\\Assets\\Animations\\characters assets\\fire head rising.png"); 
	 fire_ice_steps.loadFromFile("Main\\Assets\\Animations\\characters assets\\fire ice steps.png"); 
    fire_idle_body.loadFromFile("Main\\Assets\\Animations\\characters assets\\fire idle body.png");
	 fire_idle_head.loadFromFile("Main\\Assets\\Animations\\characters assets\\fire idle head.png");
	 fire_running.loadFromFile("Main\\Assets\\Animations\\characters assets\\fire running.png");
	fire_stairs.loadFromFile("Main\\Assets\\Animations\\characters assets\\fire stairs.png");
	fire_head_falling.loadFromFile("Main\\Assets\\Animations\\characters assets\\firehead falling.png");
	 water_body_idle.loadFromFile("Main\\Assets\\Animations\\characters assets\\water body idle.png");
	 water_glow.loadFromFile("Main\\Assets\\Animations\\characters assets\\water glow.png");
	 water_head_falling.loadFromFile("Main\\Assets\\Animations\\characters assets\\water head falling.png");
	 water_head_idle.loadFromFile("Main\\Assets\\Animations\\characters assets\\water head idle.png");
	 water_head_jump.loadFromFile("Main\\Assets\\Animations\\characters assets\\water head jump.png");
	 water_head_rising.loadFromFile("Main\\Assets\\Animations\\characters assets\\water head rising.png");
	 water_ice_steps.loadFromFile("Main\\Assets\\Animations\\characters assets\\water ice steps.png");
	 water_running.loadFromFile("Main\\Assets\\Animations\\characters assets\\water running.png");
	 water_stairs.loadFromFile("Main\\Assets\\Animations\\characters assets\\water stairs.png");
	  BackButton0.loadFromFile("Main\\Assets\\Animations\\menu assets\\BackButton0000.png");
	  BackButtonFull0.loadFromFile("Main\\Assets\\Animations\\menu assets\\BackButtonFull0000.png");
	  Diamond0.loadFromFile("Main\\Assets\\Animations\\menu assets\\Diamond0000.png");
	  Diamond1.loadFromFile("Main\\Assets\\Animations\\menu assets\\Diamond0001.png");
	  Diamond2.loadFromFile("Main\\Assets\\Animations\\menu assets\\Diamond0002.png");
	  Diamond3.loadFromFile("Main\\Assets\\Animations\\menu assets\\Diamond0003.png");
	  DiamondDark0.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondDark0000.png");
	  DiamondDar1.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondDark0001.png");
	  DiamondDark2.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondDark0002.png");
	  DiamondDark3.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondDark0003.png");
	  DiamondPuzzle0.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondPuzzle0000.png");
	  DiamondPuzzle1.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondPuzzle0001.png");
	  DiamondPuzzle2.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondPuzzle0002.png");
	  DiamondPuzzle3.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondPuzzle0003.png");
	  DiamondSpeed0.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondSpeed0000.png");
	  DiamondSpeed1.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondSpeed0001.png");
	  DiamondSpeed2.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondSpeed0002.png");
	  DiamondSpeed3.loadFromFile("Main\\Assets\\Animations\\menu assets\\DiamondSpeed0003.png");
	  FxButton0.loadFromFile("Main\\Assets\\Animations\\menu assets\\FxButton0000.png");
	  FxButton1.loadFromFile("Main\\Assets\\Animations\\menu assets\\FxButton0001.png");
	  GoldLock0.loadFromFile("Main\\Assets\\Animations\\menu assets\\GoldLock0000.png");
	  Lock0.loadFromFile("Main\\Assets\\Animations\\menu assets\\Lock0000.png");
	  MusicButton0.loadFromFile("Main\\Assets\\Animations\\menu assets\\MusicButton0000.png");
	  MusicButton1.loadFromFile("Main\\Assets\\Animations\\menu assets\\MusicButton0001.png");
	  MuteButton0.loadFromFile("Main\\Assets\\Animations\\menu assets\\MuteButton0000.png");
	  MuteButton1.loadFromFile("Main\\Assets\\Animations\\menu assets\\MuteButton0001.png");
	  SettingsButton0.loadFromFile("Main\\Assets\\Animations\\menu assets\\SettingsButton0000.png");
	  sound_icon.loadFromFile("Main\\Assets\\Animations\\menu assets\\sound icon.png");
	  movingbox.loadFromFile("Main\\Assets\\Animations\\map objects assets\\movingbox.png");
	  snow_flat.loadFromFile("Main\\Assets\\Animations\\map objects assets\\snow flat.png");
      snow_slope_right_side_down.loadFromFile("Main\\Assets\\Animations\\map objects assets\\snow slope right side down.png");
		  snow_slope_left_side_down.loadFromFile("Main\\Assets\\Animations\\map objects assets\\snow slope left side down.png");
		  pusher_block.loadFromFile("Main\\Assets\\Animations\\map objects assets\\pusher_block.png");
		  fire_door_open.loadFromFile("Main\\Assets\\Animations\\map objects assets\\fire door open.png");
		  water_door_open.loadFromFile("Main\\Assets\\Animations\\map objects assets\\water door open.png");
		 fire_pond.loadFromFile("Main\\Assets\\Animations\\map objects assets\\fire box.png");
		  fire_pond_right.loadFromFile("Main\\Assets\\Animations\\map objects assets\\fire box right.png");
		  fire_pond_left.loadFromFile("Main\\Assets\\Animations\\map objects assets\\fire box left.png");
		  lever_stick.loadFromFile("Main\\Assets\\Animations\\map objects assets\\lever stick.png");
		  bar.loadFromFile("Main\\Assets\\Animations\\map objects assets\\bar center.png");
		  bar_cap_right.loadFromFile("Main\\Assets\\Animations\\map objects assets\\bar cap right.png");
		  bar_cap_left.loadFromFile("Main\\Assets\\Animations\\map objects assets\\bar cap left.png");
		  ramp_1.loadFromFile("Main\\Assets\\Animations\\map objects assets\\ramp_1.png");
		  water_pond_right.loadFromFile("Main\\Assets\\Animations\\map objects assets\\water box right.png");
		   water_pond.loadFromFile("Main\\Assets\\Animations\\map objects assets\\water box.png");
		   water_pond_left.loadFromFile("Main\\Assets\\Animations\\map objects assets\\water box left.png");
		   slider_dot.loadFromFile("Main\\Assets\\Animations\\map objects assets\\sliderdot.png");
		  slider_light_on.loadFromFile("Main\\Assets\\Animations\\map objects assets\\slider_light_on.png");



	// divide the process into functions
	InitializeMenuTextures();
	InitializeGameTextures();
}

