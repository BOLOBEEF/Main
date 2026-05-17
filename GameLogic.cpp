
// GAME LOGIC





void InitializeGame()
{

}


void HandleGameInput(Event event)
{
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::F2)
	{
		developerMode = !developerMode;

		if (developerMode)
			cout << "Entered developer mode" << endl;
		else
			cout << "Exited developer mode" << endl;
	}

	if (developerMode)
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::F10)
	{
		ClearPlayerProgress();
		if (gameState == LEVEL_MENU)
			UpdateGameState(LEVEL_MENU, true);
	}


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

	cameraMousePosition.x += 16;
	currentLevel.Update();
}


void DrawGame(bool forceDraw)
{
	if (!forceDraw && (gameState != GAME))// && gameState != LevelEditor)) return;
		return;
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