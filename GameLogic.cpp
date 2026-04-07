
// GAME LOGIC


// Settings :



// Structs and enums



// Runtime variables


// Functions


Player fireBoy = Player(Player::Fireboy, center + Vector2f(-50, -500));
Player waterGirl = Player(Player::Watergirl, center + Vector2f(50, -500));


#define colliderNum 3
Collider colliders[colliderNum] = {
	Collider(Collider::ColliderType::Rectangle, Vector2f(center.x + 0, center.y - 0)),
	Collider(Collider::ColliderType::Triangle, Vector2f(center.x - 200, center.y - 50)),
	Collider(Collider::ColliderType::Triangle_Rotated, Vector2f(center.x - 100, center.y - 50))
};


void CheckPlayerCollision(Player& player) {
	bool isOnGround = false;
	
	for (int i = 0; i < colliderNum; i++)
		isOnGround |= colliders[i].CheckCollision(player);
	
	player.isOnGround = isOnGround;
}

void InitializeGame()
{
	// code for initializing game variables and objects
	for (int i = 0; i < colliderNum; i++)
		colliders[i].Initialize();


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

	CheckPlayerCollision(fireBoy);
	CheckPlayerCollision(waterGirl);
}



void DrawGame()
{
	if (gameState != GAME) return;

	// no need for window.clear or window.display
	window.draw(fireBoy.sprite);
	window.draw(waterGirl.sprite);

	for (int i = 0; i < colliderNum; i++)
		window.draw(colliders[i].sprite);
}