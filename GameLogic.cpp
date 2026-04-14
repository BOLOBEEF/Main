
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
Gem fireGem = Gem(Gem::fireGem, Vector2f(650, 800));
Gem waterGem = Gem(Gem::waterGem, Vector2f(800, 800));
Pond firePond = Pond(Pond::FIRE_POND, Vector2f(600, 550));
Pond waterPond = Pond(Pond::WATER_POND, Vector2f(1000, 650));
Pond poisonPond = Pond(Pond::POISON_POND, Vector2f(800, 600));

Box box = Box(Vector2f(1100, 200));
Final_door water_door = Final_door(Final_door::WATER_DOOR, Vector2f(1200, 25));
Final_door fire_door = Final_door(Final_door::FIRE_DOOR, Vector2f(1300, 25));
Switch lever = Switch(Vector2f(900, 800));
Game_Door door = Game_Door(Game_Door::CLOSED, Vector2f(400.0f, 300.0f), Vector2f(400.0f, 200.0f));

Sprite ground;
Click click = Click(Vector2f(1200, 800));

RenderTexture maskTexture;
RenderTexture resultTexture;
RenderTexture outlineTexture;
Sprite outlineSprite;
Sprite resultSprite;

ColliderList colliders;


// LEVEL EDITING TOOLS
const bool enableEditMode = true;	// if true, you can place down objects by clicking, and remove them by right clicking, change object type by pressing 0 or 1 or....
Vector2f editScale = Vector2f(1, 1);

enum EditType
{
	Rectangle,
	Triangle,
	Triangle_Rotated,
};
EditType currentEditType = EditType::Rectangle;


void CheckPlayerCollision(Player& player) {
	for (int i = 0; i < colliders.count; i++)
	{
		Collider::CollisionData collisionData;
		player.isOnGround |= colliders.elements[i].CheckCollision(player, collisionData);
		if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Slope)
			player.isOnSlope = true;
	}
}

void CheckBoxCollision(Box& box, Collider::CollisionData* colliderDatas) {
	for (int i = 0; i < colliders.count; i++)
	{
		Collider::CollisionData collisionData = colliders.elements[i].CheckRectangleCollision(box.collider.sprite, colliders.elements[i].sprite.getGlobalBounds());
		if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Top)
			box.velocity.y = min(box.velocity.y, 1.0f);

		colliderDatas[i] = collisionData;
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
	fireBoy.start();
	waterGirl.start();
	fireGem.start();
	waterGem.start();
	click.start();
	box.Initialize();
	lever.start();
	lever.SetDoor(&door);

	ApplyTexture(ground, LoadTexture::GROUND, Vector2f(256, 256));
	ground.setTextureRect(IntRect(0, 0, windowSize.x, windowSize.y));

	firePond.Initialilze();
	waterPond.Initialilze();
	poisonPond.Initialilze();
	firePond.sprite.setColor(Color::Red);
	waterPond.sprite.setColor(Color::Blue);
	poisonPond.sprite.setColor(Color::Green);


	maskTexture.create(windowSize.x, windowSize.y);
	outlineTexture.create(windowSize.x, windowSize.y);
	resultTexture.create(windowSize.x, windowSize.y);
	outlineSprite.setTexture(outlineTexture.getTexture());
	resultSprite.setTexture(resultTexture.getTexture());

	water_door.Initialilze();
	water_door.sprite.setColor(Color::Blue);
	fire_door.Initialilze();
	fire_door.sprite.setColor(Color::Red);

	door.Intialization();
	door.collider.sprite.setColor(Color::Yellow);

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
		if (event.mouseButton.button == Mouse::Left) {
			// add object
			if (editScale.x <= 0) editScale.x = 1;
			if (editScale.y <= 0) editScale.y = 1;

			Collider collider;

			switch (currentEditType)
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

	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::P) {
			// print objects code
			PrintObjectsCode();
		}

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


		if (event.key.code == Keyboard::Num1) {
			// undo last object placement
			currentEditType = EditType::Rectangle;
		}

		if (event.key.code == Keyboard::Num2) {
			// undo last object placement
			currentEditType = EditType::Triangle;
		}

		if (event.key.code == Keyboard::Num3) {
			// undo last object placement
			currentEditType = EditType::Triangle_Rotated;
		}
	}

}


void HandleGameInput(Event event)
{
	if (gameState != GAME) return;

	// code for handling game input that is related to game logic
	fireBoy.checkJump(event);
	waterGirl.checkJump(event);
	lever.leverMove(fireBoy, waterGirl, event);

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

	fireBoy.UpdateMotion();
	waterGirl.UpdateMotion();

	if (fireBoy.isOnGround) fireBoy.sprite.setColor(Color::Red);
	else fireBoy.sprite.setColor(Color(255, 100, 100));
	if (waterGirl.isOnGround) waterGirl.sprite.setColor(Color::Blue);
	else waterGirl.sprite.setColor(Color(100, 100, 255));


	CheckPlayerCollision(fireBoy);
	CheckPlayerCollision(waterGirl);

	box.UpdatePhysics();

	Collider::CollisionData* boxCollisionDatas = new Collider::CollisionData[colliders.count];
	CheckBoxCollision(box, boxCollisionDatas);

	box.CheckPlayerCollision(fireBoy, boxCollisionDatas, colliders.count);
	box.CheckPlayerCollision(waterGirl, boxCollisionDatas, colliders.count);
	delete[] boxCollisionDatas;


	fireGem.checkintersect(fireBoy);
	waterGem.checkintersect(waterGirl);

	
	click.isPressed(fireBoy,waterGirl);
	

	firePond.Update(fireBoy,waterGirl);
	waterPond.Update(fireBoy,waterGirl);
	poisonPond.Update(fireBoy,waterGirl);

	water_door.Update(waterGirl);
	fire_door.Update(fireBoy);

	if (fireBoy.isDead)
		fireBoy.sprite.setColor(Color::Yellow);
	if (waterGirl.isDead)
		waterGirl.sprite.setColor(Color::Yellow);
	if (water_door.player_on_door && fire_door.player_on_door)
	{
		water_door.sprite.setColor(Color(128, 0, 128));
		fire_door.sprite.setColor(Color(128, 0, 128));
	}

	door.moving_door();
	door.CheckCollision(fireBoy);
	door.CheckCollision(waterGirl);
}


void DrawGame(bool forceDraw)
{
	if (!forceDraw && gameState != GAME) return;

	// no need for window.clear or window.display
	window.draw(outlineSprite);
	window.draw(resultSprite);


	window.draw(waterGem.sprite);
	window.draw(fireGem.sprite);


	window.draw(fireBoy.sprite);
	window.draw(waterGirl.sprite);

	box.Draw(window);
	window.draw(click.sprite);
	window.draw(lever.sprite);

	window.draw(waterPond.sprite);
	window.draw(poisonPond.sprite);
	window.draw(firePond.sprite);

	window.draw(water_door.sprite);
	window.draw(fire_door.sprite);

	window.draw(door.sprite);
}