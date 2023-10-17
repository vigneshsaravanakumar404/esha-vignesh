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

    Vehicle wanderers[5];
    for (int i = 0; i < 5; i++)
    {
        wanderers[i]= Vehicle(rand() % 790, rand() % 440);
    }

    bool updateRandomCircles = true;
    clock_t lastUpdateTime = clock();
    float randomCircleInterval = 30.0f; // Change random circle positions every 5 seconds

    bool updatePosition = true;
    clock_t lastUpdateTimePosOne = clock();
    clock_t lastUpdateTimePosTwo = clock();
    clock_t lastUpdateTimePosThree = clock();
    clock_t lastUpdateTimePosFour = clock();
    clock_t lastUpdateTimePosFive = clock();

    float randomPosIntervalOne = 3.0f; // Change position  positions every 5 seconds
    float randomPosIntervalTwo = 5.0f;
    float randomPosIntervalThree = 2.0f;
    float randomPosIntervalFour = 4.0f;
    float randomPosIntervalFive = 6.0f;

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
            float elapsedSecondsOne = (currentTime - lastUpdateTimePosOne) / CLOCKS_PER_SEC;
            float elapsedSecondsTwo = (currentTime - lastUpdateTimePosTwo) / CLOCKS_PER_SEC;
            float elapsedSecondsThree = (currentTime - lastUpdateTimePosThree) / CLOCKS_PER_SEC;
            float elapsedSecondsFour = (currentTime - lastUpdateTimePosFour) / CLOCKS_PER_SEC;
            float elapsedSecondsFive = (currentTime - lastUpdateTimePosFive) / CLOCKS_PER_SEC;


            if (elapsedSecondsOne >= randomPosIntervalOne)
            {
                wanderers[0].desiredLocation.x = rand() % 790;
                wanderers[0].desiredLocation.y = rand() % 440;
                lastUpdateTimePosOne = currentTime;
            }

            if (elapsedSecondsTwo >= randomPosIntervalTwo)
            {
                wanderers[1].desiredLocation.x = rand() % 790;
                wanderers[1].desiredLocation.y = rand() % 440;
                lastUpdateTimePosTwo = currentTime;
            }
            if (elapsedSecondsThree >= randomPosIntervalThree)
            {
                wanderers[2].desiredLocation.x = rand() % 790;
                wanderers[2].desiredLocation.y = rand() % 440;
                lastUpdateTimePosThree = currentTime;

            }
            if (elapsedSecondsFour >= randomPosIntervalFour)
            {
               
                wanderers[3].desiredLocation.x = rand() % 790;
                wanderers[3].desiredLocation.y = rand() % 440;
                lastUpdateTimePosFour = currentTime;

            }
            if (elapsedSecondsFive >= randomPosIntervalFive)
            {
                wanderers[4].desiredLocation.x = rand() % 790;
                wanderers[4].desiredLocation.y = rand() % 440;
                lastUpdateTimePosFive = currentTime;
            }

        }

        // Draw random circles in the background
        for (int i = 0; i < 50; i++)
        {
            DrawCircle(foods[i].xPos, foods[i].yPos, 5.0f, foods[i].color);
        }

        /*
        for (int i = 0; i < 5; i++)
        {
            wanderers[i].arrive(wanderers[i].desiredLocation);
            wanderers[i]
        }
        */

        wanderers[0].arrive(wanderers[0].desiredLocation);
        wanderers[0].update();
        wanderers[1].arrive(wanderers[1].desiredLocation);
        wanderers[1].update();
        wanderers[2].arrive(wanderers[2].desiredLocation);
        wanderers[2].update();
        wanderers[3].arrive(wanderers[3].desiredLocation);
        wanderers[3].update();
        wanderers[4].arrive(wanderers[4].desiredLocation);
        wanderers[4].update();

        float angleOne = atan2f(wanderers[0].desiredLocation.y - wanderers[0].location.y, wanderers[0].desiredLocation.x - wanderers[0].location.x);
        float angleDiffOne = angleOne - rotationOne;
        rotationOne += angleDiffOne * 0.05f; 

        float angleTwo = atan2f(wanderers[1].desiredLocation.y - wanderers[1].location.y, wanderers[1].desiredLocation.x - wanderers[1].location.x);
        float angleDiffTwo = angleTwo - rotationTwo;
        rotationTwo += angleDiffTwo * 0.05f;

        float angleThree = atan2f(wanderers[2].desiredLocation.y - wanderers[2].location.y, wanderers[2].desiredLocation.x - wanderers[2].location.x);
        float angleDiffThree = angleThree - rotationThree;
        rotationThree += angleDiffThree * 0.05f;

        float angleFour = atan2f(wanderers[3].desiredLocation.y - wanderers[3].location.y, wanderers[3].desiredLocation.x - wanderers[3].location.x);
        float angleDiffFour = angleFour - rotationFour;
        rotationFour += angleDiffFour * 0.05f;

        float angleFive = atan2f(wanderers[4].desiredLocation.y - wanderers[4].location.y, wanderers[4].desiredLocation.x - wanderers[4].location.x);
        float angleDiffFive = angleFive - rotationFive;
        rotationFive += angleDiffFive * 0.05f;
      
        Rectangle shipRectangle = { 0,0, ship.width, ship.height };
        Rectangle newRectangleOne = { wanderers[0].location.x,wanderers[0].location.y, ship.width, ship.height };
        Rectangle newRectangleTwo = { wanderers[1].location.x,wanderers[1].location.y, ship.width, ship.height };
        Rectangle newRectangleThree = { wanderers[2].location.x,wanderers[2].location.y, ship.width, ship.height };
        Rectangle newRectangleFour = { wanderers[3].location.x,wanderers[3].location.y, ship.width, ship.height };
        Rectangle newRectangleFive = { wanderers[4].location.x,wanderers[4].location.y, ship.width, ship.height };
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
