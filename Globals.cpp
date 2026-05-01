// GLOBAL VARIABLES


// variables that are used across multiple files and functions

RenderWindow window = { VideoMode::getDesktopMode(), "SFML" };
Vector2u windowSize = window.getSize();
Vector2f center = Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);

Clock globalClock;
Clock dtClock;
float dt = 0.0f;
Vector2f mousePosition;
bool levelLoadFailed = false; // if true, return to main menu instead of loading level



// Function Declarations

// Audio
void InitializeAudio();

// menu
void RatingCheck(bool maleAndFemale_case, bool DiamondCollection_case, bool BeforeTimeOut_case);
void InitializeMenu();
void HandleMenuInput(Event event);
void OnUpdatedGameStateMenu();
void UpdateUI();
void DrawUI();

// game logic
void InitializeGame();
void HandleGameInput(Event event);
void OnUpdatedGameStateGameLogic();
void UpdateGame();
void DrawGame(bool forceDraw);

// Animations
void InitializeAnimations();
void HandleAnimationsInput(Event event);
void UpdateAnimations();

// Textures
void InitializeTextures();

// Testing
void InitializeTest();
void HandleTestInput(Event event);
void OnUpdatedGameStateTest();
void UpdateTest();
void DrawTest();




// Game flow:

// Main GameState 
enum GameState
{
	MAIN_MENU,
	LEVEL_MENU,
	PAUSE_MENU,
	WIN_MENU,
	SETTINGS,
	GAMEOVER,
	CREDITS,
	GAME			// this is the in-game UI, not the game logic
};


// DO NOT CHANGE THIS DIRECTLY, USE UpdateGameState() INSTEAD
GameState gameState = LEVEL_MENU;
GameState lastGameState = gameState;	// used to keep track of the last game state


void UpdateGameState(GameState newState, bool ForceUpdate);



void Initialize()
{
	InitializeTextures();
	InitializeAnimations();
	InitializeAudio();
	InitializeMenu();
	InitializeGame();
	InitializeTest();
	UpdateGameState(gameState, true);
}

void HandleInput(Event event)
{
	HandleMenuInput(event);
	HandleGameInput(event);
	HandleAnimationsInput(event);
	HandleTestInput(event);
}

void UpdateGameState(GameState newState, bool ForceUpdate = false)
{
	// if didn't actually change gameState then skip
	if (newState == gameState && !ForceUpdate) return;

	lastGameState = gameState;

	if (!levelLoadFailed)
		gameState = newState;
	else
		gameState = MAIN_MENU;

	OnUpdatedGameStateMenu();
	OnUpdatedGameStateGameLogic();
	OnUpdatedGameStateTest();
}

void UpdateGlobals() {

	// deltaTime
	dt = dtClock.restart().asSeconds();
	if (dt > 0.05f) dt = 0.05f;	// fix player stutter when moving the window around, by capping deltaTime to a maximum value

	Vector2i pixelPos = Mouse::getPosition(window);
	mousePosition = window.mapPixelToCoords(pixelPos);	// fix mouse position not updating when the window is resized by using mapPixelToCoords instead of getPosition


	UpdateUI();
	UpdateGame();
	UpdateTest();
}

void Draw()
{
	DrawGame(false);
	DrawUI();
	DrawTest();
}