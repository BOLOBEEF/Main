
// S


// Settings :



// Structs and enums


// ALL SPRITE S MUST BE GLOBAL
// so they are always store and never deleted


enum LoadTexture
{
	//texture for temporary_ground
	
	/*--------------------------------------------*/
	TEMPORARY_GROUND,
	/*--------------------------------------------*/

	// texture for game objects
	PLAYER_FIRE,
	TRIANGLE,
	TRIANGLE_ROTATED,


	FLAME_POND,
	WATER_POND,
	TOXIC_POND,

	RECTANGLE,
	GROUND,
	BACKGROUND,

	// char assets s
	death_smoke_texture,
	diamonds_texture,
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
	diamond_fire_texture,
	diamond_water_texture,
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
	lever_base_texture,
	bar_texture,
	green_pond_texture,
	green_pond_left_texture,
	green_pond_right_texture,
	bar_cap_right_texture,
	bar_cap_left_texture,
	ramp_1_texture,
	water_pond_right_texture,
	water_pond_texture,
	water_pond_left_texture,
	slider_dot_texture,
	slider_light_on_texture,
	DOOR_WATER,
	DOOR_FIRE,

	//menu assets s
	BackButton0_texture,
	BackButtonFull0_texture,
	Diamond0_texture,
	Diamond1_texture,
	Diamond2_texture,
	Diamond3_texture,
	DiamondDark0_texture,
	DiamondDark1_texture,
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
	loading_icon_texture,
	menu_box_texture,
	pause_icon_texture,
	clock_timer_texture,
	stone_button_0_texture,
	stone_button_1_texture,
	main_menu_background_texture,
	game_name_texture,
	cursor_texture,
	pointer_texture,
	arrow_icon0_texture,
	arrow_icon1_texture,
	x_icon_texture,
	tick_icon_texture,
	rating_diamonds_texture,
	finished_icon_texture,
	diamonds_green_texture,
	diamonds_purple_texture,
	diamonds_orange_texture,


};


// only initialize one texture for every image, multiple sprites can use the same texture and setTextureRect independently
Texture menuBackground;
Texture playerTexture;
Texture triangleTexture;

Texture firePondTexture, waterPondTexture, toxicPondTexture;
Texture firedoor, waterdoor;
Texture cubeTexture;
Texture groundTexture;
Texture backgroundTexture;

// char assets textures
Texture death_smoke;
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
Texture diamond_fire;
Texture diamond_water;
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
Texture lever_base;
Texture bar;
Texture bar_cap_right;
Texture bar_cap_left;
Texture ramp_1;
Texture water_pond_right;
Texture water_pond;
Texture water_pond_left;
Texture slider_dot;
Texture slider_light_on;
Texture green_pond;
Texture green_pond_right;
Texture green_pond_left;
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
Texture loading_icon;
Texture pause_icon;
Texture menu_box;
Texture clock_timer;
Texture stone_button;
Texture main_menu_background;
Texture game_name;
Texture arrow_icon0;
Texture arrow_icon1;
Texture x_icon;
Texture tick_icon;
Texture rating_diamonds;
Texture finished_icon;
Texture diamonds_green;
Texture diamonds_purple;
Texture diamonds_orange;
//cursor texture
Texture CursorAndPointer;

// Functions


// menu and gameLogic scripts should apply their textures using this script
// maybe divide it into a menu version and a gamelogic version for clarity

// set size of sprite in pixels
void SetSpriteSize(Sprite& sprite, Vector2f size, bool rotate = false) {
	Vector2f scale = Vector2f(size.x / sprite.getLocalBounds().width, size.y / sprite.getLocalBounds().height);
	sprite.setScale((rotate ? -scale.x : scale.x), scale.y);
}

// set sprite bounds start from point to point
void StrechSprite(Sprite& sprite, Vector2f startPoint, Vector2f endPoint, bool rotate = false) {
	Vector2f origin = sprite.getOrigin();
	sprite.setOrigin(Vector2f(0, 0));
	sprite.setPosition(startPoint);
	SetSpriteSize(sprite, Vector2f(abs(endPoint.x - startPoint.x), abs(endPoint.y - startPoint.y)), rotate);
	sprite.setOrigin(origin);
}

void DrawSpriteWithOffset(Sprite sprite, Vector2f offset, RenderTarget& renderTarget) {
	sprite.move(offset);
	renderTarget.draw(sprite);
}

void FlipSprite(Sprite& sprite) {
	Vector2f scale = sprite.getScale();
	sprite.setScale(-scale.x, scale.y);
}

void SetSpriteOriginToCenter(Sprite& sprite, bool dontMove = false) {
	FloatRect bounds = sprite.getLocalBounds();
	Vector2f oldOrigin = sprite.getOrigin();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	// instead accept any origin
	if (dontMove) sprite.move(-Vector2f((oldOrigin.x - bounds.width / 2.0f) * sprite.getScale().x, (oldOrigin.y - bounds.height / 2.0f) * sprite.getScale().y));
}


void ApplyTexture(Sprite& sprite, LoadTexture texture, Vector2f size = Vector2f(1.0f, 1.0f), Vector2f scale = Vector2f(1.0f, 1.0f), bool centerOrigin = true) {
	bool isValid = true;
	bool flip = false;

	switch (texture)
	{

		// char assets

		// this is new!!
		/*--------------------------------------------*/
		case TEMPORARY_GROUND:
			sprite.setTexture(groundTexture);
			break;
			/*--------------------------------------------*/

	case death_smoke_texture:
		sprite.setTexture(death_smoke);
		break;
	case diamond_fire_texture:
		sprite.setTexture(diamond_fire);
		break;

	case diamond_water_texture:
		sprite.setTexture(diamond_water);
		break; 
	case fire_glow_texture:
		sprite.setTexture(fire_glow);
		break;

	case fire_head_jumping_texture:
		sprite.setTexture(fire_head_jumping);
		break;

	case fire_head_rising_texture:
		sprite.setTexture(fire_head_rising);
		break;

	case fire_ice_steps_texture:
		sprite.setTexture(fire_ice_steps);
		break;

	case fire_idle_body_texture:
		sprite.setTexture(fire_idle_body);
		break;

	case fire_idle_head_texture:
		sprite.setTexture(fire_idle_head);
		break;

	case fire_running_texture:
		sprite.setTexture(fire_running);
		break;

	case fire_stairs_texture:
		sprite.setTexture(fire_stairs);
		break;

	case fire_head_falling_texture:
		sprite.setTexture(fire_head_falling);
		break;

	case water_body_idle_texture:
		sprite.setTexture(water_body_idle);
		break;

	case water_glow_texture:
		sprite.setTexture(water_glow);
		break;

	case water_head_falling_texture:
		sprite.setTexture(water_head_falling);
		break;

	case water_head_idle_texture:
		sprite.setTexture(water_head_idle);
		break;

	case water_head_jump_texture:
		sprite.setTexture(water_head_jump);
		break;
		
	case water_head_rising_texture:
		sprite.setTexture(water_head_rising);
		break;

	case water_ice_steps_texture:
		sprite.setTexture(water_ice_steps);
		break;

	case water_running_texture:
		sprite.setTexture(water_running);
		break;

	case water_stairs_texture:
		sprite.setTexture(water_stairs);
		break;

		// map objects assets








	case movingbox_texture:
		sprite.setTexture(movingbox);
		sprite.setTextureRect(IntRect(0, 0, 74, 76));
		break;
	

	case snow_flat_texture:
		sprite.setTexture(snow_flat);
		break;

	case snow_slope_right_side_down_texture:
		sprite.setTexture(snow_slope_right_side_down);
		break;

	case snow_slope_left_side_down_texture:
		sprite.setTexture(snow_slope_left_side_down);
		break;

	case pusher_block_texture:
		sprite.setTexture(pusher_block);
		break;

	case fire_door_open_texture:
		sprite.setTexture(fire_door_open);
		break;

	case water_door_open_texture:
		sprite.setTexture(water_door_open);
		break;

	case fire_pond_texture:
		sprite.setTexture(fire_pond);
		break;

	case fire_pond_right_texture:
		sprite.setTexture(fire_pond_right);
		break;

	case fire_pond_left_texture:
		sprite.setTexture(fire_pond_left);
		break;

	case lever_stick_texture:
		sprite.setTexture(lever_stick);
		break;

	case lever_base_texture:
		sprite.setTexture(lever_base);
		break;

	case bar_texture:
		sprite.setTexture(bar);
		break;

	case bar_cap_right_texture:
		sprite.setTexture(bar_cap_right);
		break;

	case bar_cap_left_texture:
		sprite.setTexture(bar_cap_left);
		break;

	case ramp_1_texture:
		sprite.setTexture(ramp_1);
		break;

	case water_pond_right_texture:
		sprite.setTexture(water_pond_right);
		break;

	case water_pond_texture:
		sprite.setTexture(water_pond);
		break;

	case water_pond_left_texture:
		sprite.setTexture(water_pond_left);
		break;

	case slider_dot_texture:
		sprite.setTexture(slider_dot);
		break;

	case slider_light_on_texture:
		sprite.setTexture(slider_light_on);
		break;

	case green_pond_texture:
		sprite.setTexture(green_pond);
		break;

	case green_pond_right_texture:
		sprite.setTexture(green_pond_right);
		break;

	case green_pond_left_texture:
		sprite.setTexture(green_pond_left);
		break;






		// menu assets

	case arrow_icon0_texture:
		sprite.setTexture(arrow_icon0);
		break;

	case arrow_icon1_texture:
		sprite.setTexture(arrow_icon1);
		break;

	case x_icon_texture:
		sprite.setTexture(x_icon);
		break;

	case tick_icon_texture:
		sprite.setTexture(tick_icon);
		break;

	case rating_diamonds_texture:
		sprite.setTexture(rating_diamonds);
		break;

	case finished_icon_texture:
		sprite.setTexture(finished_icon);
		break;

	case diamonds_green_texture:
		sprite.setTexture(diamonds_green);
		break;

	case diamonds_purple_texture:
		sprite.setTexture(diamonds_purple);
		break;

	case diamonds_orange_texture:
		sprite.setTexture(diamonds_orange);
		break;

	case BackButton0_texture:
		sprite.setTexture(BackButton0);
		break;
	case BackButtonFull0_texture:
		sprite.setTexture(BackButtonFull0);
		break;
	case Diamond0_texture:
		sprite.setTexture(Diamond0);
		break;
	case Diamond1_texture:
		sprite.setTexture(Diamond1);
		break;
	case Diamond2_texture:
		sprite.setTexture(Diamond2);
		break;
	case Diamond3_texture:
		sprite.setTexture(Diamond3);
		break;
	case DiamondDark0_texture:
		sprite.setTexture(DiamondDark0);
		break;
	case DiamondDark1_texture:
		sprite.setTexture(DiamondDar1);
		break;
	case DiamondDark2_texture:
		sprite.setTexture(DiamondDark2);
		break;
	case DiamondDark3_texture:
		sprite.setTexture(DiamondDark3);
		break;
	case DiamondPuzzle0_texture:
		sprite.setTexture(DiamondPuzzle0);
		break;
	case DiamondPuzzle1_texture:
		sprite.setTexture(DiamondPuzzle1);
		break;
	case DiamondPuzzle2_texture:
		sprite.setTexture(DiamondPuzzle2);
		break;
	case DiamondPuzzle3_texture:
		sprite.setTexture(DiamondPuzzle3);
		break;
	case DiamondSpeed0_texture:
		sprite.setTexture(DiamondSpeed0);
		break;
	case DiamondSpeed1_texture:
		sprite.setTexture(DiamondSpeed1);
		break;
	case DiamondSpeed2_texture:
		sprite.setTexture(DiamondSpeed2);
		break;
	case DiamondSpeed3_texture:
		sprite.setTexture(DiamondSpeed3);
		break;
	case FxButton0_texture:
		sprite.setTexture(FxButton0);
		break;
	case FxButton1_texture:
		sprite.setTexture(FxButton1);
		break;
	case GoldLock0_texture:
		sprite.setTexture(GoldLock0);
		break;
	case Lock0_texture:
		sprite.setTexture(Lock0);
		break;
	case MusicButton0_texture:
		sprite.setTexture(MusicButton0);
		break;
	case MusicButton1_texture:
		sprite.setTexture(MusicButton1);
		break;
	case MuteButton0_texture:
		sprite.setTexture(MuteButton0);
		break;
	case MuteButton1_texture:
		sprite.setTexture(MuteButton1);
		break;
	case SettingsButton0_texture:
		sprite.setTexture(SettingsButton0);
		break;
	case sound_icon_texture:
		sprite.setTexture(sound_icon);
		break;
	case loading_icon_texture:
		sprite.setTexture(loading_icon);
		break;
	case pause_icon_texture:
		sprite.setTexture(pause_icon);
			break;
	case menu_box_texture:
		sprite.setTexture(menu_box);
			break;
	case clock_timer_texture:
		sprite.setTexture(clock_timer);
		break;
	case stone_button_0_texture:
		sprite.setTexture(stone_button);
		break;
	case stone_button_1_texture:
		sprite.setTexture(stone_button);
		break;

	case main_menu_background_texture:
		sprite.setTexture(main_menu_background);
		break;
	case game_name_texture:
		sprite.setTexture(game_name);
		break;
		// cursor and pointer
	case cursor_texture:
		sprite.setTexture(CursorAndPointer);
		break;
	case pointer_texture:
		sprite.setTexture(CursorAndPointer);
		break;

		// temporary assets
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
	case BACKGROUND:
		sprite.setTexture(backgroundTexture);
		centerOrigin = false;
		break;
	case DOOR_FIRE:
		sprite.setTexture(firedoor);
		sprite.setColor(Color::Red);
		break;
	case DOOR_WATER:
		sprite.setTexture(waterdoor);
		sprite.setColor(Color::Blue);

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
	backgroundTexture.loadFromFile("Main/Assets/Textures/backGround.png");
	backgroundTexture.setRepeated(true);
}


void InitializeTextures()
{
	// load all texture here
	// this functions maybe called again if reloading the textures is needed

	death_smoke.loadFromFile("Main/Assets/Animations/characters assets/death smoke.png");
	diamond_fire.loadFromFile("Main/Assets/Animations/characters assets/diamond_fire.png");
	diamond_water.loadFromFile("Main/Assets/Animations/characters assets/diamond_water.png");
	fire_glow.loadFromFile("Main/Assets/Animations/characters assets/fire glow.png");
	fire_head_jumping.loadFromFile("Main/Assets/Animations/characters assets/fire head jumping.png");
	fire_head_rising.loadFromFile("Main/Assets/Animations/characters assets/fire head rising.png");
	fire_ice_steps.loadFromFile("Main/Assets/Animations/characters assets/fire ice steps.png");
	fire_idle_body.loadFromFile("Main/Assets/Animations/characters assets/fire idle body.png");
	fire_idle_head.loadFromFile("Main/Assets/Animations/characters assets/fire idle head.png");
	fire_running.loadFromFile("Main/Assets/Animations/characters assets/fire running.png");
	fire_stairs.loadFromFile("Main/Assets/Animations/characters assets/fire stairs.png");
	fire_head_falling.loadFromFile("Main/Assets/Animations/characters assets/firehead falling.png");
	water_body_idle.loadFromFile("Main/Assets/Animations/characters assets/water body idle.png");
	water_glow.loadFromFile("Main/Assets/Animations/characters assets/water glow.png");
	water_head_falling.loadFromFile("Main/Assets/Animations/characters assets/water head falling.png");
	water_head_idle.loadFromFile("Main/Assets/Animations/characters assets/water head idle.png");
	water_head_jump.loadFromFile("Main/Assets/Animations/characters assets/water head jump.png");
	water_head_rising.loadFromFile("Main/Assets/Animations/characters assets/water head rising.png");
	water_ice_steps.loadFromFile("Main/Assets/Animations/characters assets/water ice steps.png");
	water_running.loadFromFile("Main/Assets/Animations/characters assets/water running.png");
	water_stairs.loadFromFile("Main/Assets/Animations/characters assets/water stairs.png");
	BackButton0.loadFromFile("Main/Assets/Animations/menu assets/BackButton0000.png");
	BackButtonFull0.loadFromFile("Main/Assets/Animations/menu assets/BackButtonFull0000.png");
	Diamond0.loadFromFile("Main/Assets/Animations/menu assets/Diamond0000.png");
	Diamond1.loadFromFile("Main/Assets/Animations/menu assets/Diamond0001.png");
	Diamond2.loadFromFile("Main/Assets/Animations/menu assets/Diamond0002.png");
	Diamond3.loadFromFile("Main/Assets/Animations/menu assets/Diamond0003.png");
	DiamondDark0.loadFromFile("Main/Assets/Animations/menu assets/DiamondDark0000.png");
	DiamondDar1.loadFromFile("Main/Assets/Animations/menu assets/DiamondDark0001.png");
	DiamondDark2.loadFromFile("Main/Assets/Animations/menu assets/DiamondDark0002.png");
	DiamondDark3.loadFromFile("Main/Assets/Animations/menu assets/DiamondDark0003.png");
	DiamondPuzzle0.loadFromFile("Main/Assets/Animations/menu assets/DiamondPuzzle0000.png");
	DiamondPuzzle1.loadFromFile("Main/Assets/Animations/menu assets/DiamondPuzzle0001.png");
	DiamondPuzzle2.loadFromFile("Main/Assets/Animations/menu assets/DiamondPuzzle0002.png");
	DiamondPuzzle3.loadFromFile("Main/Assets/Animations/menu assets/DiamondPuzzle0003.png");
	DiamondSpeed0.loadFromFile("Main/Assets/Animations/menu assets/DiamondSpeed0000.png");
	DiamondSpeed1.loadFromFile("Main/Assets/Animations/menu assets/DiamondSpeed0001.png");
	DiamondSpeed2.loadFromFile("Main/Assets/Animations/menu assets/DiamondSpeed0002.png");
	DiamondSpeed3.loadFromFile("Main/Assets/Animations/menu assets/DiamondSpeed0003.png");
	FxButton0.loadFromFile("Main/Assets/Animations/menu assets/FxButton0000.png");
	FxButton1.loadFromFile("Main/Assets/Animations/menu assets/FxButton0001.png");
	GoldLock0.loadFromFile("Main/Assets/Animations/menu assets/GoldLock0000.png");
	Lock0.loadFromFile("Main/Assets/Animations/menu assets/Lock0000.png");
	MusicButton0.loadFromFile("Main/Assets/Animations/menu assets/MusicButton0000.png");
	MusicButton1.loadFromFile("Main/Assets/Animations/menu assets/MusicButton0001.png");
	MuteButton0.loadFromFile("Main/Assets/Animations/menu assets/MuteButton0000.png");
	MuteButton1.loadFromFile("Main/Assets/Animations/menu assets/MuteButton0001.png");
	SettingsButton0.loadFromFile("Main/Assets/Animations/menu assets/SettingsButton0000.png");
	sound_icon.loadFromFile("Main/Assets/Animations/menu assets/sound icon.png");
	movingbox.loadFromFile("Main/Assets/Animations/map objects assets/movingbox.png");
	snow_flat.loadFromFile("Main/Assets/Animations/map objects assets/snow flat.png");
	snow_slope_right_side_down.loadFromFile("Main/Assets/Animations/map objects assets/snow slope right side down.png");
	snow_slope_left_side_down.loadFromFile("Main/Assets/Animations/map objects assets/snow slope left side down.png");
	pusher_block.loadFromFile("Main/Assets/Animations/map objects assets/pusher_block.png");
	fire_door_open.loadFromFile("Main/Assets/Animations/map objects assets/fire door open.png");
	water_door_open.loadFromFile("Main/Assets/Animations/map objects assets/water door open.png");
	fire_pond.loadFromFile("Main/Assets/Animations/map objects assets/fire box.png");
	fire_pond_right.loadFromFile("Main/Assets/Animations/map objects assets/fire box right.png");
	fire_pond_left.loadFromFile("Main/Assets/Animations/map objects assets/fire box left.png");
	lever_stick.loadFromFile("Main/Assets/Animations/map objects assets/lever stick.png");
	lever_base.loadFromFile("Main/Assets/Animations/map objects assets/lever base.png");
	bar.loadFromFile("Main/Assets/Animations/map objects assets/bar center.png");
	bar_cap_right.loadFromFile("Main/Assets/Animations/map objects assets/bar cap right.png");
	bar_cap_left.loadFromFile("Main/Assets/Animations/map objects assets/bar cap left.png");
	ramp_1.loadFromFile("Main/Assets/Animations/map objects assets/ramp_1.png");
	water_pond_right.loadFromFile("Main/Assets/Animations/map objects assets/water box right.png");
	water_pond.loadFromFile("Main/Assets/Animations/map objects assets/water box.png");
	water_pond_left.loadFromFile("Main/Assets/Animations/map objects assets/water box left.png");
	slider_dot.loadFromFile("Main/Assets/Animations/map objects assets/sliderdot.png");
	slider_light_on.loadFromFile("Main/Assets/Animations/map objects assets/slider_light_on.png");
	green_pond.loadFromFile("Main/Assets/Animations/map objects assets/green box.png");
	green_pond_left.loadFromFile("Main/Assets/Animations/map objects assets/green box left.png");
	green_pond_right.loadFromFile("Main/Assets/Animations/map objects assets/green box right.png");
	loading_icon.loadFromFile("Main/Assets/Animations/menu assets/loading_icon.png");
	pause_icon.loadFromFile("Main/Assets/Animations/menu assets/pause icon.png");
	menu_box.loadFromFile("Main/Assets/Animations/menu assets/menu box.png");
	CursorAndPointer.loadFromFile("Main/Assets/Animations/cursor assets/CursorAndPointer.png");
	clock_timer.loadFromFile("Main/Assets/Animations/menu assets/clock timer.png");
	stone_button.loadFromFile("Main/Assets/Animations/menu assets/stone button.png");
	main_menu_background.loadFromFile("Main/Assets/Animations/menu assets/main menu background.png");
	game_name.loadFromFile("Main/Assets/Animations/menu assets/GameNameForest.png");
	x_icon.loadFromFile("Main/Assets/Animations/menu assets/x_icon.png");
	tick_icon.loadFromFile("Main/Assets/Animations/menu assets/tick_icon.png");
	arrow_icon0.loadFromFile("Main/Assets/Animations/menu assets/arrow_icon0.png");
	arrow_icon1.loadFromFile("Main/Assets/Animations/menu assets/arrow_icon1.png");
	rating_diamonds.loadFromFile("Main/Assets/Animations/menu assets/rating_diamonds.png");
	finished_icon.loadFromFile("Main/Assets/Animations/menu assets/finished_icon.png");


	// divide the process into functions
	InitializeMenuTextures();
	InitializeGameTextures();
}
