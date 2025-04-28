#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450

int main(void)
{
    // Initialisation
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Glitch Text");

    SetTargetFPS(60);

    // Texte à afficher
    const char *text = "GLITCHED TEXT";
    int fontSize = 60;
    Vector2 textPosition = { SCREEN_WIDTH / 2.0f - MeasureText(text, fontSize) / 2.0f, SCREEN_HEIGHT / 2.0f - fontSize / 2.0f };

    // Variables pour le glitch
    int glitchTimer = 0;
    int glitchDuration = 10; // Durée du glitch en frames
    bool isGlitching = true;

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Boucle principale du jeu
    while (!WindowShouldClose())
    {
        // Mise à jour
        glitchTimer++;

        if (glitchTimer > glitchDuration)
        {
            isGlitching = false;
        }


        // Dessin
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (isGlitching)
            {
                // Effet de glitch

                // Boucle pour afficher le texte plusieurs fois avec des décalages aléatoires
                for (int i = 0; i < 5; i++)
                {
                    int offsetX = rand() % 20 - 10; // Décalage horizontal aléatoire (-10 à 10)
                    int offsetY = rand() % 10 - 5;   // Décalage vertical aléatoire (-5 à 5)
                    Color glitchColor = { (unsigned char)rand() % 255, (unsigned char)rand() % 255, (unsigned char)rand() % 255, 255 }; // Couleur aléatoire

                    DrawText(text, textPosition.x + offsetX, textPosition.y + offsetY, fontSize, glitchColor);
                }
            }
            else
            {
                // Afficher le texte normalement
                DrawText(text, textPosition.x, textPosition.y, fontSize, BLACK);

                //Afficher des instructions après le glitch
                DrawText("Text fixed!", 10, 10, 20, GREEN);
            }



        EndDrawing();
    }

    // Fermeture
    CloseWindow();

    return 0;
}

