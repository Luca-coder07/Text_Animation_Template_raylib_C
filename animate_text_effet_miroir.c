#include "raylib.h"
#include <string.h>

int main() {
    // Initialisation
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Effet Miroir Horizontal Raylib");

    SetTargetFPS(60);

    const char* text = "Raylib Miroir";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 40, 0);
    Vector2 textPosition = {screenWidth / 2 - textSize.x / 2, screenHeight / 2 - textSize.y / 2};

    float mirrorFactor = 0.0f; // Valeur entre 0.0 et 1.0 pour l'effet mirroir
    float mirrorSpeed = 0.01f;
    bool mirrorIncreasing = true;

    // Boucle principale du jeu
    while (!WindowShouldClose()) {
        // Logique de mise à jour

        // Animation de l'effet miroir
        if (mirrorIncreasing) {
            mirrorFactor += mirrorSpeed;
            if (mirrorFactor >= 1.0f) {
                mirrorFactor = 1.0f;
                mirrorIncreasing = false;
            }
        } else {
            mirrorFactor -= mirrorSpeed;
            if (mirrorFactor <= 0.0f) {
                mirrorFactor = 0.0f;
                mirrorIncreasing = true;
            }
        }

        // Dessin
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Dessin du texte avec effet mirroir horizontal progressif
        for (int i = 0; i < textSize.x; ++i) {
            // Calcule la position du caractère mirroir
            float mirrorX = textPosition.x + (textSize.x - i) * mirrorFactor + i * (1.0f - mirrorFactor);

            // Découpe le texte en caractères individuels
            char currentChar[2] = {text[i], '\0'}; // Besoin d'un tableau de char pour DrawTextEx
            if (text[i] == '\0') break; // Sortir de la boucle si on a atteint la fin de la chaîne

            // Dessine le caractère à la position miroir, avec l'angle 0.
            DrawTextEx(GetFontDefault(), currentChar, (Vector2){mirrorX, textPosition.y}, 40, 0, BLACK);

        }

        DrawFPS(10, 10);

        EndDrawing();
    }

    // Fermeture
    CloseWindow();

    return 0;
}

