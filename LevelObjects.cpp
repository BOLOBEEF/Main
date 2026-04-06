
// STRUCTS for level objects
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