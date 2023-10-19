#include "raylib.h"
#include "raymath.h"
#include <thread>
#include <iostream>
#include "Header.h"
#include <string>

using namespace std;

// TODO: Fix rotation of agent
// TODO: Make the agent not slow down when it is close to the target
// TODO: Movement even when there is no food in 
// TODO: Create visual for cross mutation for change in blue speed

// Structs
typedef struct Food {
public:
    float xPos;
    float yPos;
    Color color;
    Food() {};
    Food(float x, float y, Color colorS) {
        xPos = x;
        yPos = y;
        color = colorS;
    }
} Food;
typedef struct Ship {
public:

};
typedef struct AgentOne {
public:
    bool valid1;
    float visionRange;
    float xPos;
    float yPos;
    float maxSpeed = 3.0f;
    clock_t timer;
    float randTime = 0.0f;
    Vehicle vehicle;

    float targetX;
    float targetY;

    int foodEaten = 0;
};
typedef struct AgentTwo {
    bool valid2;
    float visionRange = 5.0f;
    float xPos;
    float yPos;
    float maxSpeed;
    clock_t timer;
    float randTime = 0.0f;
    Vehicle vehicle;

    float targetX;
    float targetY;

    int foodEaten = 0;
};

// Global Variables
float randomCircleInterval = 30.0f;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 1600;


// Main Loop
int main(void) {

    // Initialization
    InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "raylib [core] example - basic window");
    SetTargetFPS(60);
    Texture2D AgentOneTexture = LoadTexture("C:\\Users\\eshav\\OneDrive\\Desktop\\red.png");
    Texture2D AgentTwoTexture = LoadTexture("C:\\Users\\eshav\\OneDrive\\Desktop\\blue.png");

    // Resize the textures
    AgentOneTexture.width /= 5;
    AgentOneTexture.height /= 5;
    AgentTwoTexture.width /= 5;
    AgentTwoTexture.height /= 5;

    // Food
    Color colors[5] = { ORANGE, BLUE, GREEN, RED, VIOLET };
    Food foods[50];
    for (int i = 0; i < 50; i++) {
        foods[i] = Food(rand() % SCREEN_HEIGHT, rand() % SCREEN_WIDTH, colors[rand() % 5]);
    }

    // Vehicles
    AgentOne agents1[5];
    AgentTwo agents2[5];

    // Current time
    clock_t currentTime = clock();

    // Round Timer
    clock_t roundTimer = clock();

    for (int i = 0; i < 5; i++) {
        // Has small range, big speed
        agents1[i].vehicle = Vehicle(rand() % SCREEN_HEIGHT, rand() % SCREEN_WIDTH, agents1->maxSpeed);
        agents1[i].vehicle.maxspeed = 3.0f;
        agents1[i].vehicle.maxforce = 0.1f;
        agents1[i].vehicle.r = 3.0f;
        agents1[i].visionRange = 5.0f;
        agents1[i].timer = clock();
        agents1[i].randTime = 3.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 - 3.5)));
        agents1[i].targetX = rand() % SCREEN_HEIGHT;
        agents1[i].targetY = rand() % SCREEN_WIDTH;
        agents1[i].valid1 = true;

        // Has big range, small speed
        agents2[i].vehicle = Vehicle(rand() % SCREEN_HEIGHT, rand() % SCREEN_WIDTH, agents2->maxSpeed);
        agents2[i].vehicle.maxspeed = 1.5f;
        agents2[i].vehicle.maxforce = 0.1f;
        agents2[i].vehicle.r = 3.0f;
        agents2[i].visionRange = 100.0f;
        agents2[i].timer = clock();
        agents2[i].randTime = 3.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 - 3.5)));
        agents2[i].targetX = rand() % SCREEN_HEIGHT;
        agents2[i].targetY = rand() % SCREEN_WIDTH;
        agents2[i].valid2 = true;
    }


    // Main Loop
    while (!WindowShouldClose()) {

        // Rest
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw Food
        for (int i = 0; i < 50; i++) {
            DrawCircle(foods[i].xPos, foods[i].yPos, 5.0f, foods[i].color);
        }

        // Draw Agents
        for (int i = 0; i < 5; i++) {

            // Move towards food or random target
            int numberOfFoodParticles = sizeof(foods) / sizeof(Food);
            bool foundFood = false;

            for (int j = 0; j < numberOfFoodParticles; j++) {
                float dx = foods[j].xPos - agents2[i].vehicle.location.x;
                float dy = foods[j].yPos - agents2[i].vehicle.location.y;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < agents2[i].visionRange) {
                    agents2[i].targetX = foods[j].xPos;
                    agents2[i].targetY = foods[j].yPos;
                    foundFood = true;
                    break;
                }

            }

            // Draw the agents using the texture centered at the stored coordinates
            if (agents1[i].valid1)
            {
                // Calculate the top-left corner coordinates to center the texture at the agent's location
                int x1 = agents1[i].vehicle.location.x - AgentOneTexture.width / 2;
                int y1 = agents1[i].vehicle.location.y - AgentOneTexture.height / 2;

                DrawTexture(AgentOneTexture, x1, y1, WHITE);

                // Rectangles Representing Speed for AgentOne
                float speedFraction = agents1[i].vehicle.maxspeed / 25.0f;
                int redComponent = static_cast<int>(255 * (1.0f - speedFraction));
                int greenComponent = static_cast<int>(255 * speedFraction);
                Color highlightColor = { redComponent, greenComponent, 0, 128 };
                int outlineThickness = 2;
                Color outlineColor = { 0, 0, 0, 200 };
                DrawRectangleLinesEx({ (float)x1 - outlineThickness, (float)y1 - outlineThickness, (float)AgentOneTexture.width + 2 * outlineThickness+agents1[i].visionRange, (float)AgentOneTexture.height + 2 * outlineThickness + agents1[i].visionRange}, outlineThickness, outlineColor);
                DrawRectangle(x1, y1, AgentOneTexture.width + agents1[i].visionRange, AgentOneTexture.height + agents1[i].visionRange, highlightColor);

                // Display the number of food particles eaten by the agent on the center of the agent
                DrawText(std::to_string(agents1[i].foodEaten).c_str(), agents1[i].vehicle.location.x, agents1[i].vehicle.location.y, 20, BLACK);

                // if more than randTime seconds have passed, change the target
                if (clock() - agents1[i].timer > agents1[i].randTime * CLOCKS_PER_SEC) {
                    agents1[i].timer = clock();
                    agents1[i].randTime = rand() % 10 + 1;
                    agents1[i].targetX = rand() % SCREEN_HEIGHT;
                    agents1[i].targetY = rand() % SCREEN_WIDTH;
                }

                // Make the agent move towards the target
                agents1[i].vehicle.arrive(Vector2{ agents1[i].targetX, agents1[i].targetY });
                agents1[i].vehicle.update();

                // Delete Food
                for (int j = 0; j < numberOfFoodParticles; j++) {
                    float dx = foods[j].xPos - agents1[i].vehicle.location.x;
                    float dy = foods[j].yPos - agents1[i].vehicle.location.y;
                    float distance = sqrt(dx * dx + dy * dy);

                    if (distance < agents1[i].visionRange) {
                        foods[j].xPos = 10000;
                        foods[j].yPos = 10000;
                        foods[j].color = colors[rand() % 5];
                        agents1[i].foodEaten++;
                    }
                }

            }

            if (agents2[i].valid2)
            {
                // Calculate the top-left corner coordinates to center the texture at the agent's location
                int x2 = agents2[i].vehicle.location.x - AgentTwoTexture.width / 2;
                int y2 = agents2[i].vehicle.location.y - AgentTwoTexture.height / 2;

                DrawTexture(AgentTwoTexture, x2, y2, WHITE);

                // Circles Representing Vision Range for AgentTwo
                DrawCircleLines(agents2[i].vehicle.location.x, agents2[i].vehicle.location.y, agents2[i].visionRange, BLACK);

                // Display the number of food particles eaten by the agent on the center of the agent
                DrawText(std::to_string(agents2[i].foodEaten).c_str(), agents2[i].vehicle.location.x, agents2[i].vehicle.location.y, 20, BLACK);
            
                // If no food particle is within range, then set a random target
                if (!foundFood && (clock() - currentTime) > 5 * CLOCKS_PER_SEC) {
                    agents2[i].targetX = rand() % SCREEN_HEIGHT;
                    agents2[i].targetY = rand() % SCREEN_WIDTH;
                    currentTime = clock();
                }

                // Make the agent move towards the target
                agents2[i].vehicle.arrive(Vector2{ agents2[i].targetX, agents2[i].targetY });
                agents2[i].vehicle.update();

                //Delete Food
                for (int j = 0; j < numberOfFoodParticles; j++) {
                    float dx = foods[j].xPos - agents2[i].vehicle.location.x;
                    float dy = foods[j].yPos - agents2[i].vehicle.location.y;
                    float distance = sqrt(dx * dx + dy * dy);

                    if (distance < 5.0f) {
                        foods[j].xPos = 10000;
                        foods[j].yPos = 10000;
                        foods[j].color = colors[rand() % 5];
                        agents2[i].foodEaten++;
                    }
                }
            
            }
            
            // Timer
            DrawText(std::to_string(30 - ((clock() - roundTimer) / CLOCKS_PER_SEC)).c_str(), SCREEN_HEIGHT - 50, 50, 20, BLACK);

            // Rounds
            if (clock() - roundTimer > 30 * CLOCKS_PER_SEC) {
                // Reset
                roundTimer = clock();
                for (int j = 0; j < 50; j++) {
                    foods[j] = Food(rand() % SCREEN_HEIGHT, rand() % SCREEN_WIDTH, colors[rand() % 5]);
                }

                // if two agents are next to each other both of them get the highest speed and vision range between them
                for (int j = 0; j < 5; j++) {
                    if (agents1[j].valid1)
                    {
                        for (int k = 0; k < 5; k++) {
                            if (agents2[k].valid2)
                            {
                                float dx = agents1[j].vehicle.location.x - agents2[k].vehicle.location.x;
                                float dy = agents1[j].vehicle.location.y - agents2[k].vehicle.location.y;
                                float distance = sqrt(dx * dx + dy * dy);

                                if (distance < 200.0f) {
                                    agents1[j].visionRange *= 1.5;
                                    agents2[k].vehicle.maxspeed *= 1.5;
                                }
                            }
                            
                        }

                    }
                    
                }

                


                // Evolution Logic
                int maxFood1 = -1, maxFood2 = -1;
                int secondMaxFood1 = -1, secondMaxFood2 = -1;
                int thirdMaxFood1 = -1, thirdMaxFood2 = -1;
                int minFood1 = INT_MAX, minFood2 = INT_MAX;
                int maxIdx1 = -1, maxIdx2 = -1;
                int secondIdx1 = -1, secondIdx2 = -1;
                int thirdIdx1 = -1, thirdIdx2 = -1;
                int minIdx1 = -1, minIdx2 = -1;

                for (int i = 0; i < 5; i++) {
                    // Logic for AgentOne
                    if (agents1[i].valid1)
                    {
                        if (agents1[i].foodEaten > maxFood1) {
                            thirdMaxFood1 = secondMaxFood1;
                            secondMaxFood1 = maxFood1;
                            maxFood1 = agents1[i].foodEaten;

                            thirdIdx1 = secondIdx1;
                            secondIdx1 = maxIdx1;
                            maxIdx1 = i;
                        }

                        if (agents1[i].foodEaten < minFood1) {
                            minFood1 = agents1[i].foodEaten;
                            minIdx1 = i;
                            
                        }
                        
                    }                    
                    

                    // Logic for AgentTwo
                    if (agents2[i].valid2)
                    {
                        if (agents2[i].foodEaten > maxFood2) {
                            thirdMaxFood2 = secondMaxFood2;
                            secondMaxFood2 = maxFood2;
                            maxFood2 = agents2[i].foodEaten;

                            thirdIdx2 = secondIdx2;
                            secondIdx2 = maxIdx2;
                            maxIdx2 = i;
                        }

                        if (agents2[i].foodEaten < minFood2) {
                            minFood2 = agents2[i].foodEaten;
                            minIdx2 = i;
                        }
                        
                    }
                }

                // Apply multipliers to AgentOne and AgentTwo
                if (maxIdx1 != -1) agents1[maxIdx1].vehicle.maxspeed *= 1.5;
                if (secondIdx1 != -1) agents1[secondIdx1].vehicle.maxspeed *= 1.35;
                if (thirdIdx1 != -1) agents1[thirdIdx1].vehicle.maxspeed *= 1.1;

                if (maxIdx2 != -1) agents2[maxIdx2].visionRange *= 1.5;
                if (secondIdx2 != -1) agents2[secondIdx2].visionRange *= 1.35;
                if (thirdIdx2 != -1) agents2[thirdIdx2].visionRange *= 1.1;

                // "Delete" the least-performing agents by moving them far away
                if (minIdx1 != -1) {
                    agents1[minIdx1].valid1 = false;
                }
                if (minIdx2 != -1) {
                    agents2[minIdx2].valid2 = false;
                }

                

                // Reset food eaten for the next round
                for (int i = 0; i < 5; i++) {
                    agents1[i].foodEaten = 0;
                    agents2[i].foodEaten = 0;
                }
            }



        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
