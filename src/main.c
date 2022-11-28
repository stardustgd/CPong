#include "raylib.h"

#include <stdio.h>

typedef struct Player {
    Rectangle paddle;
    int score; 
} Player;

typedef struct Ball {
    Vector2 position;
    Vector2 velocity;
} Ball;

typedef enum GameState {
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameState;

// Initialize
static const int screenWidth = 1280;
static const int screenHeight = 720;
static const int frameRate = 144;

static Player playerOne = { 0 };
static Player playerTwo = { 0 };
static Ball ball = { 0 };
static GameState currentState = LOGO;

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UpdateDrawFrame(void);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Pong");
    InitGame();

    int framesCounter = 0;

    SetTargetFPS(frameRate);

    // Main game loop
    while (!WindowShouldClose())
    {
        switch (currentState)
        {
            case LOGO:
            {
                framesCounter++;

                if (framesCounter > frameRate * 2)
                {
                    currentState = TITLE;
                }
            } break;
            case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentState = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                UpdateDrawFrame();
            } break;
            case ENDING:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentState = TITLE;
                }
            } break;
            default: break;


        }
        DrawGame();
        // UpdateDrawFrame();
    }

    CloseWindow();
        
    return 0;
}

void InitGame(void)
{
    playerOne.paddle = (Rectangle){ 100.0f, (float)screenHeight / 2 - 100, 30, 200 };
    playerOne.score = 0;
    playerTwo.paddle = (Rectangle){ screenWidth - 100, (float)screenHeight / 2 - 100, 30, 200 };
    playerTwo.score = 0;

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
    if ( (ball.position.x == screenWidth))
    {
        playerOne.score++;
    }

    if ((ball.position.x == 0))
    {
        playerTwo.score++;
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

    switch(currentState) 
    {
        case LOGO:
        {
            DrawText("CPong", screenWidth/2, screenHeight/2, 40, WHITE);
        } break;
        case TITLE:
        {
            DrawText("PONG", 20, 20, 40, WHITE);
        } break;
        case GAMEPLAY:
        {
            DrawRectangleRec(playerOne.paddle, WHITE);
            DrawRectangleRec(playerTwo.paddle, WHITE);
            DrawCircleV(ball.position, 25.0f, WHITE);
            DrawText(TextFormat("%d", playerOne.score), (screenWidth/2)/2, 30, 75, WHITE);
            DrawText(TextFormat("%d", playerTwo.score), (screenWidth - (screenWidth/4)), 30, 75, WHITE);
        } break;
        case ENDING:
        {
            DrawText("GAME OVER", screenWidth/2, screenHeight/2, 50, WHITE);
        } break;
        default: break;
    }
    // DrawRectangleRec(playerOne.paddle, WHITE);
    // DrawRectangleRec(playerTwo.paddle, WHITE);
    // DrawCircleV(ball.position, 25.0f, WHITE);
    // DrawText(TextFormat("%d", playerOne.score), (screenWidth/2)/2, 30, 75, WHITE);
    // DrawText(TextFormat("%d", playerTwo.score), (screenWidth - (screenWidth/4)), 30, 75, WHITE);
    EndDrawing();
}

void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}