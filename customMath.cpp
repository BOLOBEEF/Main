
// Custom Math Functions

int RandomRange(int Intialization, int end) {
	return rand() % (end + 1 - Intialization) + Intialization;
}
float RandomRangeF(float Intialization, float end, int decimalPoints = 1) {
	
	int multiplier = 1;
	for (int i = 0; i < decimalPoints; i++)
	{
		multiplier *= 10;
	}

	Intialization *= multiplier;
	end *= multiplier;

	float random = rand() % (int)(end + 1 - Intialization) + Intialization;
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
float Lerp(float Intialization, float end, float lerp) {
	return Intialization + lerp * (end - Intialization);
}
Vector2f Lerp(Vector2f Intialization, Vector2f end, float lerp) {
	return Vector2f(Lerp(Intialization.x, end.x, lerp), Lerp(Intialization.y, end.y, lerp));
}
float LerpAngle(float Intialization, float end, float lerp) {
	// Ensure the angles are between 0 and 360
	while (Intialization < 0) Intialization += 360;
	while (Intialization >= 360) Intialization -= 360;
	while (end < 0) end += 360;
	while (end >= 360) end -= 360;

	// Calculate the difference
	float difference = end - Intialization;

	// if the difference is greater than 180, we take the shorter path
	if (difference > 180) difference -= 360;

	// if the difference is less than -180, we take the shorter path
	else if (difference < -180) difference += 360;

	return Intialization + difference * lerp;
}
float Damp(float current, float target, float speed, float dt)
{
	if (speed <= 0) return current;

	return target + (current - target) * Clamp(pow(1 / speed, dt), 0, 1);
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