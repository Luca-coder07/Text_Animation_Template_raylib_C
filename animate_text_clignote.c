#include "raylib.h"

int main(void)
{
    // Initialisation
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib - Texte Clignotant");

    // Texte à afficher
    const char* text = "Texte Clignotant";
    Vector2 textPosition = {screenWidth / 2 - MeasureText(text, 20) / 2, screenHeight / 2}; // Centrer le texte

    // Variables pour le clignotement
    float blinkTimer = 0.0f;
    const float blinkSpeed = 0.5f;  // Vitesse du clignotement (secondes)
    bool textVisible = true;

    SetTargetFPS(60);               // Définir la cible FPS

    // Boucle principale du jeu
    while (!WindowShouldClose())    // Detecter si le bouton fermer est appuyé
    {
        // Mise à jour
        blinkTimer += GetFrameTime();

        if (blinkTimer >= blinkSpeed)
        {
            textVisible = !textVisible;  // Inverser la visibilité du texte
            blinkTimer = 0.0f;        // Réinitialiser le timer
        }

        // Dessin
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (textVisible)
            {
                DrawText(text, (int)textPosition.x, (int)textPosition.y, 20, BLACK);
            }

        EndDrawing();
    }

    // Dé-initialisation
    CloseWindow();        // Fermer la fenêtre et le contexte OpenGL

    return 0;
}

