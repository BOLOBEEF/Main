
// TESTING
Sprite testSprite;
// test


// this is a script just for testing out functions or logic
// when you add a new function and u want to test it, you can call the function from here

void InitializeTest() {
	// for example test if a sound function is working here
	// PlayMusic(BackgroundMusic::MainMenu);
	// test push
}

void HandleTestInput(Event event)
{


}

void OnUpdatedGameStateTest() {


}

void UpdateTest()
{
	ApplyTexture(testSprite, LoadTexture::lever_stick_texture, Vector2f(100.0f, 100.0f));
	UpdateAnimation(testSprite, LoadTexture::lever_stick_texture);
	testSprite.setPosition(400.0f, 200.0f);


}

void DrawTest() {
	// for example test if a sound function is working here
	// PlayMusic(BackgroundMusic::MainMenu);
	window.draw(testSprite);

}