
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
	// Settings:
	const float accelration = 100.0f;
	const float deccelration = 5.0f;
	const float speed = 150.0f;
	const float slopeSpeed = speed * 0.707f;
	const float pushSpeed = slopeSpeed;
	const float gravity = 250.0f;
	const float jump = -250.0f;
	const Vector2f idleRange = Vector2f(10.0f, 10.0f); // the range of velocity in which the player is considered idle

	// runtime variables
	enum PlayerType { Fireboy, Watergirl } playertype;
	enum PlayerState { Walk, Jump_Rise, Fall, Idle } playerState = Idle, lastState = Idle;

	Sprite sprite;
	Vector2f velocity = { 0,0 };
	bool justUpdatedPlayerState = false;
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

	void Initialize() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(50, 60));
		if (playertype == Fireboy)
			sprite.setColor(Color::Red);
		else sprite.setColor(Color::Blue);
	}


	void Update() {
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

		if (velocity.x > idleRange.x || velocity.x < -idleRange.y) {
			playerState = Walk;
		}
		else if (velocity.y > idleRange.y)playerState = Fall;
		else if (velocity.y < -idleRange.y)playerState = Jump_Rise;
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

	void CheckInput(Event event) {
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


	// Settings:
	Vector2f defaultSize = Vector2f(32, 32);
	float groundedDistance = 20.0f;

	// runtime variables
	Sprite sprite;
	ColliderType type;
	Vector2f startPosition;
	Vector2f scale;

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
		} collisionDirection = CollisionData::None;

		float overlapDistance = 0.0f;
	};



	bool IsPointInsideTriangle(Vector2f point, Vector2f trianglePoints[3]) {
		bool isPositive = Cross(point - trianglePoints[1], trianglePoints[1] - trianglePoints[0]) > 0;
		if (Cross(point - trianglePoints[2], trianglePoints[2] - trianglePoints[1]) > 0 != isPositive) return false;
		if (Cross(point - trianglePoints[0], trianglePoints[0] - trianglePoints[2]) > 0 != isPositive) return false;

		return true;
	}

	void ResolveCollision(CollisionData collisionData, Sprite& other, float currentMoveRatio = 1.0f) {
		if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top || collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Slope) {
			other.move(0, -collisionData.overlapDistance * currentMoveRatio);
		}
		else if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left) {
			other.move(-collisionData.overlapDistance * currentMoveRatio, 0);
		}
		else if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom) {
			other.move(0,  collisionData.overlapDistance * currentMoveRatio);
		}
		else if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right) {
			other.move(collisionData.overlapDistance * currentMoveRatio, 0);
		}
	}

	void ResolveCollisionVelocity(Collider::CollisionData collisionData, Player& player) {
		// basic velocity resolve for rectangle collision
		switch (collisionData.collisionDirection)
		{
		case Collider::CollisionData::Top:
		case Collider::CollisionData::Slope:
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
		}
	}
	

	// get CollisiontData for 2 bounds, if they are colliding and from which side and how much they should move to resolve the collision
	Collider::CollisionData CheckRectangleCollision(FloatRect checkBounds, FloatRect otherBounds, FloatRect bias = FloatRect(5.0f, 5.0f, 0.0f, 0.0f)) {
		Collider::CollisionData collisionData;

		FloatRect playerBounds = checkBounds;

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

	// Function overload, used for collision resolve for sprites
	Collider::CollisionData CheckRectangleCollision(Sprite& other, FloatRect otherBounds, bool resolveCollision = true, FloatRect bias = FloatRect(5.0f, 5.0f, 0.0f, 0.0f), float thisMoveRatio = 0.0f) {
		Collider::CollisionData collisionData = CheckRectangleCollision(other.getGlobalBounds(), otherBounds, bias);

		if (resolveCollision)
		{
			ResolveCollision(collisionData, other, 1 - thisMoveRatio);
			if (thisMoveRatio != 0)
				ResolveCollision(collisionData, sprite, -thisMoveRatio);
		}

		return collisionData;
	}

	// Function overload, used for collision resolve for players, with velocity resolve
	Collider::CollisionData CheckRectangleCollision(Player& player, FloatRect otherBounds, bool resolveCollision = true, FloatRect bias = FloatRect(5.0f, 5.0f, 0.0f, 0.0f), float thisMoveRatio = 0.0f, bool resolveVelocity = true) {
		CollisionData collisionData = CheckRectangleCollision(player.sprite, otherBounds, resolveCollision, bias, thisMoveRatio);

		if (resolveCollision && resolveVelocity) ResolveCollisionVelocity(collisionData, player);

		return collisionData;
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
						float triangleHeight = triangleBounds.height;
						float triangleWidth = triangleBounds.width;
						float newWidth = abs(playerDownLeftPoint.x - usedTrianglePoints[2].x);
						float newHeight = newWidth * triangleHeight / triangleWidth;

						// move up a distance till the point is no longer inside the triangle
						float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));
						return { Collider::CollisionData::Slope, abs(heightOverlap) };
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
						float triangleHeight = triangleBounds.height;
						float triangleWidth = triangleBounds.width;
						float newWidth = abs(playerDownRightPoint.x - usedTrianglePoints[2].x);
						float newHeight = newWidth * triangleHeight / triangleWidth;

						// move up a distance till the point is no longer inside the triangle
						float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));
						return { Collider::CollisionData::Slope, abs(heightOverlap) };
					}
			}
		}

		return { Collider::CollisionData::None, 0.0f };;	// return no collision
	}
	
	Collider::CollisionData CheckTriangleCollision(Player& player, FloatRect triangleBounds, bool rotated, bool resolveCollision = true, float thisMoveRatio = 0.0f, bool resolveVelocity = true) {

		Sprite playerSprite = player.sprite;
		FloatRect playerBounds = player.sprite.getGlobalBounds();
		CollisionData triangleCollisionData = CheckTriangleCollision(playerBounds, triangleBounds, rotated);

		if (resolveCollision) {
			ResolveCollision(triangleCollisionData, player.sprite, 1 - thisMoveRatio);
			if (resolveVelocity) ResolveCollisionVelocity(triangleCollisionData, player);

			if (thisMoveRatio != 0.0f)
				ResolveCollision(triangleCollisionData, sprite, -thisMoveRatio);
		}

		return triangleCollisionData;
		//bool collided = false;

		//if (playerBounds.intersects(triangleBounds)) {
		//	Vector2f usedTrianglePoints[3];

		//	if (!rotated) {
		//		usedTrianglePoints[0] = Vector2f(triangleBounds.left, triangleBounds.top);
		//		usedTrianglePoints[1] = Vector2f(triangleBounds.left, triangleBounds.top + triangleBounds.height);
		//		usedTrianglePoints[2] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top + triangleBounds.height);
		//	}
		//	else {
		//		usedTrianglePoints[0] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top);
		//		usedTrianglePoints[1] = Vector2f(triangleBounds.left + triangleBounds.width, triangleBounds.top + triangleBounds.height);
		//		usedTrianglePoints[2] = Vector2f(triangleBounds.left, triangleBounds.top + triangleBounds.height);
		//	}



		//	Vector2f playerDownLeftPoint = Vector2f(playerBounds.left, playerBounds.top + playerBounds.height);
		//	Vector2f playerDownRightPoint = Vector2f(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height);


		//	Collider::CollisionData boxCollisionData = CheckRectangleCollision(player, triangleBounds, false, (!rotated ? FloatRect(5.0f, 0.0f, 5.0f, 0.0f) : FloatRect(5.0f, 0.0f, 0.0f, 5.0f)));

		//	if (!rotated) {
		//		if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom)
		//		{
		//			if (!resolveCollision)
		//				return boxCollisionData;

		//			player.sprite.move(0, boxCollisionData.overlapDistance);
		//			player.velocity.y = max(player.velocity.y, 0.0f);
		//			return boxCollisionData;
		//		}
		//		else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left)
		//		{
		//			if (!resolveCollision)
		//				return boxCollisionData;

		//			player.sprite.move(-boxCollisionData.overlapDistance, 0);
		//			player.velocity.x = min(player.velocity.x, 0.0f);
		//			return boxCollisionData;
		//		}

		//		else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
		//		{
		//			if (!resolveCollision)
		//				return boxCollisionData;

		//			player.sprite.move(0, -boxCollisionData.overlapDistance);
		//			player.velocity.y = min(player.velocity.y, 1.0f);
		//			return boxCollisionData;
		//		}

		//		else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right && playerBounds.contains(usedTrianglePoints[2]))
		//		{
		//			// Compare the overlap distance with the distance to move out of the triangle upwards, and move according to the smaller one
		//			float triangleHeight = triangleBounds.height;
		//			float triangleWidth = triangleBounds.width;
		//			float newWidth = abs(playerDownLeftPoint.x - usedTrianglePoints[2].x);
		//			float newHeight = newWidth * triangleHeight / triangleWidth;

		//			// move up a distance till the point is no longer inside the triangle
		//			float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));

		//			if (boxCollisionData.overlapDistance < abs(heightOverlap) - 2) {
		//				if (!resolveCollision)
		//					return boxCollisionData;

		//				player.sprite.move(boxCollisionData.overlapDistance, 0);
		//				player.velocity.x = max(player.velocity.x, 0.0f);
		//				return boxCollisionData;
		//			}
		//			else
		//			{
		//				if (!resolveCollision)
		//					return { Collider::CollisionData::Slope, abs(heightOverlap) };

		//				player.sprite.move(0, -abs(heightOverlap));
		//				player.velocity.y = min(player.velocity.y, 1.0f);
		//				return { Collider::CollisionData::Slope, abs(heightOverlap) };
		//			}
		//		}
		//		else if (IsPointInsideTriangle(playerDownLeftPoint + Vector2f(0, -1), usedTrianglePoints))
		//		{
		//			if (!resolveCollision)
		//				return { Collider::CollisionData::Slope, 0 };

		//			float triangleHeight = triangleBounds.height;
		//			float triangleWidth = triangleBounds.width;
		//			float newWidth = abs(playerDownLeftPoint.x - usedTrianglePoints[2].x);
		//			float newHeight = newWidth * triangleHeight / triangleWidth;

		//			// move up a distance till the point is no longer inside the triangle
		//			float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));
		//			player.sprite.move(0, -abs(heightOverlap) + 1);
		//			player.velocity.y = min(player.velocity.y, 1.0f);
		//			return { Collider::CollisionData::Slope, abs(heightOverlap) };
		//		}
		//	}
		//	else {
		//		if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom)
		//		{
		//			if (!resolveCollision)
		//				return boxCollisionData;

		//			player.sprite.move(0, boxCollisionData.overlapDistance);
		//			player.velocity.y = max(player.velocity.y, 0.0f);
		//			return boxCollisionData;
		//		}
		//		else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right)
		//		{
		//			if (!resolveCollision)
		//				return boxCollisionData;

		//			player.sprite.move(boxCollisionData.overlapDistance, 0);
		//			player.velocity.x = max(player.velocity.x, 0.0f);
		//			return boxCollisionData;
		//		}

		//		else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
		//		{
		//			if (!resolveCollision)
		//				return boxCollisionData;

		//			player.sprite.move(0, -boxCollisionData.overlapDistance);
		//			player.velocity.y = min(player.velocity.y, 1.0f);
		//			return boxCollisionData;
		//		}

		//		else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left && playerBounds.contains(usedTrianglePoints[2]))
		//		{
		//			float triangleHeight = triangleBounds.height;
		//			float triangleWidth = triangleBounds.width;
		//			float newWidth = abs(playerDownRightPoint.x - usedTrianglePoints[2].x);
		//			float newHeight = newWidth * triangleHeight / triangleWidth;

		//			// move up a distance till the point is no longer inside the triangle
		//			float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));

		//			if (boxCollisionData.overlapDistance < abs(heightOverlap) - 2) {
		//				if (!resolveCollision)
		//					return boxCollisionData;

		//				player.sprite.move(-boxCollisionData.overlapDistance, 0);
		//				player.velocity.x = min(player.velocity.x, 0.0f);
		//				return boxCollisionData;
		//			}
		//			else
		//			{
		//				if (!resolveCollision)
		//					return { Collider::CollisionData::Slope, abs(heightOverlap) };

		//				player.sprite.move(0, -abs(heightOverlap));
		//				player.velocity.y = min(player.velocity.y, 1.0f);
		//				return { Collider::CollisionData::Slope, abs(heightOverlap) };
		//			}
		//		}
		//		else if (IsPointInsideTriangle(playerDownRightPoint + Vector2f(0, -1), usedTrianglePoints))
		//		{
		//			if (!resolveCollision)
		//				return { Collider::CollisionData::Slope, 0 };

		//			float triangleHeight = triangleBounds.height;
		//			float triangleWidth = triangleBounds.width;
		//			float newWidth = abs(playerDownRightPoint.x - usedTrianglePoints[2].x);
		//			float newHeight = newWidth * triangleHeight / triangleWidth;

		//			// move up a distance till the point is no longer inside the triangle
		//			float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));
		//			player.sprite.move(0, -abs(heightOverlap) + 1);
		//			player.velocity.y = min(player.velocity.y, 1.0f);
		//			return { Collider::CollisionData::Slope, abs(heightOverlap) };
		//		}
		//	}

		//}

		//return { Collider::CollisionData::None, 0.0f };;	// placeholder, implement this later
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

	
	// need empty constructor for collider list, but make sure to set the type and position before using the collider
	Collider() {}
	Collider(ColliderType newType, Vector2f position, Vector2f newScale = Vector2f(1, 1)) {
		type = newType;
		scale = newScale;
		startPosition = position;
	}


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

	// check collision and return if player is grounded, also return collision data if needed (as a pointer or reference)
	// bias is used to prefer one collision direction over the other when the overlaps are close, to avoid getting stuck on edges, it is applied like this: { topBias, bottomBias, leftBias, rightBias }
	bool CheckCollision(Player& player, CollisionData& collisionData, FloatRect bias = FloatRect(5.0f, 5.0f, 0.0f, 0.0f), float thisMoveRatio = 0.0f, bool resolveVelocity = true) {

		switch (type)
		{
		case Collider::Rectangle:
			collisionData = CheckRectangleCollision(player, sprite.getGlobalBounds(), true, bias, thisMoveRatio, resolveVelocity);
			break;
		case Collider::Triangle:
			collisionData = CheckTriangleCollision(player, sprite.getGlobalBounds(), false);
			break;
		case Collider::Triangle_Rotated:
			collisionData = CheckTriangleCollision(player, sprite.getGlobalBounds(), true, true, thisMoveRatio, resolveVelocity);
			break;
		default:
			break;
		}


		FloatRect playerBounds = player.sprite.getGlobalBounds();
		FloatRect colliderBounds = FloatRect(playerBounds.left, playerBounds.top + groundedDistance, playerBounds.width, playerBounds.height);


		return IsOnGround(player, colliderBounds);
	}

	// function overload for when collision data is not needed
	bool CheckCollision(Player& player) {
		CollisionData collisionData;
		return CheckCollision(player, collisionData);
	}
};
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
struct FinalDoor
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
	FinalDoor(door_type startType, Vector2f position) {
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
			case FinalDoor::WATER_DOOR:
				sprite.setColor(Color::Blue);
				break;
			case FinalDoor::FIRE_DOOR:
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




// Generic struct for all level objects exculding colliders and players


struct Gem
{
	enum Gemtype { waterGem, fireGem };
	Gemtype gemtype;
	Sprite sprite;
	bool isCollected = false;

	void Initialize() {
		
		
		if (gemtype == waterGem) {
			sprite.setColor(Color::Blue);
			ApplyTexture(sprite, LoadTexture::diamond_water_texture, Vector2f(80, 80));
		}
		else {
			sprite.setColor(Color::Red);
			ApplyTexture(sprite, LoadTexture::diamond_fire_texture, Vector2f(80, 80));
		}
	}

	Gem(){}
	Gem(Gemtype crystaltype, Vector2f position) {
		gemtype = crystaltype;
		sprite.setPosition(position);
		AllignSprite(sprite);
	}

	void Update(Player hamada) {
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
struct Lever {

	bool initialized = false;
	Sprite sprite;
	Sprite baseSprite;

	bool state = false;

	void Initialize() {
		ApplyTexture(sprite, LoadTexture::lever_stick_texture, Vector2f(100, 100));
		ApplyTexture(baseSprite, LoadTexture::lever_base_texture, Vector2f(100, 100));
		initialized = true;
	}

	Lever(){}
	Lever(Vector2f postion, bool initialize = false) {
		sprite.setPosition(postion);
		AllignSprite(sprite);
		if (initialize) Initialize();
	}

	void CheckInput(Player moroo, Player mora, Event event) {
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Space) {
				if (sprite.getGlobalBounds().intersects(moroo.sprite.getGlobalBounds()) || sprite.getGlobalBounds().intersects(mora.sprite.getGlobalBounds())) {

					state = !state;
					if (state) 
					{ 
					
						PlayGameSoundEffect(GameSoundEffect::Lever_sound);
					}
					else
					{
		
						PlayGameSoundEffect(GameSoundEffect::Lever_sound);
					}
				}
			}
		}
	}
	void leverDraw() {
		if (state)sprite.setRotation(-30);
		else
		{
			sprite.setRotation(30);
		}
		window.draw(sprite);
		baseSprite.setPosition(sprite.getPosition());
		window.draw(baseSprite);
	}
	
};
struct Click
{
	bool initialized = false;

	Sprite sprite;
	bool isPressed = false;

	void Initialize() {
		ApplyTexture(sprite, LoadTexture::pusher_block_texture, Vector2f(75, 75));
		
		initialized = true;
	}

	Click(){}
	Click(Vector2f postion, bool initialize = false) {
		sprite.setPosition(postion+Vector2f(0,40));
		AllignSprite(sprite);
		if (initialize) Initialize();
	}

	void Update(Player anteel,Player anteela) {
		bool lastState = isPressed;
		if (sprite.getGlobalBounds().intersects(anteel.sprite.getGlobalBounds())|| sprite.getGlobalBounds().intersects(anteela.sprite.getGlobalBounds())) {
		
			isPressed = true;
			if (sprite.getTextureRect().top<50)
			sprite.setTextureRect(IntRect(sprite.getTextureRect().left, sprite.getTextureRect().top-100*dt, sprite.getTextureRect().width, sprite.getTextureRect().height));
			
		}
		else {
			isPressed = false;
			
		}
		if (isPressed!=lastState) {
			PlayGameSoundEffect(GameSoundEffect::Platform_sound);
		}
	}
	

};
struct Door
{
	bool isOpen = false;
	Sprite sprite;
	Collider collider;
	Vector2f startPosition;
	Vector2f endPosition;
	float speed = 100.0f;

	Vector2f door_position = Vector2f(collider.sprite.getPosition());
	bool rotated = false;

	Click button1;
	Click button2;
	Lever lever;


	void Initialize() {
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
		startPosition = sprite.getPosition();
	}

	Door(){}
	Door(Vector2f start, Vector2f end) {
		startPosition = start;
		endPosition = end;
	}

	void CheckCollision(Player& player) {
		player.isOnGround |= collider.CheckCollision(player);
	}

	void UpdateMovement() {
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

	void CheckInput(Player& fireBoy, Player& waterGirl, Event event) {
		if (lever.initialized)
			lever.CheckInput(fireBoy, waterGirl, event);
	}

	void Update(Player& fireBoy, Player& waterGirl)
	{
		// reset door state
		isOpen = false;

		if (button1.initialized)
			button1.Update(fireBoy, waterGirl);
		if (button2.initialized)
			button2.Update(fireBoy, waterGirl);

		isOpen |= button1.isPressed;
		isOpen |= button2.isPressed;
		isOpen |= lever.state;

		UpdateMovement();

		CheckCollision(fireBoy);
		CheckCollision(waterGirl);
	}

	void Draw() {
		window.draw(sprite);

		if (button1.initialized) window.draw(button1.sprite);
		if (button2.initialized) window.draw(button2.sprite);
		if (lever.initialized) lever.leverDraw();
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

	Pond(){}
	Pond(ponds_type startType, Vector2f position) {
		type = startType;
		sprite.setPosition(position);
	}

	void Initialilze() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(32 * 5, 32));
		AllignSprite(sprite);

		switch (type)
		{
		case Pond::POISON_POND: sprite.setColor(Color::Green);
			break;
		case Pond::FIRE_POND: sprite.setColor(Color::Red);
			break;
		case Pond::WATER_POND: sprite.setColor(Color::Blue);
			break;
		default:
			break;
		}
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
struct Box {
	Collider collider;
	Vector2f startPosition;
	Vector2f velocity = Vector2f(0, 0);

	float gravity = 500.0f;

	Box(){}
	Box(Vector2f position) {
		startPosition = position;
	}

	void Initialize() {
		collider = Collider(Collider::ColliderType::Rectangle, startPosition);
		ApplyTexture(collider.sprite, LoadTexture::movingbox_texture, Vector2f(48, 48));
		collider.sprite.setTexture(movingbox);
		collider.sprite.setPosition(startPosition);
	}

	void CheckCollision(ColliderList& colliders, Collider::CollisionData* colliderDatas) {
		for (int i = 0; i < colliders.count; i++)
		{
			Collider::CollisionData collisionData = colliders.elements[i].CheckRectangleCollision(collider.sprite, colliders.elements[i].sprite.getGlobalBounds());
			if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top)
				velocity.y = min(velocity.y, 1.0f);

			colliderDatas[i] = collisionData;
		}
	}

	void UpdatePhysics() {
		// update gravity and move
		velocity.y += gravity * dt;
		collider.sprite.move(velocity * dt);
	}

	void CheckCollision(Player& player, Collider::CollisionData* boxCollisionDatas, int colliderCount) {
		Collider::CollisionData collisionData;
		player.isOnGround |= collider.CheckCollision(player, collisionData, FloatRect(), 1.0f, false);
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

	void Update(Player& fireBoy, Player& waterGirl, ColliderList& colliders) {
		UpdatePhysics();
		Collider::CollisionData* boxCollisionDatas = new Collider::CollisionData[colliders.count];
		CheckCollision(colliders, boxCollisionDatas);
		CheckCollision(fireBoy, boxCollisionDatas, colliders.count);
		CheckCollision(waterGirl, boxCollisionDatas, colliders.count);
		delete[] boxCollisionDatas;
	}

	void PreDraw() {
		Sprite displaySprite = collider.sprite;
		displaySprite.scale(1.1f, 1.1f);
		window.draw(displaySprite);
	}
};





// this is a generic object struct to have any level object
// how to add a new object
// 1. finish it's normal struct
// 2. add it in the ObjectData struct and add it to the copyFrom function
// 3. add a new enum for it in ObjectType enum
// 4. add an Initialize"enum name here" funtion for it		for ex: InitializeGemObject is just the construct of Gem + gem.Initialize() at it's end
// 5. add it's update and draw and checkInput functions to the switch cases of the Object struct if needed

struct ObjectData {
	Gem gem;
	Door door;
	Pond pond;
	Box box;

	void CopyFrom(ObjectData other) {
		gem = other.gem;
		door = other.door;
		pond = other.pond;
		box = other.box;
	}

	bool CheckContainsPoint(Vector2f point) {
		if (gem.sprite.getGlobalBounds().contains(point))
			return true;
		if (door.sprite.getGlobalBounds().contains(point))
			return true;
		if (pond.sprite.getGlobalBounds().contains(point))
			return true;
		if (box.collider.sprite.getGlobalBounds().contains(point))
			return true;

		return false;
	}
};

struct Object {
	enum ObjectType
	{
		GemObject,
		DoorObject,
		PondObject,
		BoxObject,
	} type;

	ObjectData data;

	Object(){} // empty constructor for ObjectList to work
	Object(ObjectType startType) {
		type = startType;
	}

	void CopyFrom(Object other) {
		type = other.type;
		data.CopyFrom(other.data);
	}

	void InitializeGemObject(Gem::Gemtype crystaltype, Vector2f position) {
		data.gem.gemtype = crystaltype;
		data.gem.Initialize();
		data.gem.sprite.setPosition(position);
		AllignSprite(data.gem.sprite);
	}

	void InitializeDoorObject(Vector2f Initialize, Vector2f end) {
		data.door.startPosition = Initialize;
		data.door.endPosition = end;
		data.door.Initialize();
	}

	void InitializePondObject(Pond::ponds_type startType, Vector2f position) {
		data.pond.type = startType;
		data.pond.Initialilze();
		data.pond.sprite.setPosition(position);
		AllignSprite(data.pond.sprite);
	}

	void InitializeBoxObject(Vector2f position) {
		data.box.startPosition = position;
		data.box.Initialize();
	}

	void CheckInput(Player& fireboy, Player& waterGirl, Event event) {
		switch (type)
		{
		case Object::GemObject:
			break;
		case Object::DoorObject: data.door.CheckInput(fireboy, waterGirl, event);
			break;
		case Object::PondObject:
			break;
		case Object::BoxObject:
			break;
		default:
			break;
		}
	}

	void Update(Player& fireBoy, Player& waterGirl, ColliderList& colliders) {
		switch (type)
		{
		case Object::GemObject:
			data.gem.Update(fireBoy);
			data.gem.Update(waterGirl);
			break;
		case Object::PondObject:
			data.pond.UpdateFireBoy(fireBoy);
			data.pond.UpdateWaterGirl(waterGirl);
			break;
		case Object::BoxObject: data.box.Update(fireBoy, waterGirl, colliders);
			break;
		case Object::DoorObject: data.door.Update(fireBoy, waterGirl);
			break;
		default:
			break;
		}
	}

	// draw behind the players
	void PreDraw() {
		switch (type)
		{
		case Object::GemObject: window.draw(data.gem.sprite);
			break;
		}
	}

	// draw on top of the players
	void PostDraw() {
		switch (type)
		{
	

		case Object::DoorObject: data.door.Draw();
			break;
		case Object::PondObject: window.draw(data.pond.sprite);
			break;
		case Object::BoxObject: data.box.PreDraw();
			
			break;
		}
	}
};


// just doing Object = another object gives an error for some reason
// so had to add a copy funtcion instaed
struct ObjectList {
	int count = 0;
	Object* elements;

	ObjectList() {
		elements = new Object[count];
	}

	void Add(Object element) {
		Object* temp = new Object[count];

		for (int i = 0; i < count; i++)
			temp[i].CopyFrom(elements[i]);

		count++;
		elements = new Object[count];

		if (count - 1 >= 0)
			for (int i = 0; i < count - 1; i++)
				elements[i].CopyFrom(temp[i]);

		delete[] temp;

		elements[count - 1].CopyFrom(element);
	}

	void RemoveAt(int index) {
		if (count <= 0 || index < 0 || index >= count) return;

		Object* temp = new Object[count];

		for (int i = 0; i < count; i++)
			temp[i].CopyFrom(elements[i]);

		count--;
		elements = new Object[count];

		for (int i = 0; i < count; i++)
			if (i < index)
				elements[i].CopyFrom(temp[i]);
			else
				elements[i].CopyFrom(temp[i + 1]);

		delete[] temp;
	}

	Object& GetLastElement() {
		return elements[count - 1];
	}

	~ObjectList() {
		delete[] elements;
	}
};

struct Temporary_ground
{
	Sprite sprite;
	Collider collider;
	Vector2f startPosition;
	bool idle = true;
	//bool player_on_ground = false;
	Temporary_ground() {}
	Temporary_ground(Vector2f position) {
		sprite.setPosition(position);
		AllignSprite(sprite);
	}
	void CheckCollision(Player& player, Temporary_ground& temp) {
		if(player.sprite.getGlobalBounds().intersects(temp.sprite.getGlobalBounds()))
			temp.idle = false;
		//else
		//	temp.idle = true;
	}
	void Initialize() {
		//collider = Collider(Collider::ColliderType::Rectangle, sprite.getPosition());
		ApplyTexture(sprite, LoadTexture::TEMPORARY_GROUND, Vector2f(32*2, 32));
		
	}
	void update(Player& player,Temporary_ground& temp) {
		CheckCollision(player,temp);
		static float timer = 0.0f;
		Clock clock;
		if (!temp.idle) {
			
		
			timer += dt;
			
			if (timer >= 5.0f)
			{
				cout << "Omar";
				temp.sprite.setPosition(5000, 5000);
				timer = 0.0f;
				temp.idle = true;
			}
		}
		else {
		
			
			//float timer = 0.0f;
			timer += dt;
			if (timer >= 8.0f)
			{
				timer = 0.0f;
				temp.sprite.setPosition(temp.startPosition);
			}
		}
	}
};