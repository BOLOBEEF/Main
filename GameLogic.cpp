
// GAME LOGIC


// Settings :



// Structs and enums



// Runtime variables
Sprite player;


// Functions

void InitializeGame()
{
	// code for initializing game variables and objects
}

void HandleGameInput(Event event)
{
	// code for handling game input that is related to game logic
}


void UpdateGame()
{
	// Game logic
	Vector2f mousePos = Vector2f(Mouse::getPosition(window));
	player.setPosition(Damp(player.getPosition().x, mousePos.x, 1000.0f, dt), Damp(player.getPosition().y, mousePos.y, 1000.0f, dt));

	if (player.getGlobalBounds().contains(mousePos))
		player.setColor(Color::Red);
	else
		player.setColor(Color::White);
	//sprite.setPosition(mousePos);
}

void DrawGame()
{
	if (gameState != GAME) return;

	// no need for window.clear or window.display
	window.draw(player);
}
