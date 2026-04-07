
// GAME LOGIC


// Settings :



// Structs and enums



// Runtime variables


// Functions
struct Collider
{
	enum ColliderType {
		Rectangle,
		Triangle,
		Triangle_Rotated
	};

	ColliderType type;
};

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

CollisionData CheckRectangleCollision(Player& player, FloatRect otherBounds, bool resolveCollision = true) {
	RectangleShape& sprite = player.sprite;
	CollisionData collisionData;

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

			collisionData = { CollisionData::CollisionDirection::Top , topOverlap };

		}
		else if (comparedBottomOverlap < comparedTopOverlap && comparedBottomOverlap < leftOverlap && comparedBottomOverlap < rightOverlap) {
			// Collision from the bottom
			if (resolveCollision)
				sprite.move(0, bottomOverlap);

			collisionData = { CollisionData::CollisionDirection::Bottom , bottomOverlap };
		}
		else if (leftOverlap < rightOverlap && leftOverlap < comparedTopOverlap && leftOverlap < comparedBottomOverlap) {
			// Collision from the left
			if (resolveCollision)
				sprite.move(-leftOverlap, 0);

			collisionData = { CollisionData::CollisionDirection::Left , leftOverlap };
		}
		else {
			// Collision from the right
			if (resolveCollision)
				sprite.move(rightOverlap, 0);

			collisionData = { CollisionData::CollisionDirection::Right , rightOverlap };
		}
	}

	return collisionData;
}

bool IsPointInsideTriangle(Vector2f point, Vector2f trianglePoints[3]) {
	bool isPositive = Cross(point - trianglePoints[1], trianglePoints[1] - trianglePoints[0]) > 0;
	if (Cross(point - trianglePoints[2], trianglePoints[2] - trianglePoints[1]) > 0 != isPositive) return false;
	if (Cross(point - trianglePoints[0], trianglePoints[0] - trianglePoints[2]) > 0 != isPositive) return false;

	return true;
}

CollisionData CheckTriangleCollision(Player& player, Sprite triangle, bool rotated) {

	FloatRect playerBounds = player.sprite.getGlobalBounds();
	FloatRect triangleBounds = triangle.getGlobalBounds();
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

		CollisionData boxCollisionData = CheckRectangleCollision(player, triangleBounds, false);

		if (!rotated) {
			if (boxCollisionData.collisionDirection == CollisionData::CollisionDirection::Bottom)
			{
				player.sprite.move(0, boxCollisionData.overlapDistance);
				return boxCollisionData;
			}
			else if (boxCollisionData.collisionDirection == CollisionData::CollisionDirection::Left)
			{
				player.sprite.move(-boxCollisionData.overlapDistance, 0);
				return boxCollisionData;
			}

			else if (boxCollisionData.collisionDirection == CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
			{
				player.sprite.move(0, -boxCollisionData.overlapDistance);
				player.velocity.y = min(player.velocity.y, 1.0f);
				return boxCollisionData;
			}

			else if (boxCollisionData.collisionDirection == CollisionData::CollisionDirection::Right && playerBounds.contains(usedTrianglePoints[2]))
			{
				player.sprite.move(boxCollisionData.overlapDistance, 0);
				return boxCollisionData;
			}
			else if (IsPointInsideTriangle(playerDownLeftPoint, usedTrianglePoints))
			{
				float triangleHeight = triangleBounds.height;
				float triangleWidth = triangleBounds.width;
				float newWidth = abs(playerDownLeftPoint.x - (triangleBounds.left + triangleBounds.width));
				float newHeight = newWidth * triangleHeight / triangleWidth;

				// move up a distance till the point is no longer inside the triangle
				float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));
				player.sprite.move(0, -abs(heightOverlap));
				player.velocity.y = min(player.velocity.y, 1.0f);
				return { CollisionData::Slope, abs(heightOverlap) };
			}
		}
		else {
			if (boxCollisionData.collisionDirection == CollisionData::CollisionDirection::Bottom)
			{
				player.sprite.move(0, boxCollisionData.overlapDistance);
				return boxCollisionData;
			}
			else if (boxCollisionData.collisionDirection == CollisionData::CollisionDirection::Right)
			{
				player.sprite.move(boxCollisionData.overlapDistance, 0);
				return boxCollisionData;
			}

			else if (boxCollisionData.collisionDirection == CollisionData::CollisionDirection::Top && playerBounds.contains(usedTrianglePoints[0]))
			{
				player.sprite.move(0, -boxCollisionData.overlapDistance);
				player.velocity.y = min(player.velocity.y, 1.0f);
				return boxCollisionData;
			}

			else if (boxCollisionData.collisionDirection == CollisionData::CollisionDirection::Left && playerBounds.contains(usedTrianglePoints[2]))
			{
				player.sprite.move(-boxCollisionData.overlapDistance, 0);
				return boxCollisionData;
			}
			else if (IsPointInsideTriangle(playerDownRightPoint, usedTrianglePoints))
			{
				float triangleHeight = triangleBounds.height;
				float triangleWidth = triangleBounds.width;
				float newWidth = abs(playerDownRightPoint.x - (rotated ? triangleBounds.left : triangleBounds.left + triangleBounds.width));
				float newHeight = newWidth * triangleHeight / triangleWidth;

				// move up a distance till the point is no longer inside the triangle
				float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));
				player.sprite.move(0, -abs(heightOverlap));
				player.velocity.y = min(player.velocity.y, 1.0f);
				return { CollisionData::Slope, abs(heightOverlap) };
			}
		}

	}

	return { CollisionData::None, 0.0f };;	// placeholder, implement this later
}

bool IsOnGround(CollisionData collisionData) {
	return collisionData.collisionDirection == CollisionData::Top || collisionData.collisionDirection == collisionData.Slope;
}

void CheckPlayerCollision(Player& player);

Player fireBoy = Player(Player::Fireboy, center + Vector2f(-50, -500));
Player waterGirl = Player(Player::Watergirl, center + Vector2f(50, -500));

RectangleShape ground = RectangleShape(Vector2f(400, 100));
Sprite triangle;
Sprite rotatedTriangle;


void InitializeGame()
{
	// code for initializing game variables and objects
	ground.setOrigin(ground.getLocalBounds().width / 2.0f, ground.getLocalBounds().height / 2.0f);
	ground.setPosition(center.x, center.y);

	ApplyTexture(triangle, LoadTexture::TRIANGLE);
	triangle.setPosition(center.x + 200, center.y - 50);

	ApplyTexture(rotatedTriangle, LoadTexture::TRIANGLE_ROTATED);
	rotatedTriangle.setPosition(center.x - 200, center.y - 50);

	fireBoy.sprite.setFillColor(Color::Red);
	waterGirl.sprite.setFillColor(Color::Blue);
}

void HandleGameInput(Event event)
{
	if (gameState != GAME) return;

	// code for handling game input that is related to game logic
	fireBoy.checkJump(event);
	waterGirl.checkJump(event);
}

void OnUpdatedGameStateGameLogic() {
	// do stuff here exactly when the gameState is changed
}


void UpdateGame()
{
	if (gameState != GAME) return;

	fireBoy.UpdateMotion();
	waterGirl.UpdateMotion();
	//firePlayer.sprite.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

	CheckPlayerCollision(fireBoy);
	CheckPlayerCollision(waterGirl);
}

void CheckPlayerCollision(Player& player) {
	bool isOnGround = false;
	isOnGround |= IsOnGround(CheckRectangleCollision(player, ground.getGlobalBounds()));
	isOnGround |= IsOnGround(CheckTriangleCollision(player, triangle, false));
	isOnGround |= IsOnGround(CheckTriangleCollision(player, rotatedTriangle, true));
	player.isOnGround = isOnGround;
}


void DrawGame()
{
	if (gameState != GAME) return;

	// no need for window.clear or window.display
	window.draw(fireBoy.sprite);
	window.draw(waterGirl.sprite);
	window.draw(ground);
	window.draw(triangle);
	window.draw(rotatedTriangle);
}