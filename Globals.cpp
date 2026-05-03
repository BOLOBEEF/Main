// GLOBAL VARIABLES


// variables that are used across multiple files and functions

RenderWindow window = { VideoMode::getDesktopMode(), "SFML", Style::Fullscreen};
Vector2u windowSize = window.getSize();
View gameCamera = window.getDefaultView();
Vector2f center = Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);
bool isFullscreen = true;


void InitializeWindow() {
	// input issues: key repeat is enabled by default, which causes problems with our input handling, so we disable it
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true); // makes the game feel more consistent, not needed as all our logic is framerate-independent
	window.setMouseCursorVisible(false); // hides the original cursor
}
void ToggleFullscreen() {
	isFullscreen = !isFullscreen;
	if (isFullscreen)
		window.create(VideoMode::getDesktopMode(), "SFML", Style::Fullscreen);
	else
		window.create(VideoMode::getDesktopMode(), "SFML");

	InitializeWindow();
}


Clock globalClock;
Clock dtClock;
float dt = 0.0f;
Vector2f mousePosition;
Vector2f cameraMousePosition;
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
GameState gameState = MAIN_MENU;
GameState lastGameState = gameState;	// used to keep track of the last game state


void UpdateGameState(GameState newState, bool ForceUpdate);



void Initialize()
{
	InitializeWindow();
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
	if (event.type == Event::KeyPressed)
		if (event.key.code == Keyboard::F11)
			ToggleFullscreen();


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
	cameraMousePosition = window.mapPixelToCoords(pixelPos, gameCamera);


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