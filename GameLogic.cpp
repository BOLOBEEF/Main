
// GAME LOGIC




// Runtime variables
Player fireBoy = Player(Player::Fireboy, center + Vector2f(-50, -500));
Player waterGirl = Player(Player::Watergirl, center + Vector2f(50, -500));

const bool displayColliders = true;
ColliderList colliders;



// LEVEL EDITING TOOLS
const bool debugMode = true;	// if true, you can place down objects by clicking, and remove them by right clicking, change object type by pressing 0 or 1 or....
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

void InitializeGame()
{
	colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-60, -40)));
	colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(40, -40)));
	colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-60, -40)));

	// code for initializing game variables and objects
	for (int i = 0; i < colliders.count; i++)
		colliders.elements[i].Initialize();


	fireBoy.sprite.setFillColor(Color::Red);
	waterGirl.sprite.setFillColor(Color::Blue);
}

void PrintCollidersCode() {
	for (int i = 0; i < colliders.count; i++) {
		string type = (colliders.elements[i].type == Collider::ColliderType::Rectangle ? "Rectangle" : colliders.elements[i].type == Collider::ColliderType::Triangle ? "Triangle" : "Triangle_Rotated");
		string position = "Vector2f(" + to_string((int)(colliders.elements[i].sprite.getPosition().x - center.x)) + ", " + to_string((int)(colliders.elements[i].sprite.getPosition().y - center.y)) + ")";
		cout << "colliders.Add(Collider(Collider::ColliderType::" << type << ", center + " << position << "));" << endl;
	}
		
}

void PrintObjectsCode() {
	cout << "START" << endl;
	PrintCollidersCode();
	cout << "END" << endl;
}

void AllignColliders() {
	int precision = 100;	// the smaller, the more precise, but also the more objects you will have to place to fill the same area


	for (int i = 0; i < colliders.count; i++)
	{
		Vector2f position = colliders.elements[i].sprite.getPosition();
		position.x = round(position.x / precision) * precision;
		position.y = round(position.y / precision) * precision;

		colliders.elements[i].sprite.setPosition(position);
	}
}


void HandleGameInput(Event event)
{
	if (gameState != GAME) return;

	// code for handling game input that is related to game logic
	fireBoy.checkJump(event);
	waterGirl.checkJump(event);


	// in debug mode, when you press
	if (!debugMode) return;

	if (event.type == Event::MouseButtonPressed) {
		if (event.mouseButton.button == Mouse::Left) {
			// add object

			switch (currentEditType)
			{
			case Rectangle:
				colliders.Add(Collider(Collider::ColliderType::Rectangle, Vector2f(event.mouseButton.x, event.mouseButton.y)));
				colliders.elements[colliders.count - 1].Initialize();
				colliders.elements[colliders.count - 1].sprite.move(-colliders.elements[colliders.count - 1].sprite.getGlobalBounds().width / 2.0f, -colliders.elements[colliders.count - 1].sprite.getGlobalBounds().height / 2.0f);
				AllignColliders();
				break;
			case Triangle:
				colliders.Add(Collider(Collider::ColliderType::Triangle, Vector2f(event.mouseButton.x, event.mouseButton.y)));
				colliders.elements[colliders.count - 1].Initialize();
				colliders.elements[colliders.count - 1].sprite.move(-colliders.elements[colliders.count - 1].sprite.getGlobalBounds().width / 2.0f, -colliders.elements[colliders.count - 1].sprite.getGlobalBounds().height / 2.0f);
				AllignColliders();
				break;
			case Triangle_Rotated:
				colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, Vector2f(event.mouseButton.x, event.mouseButton.y)));
				colliders.elements[colliders.count - 1].Initialize();
				colliders.elements[colliders.count - 1].sprite.move(colliders.elements[colliders.count - 1].sprite.getGlobalBounds().width / 2.0f, -colliders.elements[colliders.count - 1].sprite.getGlobalBounds().height / 2.0f);
				AllignColliders();
				break;
			default:
				break;
			}
			
		}
		
		
		else if (event.mouseButton.button == Mouse::Right) {
			// remove object
			for (int i = 0; i < colliders.count; i++) {
				if (colliders.elements[i].sprite.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
					colliders.RemoveAt(i);
					break;
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
}