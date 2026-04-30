
// Animations


// Settings :



// Structs and enums


// Runtime variables
// Ex: clocks and timers for animations



// Functions
Clock animClock1;
void InitializeOneTimeAnimations()
{
	animClock1.restart(); // so that the animation will start from the beginning when we open the win menu, and not from the middle if we win multiple times in a row without closing the game
}

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

void DoorUpdateAnimation(FinalDoor& door) {
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

		door.sprite.setTextureRect(IntRect(displayFrame * (width / frameCount), 0, (width / frameCount), height));
}

void UpdateAnimation(Sprite& sprite, LoadTexture texture) {
	float speed = 20.0f;

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
		sprite.setTextureRect(IntRect(8 * 32, 0, 32, 32));
		break;
	case diamonds_texture:
	{
		int frameCount = 4;// 1 fire , 2 hald fire half water, 3 white , 4 water
		int width =468, height = 117;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}

	// char animations
	case death_smoke_texture: {

		int frameCount = 45;
		int width = 4590, height = 107;
		int frameWidth = width / frameCount;

		float speed = 15.0f;

		float time = animClock1.getElapsedTime().asSeconds();
		int index = (int)(time * speed);

		if (index >= frameCount) {
			index = frameCount ;

		}

		sprite.setTextureRect(sf::IntRect(index * frameWidth, 0, frameWidth, height));
		break;
	}

	case fire_glow_texture:
		break;
	case water_glow_texture:
		break;

	case fire_head_jumping_texture:
	{
		int frameCount = 11;
		int width = 1716, height = 130;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case fire_head_rising_texture:
	{
		int frameCount = 5;
		int width = 530, height = 130;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width/frameCount), 0, (width / frameCount), height));
		break;
	}
	case fire_head_falling_texture:
	{
		int frameCount = 5;
		int width =650, height = 162;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}

	case water_head_jump_texture:
	{
		int frameCount = 11;
		int width = 1914, height =142 ;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case water_head_rising_texture:
	{
		int frameCount = 11;
		int width =1452, height = 143;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case water_head_falling_texture:
	{
		int frameCount = 11;
		int width = 1430, height = 204;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}




	case fire_ice_steps_texture:
		{
		int frameCount = 3;
		int width = 216, height = 88;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case water_ice_steps_texture:
	{
		int frameCount = 3;
		int width =198, height = 110;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}


	case fire_idle_body_texture:
		break;
	case water_body_idle_texture:
		break;

	case fire_idle_head_texture:
	{
		int frameCount = 19;
		int width = 2470, height = 162;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case water_head_idle_texture:
	{
		int frameCount = 30;
		int width = 3900, height = 162;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}


	case fire_running_texture: {
		int frameCount = 8;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * 130, 0, 130, 172));
		break;
	}
	case water_running_texture:
	{
		int frameCount = 8;
		int width =1040, height = 172;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}

	case fire_stairs_texture:
	{
		int frameCount = 30;
		int width =2130, height = 103;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) ;
		if (index >= frameCount) {
			index = frameCount;


		}
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case water_stairs_texture:
	{
		int frameCount = 30;
		int width =2100, height = 103;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) ;
		if (index >= frameCount) {
			index = frameCount;


		}
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	

	// map objects animations

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
	{
		sprite.setTextureRect(IntRect(0, 0, 50, 51));
		break;
	}
	case snow_slope_right_side_down_texture:
	{
		sprite.setTextureRect(IntRect(0, 0, 50, 51));
		break;
	}
	case wind_base_texture:
	{
		int frameCount = 4;
		int width = 472, height = 80;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index* (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case wind_effect_texture:
	{
		int frameCount = 30;
		int width = 3840, height = 241;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case fire_door_open_texture:
	{
		int frameCount = 22;
		int width =3586, height = 138;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}
	case water_door_open_texture:
	{
		int frameCount = 22;
		int width =3586, height = 138;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;
	}

	case fire_pond_texture: {
		int frameCount = 15;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * 50, 0, 50, 50));
	}
	case fire_pond_right_texture: {
		int frameCount = 15;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * 50, 0, 50, 44));
		break;
	}
	case fire_pond_left_texture:
	{
		int frameCount = 15;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * 50, 0, 50, 42));
		break;
	}

	case water_pond_texture:
	{
		int frameCount = 15;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * 46, 0, 46, 47));
		break;
	}
	case water_pond_right_texture:
	{
		int frameCount = 15;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * 46, 0, 46, 47));
		break;
	}
	case water_pond_left_texture:
	{
		int frameCount = 15;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * 46, 0, 46, 47));
		break;
	}

	case green_pond_texture:
	{
		
			int frameCount = 15;
			int width =750, height =50 ;
			int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
			sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
			break;
		
	}
	case green_pond_right_texture:
	{

		int frameCount = 15;
		int width = 750, height = 43;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;

	}
	case green_pond_left_texture:
	{

		int frameCount = 15;
		int width = 750, height = 42;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;

	}


	case lever_stick_texture:
		break;
	case moving_platform_texture:
		sprite.setTextureRect(IntRect(0, 0, 1032, 234));
		break;
	
	case ramp_1_texture:
		break;
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
		sprite.setTextureRect(IntRect(0, 0, 98, 82));
		break;
	case FxButton1_texture:
		sprite.setTextureRect(IntRect(0, 0, 98, 82));
		break;
	case GoldLock0_texture:
		break;
	case Lock0_texture:
		break;
	case MusicButton0_texture:
		sprite.setTextureRect(IntRect(0, 0, 113, 109));
		break;
	case MusicButton1_texture:
		sprite.setTextureRect(IntRect(0, 0, 113, 109));
		break;
	case MuteButton0_texture:
		sprite.setTextureRect(IntRect(0, 0, 113, 109));
		break;
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
		sprite.setTextureRect(IntRect(0, 0,1536, 1024));
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
		sprite.setTextureRect(IntRect(0, 0, 128, 128));
		break;
	case diamonds_orange_idle_texture:
		sprite.setTextureRect(IntRect(0, 0, 128, 128));
		break;
	case diamonds_purple_idle_texture:
		sprite.setTextureRect(IntRect(0, 0, 128, 128));
		break;
	case dust_texture:
	{
		int speed = 15.f;
		int frameCount = 60;
		int width = 3240, height = 53;
		int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
		sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
		break;

	}
	case diamonds_green_texture: {
		int frameCount = 8;
		int width = 1024, height = 128;
		int frameWidth = width / frameCount;
		
		float speed = 30.f;

		int index = (int)(animClock1.getElapsedTime().asSeconds() * speed);

		if (index >= frameCount) {
			index = frameCount - 1;
		
		}

		sprite.setTextureRect(sf::IntRect(index * frameWidth, 0, frameWidth, height));
		break;
	}
	case diamonds_orange_texture: {
		int frameCount = 8;
		int width = 1024, height = 128;
		int frameWidth = width / frameCount;

		
		float speed = 30.f;

		int index = (int)(animClock1.getElapsedTime().asSeconds() * speed);

		if (index >= frameCount) {
			index = frameCount - 1;

		}

		sprite.setTextureRect(sf::IntRect(index * frameWidth, 0, frameWidth, height));
		break;
	}
	case diamonds_purple_texture: {
		int frameCount = 8;
		int width = 1024, height = 128;
		int frameWidth = width / frameCount;

	    
		float speed = 30.f;

		int index = (int)(animClock1.getElapsedTime().asSeconds() * speed) ;

		if (index >= frameCount) {
			index = frameCount - 1;

		}

		sprite.setTextureRect(sf::IntRect(index * frameWidth, 0, frameWidth, height));
		break;
	}
	
	default:
		break;
	}
}

void UpdatePlayerTexture(Sprite& sprite, PlayerType type, PlayerState newState, bool Head = false) {

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

void UpdateAnimationPlayer(Sprite& sprite, PlayerType type,PlayerState state, bool Head = false)
{
	float speed = 25.0f;
	float width = 10, height = 0;

	if (!Head) {
		
		
		
		if (state == Walk) {
			int frameCount = 8;
			int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
			float width = 1040, height = 170;
		      
			sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width/frameCount), height));
		}
		else {
			int framecount = 8;
			float width = 1040, height = 170;
			sprite.setTextureRect(IntRect(0, 0, (width/framecount), height));
		}
	}
	else {
		switch (type) {
		case Fireboy:
			switch (state)
			{
			case Walk: {
				int frameCount = 11;
				int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
				float width = 1716, height = 130;

				sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
				break;
			}
			case Jump_Rise:{
				int frameCount = 5;
				int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
				float width = 530, height = 130;

				sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
				break;
			}
			case Fall:
			{
				int frameCount = 5;
				int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
				float width = 650, height = 162;

				sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
				break;
			}
			case Idle:
			{
				int frameCount = 19;
				int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
				float width = 2470, height = 162;

				sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
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
				int frameCount = 11;
				int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
				float width = 1914, height = 142;

				sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
				break;
			}
			case Jump_Rise: {
				int frameCount = 11;
				int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
				float width = 1452, height = 143;

				sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
				break;
			}
			case Fall:
			{
				int frameCount = 11;
				int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
				float width = 1430, height = 204;

				sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
				break;
			}
			case Idle:
			{
				int frameCount = 30;
				int index = (int)(globalClock.getElapsedTime().asSeconds() * speed) % frameCount;
				float width = 3900, height = 162;

				sprite.setTextureRect(IntRect(index * (width / frameCount), 0, (width / frameCount), height));
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