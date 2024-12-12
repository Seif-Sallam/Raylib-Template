/*******************************************************************************************
*
*   raylib [core] example - Custom logging
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example contributed by Pablo Marcos Oltra (@pamarcos) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2024 Pablo Marcos Oltra (@pamarcos) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdio.h>                  // Required for: fopen(), fclose(), fputc(), fwrite(), printf(), fprintf(), funopen()
#include <time.h>                   // Required for: time_t, tm, time(), localtime(), strftime()

// Custom logging function
void CustomLog(int msgType, const char *text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO: printf("[INFO] : "); break;
        case LOG_ERROR: printf("[ERROR]: "); break;
        case LOG_WARNING: printf("[WARN] : "); break;
        case LOG_DEBUG: printf("[DEBUG]: "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

inline constexpr unsigned char operator "" _u8( unsigned long long arg ) noexcept
{
    return static_cast< unsigned char >( arg );
}

Color invertColor(Color c)
{
    Color c2{};
    c2.r = 255 - c.r;
    c2.g = 255 - c.g;
    c2.b = 255 - c.b;
    c2.a = c.a;
    return c2;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 800;

    // Set custom logger
    SetTraceLogCallback(CustomLog);
    SetTraceLogLevel(LOG_ALL);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom logging");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    const Color allColors[] = { MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN, GRAY, DARKGRAY, BLACK, RAYWHITE, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, WHITE };
    const char* allColorsStr[] = { "MAROON", "ORANGE", "DARKGREEN", "DARKBLUE", "DARKPURPLE", "DARKBROWN", "GRAY", "DARKGRAY", "BLACK", "RAYWHITE", "RED", "GOLD", "LIME", "BLUE", "VIOLET", "BROWN", "LIGHTGRAY", "WHITE" };


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        static const int blockSize = screenHeight / 18;
        for (int i = 0; i < 18; i++)
        {
            DrawRectangle(0, i*blockSize, screenWidth, blockSize, allColors[i]);
            DrawText(allColorsStr[i], 10, 4 + i*blockSize, 16, invertColor(allColors[i]));
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}