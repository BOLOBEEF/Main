
// GAME LOGIC




// Runtime variables
Player fireBoy = Player(Player::Fireboy, center + Vector2f(-600, 200));
Player waterGirl = Player(Player::Watergirl, center + Vector2f(-550, 200));
Gem gem = Gem(Vector2f(650, 800));
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
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-900, 360), Vector2f(30, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-1140, 60), Vector2f(23, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-360, -240), Vector2f(23, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-300, 300), Vector2f(8, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-300, 300), Vector2f(2, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(180, 300), Vector2f(2, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(420, 240), Vector2f(2, 2)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(540, 120), Vector2f(2, 2)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(540, 120), Vector2f(2, 2)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(540, 240), Vector2f(2, 2)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-300, 0), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-300, 0), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-240, 0), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-180, 0), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-720, 0), Vector2f(3, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-900, -120), Vector2f(3, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-720, -120), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-540, 0), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-720, 0), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-480, -240), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-420, -240), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-480, -240), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-960, 360), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(900, 360), Vector2f(1, 1)));
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(840, 180), Vector2f(2, 1)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(840, 180), Vector2f(1, 1)));
}


void InitializeGame()
{
	LoadLevelData();


	// code for initializing game variables and objects
	for (int i = 0; i < colliders.count; i++)
		colliders.elements[i].Initialize();

	AllignColliders();

	fireBoy.sprite.setFillColor(Color::Red);
	waterGirl.sprite.setFillColor(Color::Blue);
	gem.start();
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




void HandleGameInput(Event event)
{
	if (gameState != GAME) return;

	// code for handling game input that is related to game logic
	fireBoy.checkJump(event);
	waterGirl.checkJump(event);


	// in debug mode, when you press
	if (!editMode) return;

	if (event.type == Event::MouseButtonPressed) {
		if (event.mouseButton.button == Mouse::Left) {
			// add object

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

			/*bool isColliding = false;
			for (int i = 0; i < colliders.count; i++)
				if (colliders.elements[i].sprite.getGlobalBounds().intersects(collider.sprite.getGlobalBounds())) {
					isColliding = true;
					break;
				}*/
			
			//if (!isColliding) {
				colliders.Add(collider);
			//}
		}
		
		
		else if (event.mouseButton.button == Mouse::Right) {
			// remove object
			for (int i = 0; i < colliders.count; i++) {
				if (colliders.elements[i].sprite.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
					colliders.RemoveAt(i);
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

void OnUpdatedGameStateGameLogic() {
	// do stuff here exactly when the gameState is changed
	if (gameState != GAME) return;

}


void UpdateGame()
{
	if (gameState != GAME) return;

	fireBoy.UpdateMotion();
	waterGirl.UpdateMotion();


	CheckPlayerCollision(fireBoy);
	CheckPlayerCollision(waterGirl);
	gem.checkintersect(fireBoy);
	gem.checkintersect(waterGirl);
}



void DrawGame()
{
	if (gameState != GAME) return;

	// no need for window.clear or window.display
	window.draw(fireBoy.sprite);
	window.draw(waterGirl.sprite);

	if (displayColliders)
		for (int i = 0; i < colliders.count; i++)
		{
			window.draw(colliders.elements[i].sprite);
		}
	window.draw(gem.sprite);
}