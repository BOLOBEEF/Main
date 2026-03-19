// all levels data here


struct Level
{
	// store all the variables related to a level here, for example:
	int currentLevelIndex = 0;

	// background music enum
	// ground texture enum
	// array of rectangleShapes for collision detection
	// 2 positions for player spawns
	// 2 goal doors
	// gems
	// ponds of type -> water or lava or poison
	// buttons connected to doors
	// levers connected to doors
	// fans and so on

	// and so on, you can add more things as you see fit
	// now how to store those variables?

	// most of those are expected to be arrays of structs


	// first we need to make empty arrays for every possible variable, then we can fill those arrays with the actual data for each level
	// still not sure if they would allow using vectors instead of arrays, but I will try to use vectors if possible since they are more flexible and easier to work with
	// Ex: Gem gems[10]; // empty array for gems
	// Collider colliders[20]; // empty array for colliders

	// then to add actual data for each level, in the constructor of the Level struct, we can fill those arrays with the actual data for each level based on the provided level index

	Level(int levelIndex)
	{
		LoadLevelData(levelIndex);
	}

	void LoadLevelData(int levelIndex) {
		currentLevelIndex = levelIndex;
		// based on the level index, fill the arrays with the actual data for each level
		switch (levelIndex)
		{
		case 1:	Level1();	break;
		case 2: Level2();	break;

		default:
			cout << "Invalid level index: " << levelIndex << endl;
			break;
		}
	}


	// LEVEL DATA :
	void Level1()
	{
		// fill the arrays with the actual data for level 1
	}

	void Level2()
	{
		// fill the arrays with the actual data for level 1
	}

	// RESTART CURRENT LEVEL
	void ResetLevel()
	{
		// reset the level to its initial state, for example when the player dies or restarts the level
		EraseData();
		LoadLevelData(currentLevelIndex);
	}

	void EraseData()
	{
		// erase the level data
		// reset all arrays to be empty
	}


	// LOAD A NEW LEVEL
	void LoadNewLevel(int levelIndex)
	{
		// reset the level to its initial state, for example when the player dies or restarts the level
		EraseData();
		LoadLevelData(levelIndex);
	}
};

// we make actual level objects here, and we can access them in the game logic when we need to load a level
Level currentLevel(1); // start at level 1
//currentLevel.LoadNewLevel(2); // load level 2
//currentLevel.LoadNewLevel(currentLevel.currentLevelIndex + 1); // load the next level