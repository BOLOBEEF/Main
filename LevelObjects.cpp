
// STRUCTS for level objects
void AllignSprite(Sprite& sprite, Vector2f defaultSize = Vector2f(32, 32)) {
	FloatRect bounds = sprite.getGlobalBounds();
	Vector2f position = Vector2f(bounds.left, bounds.top);
	position.x = round(position.x / defaultSize.x) * defaultSize.x;
	position.y = round(position.y / defaultSize.y) * defaultSize.y;

	sprite.setPosition(position + Vector2f(bounds.width / 2.0f, bounds.height / 2.0f));
}

struct Player
{
	enum PlayerType { Fireboy, Watergirl };
	PlayerType playertype;
	const int idleRange_x = 10;
	const int idleRange_y = 10;

	// Body:
	// Idle, walk if moving left or right
	// Head:
	// Right, Left, Idle, headRising, headMid = Idle, headFalling

	enum PlayerState { Walk, Jump_Rise, Fall, Idle };
	PlayerState playerState = Idle;
	PlayerState lastState = Idle;
	bool justUpdatedPlayerState = false;

	Sprite sprite;
	void start() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(50, 60));
		if (playertype == Fireboy)
			sprite.setColor(Color::Red);
		else sprite.setColor(Color::Blue);
	}

	Vector2f velocity = { 0,0 };

	const float accelration = 100.0f;
	const float deccelration = 5.0f;
	const float speed = 150.0f;
	const float slopeSpeed = speed * 0.707f;
	const float pushSpeed = slopeSpeed;
	const float gravity = 250.0f;
	const float jump = -250.0f;

	float currentSpeed = speed;
	bool isOnGround = false;
	bool isOnSlope = false;
	bool isPushing = false;
	bool isDead = false;



	Player(PlayerType charctertype, Vector2f startPosition) {
		playertype = charctertype;
		sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
		sprite.setPosition(startPosition);
	}

	void UpdateMotion() {
		if (playertype == Fireboy) {
			
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				velocity.x += accelration * dt;
				//PlayGameSoundEffect(GameSoundEffect::Walking_boy_sound);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				velocity.x -= accelration * dt;
				//PlayGameSoundEffect(GameSoundEffect::Walking_boy_sound);
			}
			else velocity.x -= velocity.x * deccelration * dt;
		}
		else if (playertype == Watergirl) {
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				velocity.x += accelration * dt;
				//PlayGameSoundEffect(GameSoundEffect::Walking_girl_sound);
			}
			else if (Keyboard::isKeyPressed(Keyboard::A)) {
				velocity.x -= accelration * dt;
				//PlayGameSoundEffect(GameSoundEffect::Walking_girl_sound);
			}
			else velocity.x -= velocity.x * deccelration * dt;
		}


		lastState = playerState;

		if (velocity.x > idleRange_x || velocity.x < -idleRange_x) {
			playerState = Walk;
		}
		else if (velocity.y > idleRange_y)playerState = Fall;
		else if (velocity.y < -idleRange_y)playerState = Jump_Rise;
		else playerState = Idle;

		if (lastState != playerState) justUpdatedPlayerState = true;
		else justUpdatedPlayerState = false;


		velocity.y += gravity * dt;

		if (isOnSlope) currentSpeed = slopeSpeed;
		else if (isPushing) currentSpeed = pushSpeed;
		else currentSpeed = speed;

		velocity.x = Clamp(velocity.x, -currentSpeed, currentSpeed);

		sprite.move(velocity * dt);

		isOnGround = false;
		isOnSlope = false;
		isPushing = false;
	}

	void checkJump(Event event) {
		if (!isOnGround) return;

		if (event.type == Event::KeyPressed) {
			if (playertype == Fireboy) {
				if (event.key.code == Keyboard::Up) {
					velocity.y = jump;
					PlayGameSoundEffect(GameSoundEffect::BoyJump_sound);
				}
			}
			else if (playertype == Watergirl) {
				if (event.key.code == Keyboard::W) {
					velocity.y = jump;
					PlayGameSoundEffect(GameSoundEffect::GirlJump_sound);
				}
			}
		}
	}
};

struct Collider
{
	enum ColliderType {
		Rectangle,
		Triangle,
		Triangle_Rotated
	};

	Sprite sprite;
	ColliderType type;

	Vector2f defaultSize = Vector2f(32, 32);
	float groundedDistance = 20.0f;
	Vector2f startPosition;
	Vector2f scale;
	float moveRatio = 0.0f; // a value from zero to one to determine who gets pushedand how much (player pushing box)

	struct CollisionData
	{
		// the collision direction relative to the collider not the player
		enum CollisionDirection {
			None,
			Top,
			Bottom,
			Left,
			Right,
			Slope
		};
		CollisionDirection collisionDirection = CollisionData::None;

		float overlapDistance = 0.0f;
	};


	bool IsPointInsideTriangle(Vector2f point, Vector2f trianglePoints[3]) {
		bool isPositive = Cross(point - trianglePoints[1], trianglePoints[1] - trianglePoints[0]) > 0;
		if (Cross(point - trianglePoints[2], trianglePoints[2] - trianglePoints[1]) > 0 != isPositive) return false;
		if (Cross(point - trianglePoints[0], trianglePoints[0] - trianglePoints[2]) > 0 != isPositive) return false;

		return true;
	}

	Collider::CollisionData CheckRectangleCollision(Player& player, FloatRect otherBounds, bool resolveCollision = true, FloatRect bias = FloatRect(5.0f, 5.0f, 0.0f, 0.0f)) {
		Sprite& playerSprite = player.sprite;
		Collider::CollisionData collisionData;

		FloatRect playerBounds = playerSprite.getGlobalBounds();

		if (playerBounds.intersects(otherBounds)) {

			float topOverlap = abs(otherBounds.top - (playerBounds.top + playerBounds.height));
			float bottomOverlap = abs((otherBounds.top + otherBounds.height) - playerBounds.top);
			float leftOverlap = abs(otherBounds.left - (playerBounds.left + playerBounds.width));
			float rightOverlap = abs((otherBounds.left + otherBounds.width) - playerBounds.left);

			// on comparing overlap, slightly prefer top and bottom overlaps, to avoid getting stuck on edges
			float comparedTopOverlap = topOverlap - bias.left;
			float comparedBottomOverlap = bottomOverlap - bias.top;
			float comparedLeftOverlap = leftOverlap - bias.width;
			float comparedRightOverlap = rightOverlap - bias.height;


			if (comparedTopOverlap < comparedBottomOverlap && comparedTopOverlap < comparedLeftOverlap && comparedTopOverlap < comparedRightOverlap) {
				// Collision from the top
				if (resolveCollision)
				{
					playerSprite.move(0, -topOverlap * (1 - moveRatio));
					if (moveRatio != 0.0f)	sprite.move(0, topOverlap * moveRatio);
					else player.velocity.y = min(player.velocity.y, 1.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Top , topOverlap };

			}
			else if (comparedBottomOverlap < comparedTopOverlap && comparedBottomOverlap < comparedLeftOverlap && comparedBottomOverlap < comparedRightOverlap) {
				// Collision from the bottom
				if (resolveCollision)
				{
					playerSprite.move(0, bottomOverlap * (1 - moveRatio));
					if (moveRatio != 0.0f)	sprite.move(0, -bottomOverlap * moveRatio);
					else player.velocity.y = max(player.velocity.y, 0.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Bottom , bottomOverlap };
			}
			else if (comparedLeftOverlap < comparedRightOverlap && comparedLeftOverlap < comparedTopOverlap && comparedLeftOverlap < comparedBottomOverlap) {
				// Collision from the left
				if (resolveCollision)
				{
					playerSprite.move(-leftOverlap * (1 - moveRatio), 0);
					if (moveRatio != 0.0f)	sprite.move(leftOverlap * moveRatio, 0);
					else player.velocity.x = min(player.velocity.x, 0.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Left , leftOverlap };
			}
			else {
				// Collision from the right
				if (resolveCollision)
				{
					playerSprite.move(rightOverlap * (1 - moveRatio), 0);
					if (moveRatio != 0.0f)	sprite.move(-rightOverlap * moveRatio, 0);
					else player.velocity.x = max(player.velocity.x, 0.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Right , rightOverlap };
			}
		}

		return collisionData;
	}

	Collider::CollisionData CheckRectangleCollision(FloatRect checkBounds, FloatRect otherBounds) {
		Collider::CollisionData collisionData;

		FloatRect playerBounds = checkBounds;

		if (playerBounds.intersects(otherBounds)) {

			float topOverlap = abs(otherBounds.top - (playerBounds.top + playerBounds.height));
			float bottomOverlap = abs((otherBounds.top + otherBounds.height) - playerBounds.top);
			float leftOverlap = abs(otherBounds.left - (playerBounds.left + playerBounds.width));
			float rightOverlap = abs((otherBounds.left + otherBounds.width) - playerBounds.left);

			// on comparing overlap, slightly prefer top and bottom overlaps, to avoid getting stuck on edges
			float comparedTopOverlap = topOverlap - 5;
			float comparedBottomOverlap = bottomOverlap - 5;


			if (comparedTopOverlap < comparedBottomOverlap && comparedTopOverlap < leftOverlap && comparedTopOverlap < rightOverlap) {
				collisionData = { Collider::CollisionData::CollisionDirection::Top , topOverlap };
			}
			else if (comparedBottomOverlap < comparedTopOverlap && comparedBottomOverlap < leftOverlap && comparedBottomOverlap < rightOverlap) {
				collisionData = { Collider::CollisionData::CollisionDirection::Bottom , bottomOverlap };
			}
			else if (leftOverlap < rightOverlap && leftOverlap < comparedTopOverlap && leftOverlap < comparedBottomOverlap) {
				collisionData = { Collider::CollisionData::CollisionDirection::Left , leftOverlap };
			}
			else {
				collisionData = { Collider::CollisionData::CollisionDirection::Right , rightOverlap };
			}
		}

		return collisionData;
	}
	Collider::CollisionData CheckRectangleCollision(Sprite& other, FloatRect otherBounds) {
		Collider::CollisionData collisionData = CheckRectangleCollision(other.getGlobalBounds(), otherBounds);

		if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top) {
			other.move(0, -collisionData.overlapDistance);
		}
		else if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom) {
			other.move(0, collisionData.overlapDistance);
		}
		else if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left) {
			other.move(-collisionData.overlapDistance, 0);
		}
		else if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right) {
			other.move(collisionData.overlapDistance, 0);
		}

		return collisionData;
	}

	Collider::CollisionData CheckTriangleCollision(Player& player, FloatRect triangleBounds, bool rotated, bool resolveCollision = true) {

		FloatRect playerBounds = player.sprite.getGlobalBounds();

		bool collided = false;

		if (playerBounds.intersects(triangleBounds)) {
			Vector2f usedTrianglePoints[3];

			if (!rotated) {
				usedTrianglePoints[0] = Vector2f(triangleBounds.left, triangleBounds.top);
				usedTrianglePoints[1] = Vector2f(triangleBounds.left, triangleBounds.top + triangleBounds.height);
				usedTrianglePoints[2] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top + triangleBounds.height);
			}
			else {
				usedTrianglePoints[0] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top);
				usedTrianglePoints[1] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top + triangleBounds.height);
				usedTrianglePoints[2] = Vector2f(triangleBounds.left, triangleBounds.top + triangleBounds.height);
			}



			Vector2f playerDownLeftPoint = Vector2f(playerBounds.left, playerBounds.top + playerBounds.height);
			Vector2f playerDownRightPoint = Vector2f(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height);


			Collider::CollisionData boxCollisionData = CheckRectangleCollision(player, triangleBounds, false, (!rotated ? FloatRect(5.0f, 0.0f, 5.0f, 0.0f) : FloatRect(5.0f, 0.0f, 0.0f, 5.0f)));

			if (!rotated) {
				if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom)
				{
					if (!resolveCollision)
						return boxCollisionData;

					player.sprite.move(0, boxCollisionData.overlapDistance);
					player.velocity.y = max(player.velocity.y, 0.0f);
					return boxCollisionData;
				}
				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left)
				{
					if (!resolveCollision)
						return boxCollisionData;

					player.sprite.move(-boxCollisionData.overlapDistance, 0);
					player.velocity.x = min(player.velocity.x, 0.0f);
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
				{
					if (!resolveCollision)
						return boxCollisionData;

					player.sprite.move(0, -boxCollisionData.overlapDistance);
					player.velocity.y = min(player.velocity.y, 1.0f);
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right && playerBounds.contains(usedTrianglePoints[2]))
				{
					// Compare the overlap distance with the distance to move out of the triangle upwards, and move according to the smaller one
					float triangleHeight = triangleBounds.height;
					float triangleWidth = triangleBounds.width;
					float newWidth = abs(playerDownLeftPoint.x - usedTrianglePoints[2].x);
					float newHeight = newWidth * triangleHeight / triangleWidth;

					// move up a distance till the point is no longer inside the triangle
					float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));

					if (boxCollisionData.overlapDistance < abs(heightOverlap) - 2) {
						if (!resolveCollision)
							return boxCollisionData;

						player.sprite.move(boxCollisionData.overlapDistance, 0);
						player.velocity.x = max(player.velocity.x, 0.0f);
						return boxCollisionData;
					}
					else
					{
						if (!resolveCollision)
							return { Collider::CollisionData::Slope, abs(heightOverlap) };

						player.sprite.move(0, -abs(heightOverlap));
						player.velocity.y = min(player.velocity.y, 1.0f);
						return { Collider::CollisionData::Slope, abs(heightOverlap) };
					}
				}
				else if (IsPointInsideTriangle(playerDownLeftPoint + Vector2f(0, -1), usedTrianglePoints))
				{
					if (!resolveCollision)
						return { Collider::CollisionData::Slope, 0 };

					float triangleHeight = triangleBounds.height;
					float triangleWidth = triangleBounds.width;
					float newWidth = abs(playerDownLeftPoint.x - usedTrianglePoints[2].x);
					float newHeight = newWidth * triangleHeight / triangleWidth;

					// move up a distance till the point is no longer inside the triangle
					float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));
					player.sprite.move(0, -abs(heightOverlap) + 1);
					player.velocity.y = min(player.velocity.y, 1.0f);
					return { Collider::CollisionData::Slope, abs(heightOverlap) };
				}
			}
			else {
				if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom)
				{
					if (!resolveCollision)
						return boxCollisionData;

					player.sprite.move(0, boxCollisionData.overlapDistance);
					player.velocity.y = max(player.velocity.y, 0.0f);
					return boxCollisionData;
				}
				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right)
				{
					if (!resolveCollision)
						return boxCollisionData;

					player.sprite.move(boxCollisionData.overlapDistance, 0);
					player.velocity.x = max(player.velocity.x, 0.0f);
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
				{
					if (!resolveCollision)
						return boxCollisionData;

					player.sprite.move(0, -boxCollisionData.overlapDistance);
					player.velocity.y = min(player.velocity.y, 1.0f);
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left && playerBounds.contains(usedTrianglePoints[2]))
				{
					float triangleHeight = triangleBounds.height;
					float triangleWidth = triangleBounds.width;
					float newWidth = abs(playerDownRightPoint.x - usedTrianglePoints[2].x);
					float newHeight = newWidth * triangleHeight / triangleWidth;

					// move up a distance till the point is no longer inside the triangle
					float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));

					if (boxCollisionData.overlapDistance < abs(heightOverlap) - 2) {
						if (!resolveCollision)
							return boxCollisionData;

						player.sprite.move(-boxCollisionData.overlapDistance, 0);
						player.velocity.x = min(player.velocity.x, 0.0f);
						return boxCollisionData;
					}
					else
					{
						if (!resolveCollision)
							return { Collider::CollisionData::Slope, abs(heightOverlap) };

						player.sprite.move(0, -abs(heightOverlap));
						player.velocity.y = min(player.velocity.y, 1.0f);
						return { Collider::CollisionData::Slope, abs(heightOverlap) };
					}
				}
				else if (IsPointInsideTriangle(playerDownRightPoint + Vector2f(0, -1), usedTrianglePoints))
				{
					if (!resolveCollision)
						return { Collider::CollisionData::Slope, 0 };

					float triangleHeight = triangleBounds.height;
					float triangleWidth = triangleBounds.width;
					float newWidth = abs(playerDownRightPoint.x - usedTrianglePoints[2].x);
					float newHeight = newWidth * triangleHeight / triangleWidth;

					// move up a distance till the point is no longer inside the triangle
					float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));
					player.sprite.move(0, -abs(heightOverlap) + 1);
					player.velocity.y = min(player.velocity.y, 1.0f);
					return { Collider::CollisionData::Slope, abs(heightOverlap) };
				}
			}

		}

		return { Collider::CollisionData::None, 0.0f };;	// placeholder, implement this later
	}

	Collider::CollisionData CheckTriangleCollision(FloatRect checkBounds, FloatRect triangleBounds, bool rotated) {

		FloatRect playerBounds = checkBounds;

		bool collided = false;

		if (playerBounds.intersects(triangleBounds)) {
			Vector2f usedTrianglePoints[3];

			if (!rotated) {
				usedTrianglePoints[0] = Vector2f(triangleBounds.left, triangleBounds.top);
				usedTrianglePoints[1] = Vector2f(triangleBounds.left, triangleBounds.top + triangleBounds.height);
				usedTrianglePoints[2] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top + triangleBounds.height);
			}
			else {
				usedTrianglePoints[0] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top);
				usedTrianglePoints[1] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top + triangleBounds.height);
				usedTrianglePoints[2] = Vector2f(triangleBounds.left, triangleBounds.top + triangleBounds.height);
			}



			Vector2f playerDownLeftPoint = Vector2f(playerBounds.left, playerBounds.top + playerBounds.height);
			Vector2f playerDownRightPoint = Vector2f(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height);

			Collider::CollisionData boxCollisionData = CheckRectangleCollision(checkBounds, triangleBounds);

			if (!rotated) {
				if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom)
				{
					return boxCollisionData;
				}
				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left)
				{
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
				{
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right && playerBounds.contains(usedTrianglePoints[2]))
				{
					// Compare the overlap distance with the distance to move out of the triangle upwards, and move according to the smaller one
					float triangleHeight = triangleBounds.height;
					float triangleWidth = triangleBounds.width;
					float newWidth = abs(playerDownLeftPoint.x - usedTrianglePoints[2].x);
					float newHeight = newWidth * triangleHeight / triangleWidth;

					// move up a distance till the point is no longer inside the triangle
					float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));

					if (boxCollisionData.overlapDistance < abs(heightOverlap) - 2) {
						return boxCollisionData;
					}
					else
					{
						return { Collider::CollisionData::Slope, abs(heightOverlap) };
					}
				}
				else if (IsPointInsideTriangle(playerDownLeftPoint + Vector2f(0, -1), usedTrianglePoints))
				{
					return { Collider::CollisionData::Slope, 0 };
				}
			}
			else {
				if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom)
				{
					return boxCollisionData;
				}
				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right)
				{
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
				{
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left && playerBounds.contains(usedTrianglePoints[2]))
				{
					float triangleHeight = triangleBounds.height;
					float triangleWidth = triangleBounds.width;
					float newWidth = abs(playerDownRightPoint.x - usedTrianglePoints[2].x);
					float newHeight = newWidth * triangleHeight / triangleWidth;

					// move up a distance till the point is no longer inside the triangle
					float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));

					if (boxCollisionData.overlapDistance < abs(heightOverlap) - 2) {
						return boxCollisionData;
					}
					else
					{
						return { Collider::CollisionData::Slope, abs(heightOverlap) };
					}
				}
				else if (IsPointInsideTriangle(playerDownRightPoint + Vector2f(0, -1), usedTrianglePoints))
				{
					return { Collider::CollisionData::Slope, 0 };
				}
			}

		}

		return { Collider::CollisionData::None, 0.0f };;	// placeholder, implement this later
	}


	Collider(ColliderType newType, Vector2f position, Vector2f newScale = Vector2f(1, 1)) {
		type = newType;
		scale = newScale;
		startPosition = position;
	}

	Collider() {}

	void Initialize() {
		switch (type)
		{
		case Collider::Rectangle:
			ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(defaultSize.x * scale.x, defaultSize.y * scale.y));
			break;
		case Collider::Triangle:
			ApplyTexture(sprite, LoadTexture::TRIANGLE, Vector2f(defaultSize.x * scale.x, defaultSize.y * scale.y));
			break;
		case Collider::Triangle_Rotated:
			ApplyTexture(sprite, LoadTexture::TRIANGLE_ROTATED, Vector2f(defaultSize.x * scale.x, defaultSize.y * scale.y));
			break;
		default:
			break;
		}

		sprite.setPosition(startPosition);
	}


	bool IsOnGround(Player player, FloatRect groundCheckBounds) {
		CollisionData collisionData;

		switch (type)
		{
		case Collider::Rectangle:
			return groundCheckBounds.intersects(sprite.getGlobalBounds());
		case Collider::Triangle:
			collisionData = CheckTriangleCollision(groundCheckBounds, sprite.getGlobalBounds(), false);
			return collisionData.collisionDirection == CollisionData::CollisionDirection::Top || collisionData.collisionDirection == CollisionData::CollisionDirection::Slope;
		case Collider::Triangle_Rotated:
			collisionData = CheckTriangleCollision(groundCheckBounds, sprite.getGlobalBounds(), true);
			return collisionData.collisionDirection == CollisionData::CollisionDirection::Top || collisionData.collisionDirection == CollisionData::CollisionDirection::Slope;
		default:
			break;
		}
		return false;
	}


	bool CheckCollision(Player& player, CollisionData& collisionData, FloatRect bias = FloatRect(5.0f, 5.0f, 0.0f, 0.0f)) {

		switch (type)
		{
		case Collider::Rectangle:
			collisionData = CheckRectangleCollision(player, sprite.getGlobalBounds(), true, bias);
			break;
		case Collider::Triangle:
			collisionData = CheckTriangleCollision(player, sprite.getGlobalBounds(), false);
			break;
		case Collider::Triangle_Rotated:
			collisionData = CheckTriangleCollision(player, sprite.getGlobalBounds(), true);
			break;
		default:
			break;
		}


		FloatRect playerBounds = player.sprite.getGlobalBounds();
		FloatRect colliderBounds = FloatRect(playerBounds.left, playerBounds.top + groundedDistance, playerBounds.width, playerBounds.height);


		return IsOnGround(player, colliderBounds);
	}

	bool CheckCollision(Player& player) {
		CollisionData collisionData;
		return CheckCollision(player, collisionData);
	}
};

void ResolveCollisionVelocity(Collider::CollisionData::CollisionDirection collisionDirection, Player& player) {
	// basic velocity resolve for rectangle collision
	switch (collisionDirection)
	{
	case Collider::CollisionData::Top:
		player.velocity.y = min(player.velocity.y, 1.0f);
		break;
	case Collider::CollisionData::Bottom:
		player.velocity.y = max(player.velocity.y, 0.0f);
		break;
	case Collider::CollisionData::Left:
		player.velocity.x = min(player.velocity.x, 0.0f);

		break;
	case Collider::CollisionData::Right:
		player.velocity.x = max(player.velocity.x, 0.0f);
		break;
	default:
		break;
	}
}

struct ColliderList {
	int count = 0;
	Collider* elements;

	ColliderList() {
		elements = new Collider[count];
	}

	void Add(Collider element) {
		Collider* temp = new Collider[count];

		for (int i = 0; i < count; i++)
			temp[i] = elements[i];

		count++;
		elements = new Collider[count];

		if (count - 1 >= 0)
			for (int i = 0; i < count - 1; i++)
				elements[i] = temp[i];

		delete[] temp;

		elements[count - 1] = element;
	}

	void RemoveAt(int index) {
		if (count <= 0 || index < 0 || index >= count) return;

		Collider* temp = new Collider[count];

		for (int i = 0; i < count; i++)
			temp[i] = elements[i];

		count--;
		elements = new Collider[count];

		for (int i = 0; i < count; i++)
			if (i < index)
				elements[i] = temp[i];
			else
				elements[i] = temp[i + 1];

		delete[] temp;
	}

	~ColliderList() {
		delete[] elements;
	}
};

struct Gem
{
	enum Gemtype { waterGem, fireGem };
	Gemtype gemtype;
	Sprite sprite;
	bool isCollected = false;
	void start() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(30, 30));
		if (gemtype == waterGem) {
			sprite.setColor(Color::Blue);

		}
		else
		{
			sprite.setColor(Color::Red);
		}

	}
	Gem(Gemtype crystaltype, Vector2f position) {
		gemtype = crystaltype;
		sprite.setPosition(position);
		AllignSprite(sprite);
	}
	void checkintersect(Player hamada) {
		if (gemtype == waterGem && hamada.playertype == Player::Watergirl) {
			if (sprite.getGlobalBounds().intersects(hamada.sprite.getGlobalBounds())) {
				PlayGameSoundEffect(GameSoundEffect::DiamondCollect_sound);
				isCollected = true;
				sprite.setScale(0, 0);
			}
		}
		if (gemtype == fireGem && hamada.playertype == Player::Fireboy) {
			if (sprite.getGlobalBounds().intersects(hamada.sprite.getGlobalBounds())) {
				PlayGameSoundEffect(GameSoundEffect::DiamondCollect_sound);
				isCollected = true;
				sprite.setScale(0, 0);
			}
		}
	}
};

struct Game_Door
{
	bool isOpen = false;
	Sprite sprite;
	Collider collider;
	Vector2f startPosition;
	Vector2f endPosition;
	const float speed = 100.0f;

	Vector2f door_position = Vector2f(collider.sprite.getPosition());
	bool rotated = false;

	void Intialization() {
		collider = Collider(Collider::ColliderType::Rectangle, startPosition);

		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(32, 32 * 2));
		sprite.setPosition(startPosition);

		if (rotated)
		{
			ApplyTexture(collider.sprite, LoadTexture::RECTANGLE, Vector2f(32, 32 * 2));
		}
		else {
			ApplyTexture(collider.sprite, LoadTexture::RECTANGLE, Vector2f(32 * 2, 32));
			sprite.rotate(90);
		}
			

		sprite.setColor(Color::Yellow);
		AllignSprite(sprite);
	}
	Game_Door(Vector2f start, Vector2f end) {
		startPosition = start;
		endPosition = end;
	}

	void PreUpdate() {
		isOpen = false;
	}

	void moving_door()
	{
		if (isOpen) {
			sprite.setColor(Color::Magenta);

			Vector2f direction = endPosition - sprite.getPosition();
			
			if (abs(direction.x) + abs(direction.y) < 10) return; // avoid moving and overshooting when close to the end position

			direction = Normalize(direction);
			sprite.move(direction * speed * dt);
		}
		else {
			sprite.setColor(Color::Yellow);

			Vector2f direction = startPosition - sprite.getPosition();
			
			if (abs(direction.x) + abs(direction.y) < 10) return; // avoid moving and overshooting when close to the start position

			direction = Normalize(direction);
			sprite.move(direction * speed * dt);
		}
		collider.sprite.setPosition(sprite.getPosition());
	}

	void CheckCollision(Player& player) {
		player.isOnGround |= collider.CheckCollision(player);
	}
};

struct Click
{
	Sprite sprite;
	bool buttonpressed = false;
	Game_Door* door;
	bool hasDoor = false;

	void start() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(30, 30));
		sprite.setColor(Color::Yellow);
	}
	Click(Vector2f postion) {
		sprite.setPosition(postion);
		AllignSprite(sprite);
	}

	void SetDoor(Game_Door* doorpointer) {
		door = doorpointer;
		hasDoor = true;
	}

	void isPressed(Player anteel,Player anteela) {
		if (!hasDoor) return;

		bool lastState = buttonpressed;
		if (sprite.getGlobalBounds().intersects(anteel.sprite.getGlobalBounds())|| sprite.getGlobalBounds().intersects(anteela.sprite.getGlobalBounds())) {
		
			buttonpressed = true;
			door->isOpen = true;
			sprite.setColor(Color::Magenta);

		}
		else {
			buttonpressed = false;
			sprite.setColor(Color::Yellow);
		}
		if (buttonpressed!=lastState) {
			PlayGameSoundEffect(GameSoundEffect::Platform_sound);
		}
	}
	

};



struct Pond
{
	Sprite sprite;

	enum ponds_type
	{
		POISON_POND,
		FIRE_POND,
		WATER_POND
	} type;

	bool fireBoyColliding = false;
	bool waterGirlColliding = false;

	Pond(ponds_type startType, Vector2f position) {
		type = startType;
		sprite.setPosition(position);
	}

	void Initialilze() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(32 * 5, 32));
		AllignSprite(sprite);
	}

	void UpdateFireBoy(Player& fireBoy) {
		// if no collision return
		bool lastState = fireBoyColliding;

		fireBoyColliding = fireBoy.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds());

		if (fireBoyColliding)
		switch (type)
		{
		case POISON_POND:
		case WATER_POND:
			

			fireBoy.isDead = true;

			if (lastState != fireBoyColliding && fireBoyColliding == true) {
				PlayGameSoundEffect(GameSoundEffect::Death_sound);
			}
			break;

		case FIRE_POND:
			if (fireBoy.playerState == Player::Idle)
				PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, false);
			else if (fireBoy.justUpdatedPlayerState && fireBoy.lastState == Player::Idle)
				PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, true);
			else if (lastState != fireBoyColliding && fireBoyColliding == true)
				PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, true);
			break;
		}

		if (lastState != fireBoyColliding && fireBoyColliding == false)
			PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, false);
	}

	void UpdateWaterGirl(Player& waterGirl) {
		// if no collision return
		bool lastState = waterGirlColliding;

		waterGirlColliding = waterGirl.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds());

		if (waterGirlColliding)
			switch (type)
			{
			case POISON_POND:
			case FIRE_POND:


				waterGirl.isDead = true;

				if (lastState != waterGirlColliding && waterGirlColliding == true) {
					PlayGameSoundEffect(GameSoundEffect::Death_sound);
				}
				break;

			case WATER_POND:
				if (waterGirl.playerState == Player::Idle)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, false);
				else if (waterGirl.justUpdatedPlayerState && waterGirl.lastState == Player::Idle)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, true);
				else if (lastState != waterGirlColliding && waterGirlColliding == true)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, true);
				break;
			}

		if (lastState != waterGirlColliding && waterGirlColliding == false)
			PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, false);
	}
};

struct Final_door
{
	enum door_type
	{
		WATER_DOOR,
		FIRE_DOOR
	}type;
	bool touched = false;
	bool player_on_door = false;

	Sprite sprite;
	Vector2f startPosition;

	void Initialilze() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(32, 32 * 2));
		sprite.setPosition(startPosition);
		AllignSprite(sprite);
	}
	Final_door(door_type startType, Vector2f position) {
		type = startType;
		startPosition = position;
	}

	void Update(Player player)
	{
		touched = player_on_door;
		if ((player.playertype == Player::PlayerType::Watergirl) && player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) && (type == WATER_DOOR))
		{

			player_on_door = true;
			sprite.setColor(Color::Green);
			
			
		}
		else if ((player.playertype == Player::PlayerType::Fireboy) && player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) && (type == FIRE_DOOR))
		{

			player_on_door = true;
			sprite.setColor(Color::Green);
		

		}
		else
		{
			player_on_door = false;
			switch (type)
			{
			case Final_door::WATER_DOOR:
				sprite.setColor(Color::Blue);
				break;
			case Final_door::FIRE_DOOR:
				sprite.setColor(Color::Red);
				break;
			default:
				break;
			}
		}
		if (touched != player_on_door&& player_on_door==true) {
			PlayGameSoundEffect(GameSoundEffect::Door_sound);
		}
	}
};
struct Box {
	Collider collider;
	Vector2f startPosition;
	Vector2f velocity = Vector2f(0, 0);

	const float gravity = 500.0f;

	Box(Vector2f position) {
		startPosition = position;
	}

	void Initialize() {
		collider = Collider(Collider::ColliderType::Rectangle, startPosition);
		collider.moveRatio = 1.0f;
		ApplyTexture(collider.sprite, LoadTexture::RECTANGLE, Vector2f(48, 48));
		collider.sprite.setPosition(startPosition);
	}

	void CheckColliderCollision(Collider collider) {
		Collider::CollisionData collisionData = collider.CheckRectangleCollision(collider.sprite, collider.sprite.getGlobalBounds());
		if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top)
			velocity.y = min(velocity.y, 1.0f);
	}

	void UpdatePhysics() {
		// update gravity and move
		velocity.y += gravity * dt;
		collider.sprite.move(velocity * dt);
	}

	void CheckPlayerCollision(Player& player, Collider::CollisionData* boxCollisionDatas, int colliderCount) {
		Collider::CollisionData collisionData;
		player.isOnGround |= collider.CheckCollision(player, collisionData, FloatRect());
		if (collisionData.collisionDirection != Collider::CollisionData::CollisionDirection::None) player.isPushing = true;

		bool resolvedVelocity = false;
		for (int i = 0; i < colliderCount && !resolvedVelocity; i++)
			if (collisionData.collisionDirection == boxCollisionDatas[i].collisionDirection)
				switch (collisionData.collisionDirection)
				{
				case Collider::CollisionData::CollisionDirection::Top:
					player.velocity.y = min(player.velocity.y, -10.0f);
					resolvedVelocity = true;
					break;
				case Collider::CollisionData::CollisionDirection::Bottom:
					player.velocity.y = max(player.velocity.y, 10.0f);
					resolvedVelocity = true;
					break;
				case Collider::CollisionData::CollisionDirection::Left:
					player.velocity.x = min(player.velocity.x, -10.0f);
					resolvedVelocity = true;
					break;
				case Collider::CollisionData::CollisionDirection::Right:
					player.velocity.x = max(player.velocity.x, 10.0f);
					resolvedVelocity = true;
					break;
				default:
					break;
				}

	}


	void Draw(RenderTarget& renderTarget) {
		renderTarget.draw(collider.sprite);
	}
};

struct Switch {
	Sprite sprite;
	Game_Door* door;
	bool hasDoor = false;

	bool moved = false;
	void start() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(20, 50));
		sprite.setColor(Color::Cyan);
	}
	Switch(Vector2f postion) {
		sprite.setPosition(postion);
		AllignSprite(sprite);
	}

	void SetDoor(Game_Door* newDoor) {
		door = newDoor;
		hasDoor = true;
	}

	void leverMove(Player moroo, Player mora, Event event) {
		if (!hasDoor) return;

		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Space) {
				if (sprite.getGlobalBounds().intersects(moroo.sprite.getGlobalBounds()) || sprite.getGlobalBounds().intersects(mora.sprite.getGlobalBounds())) {

					moved = !moved;
					if (moved) 
					{ 
						door->isOpen = true; 
						sprite.setColor(Color::Green);
						PlayGameSoundEffect(GameSoundEffect::Lever_sound);
					}
					else
					{
						sprite.setColor(Color::Cyan);
						PlayGameSoundEffect(GameSoundEffect::Lever_sound);
					}
				}
			}
		}
	}

	void Update() {
		if (!hasDoor) return;
		door->isOpen |= moved;
	}
};