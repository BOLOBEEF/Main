
// TESTING
FinalDoor door = FinalDoor(FinalDoor::FIRE_DOOR, Vector2f(1200, 25));
// this is a script just for testing out functions or logic
// when you add a new function and u want to test it, you can call the function from here

void InitializeTest() {
	// for example test if a sound function is working here
	// PlayMusic(BackgroundMusic::MainMenu);
	// test push
	ApplyTexture(door.sprite, LoadTexture::fire_door_open_texture, Vector2f(80, 80));
}

void HandleTestInput(Event event)
{


}

void OnUpdatedGameStateTest() {


}

void UpdateTest()
{
	DoorUpdateAnimation(door);
	
}

void DrawTest() {
	
	// for example test if a sound function is working here
	// PlayMusic(BackgroundMusic::MainMenu);
	window.draw(door.sprite);
	
}