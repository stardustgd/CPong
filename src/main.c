#include "raylib.h"

#include <stdio.h>

// Initialize
static const int screenWidth = 1920;
static const int screenHeight = 1080;
static const int frameRate = 144; 

static Rectangle playerOnePaddle = { 100.0f, (float)screenHeight / 2, 30, 200 };
static Rectangle playerTwoPaddle = { screenWidth - 200, (float)screenHeight / 2, 30, 200 };

static Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2};
static Vector2 ballVelocity = { -5.0f, 5.0f }; // Initial velocity heads towards playerOne

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UpdateDrawFrame(void);

int main(void)
{
    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "Pong");
    InitGame();

    SetTargetFPS(frameRate);

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    // UnloadSound(paddleHitSound);

    CloseAudioDevice();
    CloseWindow();
        
    return 0;
}

void InitGame(void)
{

}

void UpdateGame(void)
{

    if (IsKeyDown(KEY_UP))
        {
            playerOnePaddle.y = ( (playerOnePaddle.y - 4.0f) < 0.0f) ? playerOnePaddle.y : playerOnePaddle.y - 4.0f;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            playerOnePaddle.y = ( (playerOnePaddle.y + 4.0f) > (float)screenHeight - 200) ? playerOnePaddle.y : playerOnePaddle.y + 4.0f;
        }

        // Ball collides with paddle
        if ( (CheckCollisionCircleRec(ballPosition, 25.0f, playerOnePaddle)) || (CheckCollisionCircleRec(ballPosition, 25.0f, playerTwoPaddle)) )
        {
            // if ( (playerOnePaddle.y <= ballPosition.y) && (playerOnePaddle.y >= ballPosition.y - 100) ) // hits top half of paddle
            // {
            //     printf("Hits top half of paddle\n");
            //     ballVelocity.x = -(ballVelocity.x);
            //     ballVelocity.y = (ballVelocity.y);
            // }

            // if ( (playerOnePaddle.y <= ballPosition.y + 100) && (playerOnePaddle.y >= ballPosition.y + 200) ) printf("Hits bottom half of paddle\n");

            ballVelocity.x = -(ballVelocity.x);
            ballVelocity.y = -(ballVelocity.y);

            // PlaySound(paddleHitSound);
        }
        // Ball collides with top of screen
        if ( (ballPosition.y == screenHeight) || (ballPosition.y == 0)) ballVelocity.y = -(ballVelocity.y);

        // Ball collides with sides of screen
        if ( (ballPosition.x == screenWidth) || (ballPosition.x == 0)) ballVelocity.x = -(ballVelocity.x);

        ballPosition.x += ballVelocity.x;
        ballPosition.y += ballVelocity.y;

        // FIXME: RESET BUTTON FOR TESTING
        if (IsKeyDown(KEY_R))
        {
            playerOnePaddle.y = (float)screenHeight / 2;
            ballPosition.x = (float)screenWidth / 2;
            ballPosition.y = (float)screenHeight / 2;
            ballVelocity.x = -5.0f;
            ballVelocity.y = 5.0f;
        }
}

void DrawGame(void)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(playerOnePaddle, WHITE);
    DrawRectangleRec(playerTwoPaddle, WHITE);
    DrawCircleV(ballPosition, 25.0f, WHITE);
    EndDrawing();
}

void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}