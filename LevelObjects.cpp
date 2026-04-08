
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
		}
		else if (playertype == Watergirl) {
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				velocity.x += accelration* dt;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A)) {
				velocity.x -= accelration * dt;
			}
			else velocity.x -= velocity.x * deccelration * dt;
		}


		velocity.y += gravity * dt;
		velocity.x = Clamp(velocity.x, -speed, speed);

		sprite.move(velocity * dt);
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

struct Collider
{
	enum ColliderType {
		Rectangle,
		Triangle,
		Triangle_Rotated
	};

	Sprite sprite;
	ColliderType type;

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

	bool IsOnGround(Collider::CollisionData collisionData) {
		return collisionData.collisionDirection == Collider::CollisionData::Top || collisionData.collisionDirection == collisionData.Slope;
	}

	bool IsPointInsideTriangle(Vector2f point, Vector2f trianglePoints[3]) {
		bool isPositive = Cross(point - trianglePoints[1], trianglePoints[1] - trianglePoints[0]) > 0;
		if (Cross(point - trianglePoints[2], trianglePoints[2] - trianglePoints[1]) > 0 != isPositive) return false;
		if (Cross(point - trianglePoints[0], trianglePoints[0] - trianglePoints[2]) > 0 != isPositive) return false;

		return true;
	}

	Collider::CollisionData CheckRectangleCollision(Player& player, FloatRect otherBounds, bool resolveCollision = true) {
		RectangleShape& sprite = player.sprite;
		Collider::CollisionData collisionData;

		FloatRect playerBounds = sprite.getGlobalBounds();

		if (playerBounds.intersects(otherBounds)) {

			float topOverlap = abs(otherBounds.top - (playerBounds.top + playerBounds.height));
			float bottomOverlap = abs((otherBounds.top + otherBounds.height) - playerBounds.top);
			float leftOverlap = abs(otherBounds.left - (playerBounds.left + playerBounds.width));
			float rightOverlap = abs((otherBounds.left + otherBounds.width) - playerBounds.left);

			// on comparing overlap, slightly prefer top and bottom overlaps, to avoid getting stuck on edges
			float comparedTopOverlap = topOverlap - 10;
			float comparedBottomOverlap = bottomOverlap - 10;


			if (comparedTopOverlap < comparedBottomOverlap && comparedTopOverlap < leftOverlap && comparedTopOverlap < rightOverlap) {
				// Collision from the top
				if (resolveCollision)
				{
					sprite.move(0, -topOverlap);
					player.velocity.y = min(player.velocity.y, 1.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Top , topOverlap };

			}
			else if (comparedBottomOverlap < comparedTopOverlap && comparedBottomOverlap < leftOverlap && comparedBottomOverlap < rightOverlap) {
				// Collision from the bottom
				if (resolveCollision)
				{
					sprite.move(0, bottomOverlap);
					player.velocity.y = max(player.velocity.y, 0.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Bottom , bottomOverlap };
			}
			else if (leftOverlap < rightOverlap && leftOverlap < comparedTopOverlap && leftOverlap < comparedBottomOverlap) {
				// Collision from the left
				if (resolveCollision)
				{
					sprite.move(-leftOverlap, 0);
					player.velocity.x = min(player.velocity.y, 0.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Left , leftOverlap };
			}
			else {
				// Collision from the right
				if (resolveCollision)
				{
					sprite.move(rightOverlap, 0);
					player.velocity.x = max(player.velocity.y, 0.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Right , rightOverlap };
			}
		}

		return collisionData;
	}

	Collider::CollisionData CheckTriangleCollision(Player& player, FloatRect triangleBounds, bool rotated) {

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

			Collider::CollisionData boxCollisionData = CheckRectangleCollision(player, triangleBounds, false);

			if (!rotated) {
				if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom)
				{
					player.sprite.move(0, boxCollisionData.overlapDistance);
					return boxCollisionData;
				}
				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left)
				{
					player.sprite.move(-boxCollisionData.overlapDistance, 0);
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
				{
					player.sprite.move(0, -boxCollisionData.overlapDistance);
					player.velocity.y = min(player.velocity.y, 1.0f);
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right && playerBounds.contains(usedTrianglePoints[2]))
				{
					player.sprite.move(boxCollisionData.overlapDistance, 0);
					return boxCollisionData;
				}
				else if (IsPointInsideTriangle(playerDownLeftPoint + Vector2f(0, -1), usedTrianglePoints))
				{
					float triangleHeight = triangleBounds.height;
					float triangleWidth = triangleBounds.width;
					float newWidth = abs(playerDownLeftPoint.x - usedTrianglePoints[2].x);
					float newHeight = newWidth * triangleHeight / triangleWidth;

					// move up a distance till the point is no longer inside the triangle
					float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));
					player.sprite.move(0, -abs(heightOverlap));
					player.velocity.y = min(player.velocity.y, 1.0f);
					return { Collider::CollisionData::Slope, abs(heightOverlap) };
				}
			}
			else {
				if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Bottom)
				{
					player.sprite.move(0, boxCollisionData.overlapDistance);
					return boxCollisionData;
				}
				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Right)
				{
					player.sprite.move(boxCollisionData.overlapDistance, 0);
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
				{
					player.sprite.move(0, -boxCollisionData.overlapDistance);
					player.velocity.y = min(player.velocity.y, 1.0f);
					return boxCollisionData;
				}

				else if (boxCollisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Left && playerBounds.contains(usedTrianglePoints[2]))
				{
					player.sprite.move(-boxCollisionData.overlapDistance, 0);
					return boxCollisionData;
				}
				else if (IsPointInsideTriangle(playerDownRightPoint + Vector2f(0, -1), usedTrianglePoints))
				{
					float triangleHeight = triangleBounds.height;
					float triangleWidth = triangleBounds.width;
					float newWidth = abs(playerDownRightPoint.x - usedTrianglePoints[2].x);
					float newHeight = newWidth * triangleHeight / triangleWidth;

					// move up a distance till the point is no longer inside the triangle
					float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));
					player.sprite.move(0, -abs(heightOverlap));
					player.velocity.y = min(player.velocity.y, 1.0f);
					return { Collider::CollisionData::Slope, abs(heightOverlap) };
				}
			}

		}

		return { Collider::CollisionData::None, 0.0f };;	// placeholder, implement this later
	}


	Collider(ColliderType newType, Vector2f position) {
		type = newType;
		sprite.setPosition(position);
	}

	Collider(){}

	void Initialize() {
		switch (type)
		{
		case Collider::Rectangle:
			ApplyTexture(sprite, LoadTexture::RECTANGLE);
			break;
		case Collider::Triangle:
			ApplyTexture(sprite, LoadTexture::TRIANGLE);
			break;
		case Collider::Triangle_Rotated:
			ApplyTexture(sprite, LoadTexture::TRIANGLE_ROTATED);
			break;
		default:
			break;
		}
	}


	bool CheckCollision(Player& player) {
		CollisionData collisionData;

		switch (type)
		{
		case Collider::Rectangle:
			collisionData = CheckRectangleCollision(player, sprite.getGlobalBounds());
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


		return IsOnGround(collisionData);
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


