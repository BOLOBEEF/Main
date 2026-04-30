
// GAME LOGIC



// Settings :



// Structs and enums




// Object object;


void InitializeGame()
{
	currentLevel.LoadNewLevel(2);
}


void HandleGameInput(Event event)
{
	if (gameState != GAME) return;

	// code for handling game input that is related to game logic
	currentLevel.CheckInput(event);
}

// temporary restart function
void RestartGame() {
	// Load Data
	currentLevel.ResetLevel();
}


void OnUpdatedGameStateGameLogic() {
	// do stuff here exactly when the gameState is changed
	if (gameState == GAMEOVER) {
		//RestartGame();
		return;
	}

	if (gameState != GAME) return;

	if (fireBoy.isDead || waterGirl.isDead) {
		//UpdateGameState(GAMEOVER);
		return;
	}
}



void UpdateGame()
{
	if (gameState != GAME) return;
	currentLevel.Update();
}


void DrawGame(bool forceDraw)
{
	if (!forceDraw && gameState != GAME) return;
	// no need for window.clear or window.display

	currentLevel.Draw();

	//for (int i = 0; i < colliders.count; i++)
		//window.draw(colliders.elements[i].sprite);
}