
// GAME LOGIC



// Settings :



// Structs and enums


// Runtime variables
Player fireBoy = Player(Fireboy, Vector2f());
Player waterGirl = Player(Watergirl, Vector2f());
FinalDoor water_door = FinalDoor(FinalDoor::WATER_DOOR, Vector2f());
FinalDoor fire_door = FinalDoor(FinalDoor::FIRE_DOOR, Vector2f());

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
int editPondWidth = 5;
int editPondWidthMinimum = 4;

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
	Door_Target_mode,
	Door_Rotated_mode,
	FirePond_mode,
	WaterPond_mode,
	PoisonPond_mode,
	Box_mode,
	Button_mode,
	Lever_mode,
	TemporaryGround_mode,
	FanObject_mode
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
		if (colliders.elements[i].editable) {
			Allign(colliders.elements[i].sprite);
		}
	}
}

void LoadLevelData() {
	fireBoy = Player(Fireboy, Vector2f(260, 931));
	waterGirl = Player(Watergirl, Vector2f(257, 805));
	water_door = FinalDoor(FinalDoor::WATER_DOOR, Vector2f(1576, 120));
	fire_door = FinalDoor(FinalDoor::FIRE_DOOR, Vector2f(1500, 114));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-432, 436), Vector2f(25, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(16, -524), Vector2f(53, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(752, 84), Vector2f(3, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, 52), Vector2f(7, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-224, -364), Vector2f(6, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-304, -428), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-272, -428), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-256, -396), Vector2f(4, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-176, -396), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(848, 36), Vector2f(1, 34)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-816, -44), Vector2f(1, 29)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(768, 372), Vector2f(4, 3)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, 372), Vector2f(1, 3)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(768, 308), Vector2f(4, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(688, 308), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(192, 436), Vector2f(4, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(624, 436), Vector2f(13, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-592, 308), Vector2f(13, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-480, 148), Vector2f(20, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-96, 180), Vector2f(4, 3)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-64, 244), Vector2f(2, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(48, 244), Vector2f(5, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(368, 244), Vector2f(5, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(496, 244), Vector2f(3, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(560, 244), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(400, 20), Vector2f(25, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-304, -12), Vector2f(23, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(80, -12), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(816, -76), Vector2f(1, 15)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(352, -364), Vector2f(30, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-432, -172), Vector2f(23, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(304, -172), Vector2f(23, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(512, -140), Vector2f(10, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(256, -220), Vector2f(10, 2)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(448, -220), Vector2f(2, 2)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-224, -316), Vector2f(6, 2)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-736, -252), Vector2f(4, 4)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-640, -220), Vector2f(2, 2)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-352, -412), Vector2f(2, 2)));
	objects.Add(Object(Object::PondObject));
	objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, Vector2f(1008, 976), 5);
	objects.Add(Object(Object::PondObject));
	objects.GetLastElement().InitializePondObject(Pond::WATER_POND, Vector2f(1296, 976), 5);
	objects.Add(Object(Object::PondObject));
	objects.GetLastElement().InitializePondObject(Pond::POISON_POND, Vector2f(1168, 784), 5);
	objects.Add(Object(Object::DoorObject));
	objects.GetLastElement().InitializeDoorObject(Vector2f(224, 528), Vector2f(224, 640));
	objects.GetLastElement().data.door.lever = Lever(Vector2f(515, 659), true);
	objects.Add(Object(Object::DoorObject));
	objects.GetLastElement().InitializeDoorObject(Vector2f(1696, 400), Vector2f(1696, 512));
	objects.GetLastElement().data.door.button1 = Click(Vector2f(517, 500), true);
	objects.GetLastElement().data.door.button2 = Click(Vector2f(1544, 340), true);
	objects.Add(Object(Object::BoxObject));
	objects.GetLastElement().InitializeBoxObject(Vector2f(498, 307));
	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(1000, 904));
	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(360, 456));
	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1288, 904));
	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1128, 488));
	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(232, 168));
	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1224, 136));
	objects.Add(Object(Object::GemObject));
	objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(648, 72));
	objects.Add(Object(Object::FanObject));
	objects.GetLastElement().InitializeFanObject(center);
}


void UpdateOutlinesTexture() {
	const float outlineThickness = 5.0f;
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


	// add all colliders
	for (int i = 0; i < colliders.count; i++)
		maskTexture.draw(colliders.elements[i].sprite);

	// also add the ponds mask
	for (int i = 0; i < objects.count; i++)
		if (objects.elements[i].type == Object::PondObject)
		{
			maskTexture.draw(objects.elements[i].data.pond.startColl.sprite);
			maskTexture.draw(objects.elements[i].data.pond.midColl.sprite);
			maskTexture.draw(objects.elements[i].data.pond.endColl.sprite);
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
	if (water_door.currentFrame == 21 && fire_door.currentFrame == 21)
	{
		UpdateGameState(WIN_MENU);
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
	outlineSprite.setColor(Color::Black);
	resultSprite.setTexture(resultTexture.getTexture());

	water_door.Initialize();
	fire_door.Initialize();

	UpdateGroundTexture();
}

void PrintLevelData() {
	// player data
	cout << "fireBoy = Player(Fireboy, Vector2f(" << (int)fireBoy.startPosition.x << ", " << (int)fireBoy.startPosition.y << "));" << endl;
	cout << "waterGirl = Player(Watergirl, Vector2f(" << (int)waterGirl.startPosition.x << ", " << (int)waterGirl.startPosition.y << "));" << endl;
	// door data
	cout << "water_door = FinalDoor(FinalDoor::WATER_DOOR, Vector2f(" << (int)water_door.startPosition.x << ", " << (int)water_door.startPosition.y << "));" << endl;
	cout << "fire_door = FinalDoor(FinalDoor::FIRE_DOOR, Vector2f(" << (int)fire_door.startPosition.x << ", " << (int)fire_door.startPosition.y << "));" << endl;
	for (int i = 0; i < colliders.count; i++) {
		string type = (colliders.elements[i].type == Collider::ColliderType::Rectangle ? "Rectangle" : colliders.elements[i].type == Collider::ColliderType::Triangle ? "Triangle" : "Triangle_Rotated");
		string position = "Vector2f(" + to_string((int)(colliders.elements[i].sprite.getPosition().x - center.x)) + ", " + to_string((int)(colliders.elements[i].sprite.getPosition().y - center.y)) + ")";
		string scale = "Vector2f(" + to_string((int)colliders.elements[i].scale.x) + ", " + to_string((int)colliders.elements[i].scale.y) + ")";
		cout << "colliders.Add(Collider(Collider::ColliderType::" << type << ", center + " << position << ", " << scale << "));" << endl;
	}

	for (int i = 0; i < objects.count; i++) {
		string type;
		string position;
		string extraData;
		switch (objects.elements[i].type)
		{
		case Object::GemObject:
			type = (objects.elements[i].data.gem.type == Gem::fireGem ? "FireGem_mode" : "WaterGem_mode");
			position = "Vector2f(" + to_string((int)objects.elements[i].data.gem.sprite.getPosition().x) + ", " + to_string((int)objects.elements[i].data.gem.sprite.getPosition().y) + ")";
			cout << "objects.Add(Object(Object::GemObject));" << endl;
			cout << "objects.GetLastElement().InitializeGemObject(Gem::" << (objects.elements[i].data.gem.type == Gem::fireGem ? "fireGem" : "waterGem") << ", " << position << ");" << endl;
			break;
		case Object::DoorObject:
			type = (objects.elements[i].data.door.rotated ? "Door_Rotated_mode" : "Door_mode");
			position = "Vector2f(" + to_string((int)objects.elements[i].data.door.startPosition.x) + ", " + to_string((int)objects.elements[i].data.door.startPosition.y) + ")";
			extraData = "Vector2f(" + to_string((int)(objects.elements[i].data.door.endPosition.x)) + ", " + to_string((int)(objects.elements[i].data.door.endPosition.y)) + ")";
			cout << "objects.Add(Object(Object::DoorObject));" << endl;
			cout << "objects.GetLastElement().InitializeDoorObject(" << position << ", " << extraData << ");" << endl;
			if (objects.elements[i].data.door.button1.initialized)
				cout << "objects.GetLastElement().data.door.button1 = Click(Vector2f(" << (int)objects.elements[i].data.door.button1.initialPosition.x << ", " << (int)objects.elements[i].data.door.button1.initialPosition.y << "), true);" << endl;
			if (objects.elements[i].data.door.button2.initialized)
				cout << "objects.GetLastElement().data.door.button2 = Click(Vector2f(" << (int)objects.elements[i].data.door.button2.initialPosition.x << ", " << (int)objects.elements[i].data.door.button2.initialPosition.y << "), true);" << endl;
			if (objects.elements[i].data.door.lever.initialized)
				cout << "objects.GetLastElement().data.door.lever = Lever(Vector2f(" << (int)objects.elements[i].data.door.lever.initialPosition.x << ", " << (int)objects.elements[i].data.door.lever.initialPosition.y << "), true);" << endl;
			break;
		case Object::PondObject:
			if (objects.elements[i].data.pond.type == Pond::FIRE_POND)
				type = "FIRE_POND";
			else if (objects.elements[i].data.pond.type == Pond::WATER_POND)
				type = "WATER_POND";
			else
				type = "POISON_POND";
			position = "Vector2f(" + to_string((int)objects.elements[i].data.pond.collider.getPosition().x) + ", " + to_string((int)objects.elements[i].data.pond.collider.getPosition().y) + ")";
			extraData = to_string(objects.elements[i].data.pond.width);
			cout << "objects.Add(Object(Object::PondObject));" << endl;
			cout << "objects.GetLastElement().InitializePondObject(Pond::" << type << ", " << position << ", " << extraData << ");" << endl;
			break;
		case Object::BoxObject:
			cout << "objects.Add(Object(Object::BoxObject));" << endl;
			cout << "objects.GetLastElement().InitializeBoxObject(Vector2f(" << (int)objects.elements[i].data.box.collider.sprite.getPosition().x << ", " << (int)objects.elements[i].data.box.collider.sprite.getPosition().y << "));" << endl;
			break;
		case Object::TemporaryGroundObject:
			cout << "objects.Add(Object(Object::TemporaryGroundObject));" << endl;
			cout << "objects.GetLastElement().InitializeTemporaryGroundObject(Vector2f(" << (int)objects.elements[i].data.temporaryGround.collider.sprite.getPosition().x << ", " << (int)objects.elements[i].data.temporaryGround.collider.sprite.getPosition().y << "));" << endl;
			break;
		case Object::FanObject:
			cout << "objects.Add(Object(Object::FanObject));" << endl;
			cout << "objects.GetLastElement().InitializeFanObject(Vector2f(" << (int)objects.elements[i].data.fan.startPosition.x << ", " << (int)objects.elements[i].data.fan.startPosition.y << "));" << endl;
			break;
		}
	}
}

void PrintObjectsCode() {
	cout << "START" << endl;
	PrintLevelData();
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

				Allign(collider.sprite);

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
					if (colliders.elements[i].sprite.getGlobalBounds().contains(mousePosition) && colliders.elements[i].editable) {
						colliders.RemoveAt(i);
						UpdateGroundTexture();
					}
				}
			}
		}
		else if (editMode == EditMode::object_mode)
		{
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
				case Door_Target_mode:
					if (isEditingDoor)
					{
						Vector2f doorEndPos = mousePosition;
						Allign(doorEndPos);
						objects.elements[doorIndex].data.door.endPosition = doorEndPos;
					}
					break;
				case Door_Rotated_mode:
					objects.Add(Object(Object::DoorObject));
					objects.GetLastElement().data.door.rotated = true;
					objects.GetLastElement().InitializeDoorObject(mousePosition, mousePosition + Vector2f(0, -100));
					break;
				case FirePond_mode:
					objects.Add(Object(Object::PondObject));
					objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, mousePosition, editPondWidth);
					UpdateGroundTexture(); // update ground texture to add the pond mask
					break;
				case WaterPond_mode:
					objects.Add(Object(Object::PondObject));
					objects.GetLastElement().InitializePondObject(Pond::WATER_POND, mousePosition, editPondWidth);
					UpdateGroundTexture(); // update ground texture to add the pond mask
					break;
				case PoisonPond_mode:
					objects.Add(Object(Object::PondObject));
					objects.GetLastElement().InitializePondObject(Pond::POISON_POND, mousePosition, editPondWidth);
					UpdateGroundTexture(); // update ground texture to add the pond mask
					break;
				case Box_mode:
					objects.Add(Object(Object::BoxObject));
					objects.GetLastElement().InitializeBoxObject(mousePosition);
					break;
				case TemporaryGround_mode:
					objects.Add(Object(Object::TemporaryGroundObject));
					objects.GetLastElement().InitializeTemporaryGroundObject(mousePosition);
					break;
				case FanObject_mode:
					objects.Add(Object(Object::FanObject));
					objects.GetLastElement().InitializeFanObject(mousePosition);
					break;
				case Button_mode:
					if (isEditingDoor)
						if (objects.elements[doorIndex].type == Object::DoorObject)
							if (objects.elements[doorIndex].data.door.lastButtonAdded)
							{
								objects.elements[doorIndex].data.door.button1 = Click(mousePosition, true);
								objects.elements[doorIndex].data.door.lastButtonAdded = false;
							}
							else
							{
								objects.elements[doorIndex].data.door.button2 = Click(mousePosition, true);
								objects.elements[doorIndex].data.door.lastButtonAdded = true;
							}
						else
						{
							isEditingDoor = false; // break out of door edit mode since the door has been removed
							editObjectMode = EditObjectMode::FireGem_mode; // reset edit object mode to default
						}
					break;
				case Lever_mode:
					if (isEditingDoor)
						if (objects.elements[doorIndex].type == Object::DoorObject)
							objects.elements[doorIndex].data.door.lever = Lever(mousePosition, true);
					break;
				}

			// check collision with other objects	
			// Object.CheckCollisionWithObjects(objects);

			else if (event.mouseButton.button == Mouse::Right)
				// remove object
				for (int i = 0; i < objects.count; i++)
				{
					if (objects.elements[i].type == Object::DoorObject) {
						// also check the lever and buttons of the door
						int colliderIndex = objects.elements[i].data.door.CheckDoorObjects(mousePosition); // returns the index that means if button1 or 2 or lever is clicked
						if (colliderIndex != 0) {
							switch (colliderIndex)
							{
							case 1:
								objects.elements[i].data.door.button1.initialized = false; // reset button
								break;
							case 2:
								objects.elements[i].data.door.button2.initialized = false; // reset button
								break;
							case 3:
								objects.elements[i].data.door.lever.initialized = false; // reset lever
								break;
							default:
								break;
							}
							continue; // skip the rest of the loop to avoid deleting the door when trying to delete the button or lever
						}
					}

					if (objects.elements[i].data.CheckContainsPoint(mousePosition))
					{
						bool shouldUpdateGroundTexture = (objects.elements[i].type == Object::PondObject); // only update ground texture if a pond is removed since ponds affect the ground texture
						objects.RemoveAt(i);
						if (shouldUpdateGroundTexture) UpdateGroundTexture();
					}
				}
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

		if (event.key.code == Keyboard::C) {
			// set fireBoy position to mouse position
			fireBoy = Player(Fireboy, mousePosition);
			fireBoy.Initialize();
		}

		if (event.key.code == Keyboard::V) {
			// set waterGirl position to mouse position
			waterGirl = Player(Watergirl, mousePosition);
			waterGirl.Initialize();
		}

		if (event.key.code == Keyboard::B) {
			// set fireDoor position to mouse position
			fire_door = FinalDoor(FinalDoor::FIRE_DOOR, mousePosition);
			fire_door.Initialize();
		}

		if (event.key.code == Keyboard::N) {
			// set waterDoor position to mouse position
			water_door = FinalDoor(FinalDoor::WATER_DOOR, mousePosition);
			water_door.Initialize();
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
				editScale.x--;
			if (event.key.code == Keyboard::Numpad6)
				editScale.x++;
			if (event.key.code == Keyboard::Numpad2)
				editScale.y--;
			if (event.key.code == Keyboard::Numpad8)
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
				bool shouldUpdateGroundTexture = (objects.elements[objects.count - 1].type == Object::PondObject); // only update ground texture if a pond is removed since ponds affect the ground texture
				objects.RemoveAt(objects.count - 1);
				if (shouldUpdateGroundTexture) UpdateGroundTexture();
			}

			if (event.key.code == Keyboard::Numpad4)
			{
				editPondWidth--;
				editPondWidth = max(editPondWidthMinimum, editPondWidth);
			}
			if (event.key.code == Keyboard::Numpad6)
			{
				editPondWidth++;
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
				editObjectMode = EditObjectMode::FireGem_mode; // reset object mode to default
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

				if (event.key.code == Keyboard::Num9)
					editObjectMode = EditObjectMode::TemporaryGround_mode;
				if (event.key.code == Keyboard::Num0)
					editObjectMode = EditObjectMode::FanObject_mode;
			}
			else {
				if (event.key.code == Keyboard::Num1)
					editObjectMode = EditObjectMode::Button_mode;
				if (event.key.code == Keyboard::Num2)
					editObjectMode = EditObjectMode::Lever_mode;
				if (event.key.code == Keyboard::Num3)
					editObjectMode = EditObjectMode::Door_Target_mode;
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

// temporary restart function
void RestartGame() {
	// Erase Data
	colliders = ColliderList();
	objects = ObjectList();

	// Load Data
	LoadLevelData();
}


void OnUpdatedGameStateGameLogic() {
	// do stuff here exactly when the gameState is changed
	if (gameState == GAMEOVER) {
		RestartGame();
		return;
	}

	if (gameState != GAME) return;

	if (fireBoy.isDead || waterGirl.isDead) {
		UpdateGameState(GAMEOVER);
		return;
	}
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

	if (fireBoy.isOnGround) fireBoy.hitbox.setColor(Color::Red);
	else fireBoy.hitbox.setColor(Color(255, 100, 100));
	if (waterGirl.isOnGround) waterGirl.hitbox.setColor(Color::Blue);
	else waterGirl.hitbox.setColor(Color(100, 100, 255));


	CheckCollision(fireBoy);
	CheckCollision(waterGirl);

	for (int i = 0; i < objects.count; i++)
		objects.elements[i].Update(fireBoy, waterGirl, colliders);


	water_door.Update(waterGirl);
	fire_door.Update(fireBoy);


	check_game_win();
}


void DrawGame(bool forceDraw)
{
	if (!forceDraw && gameState != GAME) return;
	// no need for window.clear or window.display

	window.draw(background);

	for (int i = 0; i < objects.count; i++)
		objects.elements[i].PreDraw();

	window.draw(outlineSprite);
	window.draw(resultSprite);

	for (int i = 0; i < objects.count; i++)
		objects.elements[i].MidDraw();

	fireBoy.Draw();
	waterGirl.Draw();

	window.draw(water_door.sprite);
	window.draw(fire_door.sprite);


	for (int i = 0; i < objects.count; i++)
		objects.elements[i].PostDraw();

	//for (int i = 0; i < colliders.count; i++)
		//window.draw(colliders.elements[i].sprite);
}