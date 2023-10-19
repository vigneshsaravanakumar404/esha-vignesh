#pragma 

#include "raylib.h"
#include "raymath.h"

class Vehicle
{
public:
    Vector2 location;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 desiredLocation;
    float r;
    float maxforce;
    float maxspeed;
    Vector2 steer;

    Vehicle();

    Vehicle(float x, float y, float maxSpeed);

    void update();
    void applyForce(Vector2 force);
    void arrive(Vector2 target, float deltaTime);
    float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);

};