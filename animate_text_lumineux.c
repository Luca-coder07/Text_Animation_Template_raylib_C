#include "raylib.h"
#include <stdio.h> // Pour l'utilisation de printf (debug)
#include <stdlib.h> // Pour rand() et srand()

int main(void)
{
    //--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib - Scintillement de texte");

    SetTargetFPS(60);  // Définir la fréquence d'images cible

    // Texte à afficher
    const char *text = "RAYLIB SCINTILLE !";
    Vector2 textPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    int fontSize = 50;
    Color baseColor = YELLOW;      // Couleur de base du texte
    Color highlightColor = GOLD; // Couleur de surbrillance pour l'effet de scintillement

    float sparkleTimer = 0.0f; // Timer pour contrôler la fréquence des scintillements
    float sparkleInterval = 0.1f; // Intervalle entre les scintillements (en secondes)
    bool isHighlighting = false;    // Indique si on doit afficher la couleur de surbrillance

    // Initialisation du générateur de nombres aléatoires
    srand(GetTime());

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        sparkleTimer += GetFrameTime();

        if (sparkleTimer >= sparkleInterval)
        {
            sparkleTimer = 0.0f;

            // Générer un nombre aléatoire pour déterminer si on affiche la couleur de surbrillance
            // ou la couleur de base.  On peut ajuster la probabilité de scintillement en modifiant
            // la valeur de rand() % 10.  Plus la valeur est petite, plus le scintillement est fréquent.
            if (rand() % 5 == 0) //  1 chance sur 5
            {
                isHighlighting = true;
            }
            else
            {
                isHighlighting = false;
            }
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBLUE);

            // Choisir la couleur en fonction de l'état du scintillement
            Color currentColor = isHighlighting ? highlightColor : baseColor;

            // Centrer le texte
            Vector2 textSize = MeasureTextEx(GetFontDefault(), text, (float)fontSize, 1);
            Vector2 centeredPosition = {textPosition.x - textSize.x / 2, textPosition.y - textSize.y / 2};


            DrawTextEx(GetFontDefault(), text, centeredPosition, (float)fontSize, 1, currentColor);

            // Afficher quelques instructions à l'écran
            DrawText("Appuyez sur ESC pour quitter", 10, 10, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //--------------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

