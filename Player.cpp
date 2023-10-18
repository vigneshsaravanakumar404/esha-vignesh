#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "Header.h"

using namespace std;

Vehicle::Vehicle(void)
{

}

Vehicle::Vehicle(float x, float y)
{
	acceleration = Vector2{0.0f, 0.0f};
	velocity = Vector2{0.0f, 0.0f};
	location = Vector2{x, y};
	r = 3.0;
	maxspeed = 3.0f;
	maxforce = 0.1f;
	desiredLocation = Vector2{0.0f, 0.0f};
}

void Vehicle::update()
{
	velocity = Vector2Add(acceleration, velocity);
	Vector2ClampValue(velocity, 0.0f, maxspeed);
	location = Vector2Add(velocity, location);
	acceleration = Vector2Multiply(Vector2{0.0f,0.0f}, acceleration);
		
}

void Vehicle::applyForce(Vector2 force)
{
	acceleration = Vector2Add(force, acceleration);
}

void Vehicle::arrive(Vector2 target) {
	Vector2 desired = Vector2Subtract(target, location);
	float d = sqrt((desired.x)* (desired.x) + (desired.y)*(desired.y));
	desired = Vector2Normalize(desired);
	if (d < 100) {
		float m = map(d, 0, 100, 0, maxspeed);
		desired = Vector2Scale(desired, m);
	}
	else 
	{
		desired = Vector2Scale(desired, maxspeed);

	}

	Vector2 steer = Vector2Subtract(desired, velocity);
	Vector2ClampValue(steer, 0.0f, maxforce);
	applyForce(steer);
}

float Vehicle::map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
	return (value - fromLow) / (fromHigh - fromLow) * (toHigh - toLow) + toLow;
}

