
// Animations


// Settings :



// Structs and enums


// Runtime variables
// Ex: clocks and timers for animations



// Functions

void InitializeAnimations()
{
	// code for initializing menu variables and objects
	// for example initialize timers or counters
}


void HandleAnimationsInput(Event event)
{
	// if ever needed you can check for input events here

	switch (gameState)
	{
	case MAIN_MENU:
		// code for handling main menu input
		break;
	case SETTINGS:
		// code for handling settings menu input
		break;
	case GAME:
		// code for handling game UI input
		break;
	default:
		break;
	}
}

void UpdateAnimation(Sprite& sprite, LoadTexture texture) {
	float speed = 10.0f;
	int frameCount = 6;
	int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;

	switch (texture)
	{
	case PLAYER_FIRE:
		break;
	case TRIANGLE:
		break;
	case TRIANGLE_ROTATED:
		break;
	case FLAME_POND:
		break;
	case WATER_POND:
		break;
	case TOXIC_POND:
		break;
	case RECTANGLE:
		break;
	case GROUND:
		sprite.setTextureRect(IntRect(index * 32, 0, 32, 32));
		break;
	case death_smoke_texture:
		break;
	case diamondsh_texture:
		break;
	case fire_glow_texture:
		break;
	case fire_head_jumping_texture:
		break;
	case fire_head_rising_texture:
		break;
	case fire_ice_steps_texture:
		break;
	case fire_idle_body_texture:
		break;
	case fire_idle_head_texture:
		break;
	case fire_running_texture:
		break;
	case fire_stairs_texture:
		break;
	case fire_head_falling_texture:
		break;
	case water_body_idle_texture:
		break;
	case water_glow_texture:
		break;
	case water_head_falling_texture:
		break;
	case water_head_idle_texture:
		break;
	case water_head_jump_texture:
		break;
	case water_head_rising_texture:
		break;
	case water_ice_steps_texture:
		break;
	case water_running_texture:
		break;
	case water_stairs_texture:
		break;
	case movingbox_texture:
		break;
	case snow_flat_texture:
		break;
	case snow_slope_right_side_down_texture:
		break;
	case snow_slope_left_side_down_texture:
		break;
	case pusher_block_texture:
		break;
	case fire_door_open_texture:
		break;
	case water_door_open_texture:
		break;
	case fire_pond_texture:
		break;
	case fire_pond_right_texture:
		break;
	case fire_pond_left_texture:
		break;
	case lever_stick_texture:
		break;
	case bar_texture:
		break;
	case bar_cap_right_texture:
		break;
	case bar_cap_left_texture:
		break;
	case ramp_1_texture:
		break;
	case water_pond_right_texture:
		break;
	case water_pond_texture:
		break;
	case water_pond_left_texture:
		break;
	case slider_dot_texture:
		break;
	case slider_light_on_texture:
		break;
	case BackButton0_texture:
		break;
	case BackButtonFull0_texture:
		break;
	case Diamond0_texture:
		break;
	case Diamond1_texture:
		break;
	case Diamond2_texture:
		break;
	case Diamond3_texture:
		break;
	case DiamondDark0_texture:
		break;
	case DiamondDark1_texture:
		break;
	case DiamondDark2_texture:
		break;
	case DiamondDark3_texture:
		break;
	case DiamondPuzzle0_texture:
		break;
	case DiamondPuzzle1_texture:
		break;
	case DiamondPuzzle2_texture:
		break;
	case DiamondPuzzle3_texture:
		break;
	case DiamondSpeed0_texture:
		break;
	case DiamondSpeed1_texture:
		break;
	case DiamondSpeed2_texture:
		break;
	case DiamondSpeed3_texture:
		break;
	case FxButton0_texture:
		break;
	case FxButton1_texture:
		break;
	case GoldLock0_texture:
		break;
	case Lock0_texture:
		break;
	case MusicButton0_texture:
		break;
	case MusicButton1_texture:
		break;
	case MuteButton0_texture:
		break;
	case MuteButton1_texture:
		break;
	case SettingsButton0_texture:
		break;
	case sound_icon_texture:
		break;
	default:
		break;
	}
}

void UpdatePlayerTexture(Sprite& sprite, Player::PlayerType type, Player::PlayerState newState, Vector2f size, bool Head = false) {

	if (!Head)
	switch (type)
	{
	case Player::Fireboy:
			switch (newState)
			{
			case Player::Walk:
				ApplyTexture(sprite, LoadTexture::water_body_idle_texture, size);
				break;
			case Player::Idle:
				// Update idle animation
				break;
			default:
				break;
			}
		break;
		case Player::Watergirl:
			switch (newState)
			{
			case Player::Walk:
				ApplyTexture(sprite, LoadTexture::water_body_idle_texture, size);
			case Player::Idle:
				// Update idle animation
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
		case Player::Fireboy:
			switch (newState)
			{
			case Player::Walk:
				ApplyTexture(sprite, LoadTexture::water_body_idle_texture, size);
				break;
			case Player::Jump_Rise:
				// Update jump rise animation
				break;
			case Player::Fall:
				// Update fall animation
				break;
			case Player::Idle:
				// Update idle animation
				break;
			default:
				break;
			}
			break;
		case Player::Watergirl:
			switch (newState)
			{
			case Player::Walk:
				ApplyTexture(sprite, LoadTexture::water_body_idle_texture, size);
				break;
			case Player::Jump_Rise:
				// Update jump rise animation
				break;
			case Player::Fall:
				// Update fall animation
				break;
			case Player::Idle:
				// Update idle animation
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

}

void UpdateAnimationPlayer(Sprite& sprite, Player::PlayerState state, bool Head = false)
{
	float speed = 10.0f;
	int frameCount = 6;
	int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;

	switch (state)
	{
	case Player::Walk:
		sprite.setTextureRect(IntRect(index * 32, 0, 32, 32));
		break;
	case Player::Jump_Rise:
		// Update jump rise animation
		break;
	case Player::Fall:
		// Update fall animation
		break;
	case Player::Idle:
		// Update idle animation
		break;
	default:
		break;
	}
}