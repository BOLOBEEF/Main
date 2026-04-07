
// STRUCTS for level objects

//struct for the player
struct Player
{
	RectangleShape sprite = RectangleShape(Vector2f(100, 100));
	Vector2f velocity = { 0,0 };
	const float speed = 100.0f;
	const float gravity = 200.0f;
	Player() {

		sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
		sprite.setPosition(center.x, center.y - 200);
	}

	void UpdateMotion() {

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			velocity.x = speed;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			velocity.x = -speed;
		}
		else velocity.x = 0;
		velocity.y += gravity * dt;

		sprite.move(velocity * dt);

	}
};

//struct for ponds
struct Ponds
{
	RectangleShape ponds_sprite = RectangleShape(Vector2f(150, 100));
	Ponds() {
		ponds_sprite.setOrigin(ponds_sprite.getLocalBounds().width / 2.0f, ponds_sprite.getLocalBounds().height / 2.0f);
		ponds_sprite.setPosition(center.x+200, center.y + 200);
	}
	void PondsEffect(Player& player,Which_player who,pond_state pond) {
		// 
		switch (pond)
		{
			case POISON_POND:
				//statment
				switch (who)
				{
				case FIRE_PLAYER:
					
					break;
				case WATER_PLAYER:

					break;
				}
				break;
			case FIRE_POND:
				//statment
				switch (who)
				{
				case FIRE_PLAYER:

					break;
				case WATER_PLAYER:

					break;
				}
				break;
			case WATER_POND:
				//statment
				switch (who)
				{
				case FIRE_PLAYER:

					break;
				case WATER_PLAYER:

					break;
				}
				break;
		}
	}
};