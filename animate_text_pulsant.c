#include "raylib.h"
#include <stdio.h> // Pour la conversion float vers string (snprintf)
#include <math.h>

int main(void)
{
    // Configuration de la fenêtre
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib - Texte Pulsant");

    SetTargetFPS(60);  // FPS cible

    // Texte à afficher
    const char* text = "Texte Pulsant !";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 40, 1); // Mesure pour le centrer

    // Variables pour l'effet de pulsation
    float pulseTimer = 0.0f;
    float pulseSpeed = 1.0f;
    float minScale = 0.8f;
    float maxScale = 1.2f;
    float scale = 1.0f; // Echelle initiale

    // Boucle principale du jeu
    while (!WindowShouldClose())    // Détecte si l'utilisateur doit fermer la fenêtre ou appuyer sur ESC
    {
        // Mettre à jour
        pulseTimer += GetFrameTime() * pulseSpeed;  // Incrémente le timer en fonction du temps écoulé

        // Calcule l'échelle en utilisant une fonction sinusoïdale pour un effet de pulsation
        scale = minScale + (maxScale - minScale) * (sinf(pulseTimer) + 1.0f) / 2.0f;


        // Dessiner
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Centre le texte
            Vector2 textPosition = { (float)(screenWidth - textSize.x * scale) / 2.0f, (float)(screenHeight - textSize.y * scale) / 2.0f };

            // Dessine le texte avec l'échelle calculée
            DrawTextEx(GetFontDefault(), text, textPosition, 40 * scale, 1 * scale, BLACK);

        EndDrawing();
    }

    // Fermer la fenêtre et libérer les ressources
    CloseWindow();

    return 0;
}

