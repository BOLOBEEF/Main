// GLOBAL VARIABLES


// variables that are used across multiple files and functions

RenderWindow window = { VideoMode::getDesktopMode(), "SFML" };
Vector2u windowSize = window.getSize();
Vector2f center = Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);

Clock globalClock;
Clock dtClock;
float dt = 0.0f;


// Main GameState 
enum GameState
{
	MAIN_MENU,
	SETTINGS,
	GAME			// this is the in-game UI, not the game logic
};

GameState gameState = GAME;


// Game flow


// Function Declarations

// menu
void InitializeMenu();
void HandleMenuInput(Event event);
void UpdateUI();
void DrawUI();

// game logic
void InitializeGame();
void HandleGameInput(Event event);
void UpdateGame();
void DrawGame();



void Initialize()
{
	InitializeMenu();
	InitializeGame();
}

void HandleInput(Event event)
{
	HandleMenuInput(event);
	HandleGameInput(event);
}

void UpdateGlobals() {

	// deltaTime
	dt = dtClock.restart().asSeconds();

	UpdateUI();
	UpdateGame();
}

void Draw()
{
	DrawUI();
	DrawGame();
}