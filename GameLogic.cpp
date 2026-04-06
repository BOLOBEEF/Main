
// GAME LOGIC


// Settings :



// Structs and enums



// Runtime variables


// Functions
bool CheckRectangleCollision(Player& player, RectangleShape other) {
	RectangleShape& sprite = player.sprite;

	FloatRect playerBounds = sprite.getGlobalBounds();
	FloatRect otherBounds = other.getGlobalBounds();

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
			sprite.move(0, -topOverlap);
			player.velocity.y = Clamp(player.velocity.y, player.velocity.y, 0.0f);
		}
		else if (comparedBottomOverlap < comparedTopOverlap && comparedBottomOverlap < leftOverlap && comparedBottomOverlap < rightOverlap) {
			// Collision from the bottom
			sprite.move(0, bottomOverlap);
		}
		else if (leftOverlap < rightOverlap && leftOverlap < comparedTopOverlap && leftOverlap < comparedBottomOverlap) {
			// Collision from the left
			sprite.move(-leftOverlap, 0);
		}
		else {
			// Collision from the right
			sprite.move(rightOverlap, 0);
		}

		return true;
	}

	return false;
}

bool IsPointInsideTriangle(Vector2f point, Vector2f trianglePoints [3]) {
	bool isPositive = Cross(point - trianglePoints[1], trianglePoints[1] - trianglePoints[0]) > 0;
	if (Cross(point - trianglePoints[2], trianglePoints[2] - trianglePoints[1]) > 0 != isPositive) return false;
	if (Cross(point - trianglePoints[0], trianglePoints[0] - trianglePoints[2]) > 0 != isPositive) return false;
	
	return true;
}

bool CheckTriangleCollision(RectangleShape& player, Sprite triangle, bool rotated) {
	FloatRect playerBounds = player.getGlobalBounds();
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

		// CASE 1: the player is colliding but any of the triangle points are inside the player
		if (playerBounds.contains(usedTrianglePoints[0]))
		{
			player.move(0, -abs((playerBounds.top + playerBounds.height) - usedTrianglePoints[0].y));
			return true;
		}
		else if (playerBounds.contains(usedTrianglePoints[1]))
		{
			player.move(0, abs((playerBounds.top - usedTrianglePoints[1].y)));
			return true;
		}
		else if (playerBounds.contains(usedTrianglePoints[2]))
		{
			float verticalOverlap = abs((playerBounds.top - usedTrianglePoints[2].y));
			float horizontalOverlap = abs(((rotated ? playerBounds.left + playerBounds.width : playerBounds.left) - usedTrianglePoints[2].x));

			if (verticalOverlap < horizontalOverlap)
				player.move(0, verticalOverlap);
			else
				player.move(horizontalOverlap * (rotated ? -1 : 1), 0);

			return true;
		}

		// CASE 2: downLeftPoint of the player is inside the triangle
		else if (IsPointInsideTriangle(playerDownLeftPoint, usedTrianglePoints))
		{
			float triangleHeight = triangleBounds.height;
			float triangleWidth = triangleBounds.width;
			float newWidth = abs(playerDownLeftPoint.x - (triangleBounds.left + triangleBounds.width));
			float newHeight = newWidth * triangleHeight / triangleWidth;

			// move up a distance till the point is no longer inside the triangle
			float heightOverlap = newHeight - abs(playerDownLeftPoint.y - (triangleBounds.top + triangleBounds.height));
			player.move(0, -abs(heightOverlap));
			return true;
		}

		// CASE 3: downRightPoint of the player is inside the triangle
		else if (IsPointInsideTriangle(playerDownRightPoint, usedTrianglePoints))
		{
			float triangleHeight = triangleBounds.height;
			float triangleWidth = triangleBounds.width;
			float newWidth = abs(playerDownRightPoint.x - (rotated ? triangleBounds.left : triangleBounds.left + triangleBounds.width));
			float newHeight = newWidth * triangleHeight / triangleWidth;

			// move up a distance till the point is no longer inside the triangle
			float heightOverlap = newHeight - abs(playerDownRightPoint.y - (triangleBounds.top + triangleBounds.height));
			player.move(0, -abs(heightOverlap));
			return true;
		}

	}

	return false;	// placeholder, implement this later
}


Player firePlayer=Player(Player::Fireboy);
RectangleShape ground = RectangleShape(Vector2f(400, 100));
Sprite triangle;
Sprite rotatedTriangle;


void InitializeGame()
{


	// code for initializing game variables and objects
	ground.setOrigin(ground.getLocalBounds().width / 2.0f, ground.getLocalBounds().height / 2.0f);
	ground.setPosition(center.x, center.y);
	
	triangle.setPosition(center.x + 200, center.y - 50);
	
	rotatedTriangle.setPosition(center.x -200, center.y - 50);
}

void HandleGameInput(Event event)
{
	// code for handling game input that is related to game logic
	firePlayer.checkJump(event);
}

void OnUpdatedGameStateGameLogic() {
	// do stuff here exactly when the gameState is changed
}


void UpdateGame()
{
	firePlayer.UpdateMotion();

	bool collided = false;
	collided |= CheckRectangleCollision(firePlayer, ground);
	collided |= CheckTriangleCollision(firePlayer.sprite, triangle, false);
	collided |= CheckTriangleCollision(firePlayer.sprite, rotatedTriangle, true);
		
	if (collided)
		firePlayer.sprite.setFillColor(Color::Blue);
	else
		firePlayer.sprite.setFillColor(Color::White);

	
}

void DrawGame()
{
	if (gameState != GAME) return;

	// no need for window.clear or window.display
	window.draw(firePlayer.sprite);
	window.draw(ground);
	window.draw(triangle);
	window.draw(rotatedTriangle);
}
