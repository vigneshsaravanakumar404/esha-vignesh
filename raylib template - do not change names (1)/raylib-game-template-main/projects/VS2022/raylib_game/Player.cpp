#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "Header.h"

using namespace std;
Vehicle::Vehicle(void) {

}
Vehicle::Vehicle(float x, float y, float maxSpeed)
{
	acceleration = Vector2{ 0.0f, 0.0f };
	velocity = Vector2{ 0.0f, 0.0f };
	location = Vector2{ x, y };
	r = 3.0;
	maxspeed = maxSpeed;
	maxforce = 0.5f;
	desiredLocation = Vector2{ 0.0f, 0.0f };
}

void Vehicle::update()
{
	velocity = Vector2Add(velocity, acceleration);
	Vector2ClampValue(velocity, 0.0f, maxspeed);
	location = Vector2Add(location, velocity);
	acceleration = Vector2{ 0.0f, 0.0f };
}


void Vehicle::applyForce(Vector2 force)
{
	acceleration = Vector2Add(force, acceleration);
}

void Vehicle::arrive(Vector2 target, float deltaTime) {
    const float scaleFactor = 0.16f, maxPlayerVelocity = 3.0f, slowingRadius = 115.0f, maxSpeed = 3.5f, maxForce = 4.5f, maxSteeringRate = PI / 10.5f, stopRadius = 1.0f, timeToWait = 6.0;
    float deltaTime1 = deltaTime;

    Vector2 desired = Vector2Subtract(target, location);
    float d = Vector2Length(desired);  // Calculate the distance

    if (d > 0) {
        // Normalize the desired velocity vector and scale it to maxSpeed
        desired = Vector2Normalize(desired);
        if (d < stopRadius) {
            // If within the stop radius, bring the vehicle to a stop
            desired = Vector2{ 0.0f, 0.0f };
        }
        else if (d < slowingRadius) {
            // Within the slowing radius, map the speed between 0 and maxSpeed
            float m = map(d, 0, slowingRadius, 0, maxspeed);
            desired = Vector2Scale(desired, m);
        }
        else {
            desired = Vector2Scale(desired, maxspeed);
        }

        // Calculate the steering force and clamp it
        Vector2 steer = Vector2Subtract(desired, velocity);
        Vector2ClampValue(steer, 0.0f, maxSteeringRate);

        // Apply the force considering the time step (deltaTime)
        steer = Vector2Scale(steer, deltaTime1);
        applyForce(steer);

        // Update the velocity considering the time step (deltaTime)
        velocity = Vector2Add(velocity, Vector2Scale(steer, deltaTime1));
        Vector2ClampValue(velocity, 0.0f, maxspeed);
    }
}


float Vehicle::map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
	return (value - fromLow) / (fromHigh - fromLow) * (toHigh - toLow) + toLow;
}
