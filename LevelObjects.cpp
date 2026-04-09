
// STRUCTS for level objects
struct Player
{
	enum PlayerType { Fireboy, Watergirl };
	PlayerType playertype;
	Sprite sprite;
	void start() {
		ApplyTexture(sprite, LoadTexture::RECTANGLE, Vector2f(50, 60));
		if (playertype == Fireboy)
			sprite.setColor(Color::Red);
		else sprite.setColor(Color::Blue);
	}

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
				velocity.x += accelration * dt;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				velocity.x -= accelration * dt;
			}
			else velocity.x -= velocity.x * deccelration * dt;
		}
		else if (playertype == Watergirl) {
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				velocity.x += accelration * dt;
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
		};
		CollisionDirection collisionDirection = CollisionData::None;

		float overlapDistance = 0.0f;
	};

	void AllignCollider() {
		Vector2f position = sprite.getPosition();
		position.x = round(position.x / defaultSize.x) * defaultSize.x;
		position.y = round(position.y / defaultSize.y) * defaultSize.y;

		sprite.setPosition(position);
	}

	bool IsPointInsideTriangle(Vector2f point, Vector2f trianglePoints[3]) {
		bool isPositive = Cross(point - trianglePoints[1], trianglePoints[1] - trianglePoints[0]) > 0;
		if (Cross(point - trianglePoints[2], trianglePoints[2] - trianglePoints[1]) > 0 != isPositive) return false;
		if (Cross(point - trianglePoints[0], trianglePoints[0] - trianglePoints[2]) > 0 != isPositive) return false;

		return true;
	}

	Collider::CollisionData CheckRectangleCollision(Player& player, FloatRect otherBounds, bool resolveCollision = true, FloatRect bias = FloatRect(5.0f, 5.0f, 0.0f, 0.0f)) {
		Sprite& sprite = player.sprite;
		Collider::CollisionData collisionData;

		FloatRect playerBounds = sprite.getGlobalBounds();

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
					sprite.move(0, -topOverlap);
					player.velocity.y = min(player.velocity.y, 1.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Top , topOverlap };

			}
			else if (comparedBottomOverlap < comparedTopOverlap && comparedBottomOverlap < comparedLeftOverlap && comparedBottomOverlap < comparedRightOverlap) {
				// Collision from the bottom
				if (resolveCollision)
				{
					sprite.move(0, bottomOverlap);
					player.velocity.y = max(player.velocity.y, 0.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Bottom , bottomOverlap };
			}
			else if (comparedLeftOverlap < comparedRightOverlap && comparedLeftOverlap < comparedTopOverlap && comparedLeftOverlap < comparedBottomOverlap) {
				// Collision from the left
				if (resolveCollision)
				{
					sprite.move(-leftOverlap, 0);
					player.velocity.x = min(player.velocity.x, 0.0f);
				}

				collisionData = { Collider::CollisionData::CollisionDirection::Left , leftOverlap };
			}
			else {
				// Collision from the right
				if (resolveCollision)
				{
					sprite.move(rightOverlap, 0);
					player.velocity.x = max(player.velocity.x, 0.0f);
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
		sprite.setPosition(position);
		scale = newScale;
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


		FloatRect playerBounds = player.sprite.getGlobalBounds();
		FloatRect colliderBounds = FloatRect(playerBounds.left, playerBounds.top + groundedDistance, playerBounds.width, playerBounds.height);


		return IsOnGround(player, colliderBounds);
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
	Gem(Gemtype crystaltype,Vector2f position) {
		gemtype = crystaltype;
		sprite.setPosition(position);
	}
	void checkintersect(Player hamada) {
		if (gemtype == waterGem && hamada.playertype == Player::Watergirl) {
			if (sprite.getGlobalBounds().intersects(hamada.sprite.getGlobalBounds())) {
				isCollected = true;
				sprite.setScale(0, 0);
			}
		}
		if (gemtype == fireGem && hamada.playertype == Player::Fireboy) {
			if (sprite.getGlobalBounds().intersects(hamada.sprite.getGlobalBounds())) {
				isCollected = true;
				sprite.setScale(0, 0);
			}
		}
	}
};
