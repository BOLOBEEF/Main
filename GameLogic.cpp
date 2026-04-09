
// GAME LOGIC




// Runtime variables
Player fireBoy = Player(Player::Fireboy, center + Vector2f(-600, 200));
Player waterGirl = Player(Player::Watergirl, center + Vector2f(-550, 200));
Gem fireGem = Gem(Gem::fireGem, Vector2f(650, 800));
Gem waterGem = Gem(Gem::waterGem, Vector2f(800, 800));
Sprite ground;
Click click = Click(Vector2f(1000, 900));
RenderTexture maskTexture;
RenderTexture resultTexture;

const bool displayColliders = true;
ColliderList colliders;


// LEVEL EDITING TOOLS
const bool editMode = true;	// if true, you can place down objects by clicking, and remove them by right clicking, change object type by pressing 0 or 1 or....
Vector2f editScale = Vector2f(1, 1);

enum EditType
{
	Rectangle,
	Triangle,
	Triangle_Rotated,
};
EditType currentEditType = EditType::Rectangle;


void CheckPlayerCollision(Player& player) {
	bool isOnGround = false;

	for (int i = 0; i < colliders.count; i++)
		isOnGround |= colliders.elements[i].CheckCollision(player);

	player.isOnGround = isOnGround;
}

void AllignColliders() {
	for (int i = 0; i < colliders.count; i++)
	{
		colliders.elements[i].AllignCollider();
	}
}

void LoadLevelData() {
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-704, 420), Vector2f(44, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-704, -540), Vector2f(44, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-704, -508), Vector2f(1, 29)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(672, -508), Vector2f(1, 29)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-672, 292), Vector2f(11, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-672, 164), Vector2f(17, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-128, 228), Vector2f(19, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-64, 4), Vector2f(23, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-512, -28), Vector2f(16, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-672, -156), Vector2f(37, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-288, -316), Vector2f(30, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-128, 164), Vector2f(3, 2)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(0, -28), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(352, 36), Vector2f(10, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(448, 68), Vector2f(7, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(576, 100), Vector2f(3, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(576, 324), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(576, 324), Vector2f(3, 3)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(544, 356), Vector2f(1, 2)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(352, -124), Vector2f(5, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(32, -220), Vector2f(8, 2)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(288, -220), Vector2f(2, 2)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-288, -284), Vector2f(5, 2)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-288, -348), Vector2f(3, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-192, -348), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-256, -380), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-320, -380), Vector2f(2, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-320, -380), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-672, -316), Vector2f(5, 5)));
}

void UpdateGroundTexture() {
	// --- Step 1: Draw mask (small sprites) ---
	maskTexture.clear(Color::Transparent);

	if (displayColliders)
		for (int i = 0; i < colliders.count; i++)
		{
			maskTexture.draw(colliders.elements[i].sprite);
		}
	maskTexture.display();


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
	ApplyTexture(ground, LoadTexture::GROUND, Vector2f(256, 256));
	ground.setTextureRect(IntRect(0, 0, windowSize.x, windowSize.y));


	maskTexture.create(windowSize.x, windowSize.y);
	resultTexture.create(windowSize.x, windowSize.y);

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
				collider = Collider(Collider::ColliderType::Rectangle, Vector2f(event.mouseButton.x, event.mouseButton.y), editScale);
				collider.Initialize();
				collider.sprite.move(-collider.sprite.getGlobalBounds().width / 2.0f, -collider.sprite.getGlobalBounds().height / 2.0f);
				break;
			case Triangle:
				collider = Collider(Collider::ColliderType::Triangle, Vector2f(event.mouseButton.x, event.mouseButton.y), editScale);
				collider.Initialize();
				collider.sprite.move(-collider.sprite.getGlobalBounds().width / 2.0f, -collider.sprite.getGlobalBounds().height / 2.0f);
				break;
			case Triangle_Rotated:
				collider = Collider(Collider::ColliderType::Triangle_Rotated, Vector2f(event.mouseButton.x, event.mouseButton.y), editScale);
				collider.Initialize();
				collider.sprite.move(collider.sprite.getGlobalBounds().width / 2.0f, -collider.sprite.getGlobalBounds().height / 2.0f);
				break;
			default:
				break;
			}

			collider.AllignCollider();

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
				if (colliders.elements[i].sprite.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
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


	// in debug mode, when you press
	if (!editMode) return;
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
	fireGem.checkintersect(fireBoy);
	waterGem.checkintersect(waterGirl);
	click.buttonpressed = false;
	click.isPressed(fireBoy);
	click.isPressed(waterGirl);
	click.updateRelease();

}


void DrawGame()
{
	if (gameState != GAME) return;

	// no need for window.clear or window.display
	window.draw(fireBoy.sprite);
	window.draw(waterGirl.sprite);

	window.draw(waterGem.sprite);
	window.draw(fireGem.sprite);
	window.draw(click.sprite);
	window.draw(Sprite(resultTexture.getTexture()));
}