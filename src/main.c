#include "raylib.h"

#include <stdio.h>

typedef struct Paddle {
    Rectangle paddle;
} Paddle;

typedef struct Ball {
    Vector2 position;
    Vector2 velocity;
} Ball;

// Initialize
static const int screenWidth = 1920;
static const int screenHeight = 1080;
static const int frameRate = 144; 

static int playerOneScore = 0;
static int playerTwoScore = 0;

static Paddle playerOne = { 0 };
static Paddle playerTwo = { 0 };
static Ball ball = { 0 };

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UpdateDrawFrame(void);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Pong");
    InitGame();

    SetTargetFPS(frameRate);

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();
        
    return 0;
}

void InitGame(void)
{
    playerOne.paddle = (Rectangle){ 100.0f, (float)screenHeight / 2 - 100, 30, 200 };
    playerTwo.paddle = (Rectangle){ screenWidth - 100, (float)screenHeight / 2 - 100, 30, 200 };

    ball.position = (Vector2){ (float)screenWidth / 2, (float)screenHeight / 2 };
    ball.velocity = (Vector2){ -5.0f, 5.0f };
}

void UpdateGame(void)
{

    // Paddle Movement
    if (IsKeyDown(KEY_UP))
        {
            playerOne.paddle.y = ( (playerOne.paddle.y - 4.0f) < 0.0f) ? playerOne.paddle.y : playerOne.paddle.y - 4.0f;
        }
    if (IsKeyDown(KEY_DOWN))
    {
        playerOne.paddle.y = ( (playerOne.paddle.y + 4.0f) > (float)screenHeight - 200) ? playerOne.paddle.y : playerOne.paddle.y + 4.0f;
    }

    // Ball collides with paddle
    if ( CheckCollisionCircleRec(ball.position, 25.0f, playerOne.paddle) || CheckCollisionCircleRec(ball.position, 25.0f, playerTwo.paddle) )
    {
        if ( ((playerOne.paddle.y < ball.position.y) && (playerOne.paddle.y > ball.position.y - 100)) ||
             ((playerTwo.paddle.y <= ball.position.y) && (playerTwo.paddle.y > ball.position.y - 100)) ) // hits top half of paddle
        {
            ball.velocity.x = -(ball.velocity.x);
            ball.velocity.y = (ball.velocity.y);
        }

        if ( ((playerOne.paddle.y < (ball.position.y - 100)) && (playerOne.paddle.y > (ball.position.y - 200))) ||
             ((playerTwo.paddle.y <= (ball.position.y - 100)) && (playerTwo.paddle.y > (ball.position.y - 200))) ) // hits bottom half of paddle
        {
            ball.velocity.x = -(ball.velocity.x);
            ball.velocity.y = -(ball.velocity.y);
        }

        // PlaySound(paddleHitSound);
    }
    // Ball collides with top of screen
    if ( (ball.position.y == screenHeight) || (ball.position.y == 0)) ball.velocity.y = -(ball.velocity.y);

    // Ball collides with sides of screen
    if ( (ball.position.x == screenWidth)) // Player two scores
    {
        playerTwoScore++;
    }

    if ((ball.position.x == 0)) // Player one scores
    {
        playerOneScore++;
    }

    ball.position.x += ball.velocity.x;
    ball.position.y += ball.velocity.y;

    // FIXME: RESET BUTTON FOR TESTING
    if (IsKeyDown(KEY_R))
    {
        InitGame();
    }
}

void DrawGame(void)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(playerOne.paddle, WHITE);
    DrawRectangleRec(playerTwo.paddle, WHITE);
    DrawCircleV(ball.position, 25.0f, WHITE);
    EndDrawing();
}

void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}