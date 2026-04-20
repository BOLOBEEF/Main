
// GAME LOGIC



// Settings :



// Structs and enums
enum ponds_type
{
	FIRE_POND,
	WATER_SURFACE,
	POISON_POND
};




// Runtime variables
Player fireBoy = Player(Player::Fireboy, center + Vector2f(-600, 200));
Player waterGirl = Player(Player::Watergirl, center + Vector2f(-550, 300));

Temporary_ground temporaryground = Temporary_ground(center + Vector2f(0, 200));
FinalDoor water_door = FinalDoor(FinalDoor::WATER_DOOR, Vector2f(1200, 25));
FinalDoor fire_door = FinalDoor(FinalDoor::FIRE_DOOR, Vector2f(1300, 25));

Sprite ground;
Sprite background;

RenderTexture maskTexture;
RenderTexture resultTexture;
RenderTexture outlineTexture;
Sprite outlineSprite;
Sprite resultSprite;

ColliderList colliders;
ObjectList objects;
// Object object;


// LEVEL EDITING TOOLS
const bool enableEditMode = true;	// if true, you can place down objects by clicking, and remove them by right clicking, change object type by pressing 0 or 1 or....
Vector2f editScale = Vector2f(1, 1);
enum EditMode
{
	collider_mode,
	object_mode
} editMode;

enum EditObjectMode
{
	FireGem_mode,
	WaterGem_mode,
	Door_mode,
	Door_Rotated_mode,
	FirePond_mode,
	WaterPond_mode,
	PoisonPond_mode,
	Box_mode,
	Button_mode,
	Lever_mode,
} editObjectMode;
bool isEditingDoor = false;
int doorIndex = 0; // the door that is currently being edited



enum EditColliderMode
{
	Rectangle,
	Triangle,
	Triangle_Rotated,
};
EditColliderMode editColliderMode = EditColliderMode::Rectangle;


void CheckCollision(Player& player) {
	for (int i = 0; i < colliders.count; i++)
	{
		Collider::CollisionData collisionData;
		player.isOnGround |= colliders.elements[i].CheckCollision(player, collisionData);
		if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Slope)
			player.isOnSlope = true;
	}
}




void AllignColliders() {
	for (int i = 0; i < colliders.count; i++)
	{
		AllignSprite(colliders.elements[i].sprite);
	}
}

void LoadLevelData() {
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-432, 436), Vector2f(25, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(16, -524), Vector2f(53, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(480, 436), Vector2f(22, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-448, -236), Vector2f(22, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-576, 308), Vector2f(14, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-464, 180), Vector2f(21, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(256, 244), Vector2f(18, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-320, -44), Vector2f(18, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(336, -12), Vector2f(29, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(592, 20), Vector2f(13, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(752, 84), Vector2f(3, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, 52), Vector2f(7, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(176, -236), Vector2f(17, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(432, -204), Vector2f(11, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(272, -268), Vector2f(11, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-224, -364), Vector2f(6, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-704, -316), Vector2f(6, 4)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-336, -428), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-304, -428), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-272, -428), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-256, -396), Vector2f(4, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-176, -396), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(352, -364), Vector2f(30, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(848, 36), Vector2f(1, 34)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-816, -44), Vector2f(1, 29)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(768, 372), Vector2f(4, 3)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, 372), Vector2f(1, 3)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(768, 308), Vector2f(4, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(688, 308), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-656, 116), Vector2f(3, 3)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(784, -140), Vector2f(3, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(816, 36), Vector2f(1, 4)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-16, -44), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-752, 84), Vector2f(3, 5)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(464, -236), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(768, -76), Vector2f(4, 3)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(720, -140), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(688, -44), Vector2f(1, 1)));


	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(650, 800));
	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(800, 800));
	objects.Add(Object(Object::PondObject));
	objects.GetLastElement().InitializePondObject(Pond::POISON_POND, Vector2f(800, 600));
	objects.Add(Object(Object::PondObject));
	objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, Vector2f(600, 550));
	objects.Add(Object(Object::PondObject));
	objects.GetLastElement().InitializePondObject(Pond::WATER_POND, Vector2f(1000, 650));
	objects.Add(Object(Object::BoxObject));
	objects.GetLastElement().InitializeBoxObject(Vector2f(1100, 200));

	objects.Add(Object(Object::DoorObject));
	objects.GetLastElement().InitializeDoorObject(Vector2f(400.0f, 300.0f), Vector2f(400.0f, 200.0f));

	//objects.GetLastElement().data.door.button1 = Click(Vector2f(900, 800), true);
	//objects.GetLastElement().data.door.lever = Lever(Vector2f(1200, 800), true);
}


void UpdateOutlinesTexture() {
	const float outlineThickness = 3.0f;
	const int iterations = 8 * 4;						// number of directions

	float theta = 360 / iterations;


	outlineTexture.clear(Color::Transparent);
	Sprite outlineTest = Sprite(maskTexture.getTexture());
	outlineTest.setColor(Color::White);

	for (int i = 0; i < 360; i += theta)
		DrawSpriteWithOffset(outlineTest, outlineThickness * Vector2f(sin(i * DEGTORAD), cos(i * DEGTORAD)), outlineTexture);

	outlineTexture.display();
}

void UpdateGroundTexture() {

	// --- Step 1: Draw mask (small sprites) ---
	maskTexture.clear(Color::Transparent);

	for (int i = 0; i < colliders.count; i++)
	{
		maskTexture.draw(colliders.elements[i].sprite);
	}
	maskTexture.display();

	// update outlines too
	UpdateOutlinesTexture();


	// --- Step 2: Apply mask to background ---
	resultTexture.clear(Color::Transparent);
	resultTexture.draw(ground);

	// Draw mask using alpha blending to reveal background
	// general formula :
	// finalColor = (srcColor * srcFactor) + (dstColor * dstFactor)
	// finalAlpha = (srcAlpha * srcFactor) + (dstAlpha * dstFactor)
	// we want to take the color from the background (dst) only
	// and multiply it by the alpha of the mask (src) to make it only visible where the mask is drawn, and invisible where the mask is not drawn
	// finalColor = (srcColor * 0) + (dstColor * srcAlpha)
	// finalAlpha = (srcAlpha * 0) + (dstAlpha * srcAlpha)

	Sprite mask(maskTexture.getTexture());
	RenderStates maskStates;
	maskStates.blendMode = BlendMode(
		BlendMode::Factor::Zero,       // colorSrcFactor
		BlendMode::Factor::SrcAlpha,   // colorDstFactor
		BlendMode::Equation::Add,      // colorEquation
		BlendMode::Factor::Zero,       // alphaSrcFactor
		BlendMode::Factor::SrcAlpha,   // alphaDstFactor
		BlendMode::Equation::Add       // alphaEquation
	);
	resultTexture.draw(mask, maskStates);
	resultTexture.display();
}

void check_game_win()
{
	if (water_door.player_on_door && fire_door.player_on_door)
	{
		// end game
	}
}
void check_game_lose()
{
	if (waterGirl.isDead || fireBoy.isDead)
	{
		// end game
	}
}


void InitializeGame()
{
	LoadLevelData();


	// code for initializing game variables and objects
	for (int i = 0; i < colliders.count; i++)
		colliders.elements[i].Initialize();

	AllignColliders();
	fireBoy.Initialize();
	waterGirl.Initialize();
	
	

	ApplyTexture(ground, LoadTexture::GROUND, Vector2f(256, 256));
	ground.setTexture(groundTexture);
	ground.setTextureRect(IntRect(0, 0, windowSize.x, windowSize.y));

	ApplyTexture(background, LoadTexture::BACKGROUND, Vector2f(256, 256));
	background.setTexture(backgroundTexture);
	background.setTextureRect(IntRect(0, 0, windowSize.x, windowSize.y));


	maskTexture.create(windowSize.x, windowSize.y);
	outlineTexture.create(windowSize.x, windowSize.y);
	resultTexture.create(windowSize.x, windowSize.y);
	outlineSprite.setTexture(outlineTexture.getTexture());
	outlineSprite.setColor(Color(30, 30, 30));
	resultSprite.setTexture(resultTexture.getTexture());

	water_door.Initialilze();
	water_door.sprite.setColor(Color::Blue);
	fire_door.Initialilze();
	fire_door.sprite.setColor(Color::Red);

	temporaryground.Initialize();
	temporaryground.sprite.setColor(Color::Cyan);
	temporaryground.startPosition = center + Vector2f(112, 309);


	UpdateGroundTexture();
}

void PrintCollidersCode() {
	for (int i = 0; i < colliders.count; i++) {
		string type = (colliders.elements[i].type == Collider::ColliderType::Rectangle ? "Rectangle" : colliders.elements[i].type == Collider::ColliderType::Triangle ? "Triangle" : "Triangle_Rotated");
		string position = "Vector2f(" + to_string((int)(colliders.elements[i].sprite.getPosition().x - center.x)) + ", " + to_string((int)(colliders.elements[i].sprite.getPosition().y - center.y)) + ")";
		string scale = "Vector2f(" + to_string((int)colliders.elements[i].scale.x) + ", " + to_string((int)colliders.elements[i].scale.y) + ")";
		cout << "colliders.Add(Collider(Collider::ColliderType::" << type << ", center + " << position << ", " << scale << "));" << endl;
	}

}

void PrintObjectsCode() {
	cout << "START" << endl;
	PrintCollidersCode();
	cout << "END" << endl;
}

void Print(string message) {
	cout << message << endl;
}


void EditMode(Event event) {
	// EDITING MANUAL:
	// left click to add object, right click to remove object
	// numpad 4 and 6 to change x scale, numpad 2 and 8 to change y scale
	// 1, 2 and 3 to change object type
	// P to print code for all objects, O to undo last object placement
	// when placing objects, they will be alligned to a grid which is positioned relative to the center of the screen
	// Can't place objects on top of each other


	if (event.type == Event::MouseButtonPressed) {
		if (editMode == EditMode::collider_mode)
		{
			if (event.mouseButton.button == Mouse::Left) {
				// add object
				if (editScale.x <= 0) editScale.x = 1;
				if (editScale.y <= 0) editScale.y = 1;

				Collider collider;

				switch (editColliderMode)
				{
				case Rectangle:
					collider = Collider(Collider::ColliderType::Rectangle, mousePosition, editScale);
					collider.Initialize();
					break;
				case Triangle:
					collider = Collider(Collider::ColliderType::Triangle, mousePosition, editScale);
					collider.Initialize();
					break;
				case Triangle_Rotated:
					collider = Collider(Collider::ColliderType::Triangle_Rotated, mousePosition, editScale);
					collider.Initialize();
					break;
				default:
					break;
				}

				AllignSprite(collider.sprite);

				bool isColliding = false;
				for (int i = 0; i < colliders.count; i++)
					if (colliders.elements[i].sprite.getGlobalBounds().intersects(collider.sprite.getGlobalBounds())) {
						isColliding = true;
						break;
					}

				if (!isColliding) {
					colliders.Add(collider);
					UpdateGroundTexture();
				}
			}


			else if (event.mouseButton.button == Mouse::Right) {
				// remove object
				for (int i = 0; i < colliders.count; i++) {
					if (colliders.elements[i].sprite.getGlobalBounds().contains(mousePosition)) {
						colliders.RemoveAt(i);
						UpdateGroundTexture();
					}
				}
			}
		}
		else if (editMode == EditMode::object_mode)
		{
			// code for editing objects
			Print(isEditingDoor ? "Editing door..." : "Editing objects...");

			if (event.mouseButton.button == Mouse::Left)
				switch (editObjectMode)
				{
				case FireGem_mode:
					objects.Add(Object(Object::GemObject));
					objects.GetLastElement().InitializeGemObject(Gem::fireGem, mousePosition);
					break;
				case WaterGem_mode:
					objects.Add(Object(Object::GemObject));
					objects.GetLastElement().InitializeGemObject(Gem::waterGem, mousePosition);
					break;
				case Door_mode:
					objects.Add(Object(Object::DoorObject));
					objects.GetLastElement().InitializeDoorObject(mousePosition, mousePosition + Vector2f(0, -100));
					break;
				case Door_Rotated_mode:
					objects.Add(Object(Object::DoorObject));
					objects.GetLastElement().data.door.rotated = true;
					objects.GetLastElement().InitializeDoorObject(mousePosition, mousePosition + Vector2f(0, -100));
					break;
				case FirePond_mode:
					objects.Add(Object(Object::PondObject));
					objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, mousePosition);
					break;
				case WaterPond_mode:
					objects.Add(Object(Object::PondObject));
					objects.GetLastElement().InitializePondObject(Pond::WATER_POND, mousePosition);
					break;
				case PoisonPond_mode:
					objects.Add(Object(Object::PondObject));
					objects.GetLastElement().InitializePondObject(Pond::POISON_POND, mousePosition);
					break;
				case Box_mode:
					objects.Add(Object(Object::BoxObject));
					objects.GetLastElement().InitializeBoxObject(mousePosition);
					break;
				case Button_mode:
					if (isEditingDoor)
					if (objects.elements[doorIndex].type == Object::DoorObject)
					if (!objects.elements[doorIndex].data.door.button1.initialized)
						objects.elements[doorIndex].data.door.button1 = Click(mousePosition, true);
					else if (!objects.elements[doorIndex].data.door.button2.initialized)
						objects.elements[doorIndex].data.door.button2 = Click(mousePosition, true);
					else
					{
						objects.elements[doorIndex].data.door.button1 = Click(mousePosition, true);
						objects.elements[doorIndex].data.door.button2.initialized = false;
					}
					break;
				case Lever_mode:
					if (isEditingDoor)
					if (objects.elements[doorIndex].type == Object::DoorObject)
					if (!objects.elements[doorIndex].data.door.lever.initialized)
						objects.elements[doorIndex].data.door.lever = Lever(mousePosition, true);
					break;
				}
			else if (event.mouseButton.button == Mouse::Right)
				// remove object
				for (int i = 0; i < objects.count; i++)
					if (objects.elements[i].data.CheckContainsPoint(mousePosition))
						objects.RemoveAt(i);
		}
	}

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::I) {
			// switch edit mode
			if (editMode == EditMode::collider_mode)
				editMode = EditMode::object_mode;
			else if (editMode == EditMode::object_mode)
				editMode = EditMode::collider_mode;
		}

		if (event.key.code == Keyboard::P) {
			// print objects code
			PrintObjectsCode();
		}

		if (editMode == EditMode::collider_mode)
		{
			isEditingDoor = false;

			if (event.key.code == Keyboard::O) {
				// undo last object placement
				colliders.RemoveAt(colliders.count - 1);
				UpdateGroundTexture();
			}

			if (event.key.code == Keyboard::Numpad4)
				// undo last object placement
				editScale.x--;
			if (event.key.code == Keyboard::Numpad6)
				// undo last object placement
				editScale.x++;
			if (event.key.code == Keyboard::Numpad2)
				// undo last object placement
				editScale.y--;
			if (event.key.code == Keyboard::Numpad8)
				// undo last object placement
				editScale.y++;


			if (event.key.code == Keyboard::Num1)
				editColliderMode = EditColliderMode::Rectangle;

			if (event.key.code == Keyboard::Num2)
				editColliderMode = EditColliderMode::Triangle;

			if (event.key.code == Keyboard::Num3)
				editColliderMode = EditColliderMode::Triangle_Rotated;
		}
		else if (editMode == EditMode::object_mode)
		{
			if (event.key.code == Keyboard::O) {
				// undo last object placement
				objects.RemoveAt(objects.count - 1);
			}

			if (event.key.code == Keyboard::U) {
				// add button or lever to door
				for (int i = 0; i < objects.count; i++)
					if (objects.elements[i].data.CheckContainsPoint(mousePosition) && objects.elements[i].type == Object::DoorObject)
					{
						isEditingDoor = true;
						editObjectMode = EditObjectMode::Button_mode;
						doorIndex = i;
						Print("Editing door at index " + to_string(doorIndex));
					}
			}

			if (event.key.code == Keyboard::X) {
				// exit edit door mode
				isEditingDoor = false;
			}

			// code for editing objects

			if (!isEditingDoor) {
				if (event.key.code == Keyboard::Num1)
					editObjectMode = EditObjectMode::FireGem_mode;

				if (event.key.code == Keyboard::Num2)
					editObjectMode = EditObjectMode::WaterGem_mode;

				if (event.key.code == Keyboard::Num3)
					editObjectMode = EditObjectMode::PoisonPond_mode;

				if (event.key.code == Keyboard::Num4)
					editObjectMode = EditObjectMode::FirePond_mode;

				if (event.key.code == Keyboard::Num5)
					editObjectMode = EditObjectMode::WaterPond_mode;

				if (event.key.code == Keyboard::Num6)
					editObjectMode = EditObjectMode::Door_mode;

				if (event.key.code == Keyboard::Num7)
					editObjectMode = EditObjectMode::Door_Rotated_mode;

				if (event.key.code == Keyboard::Num8)
					editObjectMode = EditObjectMode::Box_mode;
			}
			else {
				if (event.key.code == Keyboard::Num1)
					editObjectMode = EditObjectMode::Button_mode;
				if (event.key.code == Keyboard::Num2)
					editObjectMode = EditObjectMode::Lever_mode;
			}
		}
	}

}


void HandleGameInput(Event event)
{
	if (gameState != GAME) return;

	// code for handling game input that is related to game logic
	fireBoy.CheckInput(event);
	waterGirl.CheckInput(event);
	for (int i = 0; i < objects.count; i++)
		objects.elements[i].CheckInput(fireBoy, waterGirl, event);

	// in debug mode, when you press
	if (!enableEditMode) return;
	EditMode(event);
}

void OnUpdatedGameStateGameLogic() {
	// do stuff here exactly when the gameState is changed
	if (gameState != GAME) return;

}


void UpdateGame()
{
	if (gameState != GAME) return;
	if (fireBoy.isDead || waterGirl.isDead) {
		UpdateGameState(GAMEOVER);
		return;
	}

	fireBoy.Update();
	waterGirl.Update();

	if (fireBoy.isOnGround) fireBoy.sprite.setColor(Color::Red);
	else fireBoy.sprite.setColor(Color(255, 100, 100));
	if (waterGirl.isOnGround) waterGirl.sprite.setColor(Color::Blue);
	else waterGirl.sprite.setColor(Color(100, 100, 255));


	CheckCollision(fireBoy);
	CheckCollision(waterGirl);

	for (int i = 0; i < objects.count; i++)
		objects.elements[i].Update(fireBoy, waterGirl, colliders);


	water_door.Update(waterGirl);
	fire_door.Update(fireBoy);

	if (fireBoy.isDead)
		fireBoy.sprite.setColor(Color::Yellow);
	else 
		fireBoy.sprite.setColor(Color::Red);


	if (waterGirl.isDead)
		waterGirl.sprite.setColor(Color::Yellow);
	else
		waterGirl.sprite.setColor(Color::Blue);

	if (water_door.player_on_door && fire_door.player_on_door)
	{
		water_door.sprite.setColor(Color(128, 0, 128));
		fire_door.sprite.setColor(Color(128, 0, 128));
	}
	temporaryground.CheckCollision(fireBoy,temporaryground);
	//temporaryground.CheckCollision(waterGirl,temporaryground);
	temporaryground.update(fireBoy, temporaryground);
	temporaryground.update(waterGirl, temporaryground);
}


void DrawGame(bool forceDraw)
{
	if (!forceDraw && gameState != GAME) return;

	// no need for window.clear or window.display
	window.draw(background);
	window.draw(outlineSprite);
	window.draw(resultSprite);

	for (int i = 0; i < objects.count; i++)
		objects.elements[i].PreDraw();



	window.draw(fireBoy.sprite);
	window.draw(waterGirl.sprite);

	window.draw(water_door.sprite);
	window.draw(fire_door.sprite);

	window.draw(temporaryground.sprite);

	for (int i = 0; i < objects.count; i++)
		objects.elements[i].PostDraw();
}