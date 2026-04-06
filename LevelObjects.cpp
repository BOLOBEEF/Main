
// STRUCTS for level objects
struct Player
{
	enum PlayerType { Fireboy, Watergirl };
	PlayerType playertype;
	RectangleShape sprite = RectangleShape(Vector2f(100, 100));
	Vector2f velocity = { 0,0 };

	const float speed = 100.0f;
	const float gravity = 200.0f;
	const float jump = -100.0f;


	void checkJump(Event event) {
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

	Player(PlayerType charctertype) {
		charctertype = Fireboy;
		playertype = charctertype;
		sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
		sprite.setPosition(center.x, center.y - 200);
	}

	void UpdateMotion() {
		if (playertype == Fireboy) {
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
		else if (playertype == Watergirl) {
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				velocity.x = speed;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A)) {
				velocity.x = -speed;
			}
			else velocity.x = 0;
			velocity.y += gravity * dt;

			sprite.move(velocity * dt);

		}
	}
};