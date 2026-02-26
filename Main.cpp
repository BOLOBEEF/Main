#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <queue>
#include <iomanip>
using namespace std;
using namespace sf;



// Helper Functions

int RandomRange(int start, int end) {
	return rand() % (end + 1 - start) + start;
}
float RandomRangeF(float start, float end, int decimalPoints = 1) {
	
	int multiplier = 1;
	for (int i = 0; i < decimalPoints; i++)
	{
		multiplier *= 10;
	}

	start *= multiplier;
	end *= multiplier;

	float random = rand() % (int)(end + 1 - start) + start;
	return random / multiplier;
}
float Magnitude(Vector2f vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}
float Distance(Vector2f a, Vector2f b)
{
	return Magnitude(b - a);
}
Vector2f Normalize(Vector2f vector)
{
	float length = Magnitude(vector);
	if (length != 0)
		return Vector2f(vector.x / length, vector.y / length);
	else
		return Vector2f(0.0f, 0.0f);
}
float Clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}
Vector2f ClampMagnitude(Vector2f vector, float maxMagnitude)
{
	float magnitude = Magnitude(vector);
	if (magnitude > maxMagnitude)
		return Normalize(vector) * maxMagnitude;
	else
		return vector;
}
float Lerp(float start, float end, float lerp) {
	return start + lerp * (end - start);
}
Vector2f Lerp(Vector2f start, Vector2f end, float lerp) {
	return Vector2f(Lerp(start.x, end.x, lerp), Lerp(start.y, end.y, lerp));
}
float LerpAngle(float start, float end, float lerp) {
	// Ensure the angles are between 0 and 360
	while (start < 0) start += 360;
	while (start >= 360) start -= 360;
	while (end < 0) end += 360;
	while (end >= 360) end -= 360;

	// Calculate the difference
	float difference = end - start;

	// if the difference is greater than 180, we take the shorter path
	if (difference > 180) difference -= 360;

	// if the difference is less than -180, we take the shorter path
	else if (difference < -180) difference += 360;

	return start + difference * lerp;
}
float Damp(float current, float target, float smoothing, float dt)
{
	return Lerp(current, target, 1 - pow(smoothing, dt));
}
float DampAngle(float current, float target, float smoothing, float dt) {
	// Ensure the angles are between 0 and 360
	while (current < 0) current += 360;
	while (current >= 360) current -= 360;
	while (target < 0) target += 360;
	while (target >= 360) target -= 360;

	// Calculate the difference
	float difference = target - current;

	// if the difference is greater than 180, we take the shorter path
	if (difference > 180) difference -= 360;

	// if the difference is less than -180, we take the shorter path
	else if (difference < -180) difference += 360;

	float dampFactor = 1 - pow(smoothing, dt);
	return current + dampFactor * difference;
}
float Dot(Vector2f a, Vector2f b) {
	return a.x * b.x + a.y * b.y;
}
float Cross(Vector2f a, Vector2f b) {
	return a.x * b.y - a.y * b.x;
}




// SETTINGS



// Global runtime variables
RenderWindow window = { VideoMode::getDesktopMode(), "SFML"};
Vector2u windowSize = window.getSize();
Vector2f center = Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);


int main()
{
	// Local runtime variables

	Clock dtClock;
	float dt = 0.0f;


	Event event;
	while (window.isOpen())
	{
		// close window
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			// Event loop for player input

		}

		dt = dtClock.restart().asSeconds();


		window.clear();

		// Draw objects

		window.display();
	}

	return 0;
}