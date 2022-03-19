#include "raylib.h"

int main(void)
{
    // Initialize
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int frameRate = 144; 

    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "Pong");

    Rectangle playerOnePaddle = { 100.0f, (float)screenHeight / 2, 30, 200 };
    Rectangle playerTwoPaddle = { screenWidth - 200, (float)screenHeight / 2, 30, 200 };

    Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2};
    // Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight};
    Vector2 ballVelocity = { -5.0f, 5.0f }; // Initial velocity heads towards playerOne

    Sound paddleHitSound = LoadSound("C:\\Users\\basti\\Documents\\Coding Projects\\C++\\Pong\\Resources\\boop.wav");

    SetTargetFPS(frameRate);

    // Main game loop
    while (!WindowShouldClose())
    {
        // TODO: collision check
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
            ballVelocity.x = -(ballVelocity.x);
            ballVelocity.y = -(ballVelocity.y);
            PlaySound(paddleHitSound);
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

        // Draw graphics
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(playerOnePaddle, WHITE);
            DrawRectangleRec(playerTwoPaddle, WHITE);
            DrawCircleV(ballPosition, 25.0f, WHITE);
        EndDrawing();
    }

    UnloadSound(paddleHitSound);

    CloseAudioDevice();
    CloseWindow();
        
    return 0;
}