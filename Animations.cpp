// Animations


// Settings :



// Structs and enums


// Runtime variables
// Ex: clocks and timers for animations
Clock playOnceClock;



// Functions
void InitializeOneTimeAnimations()
{
	playOnceClock.restart(); // so that the animation will start from the beginning when we open the win menu, and not from the middle if we win multiple times in a row without closing the game
}

void InitializeAnimations()
{

	// code for initializing menu variables and objects
	// for example initialize timers or counters
}

void SetAnimationFrame(Sprite& sprite, int currentFrame, int totalWidth, int height, int frameCount, int yOffset = 0) {
	int frameWidth = totalWidth / frameCount;
	sprite.setTextureRect(IntRect(currentFrame * frameWidth, yOffset, frameWidth, height));
}

void UpdateLoopingAnimation(Sprite& sprite, int totalWidth, int height, int frameCount, float speed, int yOffset = 0) {
	int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
	SetAnimationFrame(sprite, index, totalWidth, height, frameCount, yOffset);
}

void UpdatePlayOnceAnimation(Sprite& sprite, int totalWidth, int height, int frameCount, float speed, int yOffset = 0) {
	int index = (int)(playOnceClock.getElapsedTime().asSeconds() * speed);
	if (index >= frameCount) {
		index = frameCount - 1;
	}
	SetAnimationFrame(sprite, index, totalWidth, height, frameCount, yOffset);
}

void UpdateAnimationplatform(TemporaryPlatform& temporaryplatform) {
	float time_temp = 1.5f;
	int frameCount = 9;
	int width = 5508, height = 132;

	if (temporaryplatform.collided) {
		temporaryplatform.currentframe += (frameCount * dt) / time_temp;
	}
	else {
		temporaryplatform.currentframe -= (frameCount * dt) / time_temp;
	}
	temporaryplatform.currentframe = Clamp(temporaryplatform.currentframe, 0.0f, frameCount - 1);
	int displayframe = round(temporaryplatform.currentframe);

	SetAnimationFrame(temporaryplatform.displaySprite, displayframe, width, height, frameCount);
}

void UpdateAnimationDoor(FinalDoor& door) {
	float speed = 20.0f;
	int frameCount = 22;
	int width = 3586, height = 138;

	if (door.player_on_door)
	{
		door.currentFrame += speed * dt;
	}
	else
	{
		door.currentFrame -= speed * dt;
	}

	door.currentFrame = Clamp(door.currentFrame, 0.0f, frameCount - 1); // clamp the current frame to valid range
	int displayFrame = (int)(door.currentFrame);

	SetAnimationFrame(door.sprite, displayFrame, width, height, frameCount);
}

void UpdateAnimation(Sprite& sprite, LoadTexture texture) {
	float speed = 20.0f;

	switch (texture)
	{
	case PLAYER_FIRE:
	case TRIANGLE:
	case TRIANGLE_ROTATED:
	case FLAME_POND:
	case WATER_POND:
	case TOXIC_POND:
	case RECTANGLE:
		break;
	case GROUND:
		sprite.setTextureRect(IntRect(8 * 32, 0, 32, 32));
		break;
	case diamonds_texture:
	{
		// 1 fire , 2 hald fire half water, 3 white , 4 water
		UpdateLoopingAnimation(sprite, 468, 117, 4, speed);
		break;
	}

	// charachters animations
	case death_smoke_texture:
	{
		UpdatePlayOnceAnimation(sprite, 4590, 107, 45, 25.0f);
		break;
	}

	case fire_glow_texture:
	case water_glow_texture:
		break;

	case fire_head_jumping_texture:
	{
		UpdateLoopingAnimation(sprite, 1716, 130, 11, speed);
		break;
	}
	case fire_head_rising_texture:
	{
		UpdateLoopingAnimation(sprite, 530, 130, 5, speed);
		break;
	}
	case fire_head_falling_texture:
	{
		UpdateLoopingAnimation(sprite, 650, 162, 5, speed);
		break;
	}

	case water_head_jump_texture:
	{
		UpdateLoopingAnimation(sprite, 1914, 142, 11, speed);
		break;
	}
	case water_head_rising_texture:
	{
		UpdateLoopingAnimation(sprite, 1452, 143, 11, speed);
		break;
	}
	case water_head_falling_texture:
	{
		UpdateLoopingAnimation(sprite, 1430, 204, 11, speed);
		break;
	}

	case fire_ice_steps_texture:
	{
		UpdateLoopingAnimation(sprite, 216, 88, 3, speed);
		break;
	}
	case water_ice_steps_texture:
	{
		UpdateLoopingAnimation(sprite, 198, 110, 3, speed);
		break;
	}

	case fire_idle_body_texture:
	case water_body_idle_texture:
		break;

	case fire_idle_head_texture:
	{
		UpdateLoopingAnimation(sprite, 2470, 162, 19, speed);
		break;
	}
	case water_head_idle_texture:
	{
		UpdateLoopingAnimation(sprite, 3900, 162, 30, speed);
		break;
	}

	case fire_running_texture:
	{
		UpdateLoopingAnimation(sprite, 1040, 172, 8, speed);
		break;
	}
	case water_running_texture:
	{
		UpdateLoopingAnimation(sprite, 1040, 172, 8, speed);
		break;
	}

	case fire_stairs_texture:
	case water_stairs_texture:
	{
		UpdatePlayOnceAnimation(sprite, 2130, 103, 30, speed, 20);
		break;
	}

	// map objects animations

	case TEMPORARY_GROUND:
	{
		float speed_temp = 4.0f;
		UpdateLoopingAnimation(sprite, 5508, 132, 9, speed_temp);
		break;
	}
	case pusher_block_texture:
	{
		sprite.setTextureRect(IntRect(0, 0, 110, 86));
		break;
	}
	case pusher_block_light_texture:
	{
		sprite.setTextureRect(IntRect(0, 0, 64, 62));
		break;
	}
	case snow_flat_texture:
	{
		sprite.setTextureRect(IntRect(0, 0, 60, 60));
		break;
	}
	case snow_slope_left_side_down_texture:
	case snow_slope_right_side_down_texture:
	{
		sprite.setTextureRect(IntRect(0, 0, 50, 51));
		break;
	}
	case wind_base_texture:
	{
		UpdateLoopingAnimation(sprite, 472, 80, 4, speed);
		break;
	}
	case wind_effect_texture:
	{
		UpdateLoopingAnimation(sprite, 3840, 241, 30, speed);
		break;
	}
	case fire_door_open_texture:
	case water_door_open_texture:
	case fire_door_open_ice_texture:
	case water_door_open_ice_texture:
	{
		UpdateLoopingAnimation(sprite, 3586, 138, 22, speed);
		break;
	}
	case fire_pond_texture:
	{
		UpdateLoopingAnimation(sprite, 750, 50, 15, speed);
		break;
	}
	case fire_pond_right_texture:
	{
		UpdateLoopingAnimation(sprite, 750, 44, 15, speed);
		break;
	}
	case fire_pond_left_texture:
	{
		UpdateLoopingAnimation(sprite, 750, 42, 15, speed);
		break;
	}

	case water_pond_texture:
	case water_pond_right_texture:
	case water_pond_left_texture:
	{
		UpdateLoopingAnimation(sprite, 690, 47, 15, speed);
		break;
	}

	case green_pond_texture:
	{
		UpdateLoopingAnimation(sprite, 750, 50, 15, speed);
		break;
	}
	case green_pond_right_texture:
	{
		UpdateLoopingAnimation(sprite, 750, 43, 15, speed);
		break;
	}
	case green_pond_left_texture:
	{
		UpdateLoopingAnimation(sprite, 750, 42, 15, speed);
		break;
	}

	case lever_stick_texture:
		break;
	case moving_platform_texture:
		sprite.setTextureRect(IntRect(0, 0, 1032, 234));
		break;

	case ramp_1_texture:
	case slider_dot_texture:
		break;
	case lever_light_texture:
		sprite.setTextureRect(IntRect(0, 0, 106, 164));
		break;
	case BackButton0_texture:
		sprite.setTextureRect(IntRect(0, 0, 64, 109));
		break;
	case BackButtonFull0_texture:
		sprite.setTextureRect(IntRect(0, 0, 209, 89));
		break;
	case Diamond0_texture:
	case Diamond1_texture:
	case Diamond2_texture:
	case Diamond3_texture:
	case DiamondDark0_texture:
	case DiamondDark1_texture:
	case DiamondDark2_texture:
	case DiamondDark3_texture:
	case DiamondPuzzle0_texture:
	case DiamondPuzzle1_texture:
	case DiamondPuzzle2_texture:
	case DiamondPuzzle3_texture:
	case DiamondSpeed0_texture:
	case DiamondSpeed1_texture:
	case DiamondSpeed2_texture:
	case DiamondSpeed3_texture:
		break;
	case FxButton0_texture:
	case FxButton1_texture:
		sprite.setTextureRect(IntRect(0, 0, 98, 82));
		break;
	case GoldLock0_texture:
	case Lock0_texture:
		break;
	case MusicButton0_texture:
	case MusicButton1_texture:
	case MuteButton0_texture:
	case MuteButton1_texture:
		sprite.setTextureRect(IntRect(0, 0, 113, 109));
		break;
	case SettingsButton0_texture:
		sprite.setTextureRect(IntRect(0, 0, 102, 102));
		break;
	case loading_icon_texture:
		sprite.setTextureRect(IntRect(0, 0, 469, 103));
		break;
	case menu_box_texture:
		sprite.setTextureRect(IntRect(0, 0, 1082, 642));
		break;
	case pause_icon_texture:
		sprite.setTextureRect(IntRect(0, 0, 48, 48));
		break;
	case stone_button_0_texture:
		sprite.setTextureRect(IntRect(25, 0, 205, 117));
		break;
	case stone_button_1_texture:
		sprite.setTextureRect(IntRect(275, 0, 205, 117));
		break;
	case cursor_texture:
		sprite.setTextureRect(IntRect(0, 0, 300, 416));
		break;
	case pointer_texture:
		sprite.setTextureRect(IntRect(300, 0, 300, 416));
		break;
	case main_menu_background_texture:
		sprite.setTextureRect(IntRect(0, 0, 1536, 1024));
		break;
	case game_name_texture:
		sprite.setTextureRect(IntRect(0, 0, 860, 270));
		break;
	case clock_timer_texture:
		sprite.setTextureRect(IntRect(0, 0, 268, 100));
		break;
	case tick_icon_texture:
		sprite.setTextureRect(IntRect(0, 0, 69, 69));
		break;
	case rating_timer_texture:
		sprite.setTextureRect(IntRect(0, 0, 93, 73));
		break;
	case diamonds_green_idle_texture:
	case diamonds_orange_idle_texture:
	case diamonds_purple_idle_texture:
		sprite.setTextureRect(IntRect(0, 0, 128, 128));
		break;
	case dust_texture:
	{
		UpdateLoopingAnimation(sprite, 3240, 53, 60, 15.f);
		break;
	}
	case diamonds_green_texture:
	case diamonds_orange_texture:
	case diamonds_purple_texture:
	{
		UpdatePlayOnceAnimation(sprite, 1024, 128, 8, 30.f);
		break;
	}

	default:
		break;
	}
}

void UpdateTexturePlayer(Sprite& sprite, PlayerType type, PlayerState newState, bool Head = false) {

	if (!Head)
		switch (type)
		{
		case Fireboy:
			switch (newState)
			{
			case Walk:
				ApplyTexture(sprite, LoadTexture::fire_running_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			case Idle:
				ApplyTexture(sprite, LoadTexture::fire_idle_body_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			default:
				break;
			}
			break;
		case Watergirl:
			switch (newState)
			{
			case Walk:
				ApplyTexture(sprite, LoadTexture::water_running_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			case Idle:
				ApplyTexture(sprite, LoadTexture::water_body_idle_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

	else
		switch (type)
		{
		case Fireboy:
			switch (newState)
			{
			case Walk:
				ApplyTexture(sprite, LoadTexture::fire_head_jumping_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			case Jump_Rise:
				ApplyTexture(sprite, LoadTexture::fire_head_rising_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			case Fall:
				ApplyTexture(sprite, LoadTexture::fire_head_falling_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			case Idle:
				ApplyTexture(sprite, LoadTexture::fire_idle_head_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			default:
				break;
			}
			break;
		case Watergirl:
			switch (newState)
			{
			case Walk:
				ApplyTexture(sprite, LoadTexture::water_head_jump_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			case Jump_Rise:
				ApplyTexture(sprite, LoadTexture::water_head_rising_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			case Fall:
				ApplyTexture(sprite, LoadTexture::water_head_falling_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			case Idle:
				ApplyTexture(sprite, LoadTexture::water_head_idle_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), true, false);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

}

void UpdateAnimationPlayer(Sprite& sprite, PlayerType type, PlayerState state, bool Head = false)
{
	float speed = 25.0f;

	if (!Head) {
		if (state == Walk) {
			UpdateLoopingAnimation(sprite, 1040, 170, 8, speed);
		}
		else {
			SetAnimationFrame(sprite, 0, 1040, 170, 8);
		}
	}
	else {
		switch (type) {
		case Fireboy:
			switch (state)
			{
			case Walk: {
				UpdateLoopingAnimation(sprite, 1716, 130, 11, speed);
				break;
			}
			case Jump_Rise: {
				UpdateLoopingAnimation(sprite, 530, 130, 5, speed);
				break;
			}
			case Fall:
			{
				UpdateLoopingAnimation(sprite, 650, 162, 5, speed);
				break;
			}
			case Idle:
			{
				UpdateLoopingAnimation(sprite, 2470, 162, 19, speed);
				break;
			}
			default:
				break;
			}
			break;
		case Watergirl:
			switch (state)
			{
			case Walk: {
				UpdateLoopingAnimation(sprite, 1914, 142, 11, speed);
				break;
			}
			case Jump_Rise: {
				UpdateLoopingAnimation(sprite, 1452, 143, 11, speed);
				break;
			}
			case Fall:
			{
				UpdateLoopingAnimation(sprite, 1430, 204, 11, speed);
				break;
			}
			case Idle:
			{
				UpdateLoopingAnimation(sprite, 3900, 162, 30, speed);
				break;
			}
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	SetSpriteOriginToCenter(sprite);
}