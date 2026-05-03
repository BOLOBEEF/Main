
// GAME LOGIC





void InitializeGame()
{

}


void HandleGameInput(Event event)
{
	if (gameState != GAME) return;

	// code for handling game input that is related to game logic
	currentLevel.CheckInput(event);
}


void OnUpdatedGameStateGameLogic() {
	// do stuff here exactly when the gameState is changed

	currentLevel.OnUpdatedGameState();
}



void UpdateGame()
{
	if (gameState != GAME) return;

	if (levelLoadFailed) {
		UpdateGameState(MAIN_MENU);
		return;
	}

	currentLevel.Update();
}


void DrawGame(bool forceDraw)
{
	if (!forceDraw && gameState != GAME) return;
	// no need for window.clear or window.display

	if (!forceDraw && levelLoadFailed)
	{
		UpdateGameState(MAIN_MENU);
		return;
	}


	currentLevel.Draw();

	//for (int i = 0; i < colliders.count; i++)
		//window.draw(colliders.elements[i].sprite);
}