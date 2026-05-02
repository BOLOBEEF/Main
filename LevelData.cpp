// all levels data here
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
	FanObject_mode,
	SnowObject_Normal_mode,
	SnowObject_LeftDown_mode,
	SnowObject_RightDown_mode,
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


struct LevelProgress
{
	bool isCompleted = false;    // if the player has completed the level before
	bool collectedGems = false;  // if the player has collected all the gems in the level before
	bool finishedOnTime = false; // if the player has finished the level on time
};

#define MAX_LEVELS 6

LevelProgress levelProgress[MAX_LEVELS]; // progress for each level, can be used to show different icons in the level select screen

void LoadLevelProgress() {
	for (int i = 0; i < MAX_LEVELS; i++)
	{
		// load progress for each level from a file using fstream
	}
}

void SaveLevelProgress() {
	for (int i = 0; i < MAX_LEVELS; i++)
	{
		// save progress for each level to a file using fstream
	}
}


struct Level
{
	// store all the variables related to a level here, for example:
	int currentLevelIndex = 0;


	ColliderList colliders;
	ObjectList objects;
	bool isSnowLevel = false;

	// logic functions
	void CheckLevelCollision(Player& player) {
		for (int i = 0; i < colliders.count; i++)
		{
			Collider::CollisionData collisionData;
			player.isOnGround |= colliders.elements[i].CheckCollision(player, collisionData);
			if (collisionData.collisionDirection == Collider::CollisionData::CollisionDirection::Slope)
			{
				player.isOnSlope = true;
				if (colliders.elements[i].type == Collider::Triangle) player.slopeDirectionRight = true;
				else player.slopeDirectionRight = false;
			}
		}
	}
	void AllignColliders() {
		for (int i = 0; i < colliders.count; i++)
			if (colliders.elements[i].editable)
				Allign(colliders.elements[i].sprite);
	}

	// shader functions
	void SetTheme(bool isSnowTheme) {
		isSnowLevel = isSnowTheme;

		ground = Sprite();
		background = Sprite();

		if (!isSnowTheme) {
			ApplyTexture(ground, LoadTexture::GROUND, Vector2f(256, 256));
			ground.setTexture(groundTexture);
			ApplyTexture(background, LoadTexture::BACKGROUND, Vector2f(256, 256));
			background.setTexture(backgroundTexture);
		}
		else {
			ApplyTexture(background, LoadTexture::GROUND, Vector2f(256, 256));
			background.setTexture(groundTexture);
			ApplyTexture(ground, LoadTexture::BACKGROUND, Vector2f(256, 256));
			ground.setTexture(backgroundTexture);
		}

		ground.setTextureRect(IntRect(0, 0, windowSize.x, windowSize.y));
		background.setTextureRect(IntRect(0, 0, windowSize.x, windowSize.y));
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


	// background music enum
	// ground texture enum
	// array of rectangleShapes for collision detection
	// 2 positions for player spawns
	// 2 goal doors

	// then to add actual data for each level, in the constructor of the Level struct, we can fill those arrays with the actual data for each level based on the provided level index

	// LEVEL DATA :
	void Level1()
	{
		isSnowLevel = false;
		fireBoy = Player(Fireboy, Vector2f(263, 934));
		waterGirl = Player(Watergirl, Vector2f(264, 798));
		water_door = FinalDoor(FinalDoor::WATER_DOOR, Vector2f(1547, 90));
		fire_door = FinalDoor(FinalDoor::FIRE_DOOR, Vector2f(1433, 102));
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
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(-112, 180), Vector2f(3, 3)));
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, Vector2f(1008, 976), 5);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::WATER_POND, Vector2f(1296, 976), 5);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::POISON_POND, Vector2f(1168, 784), 5);
		objects.Add(Object(Object::DoorObject));
		objects.GetLastElement().InitializeDoorObject(Vector2f(224, 528), Vector2f(224, 640), false);
		objects.GetLastElement().data.door.lever = Lever(Vector2f(515, 659), true);
		objects.Add(Object(Object::DoorObject));
		objects.GetLastElement().InitializeDoorObject(Vector2f(1696, 400), Vector2f(1696, 512), false);
		objects.GetLastElement().data.door.button1 = Click(Vector2f(517, 500), true);
		objects.GetLastElement().data.door.button2 = Click(Vector2f(1544, 340), true);
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
		objects.Add(Object(Object::BoxObject));
		objects.GetLastElement().InitializeBoxObject(Vector2f(1199, 243));
	}

	void Level2()
	{
		isSnowLevel = false;
		fireBoy = Player(Fireboy, Vector2f(337, 870));
		waterGirl = Player(Watergirl, Vector2f(402, 860));
		water_door = FinalDoor(FinalDoor::WATER_DOOR, Vector2f(465, 102));
		fire_door = FinalDoor(FinalDoor::FIRE_DOOR, Vector2f(349, 86));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(0, -524), Vector2f(44, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-112, 116), Vector2f(37, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-416, -364), Vector2f(18, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(256, -364), Vector2f(8, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(352, -332), Vector2f(4, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(416, -300), Vector2f(4, 1)));
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(432, -332), Vector2f(1, 1)));
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(400, -364), Vector2f(1, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-640, 36), Vector2f(4, 4)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(640, 324), Vector2f(4, 2)));
		colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(608, 260), Vector2f(2, 2)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(672, 260), Vector2f(2, 2)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-592, 372), Vector2f(7, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-96, 372), Vector2f(6, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(496, 372), Vector2f(13, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-432, -76), Vector2f(3, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(0, -92), Vector2f(6, 2)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(512, -76), Vector2f(12, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(656, -188), Vector2f(3, 6)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(560, -140), Vector2f(3, 3)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, 84), Vector2f(1, 9)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, -396), Vector2f(1, 7)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-688, -188), Vector2f(1, 10)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-688, 244), Vector2f(1, 7)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-688, -444), Vector2f(1, 4)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-48, -44), Vector2f(1, 1)));
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(496, 116), Vector2f(1, 1)));
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, Vector2f(624, 912), 9);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, Vector2f(1104, 816), 9);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::WATER_POND, Vector2f(624, 816), 9);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::WATER_POND, Vector2f(1104, 912), 9);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::POISON_POND, Vector2f(720, 464), 9);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::POISON_POND, Vector2f(1168, 464), 7);
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(560, 848));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(688, 848));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(560, 752));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(688, 752));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1040, 848));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1168, 848));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(1040, 752));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(1168, 752));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(1168, 592));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1040, 592));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(592, 592));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(720, 592));
		objects.Add(Object(Object::TemporaryGroundObject));
		objects.GetLastElement().InitializeTemporaryGroundObject(Vector2f(1168, 357));
		objects.Add(Object(Object::TemporaryGroundObject));
		objects.GetLastElement().InitializeTemporaryGroundObject(Vector2f(720, 357));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(912, 368));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1008, 368));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(912, 112));
		objects.Add(Object(Object::DoorObject));
		objects.GetLastElement().InitializeDoorObject(Vector2f(1152, 174), Vector2f(896, 176), false);
		objects.GetLastElement().data.door.button1 = Click(Vector2f(1214, 137), true);
		objects.GetLastElement().data.door.button2 = Click(Vector2f(646, 138), true);
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1008, 112));
		objects.Add(Object(Object::DoorObject));
		objects.GetLastElement().InitializeDoorObject(Vector2f(910, 576), Vector2f(912, 448), true);
		objects.GetLastElement().data.door.button1 = Click(Vector2f(459, 617), true);
		objects.GetLastElement().data.door.button2 = Click(Vector2f(1385, 604), true);
	}

	void Level3() {
		isSnowLevel = false;
		fireBoy = Player(Fireboy, Vector2f(1546, 876));
		waterGirl = Player(Watergirl, Vector2f(354, 877));
		water_door = FinalDoor(FinalDoor::WATER_DOOR, Vector2f(1289, 443));
		fire_door = FinalDoor(FinalDoor::FIRE_DOOR, Vector2f(594, 447));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(0, -524), Vector2f(44, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, 84), Vector2f(1, 9)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, -396), Vector2f(1, 7)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-688, 244), Vector2f(1, 7)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-688, -444), Vector2f(1, 4)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(816, -524), Vector2f(1, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, 292), Vector2f(1, 4)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-688, 52), Vector2f(1, 5)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-576, 180), Vector2f(6, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(576, 180), Vector2f(6, 1)));
		colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-144, 308), Vector2f(3, 3)));
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(144, 308), Vector2f(3, 3)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(0, 308), Vector2f(6, 3)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-192, 180), Vector2f(2, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(192, 180), Vector2f(2, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(0, 372), Vector2f(12, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(592, 372), Vector2f(7, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-592, 372), Vector2f(7, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-640, 132), Vector2f(2, 2)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(640, 132), Vector2f(2, 2)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-688, -204), Vector2f(1, 11)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(688, -172), Vector2f(1, 7)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(0, -12), Vector2f(32, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-352, -396), Vector2f(14, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(352, -396), Vector2f(14, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-432, -204), Vector2f(1, 11)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(432, -204), Vector2f(1, 11)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-608, -108), Vector2f(4, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(608, -108), Vector2f(4, 1)));
		colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-528, -12), Vector2f(1, 1)));
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(528, -12), Vector2f(1, 1)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(0, -108), Vector2f(2, 5)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(-48, -188), Vector2f(1, 2)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(48, -188), Vector2f(1, 2)));
		colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-64, -60), Vector2f(2, 2)));
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(64, -60), Vector2f(2, 2)));
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(80, -268), Vector2f(3, 3)));
		colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-80, -268), Vector2f(3, 3)));
		colliders.Add(Collider(Collider::ColliderType::Rectangle, center + Vector2f(0, -316), Vector2f(2, 2)));
		colliders.Add(Collider(Collider::ColliderType::Triangle_Rotated, center + Vector2f(-208, 372), Vector2f(1, 1)));
		colliders.Add(Collider(Collider::ColliderType::Triangle, center + Vector2f(208, 372), Vector2f(1, 1)));
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, Vector2f(608, 720), 8);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::WATER_POND, Vector2f(1312, 720), 8);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::WATER_POND, Vector2f(624, 912), 9);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, Vector2f(1296, 912), 9);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::WATER_POND, Vector2f(1312, 368), 4);
		objects.Add(Object(Object::PondObject));
		objects.GetLastElement().InitializePondObject(Pond::FIRE_POND, Vector2f(608, 368), 4);
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(592, 304));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1328, 304));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(880, 208));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(1040, 208));
		objects.Add(Object(Object::FanObject));
		objects.GetLastElement().InitializeFanObject(Vector2f(337, 417));
		objects.Add(Object(Object::FanObject));
		objects.GetLastElement().InitializeFanObject(Vector2f(1590, 412));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(1360, 848));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(1232, 848));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(1008, 752));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(912, 752));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(560, 848));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(688, 848));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1264, 656));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1360, 656));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(560, 656));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(656, 656));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(336, 336));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(336, 240));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::fireGem, Vector2f(336, 144));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1584, 336));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1584, 240));
		objects.Add(Object(Object::GemObject));
		objects.GetLastElement().InitializeGemObject(Gem::waterGem, Vector2f(1584, 144));
	}

	bool LoadLevelData(int levelIndex) {
		currentLevelIndex = levelIndex;
		// based on the level index, fill the arrays with the actual data for each level
		switch (levelIndex)
		{
		case 1:	Level1();	break;
		case 2: Level2();	break;
		case 3: Level3();   break;

		default:
			cout << "Invalid level index: " << levelIndex << endl;
			return false;
		}

		return true;
	}

	void Initialize() {
		// code for initializing game variables and objects
		for (int i = 0; i < colliders.count; i++)
			colliders.elements[i].Initialize();


		AllignColliders();
		fireBoy.Initialize();
		waterGirl.Initialize();
		fireBoy.Update();
		waterGirl.Update();


		ground = Sprite();
		background = Sprite();
		outlineSprite = Sprite();
		resultSprite = Sprite();

		SetTheme(isSnowLevel);

		maskTexture.create(windowSize.x, windowSize.y);
		outlineTexture.create(windowSize.x, windowSize.y);
		resultTexture.create(windowSize.x, windowSize.y);
		outlineSprite.setTexture(outlineTexture.getTexture());
		outlineSprite.setColor(Color::Black);
		resultSprite.setTexture(resultTexture.getTexture());

		water_door.Initialize();
		fire_door.Initialize();
		water_door.Update(fireBoy);
		fire_door.Update(fireBoy);

		UpdateGroundTexture();
	}

	void EraseData()
	{
		// erase the level data
		// reset all arrays to be empty
		colliders = ColliderList();
		objects = ObjectList();
	}

	// LOAD A NEW LEVEL
	void LoadNewLevel(int levelIndex)
	{
		// reset the level to its initial state, for example when the player dies or restarts the level
		EraseData();

		levelLoadFailed = !LoadLevelData(levelIndex);
		
		if (!levelLoadFailed)
			Initialize();
	}

	// RESTART CURRENT LEVEL
	void ResetLevel()
	{
		// reset the level to its initial state, for example when the player dies or restarts the level
		EraseData();
		LoadLevelData(currentLevelIndex);
		Initialize();
	}

	// printing
	void PrintLevelData() {
		// player data
		cout << "isSnowLevel = " << (isSnowLevel ? "true;" : "false;") << endl;
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
				cout << "objects.GetLastElement().InitializeDoorObject(" << position << ", " << extraData << ", " << (objects.elements[i].data.door.rotated ? "true" : "false") << ");" << endl;
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
			break; case Object::SnowObject:
				string snowType;
				if (objects.elements[i].data.snow.type == Snow::Normal)
					snowType = "SnowObject_Normal_mode";
				else if (objects.elements[i].data.snow.type == Snow::LeftDown)
					snowType = "SnowObject_LeftDown_mode";
				else
					snowType = "SnowObject_RightDown_mode";
				cout << "objects.Add(Object(Object::SnowObject));" << endl;
				cout << "objects.GetLastElement().InitializeSnowObject(Snow::" << snowType << ", Vector2f(" << (int)objects.elements[i].data.snow.sprite.getPosition().x << ", " << (int)objects.elements[i].data.snow.sprite.getPosition().y << "));" << endl;
				break;
			}
		}
	}
	void PrintLevelCode() {
		cout << "START" << endl;
		PrintLevelData();
		cout << "END" << endl;
	}
	void Print(string message) {
		cout << message << endl;
	}

	void ChangeTheme() {

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
						objects.GetLastElement().InitializeDoorObject(mousePosition, mousePosition + Vector2f(0, -100), false);
						break;
					case Door_Target_mode:
						if (isEditingDoor)
						{
							objects.elements[doorIndex].data.door.SetEndPosition(mousePosition);
						}
						break;
					case Door_Rotated_mode:
						objects.Add(Object(Object::DoorObject));
						objects.GetLastElement().InitializeDoorObject(mousePosition, mousePosition + Vector2f(0, -100), true);
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
					case SnowObject_LeftDown_mode:
						objects.Add(Object(Object::SnowObject));
						objects.GetLastElement().InitializeSnowObject(Snow::LeftDown, mousePosition);
						break;
					case SnowObject_Normal_mode:
						objects.Add(Object(Object::SnowObject));
						objects.GetLastElement().InitializeSnowObject(Snow::Normal, mousePosition);
						break;
					case SnowObject_RightDown_mode:
						objects.Add(Object(Object::SnowObject));
						objects.GetLastElement().InitializeSnowObject(Snow::RightDown, mousePosition);
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
				// print level code
				PrintLevelCode();
			}

			if (event.key.code == Keyboard::M) {
				// switch level theme
				SetTheme(!isSnowLevel);
				UpdateGroundTexture();
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

					if (event.key.code == Keyboard::Q)
						editObjectMode = EditObjectMode::SnowObject_LeftDown_mode;
					if (event.key.code == Keyboard::W)
						editObjectMode = EditObjectMode::SnowObject_Normal_mode;
					if (event.key.code == Keyboard::E)
						editObjectMode = EditObjectMode::SnowObject_RightDown_mode;
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



	void CheckWin() {
		if (water_door.currentFrame == 21 && fire_door.currentFrame == 21)
		{
			//UpdateGameState(WIN_MENU);
			fireBoy.EnterDoor(Vector2f(fire_door.sprite.getGlobalBounds().left + fire_door.sprite.getGlobalBounds().width / 2.0f, fire_door.sprite.getGlobalBounds().top + fire_door.sprite.getGlobalBounds().height / 2.0f));
			waterGirl.EnterDoor(Vector2f(water_door.sprite.getGlobalBounds().left + water_door.sprite.getGlobalBounds().width / 2.0f, water_door.sprite.getGlobalBounds().top + water_door.sprite.getGlobalBounds().height / 2.0f));
		}
	}
	void CheckLoss()
	{
		if (waterGirl.isDead || fireBoy.isDead)
		{
			// end game
		}
	}

	void CheckInput(Event event) {
		fireBoy.CheckInput(event);
		waterGirl.CheckInput(event);
		for (int i = 0; i < objects.count; i++)
			objects.elements[i].CheckInput(fireBoy, waterGirl, event);

		// in debug mode, when you press
		if (!enableEditMode) return;
		EditMode(event);
	}

	void Update() {

		fireBoy.Update();
		waterGirl.Update();

		if (fireBoy.isOnGround) fireBoy.hitbox.setColor(Color::Red);
		else fireBoy.hitbox.setColor(Color(255, 100, 100));
		if (waterGirl.isOnGround) waterGirl.hitbox.setColor(Color::Blue);
		else waterGirl.hitbox.setColor(Color(100, 100, 255));


		CheckLevelCollision(fireBoy);
		CheckLevelCollision(waterGirl);

		for (int i = 0; i < objects.count; i++)
			objects.elements[i].Update(fireBoy, waterGirl, colliders);

		water_door.Update(waterGirl);
		fire_door.Update(fireBoy);


		CheckWin();
	}

	void Draw() {
		window.draw(background);

		for (int i = 0; i < objects.count; i++)
			objects.elements[i].PreDraw();

		window.draw(outlineSprite);
		window.draw(resultSprite);

		for (int i = 0; i < objects.count; i++)
			objects.elements[i].MidDraw();

		window.draw(fire_door.sprite);
		window.draw(water_door.sprite);


		for (int i = 0; i < gameTutorials.count; i++)
			gameTutorials.elements[i].Draw();

		fireBoy.Draw();
		waterGirl.Draw();


		for (int i = 0; i < objects.count; i++)
			objects.elements[i].PostDraw();
	}
};

// we make actual level objects here, and we can access them in the game logic when we need to load a level
Level currentLevel;
//currentLevel.LoadNewLevel(1); // load level 1
//currentLevel.LoadNewLevel(currentLevel.currentLevelIndex + 1); // load the next level