
// STRUCTS for level objects
float Allign(float num, float defaultSize = 32.0f) {
	return round(num / defaultSize) * defaultSize;
}

void Allign(Vector2f& position, Vector2f defaultSize = Vector2f(32, 32)) {
	position.x = Allign(position.x, defaultSize.x);
	position.y = Allign(position.y, defaultSize.y);
}

void Allign(Sprite& sprite, Vector2f defaultSize = Vector2f(32, 32)) {
	FloatRect bounds = sprite.getGlobalBounds();
	Vector2f position = Vector2f(bounds.left, bounds.top);
	Allign(position, defaultSize);

	sprite.setPosition(position + Vector2f(bounds.width / 2.0f, bounds.height / 2.0f));
}


enum PlayerType { Fireboy, Watergirl };
enum PlayerState { Walk, Jump_Rise, Fall, Idle };

void UpdateAnimation(Sprite&, LoadTexture);
void UpdatePlayerTexture(Sprite&, PlayerType, PlayerState, bool);
void UpdateAnimationPlayer(Sprite&, PlayerType, PlayerState, bool);
void InitializeOneTimeAnimations();

struct FinalDoor;
void DoorUpdateAnimation(FinalDoor&);



struct Player
{
	// Settings:
	float accelration = 200.0f;
	float deccelration = 10.0f;
	float speed = 150.0f;
	float slopeSpeed = speed * 0.707f;
	float pushSpeed = slopeSpeed;
	float gravity = 250.0f;
	float jump = -250.0f;
	float jumpOnSnow = -50.0f;
	Vector2f idleRange = Vector2f(15.0f, 40.0f); // the range of velocity in which the player is considered idle
	Vector2f colliderSize = Vector2f(15, 60);
	float displayBodySize = 1.0f;
	float displayHeadSize = 1.0f;
	float girlSpeedOnSnow = 50.0f; // make girl slow on snow
	float boyAccelerationOnSnow = 80.0f; // make fire slide on snow
	Clock lastTouchedSlope;
	float boySlopeFallTime = 0.3f; // the time interval after which fire will keep sliding down the slope if he is on it and on snow at the same time
	float boySlopeFallAcceleration = 300.0f; // make fire accelerate down the slope when on snow and slope at the same time
	float waitTime = 1; //wait time after death and before turning gameState to gameover

	// runtime variables
	Sprite hitbox;
	Sprite displayBodySprite;
	Sprite displayHeadSprite;
	Sprite deathsprite;
	Sprite playerEnterDoorSprite;
	float headRotation = 0.0f;
	Vector2f velocity = { 0,0 };
	PlayerType playertype;
	PlayerState playerState = Idle, lastState = Idle;
	bool justUpdatedPlayerState = false;
	bool lastFacingRight = false;
	float currentSpeed = speed;
	float currentAccelration = accelration;
	float currentDeccelration = deccelration;
	bool isOnGround = false;
	bool isOnSlope = false;
	bool isPushing = false;
	bool isDead = false;
	bool isOnSnow = false;
	bool isStop = false;
	bool enteringDoor = false;
	Vector2f startPosition;
	bool slopeDirectionRight = true; // true if slope goe1s down to the right, false if slope goes down to the left
	Clock timeSinceAnimation;		 // used to wait after death animation or enter door animation then switch the gameState to GAMEOVER or Win



	Player(PlayerType charctertype, Vector2f spPosition) {
		playertype = charctertype;
		startPosition = spPosition;
		hitbox.setOrigin(hitbox.getLocalBounds().width / 2.0f, hitbox.getLocalBounds().height / 2.0f);
		hitbox.setPosition(startPosition + Vector2f(-105, -105));
	}

	void Initialize() {
		ApplyTexture(hitbox, LoadTexture::RECTANGLE, colliderSize);
		
		ApplyTexture(deathsprite, LoadTexture::death_smoke_texture, Vector2f(1, 1), Vector2f(1, 1), true, false);
		UpdateAnimation(deathsprite, death_smoke_texture);
		SetSpriteOriginToCenter(deathsprite);

		UpdatePlayerTexture(displayBodySprite, playertype, playerState, false);
		UpdatePlayerTexture(displayHeadSprite, playertype, playerState, true);


		if (playertype == Fireboy)
		{
			ApplyTexture(playerEnterDoorSprite, LoadTexture::fire_stairs_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), false, false);
			UpdateAnimation(playerEnterDoorSprite, LoadTexture::fire_stairs_texture);
		}
		else if (playertype == Watergirl)
		{
			ApplyTexture(playerEnterDoorSprite, LoadTexture::water_stairs_texture, Vector2f(1.0f, 1.0f), Vector2f(1.0f, 1.0f), false, false);
			UpdateAnimation(playerEnterDoorSprite, LoadTexture::water_stairs_texture);
		}

		displayBodySprite.setScale(displayBodySize, displayBodySize);
		displayHeadSprite.setScale(displayHeadSize, displayHeadSize);

		if (playertype == Fireboy)
			hitbox.setColor(Color::Red);
		else hitbox.setColor(Color::Blue);
	}


	void Update() {
		currentAccelration = accelration;
		currentDeccelration = deccelration;
		if (isOnSlope)
		{
			lastTouchedSlope.restart();
		}

		if (playertype == Fireboy) {
			if (isOnSnow)
			{
				currentAccelration = boyAccelerationOnSnow;
				currentDeccelration = boyAccelerationOnSnow * -5.0f;
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				velocity.x += currentAccelration * dt;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				velocity.x -= currentAccelration * dt;
			}
			else velocity.x -= velocity.x * deccelration * dt;
		}
		else if (playertype == Watergirl) {
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				velocity.x += currentAccelration * dt;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A)) {
				velocity.x -= currentAccelration * dt;
			}
			else velocity.x -= velocity.x * currentDeccelration * dt;
		}


		lastState = playerState;

		if (velocity.x > idleRange.x || velocity.x < -idleRange.x) {
			playerState = Walk;
		}
		else if (velocity.y > idleRange.y)  playerState = Fall;
		else if (velocity.y < -idleRange.y) playerState = Jump_Rise;
		else playerState = Idle;

		if (lastState != playerState) justUpdatedPlayerState = true;
		else justUpdatedPlayerState = false;

		if (justUpdatedPlayerState)
		{
			UpdatePlayerTexture(displayBodySprite, playertype, playerState, false);
			UpdatePlayerTexture(displayHeadSprite, playertype, playerState, true);
		}

		UpdateAnimationPlayer(displayBodySprite, playertype, playerState, false);
		UpdateAnimationPlayer(displayHeadSprite, playertype, playerState, true);

		velocity.y += gravity * dt;

		if (isOnSnow && playertype == Watergirl)
		{
			currentSpeed = girlSpeedOnSnow;
		}
		else if (isOnSlope) currentSpeed = slopeSpeed;
		else if (isPushing) currentSpeed = pushSpeed;
		else currentSpeed = speed;


		if (playertype == Fireboy && isOnSnow && lastTouchedSlope.getElapsedTime().asSeconds() < boySlopeFallTime)
			velocity.x += slopeDirectionRight ? boySlopeFallAcceleration * dt : -boySlopeFallAcceleration * dt;
		
		
		velocity.x = Clamp(velocity.x, -currentSpeed, currentSpeed);

		if (!isStop) {
			
		hitbox.move(velocity * dt);
		}
		isOnGround = false;
		isOnSlope = false;
		isPushing = false;
		isOnSnow = false;
	}

	void CheckInput(Event event) {
		if (!isOnGround||isDead) return;

		if (event.type == Event::KeyPressed) {
			if (playertype == Fireboy) {
				if (event.key.code == Keyboard::Up) {
					velocity.y = isOnSnow ? jumpOnSnow : jump;
					PlayGameSoundEffect(GameSoundEffect::BoyJump_sound);
				}
			}
			else if (playertype == Watergirl) {
				if (event.key.code == Keyboard::W) {
					velocity.y = isOnSnow ? jumpOnSnow : jump;
					PlayGameSoundEffect(GameSoundEffect::GirlJump_sound);
				}
			}
		}
	}

	void Draw() {
		bool drawHeadFirst = true;
		displayBodySprite.setPosition(hitbox.getPosition());
		if (velocity.x > 0 && displayBodySprite.getScale().x < 0) displayBodySprite.scale(-1, 1);
		else if (velocity.x < 0 && displayBodySprite.getScale().x > 0) displayBodySprite.scale(-1, 1);
		displayBodySprite.move(0, -10);

		displayHeadSprite.setPosition(hitbox.getPosition());
		if (velocity.x > 0 && displayHeadSprite.getScale().x < 0) displayHeadSprite.scale(-1, 1);
		else if (velocity.x < 0 && displayHeadSprite.getScale().x > 0) displayHeadSprite.scale(-1, 1);
		displayHeadSprite.move(0, -10);

		// head rotation
		if (playerState == PlayerState::Walk)
		{
			//displayHeadSprite.setRotation((headRotation < 0 ? headRotation + 180 : headRotation));

			bool facingRight = velocity.x > 0;

		    Vector2f scale = displayHeadSprite.getScale();
			scale = facingRight ? Vector2f(abs(scale.x), abs(scale.y)) : Vector2f(abs(scale.x), -abs(scale.y));
			displayHeadSprite.setScale(scale);

			float targetRotation = atan2(velocity.y, velocity.x) * 180.f / 3.14159f;
			headRotation = targetRotation;

			displayHeadSprite.setRotation(headRotation);
		}
		else
		{
			displayHeadSprite.setRotation(0);
			Vector2f scale = displayHeadSprite.getScale();
			displayHeadSprite.setScale(Vector2f(abs(scale.x), abs(scale.y)));
		}

		// if not dead and not entering door -> draw player normally
		if (!isDead && !enteringDoor) {
			if (playerState == PlayerState::Jump_Rise) {
				window.draw(displayHeadSprite);
				window.draw(displayBodySprite);
			}
			else {
				window.draw(displayBodySprite);
				window.draw(displayHeadSprite);
			}
		}
		else if (isDead) {
			UpdateAnimation(deathsprite, death_smoke_texture);
			deathsprite.setPosition(hitbox.getPosition() + Vector2f(0, -32));
			window.draw(deathsprite);

			if (timeSinceAnimation.getElapsedTime().asSeconds() > waitTime)
				UpdateGameState(GAMEOVER);
		}
		else if (enteringDoor && gameState == GAME) {
			// play player enter door animation
			UpdateAnimation(playerEnterDoorSprite, playertype == Fireboy ? LoadTexture::fire_stairs_texture : LoadTexture::water_stairs_texture);
			playerEnterDoorSprite.setPosition(hitbox.getPosition() + Vector2f(-35, -50));
			
			if (playertype == Watergirl) playerEnterDoorSprite.move(10, 0);

			window.draw(playerEnterDoorSprite);

			if (timeSinceAnimation.getElapsedTime().asSeconds() > waitTime)
				UpdateGameState(WIN_MENU);
		}
	}
	void die() {
		if (isDead) return;
		isDead = true;
		isStop = true;
		
		timeSinceAnimation.restart();
		InitializeOneTimeAnimations();
		musicPlayer.stop();
	}

	void EnterDoor(Vector2f doorPosition) {
		if (enteringDoor) return;
		enteringDoor = true;
		isStop = true;
		hitbox.setPosition(doorPosition + Vector2f(0 , 20));
		
		timeSinceAnimation.restart();
		InitializeOneTimeAnimations();
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
	bool editable;		// if the collider should align to the grid or not (default true), used for the pond ground collider

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
			other.move(0, collisionData.overlapDistance * currentMoveRatio);
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
		CollisionData collisionData = CheckRectangleCollision(player.hitbox, otherBounds, resolveCollision, bias, thisMoveRatio);

		if (resolveCollision && resolveVelocity) ResolveCollisionVelocity(collisionData, player);

		return collisionData;
	}


	Collider::CollisionData CheckTriangleCollision(FloatRect checkBounds, FloatRect triangleBounds, bool rotated, FloatRect bias = FloatRect(5.0f, 5.0f, 0.0f, 0.0f)) {

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

			Collider::CollisionData boxCollisionData = CheckRectangleCollision(checkBounds, triangleBounds, bias);

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

		Sprite playerSprite = player.hitbox;
		FloatRect playerBounds = player.hitbox.getGlobalBounds();
		CollisionData triangleCollisionData = CheckTriangleCollision(playerBounds, triangleBounds, rotated);

		if (resolveCollision) {
			ResolveCollision(triangleCollisionData, player.hitbox, 1 - thisMoveRatio);
			if (resolveVelocity) ResolveCollisionVelocity(triangleCollisionData, player);

			if (thisMoveRatio != 0.0f)
				ResolveCollision(triangleCollisionData, sprite, -thisMoveRatio);
		}

		return triangleCollisionData;
	}


	bool IsOnGround(Player player, FloatRect groundCheckBounds) {
		CollisionData collisionData;
		float boundsReduction = 5;
		FloatRect bounds = sprite.getGlobalBounds();

		switch (type)
		{
		case Collider::Rectangle:
			bounds = FloatRect(bounds.left + boundsReduction, bounds.top + boundsReduction, bounds.width - 2 * boundsReduction, bounds.height - boundsReduction);
			return groundCheckBounds.intersects(bounds);
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
	Collider(ColliderType newType, Vector2f position, Vector2f newScale = Vector2f(1, 1), bool IsEditable = true) {
		type = newType;
		scale = newScale;
		startPosition = position;
		editable = IsEditable;
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
		FloatRect playerBounds = player.hitbox.getGlobalBounds();
		FloatRect colliderBounds = FloatRect(playerBounds.left, playerBounds.top, playerBounds.width, playerBounds.height + groundedDistance);


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
		
		bool grounded = IsOnGround(player, colliderBounds);

		return grounded || collisionData.collisionDirection == CollisionData::CollisionDirection::Top || collisionData.collisionDirection == CollisionData::CollisionDirection::Slope;
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

	void Add(Collider element) {

		if (count == 0)
		{
			count++;
			elements = new Collider[count];
			elements[0] = element;
			return;
		}

		Collider* temp = elements;

		count++;

		elements = new Collider[count];

		for (int i = 0; i < count - 1; i++)
			elements[i] = temp[i];

		delete[] temp;

		elements[count - 1] = element;
	}

	void RemoveAt(int index) {
		if (count <= 0 || index < 0 || index >= count) return;

		Collider* temp = elements;

		count--;

		elements = new Collider[count];

		for (int i = 0; i < count; i++)
			if (i < index)
				elements[i] = temp[i];
			else
				elements[i] = temp[i + 1];

		delete[] temp;
	}

	Collider& GetLastElement() {
		if (count == 0) {
			cout << "ColliderList is empty" << endl;
			exit(-2);
		}

		return elements[count - 1];
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
	float scale = 0.8f;
	float currentFrame = 0;
	bool justEntered = false;

	Sprite sprite;
	Vector2f startPosition;

	void Initialize() {
		switch (type)
		{
		case WATER_DOOR:
			ApplyTexture(sprite, LoadTexture::water_door_open_texture, Vector2f(3586, 138));
			sprite.scale(scale, scale);
			break;
		case FIRE_DOOR:
			ApplyTexture(sprite, LoadTexture::fire_door_open_texture, Vector2f(3586, 138));
			sprite.scale(scale, scale);
			break;
		}
		sprite.setPosition(startPosition + Vector2f(sprite.getGlobalBounds().width / 2.0f - 50, 0));
		Allign(sprite);
		sprite.move(0, 16);
	}

	FinalDoor(door_type startType, Vector2f position) {
		type = startType;
		startPosition = position;
	}

	void Update(Player player)
	{
		touched = player_on_door;
		if ((player.playertype == PlayerType::Watergirl) && player.hitbox.getGlobalBounds().intersects(sprite.getGlobalBounds()) && (type == WATER_DOOR))
		{

			player_on_door = true;
		}
		else if ((player.playertype == PlayerType::Fireboy) && player.hitbox.getGlobalBounds().intersects(sprite.getGlobalBounds()) && (type == FIRE_DOOR))
		{
			player_on_door = true;
		}
		else
		{
			player_on_door = false;
		}
		if (touched != player_on_door && player_on_door == true) {
			justEntered = true;
			PlayGameSoundEffect(GameSoundEffect::Door_sound);
		}
		else justEntered = false;

		DoorUpdateAnimation(*this);
	}
};




// Generic struct for all level objects exculding colliders and players


struct Gem
{
	enum Gemtype { waterGem, fireGem };
	Gemtype type;
	Sprite sprite;
	bool isCollected = false;
	float scale = 1.2f;
	float colliderReduction = 20.0f; // reduce the collider/hitbox size of the gem

	void Initialize() {


		if (type == waterGem) {
			ApplyTexture(sprite, LoadTexture::diamond_water_texture, Vector2f(80 * scale, 80 * scale));
		}
		else {
			ApplyTexture(sprite, LoadTexture::diamond_fire_texture, Vector2f(80 * scale, 80 * scale));
		}
	}

	Gem() {}
	Gem(Gemtype crystaltype, Vector2f position) {
		type = crystaltype;
		sprite.setPosition(position);
		Allign(sprite);
	}

	void Update(Player hamada) {
		if (isCollected) return;

		FloatRect hitbox = sprite.getGlobalBounds();
		hitbox.left += colliderReduction;
		hitbox.width -= colliderReduction * 2;
		hitbox.top += colliderReduction;
		hitbox.height -= colliderReduction * 2;

		if (type == waterGem && hamada.playertype == Watergirl) {
			if (hitbox.intersects(hamada.hitbox.getGlobalBounds())) {
				PlayGameSoundEffect(GameSoundEffect::DiamondCollect_sound);
				isCollected = true;
				sprite.setScale(0, 0);
			}
		}
		if (type == fireGem && hamada.playertype == Fireboy) {
			if (hitbox.intersects(hamada.hitbox.getGlobalBounds())) {
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
	Sprite light_stick;
	Vector2f initialPosition;

	bool state = false;

	void Initialize() {
		ApplyTexture(sprite, LoadTexture::lever_stick_texture, Vector2f(85, 85));
		ApplyTexture(light_stick, LoadTexture::lever_light_texture, Vector2f(1, 1), Vector2f(1, 1), true, false);
		ApplyTexture(baseSprite, LoadTexture::lever_base_texture, Vector2f(85, 85));
		initialized = true;
	}

	Lever() {}
	Lever(Vector2f position, bool initialize = false) {
		initialPosition = position;
		if (initialize) Initialize();
		sprite.setPosition(position);
		Allign(sprite);
		sprite.move(0, 20);
	}

	void CheckInput(Player moroo, Player mora, Event event) {
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Space) {
				FloatRect bounds = sprite.getGlobalBounds();
				bounds = FloatRect(bounds.left, bounds.top, bounds.width, max(bounds.height - 100, 0.0f));

				if (bounds.intersects(moroo.hitbox.getGlobalBounds()) || bounds.intersects(mora.hitbox.getGlobalBounds())) {

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
	
		window.draw(sprite);
		if (state) {
			sprite.setRotation(-30);
			light_stick.setColor(Color::Yellow);
			window.draw(light_stick);
		}
		else
		{
			sprite.setRotation(30);
		}
		baseSprite.setPosition(sprite.getPosition());
		light_stick.setPosition(sprite.getPosition()+Vector2f(-17,12));
		window.draw(baseSprite);
	}

};
struct Click
{
	bool initialized = false;

	Sprite sprite;
	Sprite ligh_click;
	bool isPressed = false;
	Vector2f initialPosition;
	Vector2f startPosition;

	float speed = 60.0f;

	void Initialize() {
		ApplyTexture(sprite, LoadTexture::pusher_block_texture, Vector2f(75, 75));
		ApplyTexture(ligh_click, LoadTexture::pusher_block_light_texture, Vector2f(1, 1), Vector2f(1, 1), true, false);
		
		initialized = true;
	}

	Click() {}
	Click(Vector2f position, bool initialize = false) {
		initialPosition = position;
		if (initialize) Initialize();
		startPosition = position;
		sprite.setPosition(startPosition);
		Allign(sprite);
		ligh_click.setPosition(sprite.getPosition() + Vector2f(0, 23));
		ligh_click.setColor(Color::Green);
		ligh_click.setScale(0.5f, 0.5f);
		sprite.move(0, 20);
		startPosition = sprite.getPosition();
	}

	void Update(Player anteel, Player anteela) {
		bool lastState = isPressed;
		ligh_click.setPosition(sprite.getPosition() + Vector2f(0, -5));
		if (sprite.getGlobalBounds().intersects(anteel.hitbox.getGlobalBounds()) || sprite.getGlobalBounds().intersects(anteela.hitbox.getGlobalBounds())) {

			isPressed = true;

			if (abs(startPosition.y - sprite.getPosition().y) < 20)
				sprite.move(0, speed * dt);
		}
		else {
			isPressed = false;
			if (startPosition.y < sprite.getPosition().y)
				sprite.move(0, -speed * dt);
		}
		if (isPressed != lastState) {
			PlayGameSoundEffect(GameSoundEffect::Platform_sound);
		}
		
	}
	void draw_click() {
	
		window.draw(sprite);
		window.draw(ligh_click);
	}


};
struct Door
{
	bool isOpen = false;
	Sprite displaySprite;
	Collider collider;
	Vector2f startPosition;
	Vector2f endPosition;
	float speed = 100.0f;

	Vector2f door_position = Vector2f(collider.sprite.getPosition());
	bool rotated = false;

	Click button1;
	Click button2;
	Lever lever;
	bool lastButtonAdded = false; // used to alternate between button1 and button2 when adding buttons to the door


	void Initialize() {
		collider = Collider(Collider::ColliderType::Rectangle, startPosition);

		ApplyTexture(displaySprite, LoadTexture::moving_platform_texture, Vector2f(), Vector2f(), true, false);
		displaySprite.setScale(0.125, 0.125);
		displaySprite.setPosition(startPosition);

		if (rotated)
		{
			ApplyTexture(collider.sprite, LoadTexture::RECTANGLE, Vector2f(displaySprite.getGlobalBounds().height, displaySprite.getGlobalBounds().width));
			displaySprite.rotate(90);
		}
		else {
			ApplyTexture(collider.sprite, LoadTexture::RECTANGLE, Vector2f(displaySprite.getGlobalBounds().width, displaySprite.getGlobalBounds().height));
		}


		
		Allign(displaySprite);
		startPosition = displaySprite.getPosition();
	}

	void SetEndPosition(Vector2f position, bool forceSet = false) {
		endPosition = position;

		if (forceSet) {
			endPosition = position;
			if (!rotated) endPosition += Vector2f(0, -16);
			else endPosition -= Vector2f(16, 0);
			return;
		}

		Allign(endPosition);
		if (!rotated) endPosition += Vector2f(0, 16);
		else endPosition -= Vector2f(16, 0);
	}


	Door() {}
	Door(Vector2f start, Vector2f end) {
		startPosition = start;
		SetEndPosition(end, true);
	}

	// check if position is inside the door objects (button or lever)
	int CheckDoorObjects(Vector2f position) {
		if (button1.sprite.getGlobalBounds().contains(position)) return 1;
		if (button2.sprite.getGlobalBounds().contains(position)) return 2;
		if (lever.sprite.getGlobalBounds().contains(position)) return 3;

		return 0; // nothing collided
	}

	void CheckCollision(Player& player) {
		player.isOnGround |= collider.CheckCollision(player);
	}

	void UpdateMovement() {
		if (isOpen) {
			

			Vector2f direction = endPosition - displaySprite.getPosition();

			if (abs(direction.x) + abs(direction.y) < 3) return; // avoid moving and overshooting when close to the end position

			direction = Normalize(direction);
			displaySprite.move(direction * speed * dt);
		}
		else {
	

			Vector2f direction = startPosition - displaySprite.getPosition();

			if (abs(direction.x) + abs(direction.y) < 3) return; // avoid moving and overshooting when close to the start position

			direction = Normalize(direction);
			displaySprite.move(direction * speed * dt);
		}
	}

	void CheckInput(Player& fireBoy, Player& waterGirl, Event event) {
		if (lever.initialized)
			lever.CheckInput(fireBoy, waterGirl, event);
	}

	void Update(Player& fireBoy, Player& waterGirl)
	{
		// reset door state
		isOpen = false;

		collider.sprite.setPosition(displaySprite.getPosition());

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

	// draw the door before the ground so the objects appear on top of the door
	void PreDraw() {
		window.draw(displaySprite);

		if (button1.initialized) button1.draw_click();
		if (button2.initialized) button2.draw_click();
	}

	// draw the lever after the ground so it appears on top of the ground and players when the door is open
	void PostDraw() {
		if (lever.initialized) lever.leverDraw();
	}
};
struct Pond
{
	Sprite collider;
	Vector2f displayOffset = Vector2f(-7, -6);
	Collider startColl;
	Collider endColl;
	Collider midColl;

	enum ponds_type
	{
		POISON_POND,
		FIRE_POND,
		WATER_POND
	} type;

	bool fireBoyColliding = false;
	bool waterGirlColliding = false;
	int width = 1;

	Vector2f GetTopLeft(Sprite sprite) {
		return Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
	}

	Pond() {}
	Pond(ponds_type startType, Vector2f position) {
		type = startType;
		collider.setPosition(position);
	}

	void Initialize(int startWidth = 1) {
		width = startWidth;
		ApplyTexture(collider, LoadTexture::RECTANGLE, Vector2f(32 * width, 32));
		Allign(collider);
	}

	void SetPosition(Vector2f position) {
		collider.setPosition(position);
		Allign(collider);
	}

	void InitializeColliders() {
		// Add custom colliders for the pond object
		float groundHeight = 0.5f;
		float slopeXScale = 2.0f;
		float slopeXOffset = 10.0f;

		midColl = Collider(Collider::ColliderType::Rectangle,
			Vector2f(
				collider.getGlobalBounds().left + collider.getGlobalBounds().width / 2.0f,
				collider.getGlobalBounds().top + collider.getGlobalBounds().height - groundHeight * 32 / 2.0f),
			Vector2f(width, groundHeight),
			false);

		startColl = Collider(Collider::ColliderType::Triangle,
			Vector2f(
				collider.getGlobalBounds().left + 16,
				collider.getGlobalBounds().top + 16), Vector2f(slopeXScale, 1), false);


		endColl = Collider(Collider::ColliderType::Triangle_Rotated,
			Vector2f(
				collider.getGlobalBounds().left + collider.getGlobalBounds().width - 16,
				collider.getGlobalBounds().top + 16), Vector2f(slopeXScale, 1), false);


		startColl.Initialize();
		endColl.Initialize();
		midColl.Initialize();
		startColl.sprite.move(slopeXOffset, 0);
		endColl.sprite.move(-slopeXOffset, 0);
	}

	void UpdateFireBoy(Player& fireBoy) {
		// if no collision return
		bool lastState = fireBoyColliding;
		FloatRect intersections;
		bool isTouching = fireBoy.hitbox.getGlobalBounds().intersects(collider.getGlobalBounds(), intersections);
		fireBoyColliding = min(intersections.width, intersections.height) > 10; // only consider it a collision if the intersection area is big enough, to avoid colliding when just touching the edge of the pond

		if (fireBoyColliding)
			switch (type)
			{
			case POISON_POND:
			case WATER_POND:


				fireBoy.die();
				
				if (lastState != fireBoyColliding && fireBoyColliding == true) {
					PlayGameSoundEffect(GameSoundEffect::Death_sound);
				}
				break;

			case FIRE_POND:
				if (fireBoy.playerState == Idle)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, false);
				else if (fireBoy.justUpdatedPlayerState && fireBoy.lastState == Idle)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, true);
				else if (lastState != fireBoyColliding && fireBoyColliding == true)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, true);
				break;
			}

		if (lastState != fireBoyColliding && fireBoyColliding == false)
			PlayGameSoundEffect(GameSoundEffect::Pondsteps_boy_sound, false);

		fireBoy.isOnGround |= startColl.CheckCollision(fireBoy);
		fireBoy.isOnGround |= midColl.CheckCollision(fireBoy);
		fireBoy.isOnGround |= endColl.CheckCollision(fireBoy);
	}

	void UpdateWaterGirl(Player& waterGirl) {
		// if no collision return
		bool lastState = waterGirlColliding;
		FloatRect intersections;
		bool isTouching = waterGirl.hitbox.getGlobalBounds().intersects(collider.getGlobalBounds(), intersections);
		waterGirlColliding = min(intersections.width, intersections.height) > 10; // only consider it a collision if the intersection area is big enough, to avoid colliding when just touching the edge of the pond

		if (waterGirlColliding)
			switch (type)
			{
			case POISON_POND:
			case FIRE_POND:


				waterGirl.die();

				if (lastState != waterGirlColliding && waterGirlColliding == true) {
					PlayGameSoundEffect(GameSoundEffect::Death_sound);
				}
				break;

			case WATER_POND:
				if (waterGirl.playerState == Idle)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_girl_sound, false);
				else if (waterGirl.justUpdatedPlayerState && waterGirl.lastState == Idle)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_girl_sound, true);
				else if (lastState != waterGirlColliding && waterGirlColliding == true)
					PlayGameSoundEffect(GameSoundEffect::Pondsteps_girl_sound, true);
				break;
			}

		if (lastState != waterGirlColliding && waterGirlColliding == false)
			PlayGameSoundEffect(GameSoundEffect::Pondsteps_girl_sound, false);

		waterGirl.isOnGround |= startColl.CheckCollision(waterGirl);
		waterGirl.isOnGround |= midColl.CheckCollision(waterGirl);
		waterGirl.isOnGround |= endColl.CheckCollision(waterGirl);
	}

	void Update(Player& fireBoy, Player& waterGirl) {

		UpdateFireBoy(fireBoy);
		UpdateWaterGirl(waterGirl);
	}

	void Draw() {
		//window.draw(collider);

		Sprite* displaySprites = new Sprite[width];

		for (int i = 0; i < width; i++)
		{
			if (i == 0)
				switch (type)
				{
				case Pond::POISON_POND: ApplyTexture(displaySprites[i], LoadTexture::green_pond_left_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::green_pond_left_texture);
					break;
				case Pond::FIRE_POND: ApplyTexture(displaySprites[i], LoadTexture::fire_pond_left_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::fire_pond_left_texture);
					break;
				case Pond::WATER_POND: ApplyTexture(displaySprites[i], LoadTexture::water_pond_left_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::water_pond_left_texture);
					break;
				}
			else if (i == width - 1)
				switch (type)
				{
				case Pond::POISON_POND: ApplyTexture(displaySprites[i], LoadTexture::green_pond_right_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::green_pond_right_texture);
					break;
				case Pond::FIRE_POND: ApplyTexture(displaySprites[i], LoadTexture::fire_pond_right_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::fire_pond_right_texture);
					break;
				case Pond::WATER_POND: ApplyTexture(displaySprites[i], LoadTexture::water_pond_right_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::water_pond_right_texture);
					break;
				}
			else
				switch (type)
				{
				case Pond::POISON_POND: ApplyTexture(displaySprites[i], LoadTexture::green_pond_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::green_pond_texture);
					break;
				case Pond::FIRE_POND: ApplyTexture(displaySprites[i], LoadTexture::fire_pond_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::fire_pond_texture);
					break;
				case Pond::WATER_POND: ApplyTexture(displaySprites[i], LoadTexture::water_pond_texture, Vector2f(32, 32), Vector2f(1, 1), false, false);
					UpdateAnimation(displaySprites[i], LoadTexture::water_pond_texture);
					break;
				}

			displaySprites[i].setPosition(GetTopLeft(collider) + displayOffset + Vector2f(32 * i, 0));

			if (type == FIRE_POND || type == POISON_POND) {
				displaySprites[i].move(-2, 0);

				if (i != 0 && i != width - 1)
					displaySprites[i].move(0, -4);
			}

			window.draw(displaySprites[i]);

		}
		delete[] displaySprites;
	}
};
struct Box {
	Collider collider;
	Vector2f startPosition;
	Vector2f velocity = Vector2f(0, 0);
	float scale = 2.8f;

	float gravity = 500.0f;
	Collider::CollisionData playerCollisionData1;
	Collider::CollisionData playerCollisionData2;
	bool blocked = false;

	Box() {}
	Box(Vector2f position) {
		startPosition = position;
	}

	void Initialize() {
		collider = Collider(Collider::ColliderType::Rectangle, startPosition);
		ApplyTexture(collider.sprite, LoadTexture::movingbox_texture, Vector2f(32 * scale, 32 * scale));
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

	void CheckCollision(Player& player, Collider::CollisionData* boxCollisionDatas, int colliderCount, Collider::CollisionData& playerCollisionData) {
		Collider::CollisionData collisionData;
		float moveRatio;
		if (playerCollisionData1.collisionDirection == Collider::CollisionData::CollisionDirection::Left && playerCollisionData2.collisionDirection == Collider::CollisionData::CollisionDirection::Right) moveRatio = 0.0f;
		else if(playerCollisionData1.collisionDirection == Collider::CollisionData::CollisionDirection::Right && playerCollisionData2.collisionDirection == Collider::CollisionData::CollisionDirection::Left) moveRatio = 0.0f;
		else moveRatio = 1.0f;

		player.isOnGround |= collider.CheckCollision(player, collisionData, FloatRect(), moveRatio, false);
		playerCollisionData = collisionData;

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
		

		CheckCollision(fireBoy, boxCollisionDatas, colliders.count, playerCollisionData1);
		CheckCollision(waterGirl, boxCollisionDatas, colliders.count, playerCollisionData2);
		delete[] boxCollisionDatas;
	}

	void PreDraw() {
		Sprite displaySprite = collider.sprite;
		displaySprite.scale(1.1f, 1.1f);
		window.draw(displaySprite);
	}
};


struct TemporaryPlatform
{
	Collider collider;
	Sprite displaySprite;
	float displayScale = 1.2f;
	Vector2f startPosition;
	Vector2f startScale;
	bool collided = false;
	bool isVisible = true;
	float timer = 0.0f;

	TemporaryPlatform() {}
	TemporaryPlatform(Vector2f position) {
		startPosition = position;
	}


	void Initialize() {
		collider = Collider(Collider::ColliderType::Rectangle, startPosition, Vector2f(32 * 2, 32));
		ApplyTexture(collider.sprite, LoadTexture::RECTANGLE, Vector2f(32 * 2, 10), Vector2f(1, 1));
		ApplyTexture(displaySprite, LoadTexture::TEMPORARY_GROUND, Vector2f(1, 1), Vector2f(1, 1), true, false);
		displaySprite.scale(displayScale, displayScale);
		startScale = collider.sprite.getScale();
		collider.sprite.setPosition(startPosition);
		Allign(collider.sprite);
		SetSpriteSize(collider.sprite, Vector2f(displaySprite.getGlobalBounds().width-15, displaySprite.getGlobalBounds().height-15));
	}

	void ContinueTimer() {
		timer += dt;
	}

	void ResetTimer() {
		timer = 0.0f;
	}


	void Update(Player& player) {
		Collider::CollisionData collisionData;
		if (isVisible) {
			player.isOnGround |= collider.CheckCollision(player, collisionData);
		}

		// if the player stood on top of it, start the timer to disappear, if not collided reset the timer and make the ground appear again
		if (!collided)
		{
			if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top) {
				collided = true;
				ResetTimer();
				PlayGameSoundEffect(GameSoundEffect::Platform_sound); // change sound later
			}
		}
		else
		{
			// if player already collided, continue the timer and check if it's time to disappear
			ContinueTimer();

			if (timer >= 1.5f)
			{
				collider.sprite.setScale(0, 0);
				isVisible = false;
				collided = false;
				ResetTimer();
			}
		}

		if (!isVisible && !collided) {
			ContinueTimer();
			if (timer >= 5.0f) {
				collider.sprite.setScale(startScale);
				isVisible = true;
				ResetTimer();
				SetSpriteSize(collider.sprite, Vector2f(displaySprite.getGlobalBounds().width - 15, displaySprite.getGlobalBounds().height - 15));
			}
		}
	}

	void Draw() {
		if (isVisible)
		{
			//window.draw(collider.sprite);
			displaySprite.setPosition(collider.sprite.getPosition());
			window.draw(displaySprite);
		}
	}
};

struct Fan
{
	Sprite fan_sprite;
	Sprite air_sprite;
	Vector2f startPosition;
	float scale = 1.0f;
	float airForce = 300.0f;


	Fan() {}
	Fan(Vector2f position) {
		startPosition = position;
	}

	void Initialize() {
		ApplyTexture(fan_sprite, LoadTexture::wind_base_texture, Vector2f(32 * 2, 32 * 2), Vector2f(1, 1), false, false);
		ApplyTexture(air_sprite, LoadTexture::wind_effect_texture, Vector2f(32 * 2, 32 * 5), Vector2f(1, 1), false, false);

		UpdateAnimation(fan_sprite, wind_base_texture);
		UpdateAnimation(air_sprite, wind_effect_texture);
		SetSpriteOriginToCenter(fan_sprite);
		SetSpriteOriginToCenter(air_sprite);

		fan_sprite.setPosition(startPosition);
		air_sprite.setPosition(startPosition - Vector2f(0, air_sprite.getGlobalBounds().height / 2));
	}

	void Update(Player& player) {
		int reduction = 30; //reducing the hitbox of the air effect to avoid pushing the player when just touching the edge of the effect
		UpdateAnimation(fan_sprite, wind_base_texture);
		UpdateAnimation(air_sprite, wind_effect_texture);
		FloatRect air_intersection=air_sprite.getGlobalBounds();
		air_intersection.left +=reduction;
		air_intersection.width -= reduction * 2;
		air_intersection.top += reduction;
		air_intersection.height -= reduction * 2;
		if (air_intersection.intersects(player.hitbox.getGlobalBounds()))
			player.velocity.y -= airForce * dt;
	}

	void Draw() {
		window.draw(air_sprite);
		window.draw(fan_sprite);
		//window.draw(collider.sprite);7
	}
};

struct Snow {
	Sprite sprite;
	Vector2f startPosition;
	enum SnowState
	{
		Normal,
		LeftDown,
		RightDown
	} type;

	Snow(){}
	Snow(Vector2f position, SnowState startState) {
		startPosition = position;
		type = startState;
	}
	void Initialize() {
		sprite.setPosition(startPosition);

		switch (type)
		{
		case Snow::Normal:
			ApplyTexture(sprite, LoadTexture::snow_flat_texture, Vector2f(), Vector2f(), true, false);
			break;
		case Snow::LeftDown:
			ApplyTexture(sprite, LoadTexture::snow_slope_left_side_down_texture, Vector2f(), Vector2f(), true, false);
			break;
		case Snow::RightDown:
			ApplyTexture(sprite, LoadTexture::snow_slope_right_side_down_texture, Vector2f(), Vector2f(), true, false);
			break;
		}

		Allign(sprite);
		sprite.move(0, 10);

		if (type == Normal) sprite.move(-10, 4);
		if (type == LeftDown) sprite.move(-10, 10 - 32);
		if (type == RightDown) sprite.move(-5, 10 - 32);
	}

	void Update(Player& someone) {
		if (sprite.getGlobalBounds().intersects(someone.hitbox.getGlobalBounds())) {
			someone.isOnSnow = true;
		}
	}

	void Draw() {
		window.draw(sprite);
	}
};




// this is a generic object struct to have any level object
// how to add a new object
// 1. finish it's normal struct
// 2. add it in the ObjectData struct and add it to the copyFrom function
// 3. add a new enum for it in ObjectType enum
// 4. add an Initialize"enum name here" funtion for it		for ex: InitializeGemObject is just the construct of Gem + gem.Initialize() at it's end
// 5. add it's update and draw and checkInput functions to the switch cases of the Object struct if needed
// then god be with you when adding it to the level editor XD

struct ObjectData {
	Gem gem;
	Door door;
	Pond pond;
	Box box;
	TemporaryPlatform temporaryGround;
	Fan fan;
	Snow snow;


	bool CheckContainsPoint(Vector2f point) {
		if (gem.sprite.getGlobalBounds().contains(point))
			return true;
		if (door.displaySprite.getGlobalBounds().contains(point))
			return true;
		if (pond.collider.getGlobalBounds().contains(point))
			return true;
		if (box.collider.sprite.getGlobalBounds().contains(point))
			return true;
		if (temporaryGround.collider.sprite.getGlobalBounds().contains(point))
			return true;
		if (fan.fan_sprite.getGlobalBounds().contains(point))
			return true;
		if (snow.sprite.getGlobalBounds().contains(point))
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
		TemporaryGroundObject,
		FanObject,
		SnowObject
	} type;

	ObjectData data;

	Object() {} // empty constructor for ObjectList to work
	Object(ObjectType startType) {
		type = startType;
	}

	void InitializeGemObject(Gem::Gemtype crystaltype, Vector2f position) {
		data.gem.type = crystaltype;
		data.gem.Initialize();
		data.gem.sprite.setPosition(position);
		Allign(data.gem.sprite);
	}

	void InitializeDoorObject(Vector2f Initialize, Vector2f end, bool rotated) {
		data.door.rotated = rotated;
		data.door.startPosition = Initialize;
		data.door.Initialize();
		data.door.startPosition = data.door.displaySprite.getPosition();
		Allign(end);
		data.door.SetEndPosition(end, true);
	}

	void InitializePondObject(Pond::ponds_type startType, Vector2f position, int width) {
		data.pond.type = startType;
		data.pond.Initialize(width);
		data.pond.SetPosition(position);
		Allign(data.pond.collider);
		data.pond.InitializeColliders();
	}

	void InitializeBoxObject(Vector2f position) {
		data.box.startPosition = position;
		data.box.Initialize();
	}

	void InitializeTemporaryGroundObject(Vector2f position) {
		data.temporaryGround.startPosition = position;
		data.temporaryGround.Initialize();
	}

	void InitializeFanObject(Vector2f position) {
		data.fan.startPosition = position;
		data.fan.Initialize();
	}

	void InitializeSnowObject(Snow::SnowState state, Vector2f position) {
		data.snow.type = state;
		data.snow.startPosition = position;
		data.snow.Initialize();
	}

	/*bool CheckObjectCollision(Object other) {
		switch (type)
		{
		case Object::GemObject:
			switch (other.type)
			{
			case Object::GemObject:
				break;
			case Object::DoorObject:
				break;
			case Object::PondObject:
				break;
			case Object::BoxObject:
				break;
			default:
				break;
			}
			break;
		case Object::DoorObject:
			break;
		case Object::PondObject:
			break;
		case Object::BoxObject:
			break;
		default:
			break;
		}

		return false;
	}*/

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
			data.pond.Update(fireBoy, waterGirl);
			break;
		case Object::BoxObject: data.box.Update(fireBoy, waterGirl, colliders);
			break;
		case Object::DoorObject: data.door.Update(fireBoy, waterGirl);
			break;
		case Object::TemporaryGroundObject:
			data.temporaryGround.Update(fireBoy);
			data.temporaryGround.Update(waterGirl);
			break;
		case Object::SnowObject:
			data.snow.Update(fireBoy);
			data.snow.Update(waterGirl);
			break;
		case Object::FanObject:
			data.fan.Update(fireBoy);
			data.fan.Update(waterGirl);
			break;
		default:
			break;
		}
	}

	// draw behind the ground and the players
	void PreDraw() {
		switch (type)
		{
		case Object::DoorObject: data.door.PreDraw();
			break;
		case Object::TemporaryGroundObject: data.temporaryGround.Draw();
			break;
		}
	}

	// draw behind the players
	void MidDraw() {
		switch (type)
		{
		case Object::GemObject: window.draw(data.gem.sprite);
			break;
		case Object::SnowObject: data.snow.Draw();
			break;
		}
	}

	// draw on top of all the other objects
	void PostDraw() {
		switch (type)
		{
		case Object::PondObject: data.pond.Draw();
			break;
		case Object::BoxObject: data.box.PreDraw();
			break;
		case Object::DoorObject: data.door.PostDraw();
			break;
		case Object::FanObject: data.fan.Draw();
			break;
		}
	}
};


// just doing Object = another object gives an error for some reason
// so had to add a copy funtcion instaed
struct ObjectList {
	int count = 0;
	Object* elements;

	void Add(Object element) {
		
		if (count == 0)
		{
			count++;
			elements = new Object[count];
			elements[0] = element;
			return;
		}

		Object* temp = elements;

		count++;

		elements = new Object[count];

		for (int i = 0; i < count - 1; i++)
			elements[i] = temp[i];

		delete[] temp;

		elements[count - 1] = element;
	}

	void RemoveAt(int index) {
		if (count <= 0 || index < 0 || index >= count) return;

		Object* temp = elements;

		count--;

		elements = new Object[count];

		for (int i = 0; i < count; i++)
			if (i < index)
				elements[i] = temp[i];
			else
				elements[i] = temp[i + 1];

		delete[] temp;
	}

	Object& GetLastElement() {
		if (count == 0) {
			cout << "ObjectList is empty" << endl;
			exit(-2);
		}

		return elements[count - 1];
	}

	~ObjectList() {
		delete[] elements;
	}
};

struct TutorialTxt
{
	float fadeTime = 1.0f; // in seconds
	bool isIntersecting = false;
	float currentAlpha = 0;

	Text text;

	TutorialTxt(){}

	void Initialize(Font& font) {
		text.setFont(font);
		text.setCharacterSize(25);
		text.setFillColor(Color(230, 194, 0));
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setOutlineColor(Color::Black);
		text.setOutlineThickness(5);
	}

	void Update(Player& player1, Player& player2) {
		isIntersecting = false;

		if (text.getGlobalBounds().intersects(player1.hitbox.getGlobalBounds()))
			isIntersecting = true;

		if (text.getGlobalBounds().intersects(player2.hitbox.getGlobalBounds()))
			isIntersecting = true;

		if (isIntersecting)
			currentAlpha = currentAlpha + 255 * fadeTime * dt;
		else
			currentAlpha = currentAlpha - 255 * fadeTime * dt;

		currentAlpha = Clamp(currentAlpha, 0, 255);

		text.setFillColor(SetColorAlpha(text.getFillColor(), currentAlpha));
		text.setOutlineColor(SetColorAlpha(text.getOutlineColor(), currentAlpha));
	}

	void Draw() {
		window.draw(text);
	}
};

struct TutorialTxtList {
	int count = 0;
	TutorialTxt* elements;

	void Add(TutorialTxt element) {

		if (count == 0)
		{
			count++;
			elements = new TutorialTxt[count];
			elements[0] = element;
			return;
		}

		TutorialTxt* temp = elements;

		count++;

		elements = new TutorialTxt[count];

		for (int i = 0; i < count - 1; i++)
			elements[i] = temp[i];

		delete[] temp;

		elements[count - 1] = element;
	}

	void RemoveAt(int index) {
		if (count <= 0 || index < 0 || index >= count) return;

		TutorialTxt* temp = elements;

		count--;

		elements = new TutorialTxt[count];

		for (int i = 0; i < count; i++)
			if (i < index)
				elements[i] = temp[i];
			else
				elements[i] = temp[i + 1];

		delete[] temp;
	}

	TutorialTxt& GetLastElement() {
		if (count == 0) {
			cout << "TutorialTxtList is empty" << endl;
			exit(-2);
		}

		return elements[count - 1];
	}

	void Clear() {
		if (count > 0)
			delete[] elements;
	}

	~TutorialTxtList() {
		delete[] elements;
	}
} gameTutorials;
