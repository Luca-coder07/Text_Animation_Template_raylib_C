#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_TEXT_PARTS 5  // Nombre maximum de parties du texte

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Text Assembly Animation");

    // Text to assemble
    const char* targetText = "RAYLIB";
    int targetTextLength = TextLength(targetText);

    // Text parts data
    char textParts[MAX_TEXT_PARTS][2] = { "R", "A", "Y", "L", "IB" };  // Divisez le texte en parties
    int numTextParts = 5;

    // Positions des parties du texte (initialement aléatoires)
    Vector2 textPartPositions[MAX_TEXT_PARTS];
    for (int i = 0; i < numTextParts; i++) {
        textPartPositions[i].x = GetRandomValue(0, screenWidth);
        textPartPositions[i].y = GetRandomValue(0, screenHeight);
    }

    // Position finale du texte assemblé
    Vector2 targetTextPosition = { screenWidth / 2.0f - MeasureText(targetText, 40) / 2.0f, screenHeight / 2.0f };

    // Vitesse de déplacement des parties du texte
    float moveSpeed = 100.0f;

    // Booléen pour vérifier si l'animation est terminée
    bool animationComplete = false;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();

        if (!animationComplete) {
            // Déplacer chaque partie du texte vers sa position finale
            bool allPartsReached = true;
            for (int i = 0; i < numTextParts; i++) {
                // Position cible pour chaque partie du texte
                Vector2 targetPosition = { targetTextPosition.x + MeasureText(TextSubtext(targetText, 0, i), 40), targetTextPosition.y };

                // Déterminer si cette partie du texte est en position
                 if(i >= targetTextLength){
                        allPartsReached = false;
                        break;
                 }

                if (TextLength(textParts[i]) == 0){
                    continue; //eviter d'afficher les text vide
                }

                Vector2 delta = { targetPosition.x - textPartPositions[i].x, targetPosition.y - textPartPositions[i].y };
                float distance = Vector2Length(delta);

                if (distance > 1.0f) { // Ajouter une petite marge pour éviter les tremblements
                    Vector2 direction = Vector2Normalize(delta);
                    textPartPositions[i].x += direction.x * moveSpeed * deltaTime;
                    textPartPositions[i].y += direction.y * moveSpeed * deltaTime;
                    allPartsReached = false; // Si une partie n'a pas atteint sa destination, l'animation n'est pas terminée
                } else {
                     targetPosition = { targetTextPosition.x + MeasureText(TextSubtext(targetText, 0, i), 40), targetTextPosition.y };
                     textPartPositions[i].x = targetPosition.x;
                     textPartPositions[i].y = targetPosition.y;
                }
            }

            animationComplete = allPartsReached;
        }


        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (animationComplete) {
                // Afficher le texte assemblé une fois l'animation terminée
                DrawText(targetText, (int)targetTextPosition.x, (int)targetTextPosition.y, 40, DARKBLUE);
            } else {
                // Afficher chaque partie du texte à sa position actuelle
                for (int i = 0; i < numTextParts; i++) {
                      if(TextLength(textParts[i]) > 0){ //eviter d'afficher les text vide
                        DrawText(textParts[i], (int)textPartPositions[i].x, (int)textPartPositions[i].y, 40, DARKBLUE);
                      }

                }
            }

            DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}

