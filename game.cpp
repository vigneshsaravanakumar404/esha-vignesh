#include "raylib.h"
#include "raymath.h"
#include <thread>
#include <iostream>
#include "Header.h"


using namespace std;

typedef struct Food
{
public:
    float xPos;
    float yPos;
    Color color;
    Food() {};
    Food(float x, float y, Color colorS)
    {
        xPos = x;
        yPos = y;
        color = colorS;
    }
};



int main(void)
{
    InitWindow(800, 450, "raylib [core] example - basic window");
    SetTargetFPS(60);
    float x = 0;
    float y = 0;
    float theta;

    float desiredX = 200;
    float desiredY = 300;
    int random = rand() % 9;

    float rotationOne;
    float rotationTwo;
    float rotationThree;
    float rotationFour;
    float rotationFive;


    Color colors[5] = {ORANGE, BLUE, GREEN, RED, VIOLET};



    Food foods[50];
    for (int i = 0; i < 50; i++)
    {
        foods[i] = Food(rand() % 790, rand() % 440, colors[rand() % 5]);

    }


    Vehicle wandererOne = Vehicle(rand() % 790, rand() % 440);
    Vehicle wandererTwo = Vehicle(rand() % 790, rand() % 440);
    Vehicle wandererThree = Vehicle(rand() % 790, rand() % 440);
    Vehicle wandererFour = Vehicle(rand() % 790, rand() % 440);
    Vehicle wandererFive = Vehicle(rand() % 790, rand() % 440);





    bool updateRandomCircles = true;
    clock_t lastUpdateTime = clock();
    float randomCircleInterval = 30.0f; // Change random circle positions every 5 seconds

    bool updatePosition = true;
    clock_t lastUpdateTimePos = clock();
    float randomPosInterval = 3.0f; // Change position  positions every 5 seconds

    Texture2D ship = LoadTexture("ships.png"); 
    ship.width *= 0.1;
    ship.height *= 0.1;
    rotationOne = 0;
    rotationTwo = 0;
    rotationThree = 0;
    rotationFour = 0;
    rotationFive = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //main simualtion timer for 30 seconds
        if (updateRandomCircles)
        {
            clock_t currentTime = clock();
            float elapsedSeconds = (currentTime - lastUpdateTime) / CLOCKS_PER_SEC;

            if (elapsedSeconds >= randomCircleInterval)
            {

                for (int i = 0; i < 50; i++)
                {
                    foods[i] = Food(rand() % 790, rand() % 440, colors[rand()%5]);

                }
                lastUpdateTime = currentTime;
            }

        }

        //updates position every 3 seconds to simulate wandering
        if (updatePosition)
        {
            clock_t currentTime = clock();
            float elapsedSeconds = (currentTime - lastUpdateTimePos) / CLOCKS_PER_SEC;

            if (elapsedSeconds >= randomPosInterval)
            {
                wandererOne.desiredLocation.x = rand() % 790;
                wandererOne.desiredLocation.y = rand() % 440; 
                wandererTwo.desiredLocation.x = rand() % 790;
                wandererTwo.desiredLocation.y = rand() % 440;
                wandererThree.desiredLocation.x = rand() % 790;
                wandererThree.desiredLocation.y = rand() % 440;
                wandererFour.desiredLocation.x = rand() % 790;
                wandererFour.desiredLocation.y = rand() % 440;
                wandererFive.desiredLocation.x = rand() % 790;
                wandererFive.desiredLocation.y = rand() % 440;

                lastUpdateTimePos = currentTime;

            }

        }

        // Draw random circles in the background
        for (int i = 0; i < 50; i++)
        {
            DrawCircle(foods[i].xPos, foods[i].yPos, 5.0f, foods[i].color);
        }

        wandererOne.arrive(wandererOne.desiredLocation);
        wandererOne.update();
        wandererTwo.arrive(wandererTwo.desiredLocation);
        wandererTwo.update();
        wandererThree.arrive(wandererThree.desiredLocation);
        wandererThree.update();
        wandererFour.arrive(wandererFour.desiredLocation);
        wandererFour.update();
        wandererFive.arrive(wandererFive.desiredLocation);
        wandererFive.update();

        float angleOne = atan2f(wandererOne.desiredLocation.y - wandererOne.location.y, wandererOne.desiredLocation.x - wandererOne.location.x);
        float angleDiffOne = angleOne - rotationOne;
        rotationOne += angleDiffOne * 0.05f; 

        float angleTwo = atan2f(wandererTwo.desiredLocation.y - wandererTwo.location.y, wandererTwo.desiredLocation.x - wandererTwo.location.x);
        float angleDiffTwo = angleTwo - rotationTwo;
        rotationTwo += angleDiffTwo * 0.05f;

        float angleThree = atan2f(wandererThree.desiredLocation.y - wandererThree.location.y, wandererThree.desiredLocation.x - wandererThree.location.x);
        float angleDiffThree = angleThree - rotationThree;
        rotationThree += angleDiffThree * 0.05f;

        float angleFour = atan2f(wandererFour.desiredLocation.y - wandererFour.location.y, wandererFour.desiredLocation.x - wandererFour.location.x);
        float angleDiffFour = angleFour - rotationFour;
        rotationFour += angleDiffFour * 0.05f;

        float angleFive = atan2f(wandererFive.desiredLocation.y - wandererFive.location.y, wandererFive.desiredLocation.x - wandererFive.location.x);
        float angleDiffFive = angleFive - rotationFive;
        rotationFive += angleDiffFive * 0.05f;
      
        Rectangle shipRectangle = { 0,0, ship.width, ship.height };
        Rectangle newRectangleOne = { wandererOne.location.x,wandererOne.location.y, ship.width, ship.height };
        Rectangle newRectangleTwo = { wandererTwo.location.x,wandererTwo.location.y, ship.width, ship.height };
        Rectangle newRectangleThree = { wandererThree.location.x,wandererThree.location.y, ship.width, ship.height };
        Rectangle newRectangleFour = { wandererFour.location.x,wandererFour.location.y, ship.width, ship.height };
        Rectangle newRectangleFive = { wandererFive.location.x,wandererFive.location.y, ship.width, ship.height };
        Vector2 shipCenter = { ship.width / 2, ship.height / 2 };

        DrawTexturePro(ship, shipRectangle, newRectangleOne, shipCenter, rotationOne * RAD2DEG + 90, WHITE);
        DrawTexturePro(ship, shipRectangle, newRectangleTwo, shipCenter, rotationTwo* RAD2DEG + 90, WHITE);
        DrawTexturePro(ship, shipRectangle, newRectangleThree, shipCenter, rotationThree* RAD2DEG + 90, WHITE);
        DrawTexturePro(ship, shipRectangle, newRectangleFour, shipCenter, rotationFour* RAD2DEG + 90, WHITE);
        DrawTexturePro(ship, shipRectangle, newRectangleFive, shipCenter, rotationFive * RAD2DEG + 90, WHITE);

        EndDrawing();
    }


    CloseWindow();
    return 0;
}
