// GLOBAL VARIABLES


// variables that are used across multiple files and functions

RenderWindow window = { VideoMode::getDesktopMode(), "SFML" };
Vector2u windowSize = window.getSize();
Vector2f center = Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);

Clock globalClock;
Clock dtClock;
float dt = 0.0f;
Vector2f mousePosition;


// Function Declarations

// menu
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
void DrawGame();

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
	SETTINGS,
	GAMEOVER,
	GAME			// this is the in-game UI, not the game logic
};


// DO NOT CHANGE THIS DIRECTLY, USE UpdateGameState() INSTEAD
GameState gameState = GAME;





void Initialize()
{
	InitializeTextures();
	InitializeAnimations();
	InitializeMenu();
	InitializeGame();
	InitializeTest();
}

void HandleInput(Event event)
{
	HandleMenuInput(event);
	HandleGameInput(event);
	HandleAnimationsInput(event);
	HandleTestInput(event);
}

void UpdateGameState(GameState newState)
{
	// if didn't actually change gameState then skip
	if (newState == gameState) return;

	gameState = newState;

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
	DrawUI();
	DrawGame();
	DrawTest();
}