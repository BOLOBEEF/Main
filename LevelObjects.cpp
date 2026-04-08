
// STRUCTS for level objects
struct Player
{
	enum PlayerType { Fireboy, Watergirl };
	PlayerType playertype;
	RectangleShape sprite = RectangleShape(Vector2f(60, 100));
	Vector2f velocity = { 0,0 };

	const float accelration = 500.0f;
	const float deccelration = 10.0f;
	const float speed = 500.0f;
	const float gravity = 1000.0f;
	const float jump = -500.0f;
	bool isOnGround = false;
	bool Player_dead = false;



	Player(PlayerType charctertype, Vector2f startPosition) {
		playertype = charctertype;
		sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
		sprite.setPosition(startPosition);
	}

	void UpdateMotion() {
		if (playertype == Fireboy) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				velocity.x += accelration*dt;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				velocity.x -= accelration * dt;
			}
			else velocity.x -= velocity.x * deccelration * dt;
			velocity.y += gravity * dt;

			sprite.move(velocity * dt);

		}
		else if (playertype == Watergirl) {
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				velocity.x +=accelration* dt;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A)) {
				velocity.x += -accelration * dt;
			}
			else velocity.x -= velocity.x * deccelration * dt;
			velocity.y += gravity * dt;

			sprite.move(velocity * dt);

		}
	}

	void checkJump(Event event) {
		if (!isOnGround) return;

		if (event.type == Event::KeyPressed) {
			if (playertype == Fireboy) {
				if (event.key.code == Keyboard::Up) {
					velocity.y = jump;

				}
			}
			else if (playertype == Watergirl) {
				if (event.key.code == Keyboard::W) {
					velocity.y = jump;

				}
			}
		}
	}
};
struct Ponds
{
	RectangleShape ponds_sprite = RectangleShape(Vector2f(150, 100));
	Ponds() {
		ponds_sprite.setOrigin(ponds_sprite.getLocalBounds().width / 2.0f, ponds_sprite.getLocalBounds().height / 2.0f);
		ponds_sprite.setPosition(center.x + 200, center.y + 200);
	}
	void PondsEffect(Player& player, ponds_type pond) {
		// 
		switch (pond)
		{
		case POISON_POND:
			//statment
			switch (player.playertype)
			{
			case player.Fireboy:

			case player.Watergirl:
				fireBoy.Player_dead= true;
				waterGirl.Player_dead = true;
				break;
			}
			break;
		case FIRE_POND:
			//statment
			switch (player.playertype)
			{
			case player.Watergirl:
				waterGirl.Player_dead = true;

				break;
			}
			break;
		case WATER_SURFACE:
			//statment
			switch (player.playertype)
			{
			case player.Fireboy:
				fireBoy.Player_dead = true;

				break;
			}
			break;
		}
	}
};