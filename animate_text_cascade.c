#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TEXT_LENGTH 256
#define MAX_DROPS 100

typedef struct {
    char text[2]; // Un seul caractère + '\0'
    Vector2 position;
    float speed;
    Color color;
    bool active;
} TextDrop;

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Text Rain");

    SetTargetFPS(60);

    // Text to display
    const char fullText[MAX_TEXT_LENGTH] = "Raylib Rain Text Demo"; // Votre texte principal

    // Array to store text drops
    TextDrop drops[MAX_DROPS];

    // Initialize drops
    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].text[0] = '\0'; // Initialement vide
        drops[i].text[1] = '\0';
        drops[i].position = (Vector2){ (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(-500, 0) }; // Placement initial hors écran
        drops[i].speed = (float)GetRandomValue(50, 150);
        drops[i].color = LIGHTGRAY;
        drops[i].active = false;
    }

    // Variables for creating the rain effect
    float timer = 0.0f;
    float spawnRate = 0.1f; // Fréquence d'apparition des gouttes (en secondes)
    int textIndex = 0; // Index du caractère actuel dans fullText

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        float deltaTime = GetFrameTime();
        timer += deltaTime;

        // Create new drops
        if (timer > spawnRate && textIndex < strlen(fullText))
        {
            timer = 0.0f;

            // Find an inactive drop
            for (int i = 0; i < MAX_DROPS; i++) {
                if (!drops[i].active) {
                    drops[i].active = true;
                    drops[i].text[0] = fullText[textIndex]; // Copie le caractère
                    drops[i].text[1] = '\0';

                    drops[i].position = (Vector2){ (float)GetRandomValue(0, screenWidth), (float)-20 };
                    drops[i].speed = (float)GetRandomValue(50, 150);
                    drops[i].color = LIGHTGRAY;
                    textIndex++;
                    break; //Sortir de la boucle apres avoir trouver une drop inactive
                }
            }
        }

        // Update drop positions
        for (int i = 0; i < MAX_DROPS; i++)
        {
            if (drops[i].active)
            {
                drops[i].position.y += drops[i].speed * deltaTime;

                // Deactivate drop when it goes off screen
                if (drops[i].position.y > screenHeight + 20)
                {
                    drops[i].active = false;
                    drops[i].text[0] = '\0'; // Clear text
                }
            }
        }


        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw drops
        for (int i = 0; i < MAX_DROPS; i++)
        {
            if (drops[i].active)
            {
                DrawText(drops[i].text, (int)drops[i].position.x, (int)drops[i].position.y, 20, drops[i].color);
            }
        }

        DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

