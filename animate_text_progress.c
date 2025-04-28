#include "raylib.h"
#include <stdio.h> // Pour sprintf
#include <string.h>

int main() {
    // Initialisation
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Loading Animation");

    SetTargetFPS(60);

    // Variables pour l'animation de chargement
    float loadingProgress = 0.0f;
    const float loadingSpeed = 0.5f; // Pourcentage par seconde
    const int maxDots = 5; // Nombre maximum de points après le texte
    int currentDots = 0;
    float dotTimer = 0.0f;
    const float dotInterval = 0.3f; // Intervalle entre l'ajout de points

    char loadingText[64] = "Chargement"; // Taille raisonnable pour le texte

    // Boucle principale du jeu
    while (!WindowShouldClose()) {
        // Mise à jour

        // Mise à jour de la progression de chargement
        loadingProgress += loadingSpeed * GetFrameTime();
        if (loadingProgress > 100.0f) {
            loadingProgress = 100.0f; // On s'arrête à 100%
        }

        // Mise à jour de l'animation des points
        dotTimer += GetFrameTime();
        if (dotTimer >= dotInterval && loadingProgress < 100.0f) {
            dotTimer = 0.0f;
            currentDots++;
            if (currentDots > maxDots) {
                currentDots = 0;
            }
        }

        // Construction de la chaine de caractères avec les points
        sprintf(loadingText, "Chargement");
        for (int i = 0; i < currentDots; i++) {
            strcat(loadingText, "."); // Ajoute un point
        }


        // Dessin
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Affichage du texte de chargement
            DrawText(loadingText, screenWidth / 2 - MeasureText(loadingText, 20) / 2, screenHeight / 2 - 10, 20, BLACK);

            // Affichage de la barre de progression (optionnel)
            int barWidth = (int)(screenWidth * (loadingProgress / 100.0f));
            DrawRectangle(0, screenHeight - 20, barWidth, 20, GREEN); // Barre verte en bas

            // Affichage du pourcentage (optionnel)
            char progressString[8]; // Taille suffisante pour "100.00%"
            sprintf(progressString, "%.2f%%", loadingProgress); // Formatage avec 2 décimales
            DrawText(progressString, screenWidth / 2 - MeasureText(progressString, 10) / 2, screenHeight - 30, 10, GRAY);

        EndDrawing();
    }

    // Fermeture
    CloseWindow();

    return 0;
}

