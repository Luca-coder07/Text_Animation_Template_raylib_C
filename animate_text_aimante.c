#include "raylib.h"
#include <math.h>

#define GRAVITY 0.2f
#define FRICTION 0.95f
#define TEXT_SIZE 40

int main() {
    // Initialisation
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Texte Aimanté/Flottant");

    SetTargetFPS(60);

    // Texte
    const char *text = "Suis Moi !";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, TEXT_SIZE, 1.0f);

    // Position et Vélocité du texte
    Vector2 textPosition = { (float)screenWidth / 2 - textSize.x / 2, (float)screenHeight / 2 - textSize.y / 2 };
    Vector2 textVelocity = { 0, 0 };

    // Animation au démarrage (effet de "flottement")
    float initialAnimationTimer = 0.0f;
    const float animationDuration = 2.0f; // Durée de l'animation en secondes
    Vector2 initialOffset = { 50.0f, 50.0f }; // Amplitude du flottement initial

    // Boucle principale
    while (!WindowShouldClose()) {
        // Mise à jour

        // Animation au démarrage
        if (initialAnimationTimer < animationDuration) {
            initialAnimationTimer += GetFrameTime();
            float animationProgress = initialAnimationTimer / animationDuration; // De 0 à 1

            // Utiliser sinusoïde pour un mouvement doux
            textPosition.x = (float)screenWidth / 2 - textSize.x / 2 + sinf(animationProgress * PI * 4) * initialOffset.x;
            textPosition.y = (float)screenHeight / 2 - textSize.y / 2 + cosf(animationProgress * PI * 4) * initialOffset.y;


        } else {
            // Une fois l'animation terminée, le texte suit la souris.

            // Calcul de la direction vers la souris
            Vector2 mousePosition = GetMousePosition();
            Vector2 direction = { mousePosition.x - textPosition.x, mousePosition.y - textPosition.y };
            float   distance = Vector2Length(direction);

            // Normalisation de la direction (si distance > 0)
            if (distance > 0) {
                direction.x /= distance;
                direction.y /= distance;
            }

            // Application d'une force d'attraction (ajuster la force selon vos préférences)
            float attractionForce = 5.0f;  // Force de l'attraction. Augmenter pour un suivi plus rapide.

            textVelocity.x += direction.x * attractionForce;
            textVelocity.y += direction.y * attractionForce;



            // Application de la gravité (pour un effet de flottement vertical)
            textVelocity.y += GRAVITY;


            // Application de la friction (pour amortir le mouvement)
            textVelocity.x *= FRICTION;
            textVelocity.y *= FRICTION;

            // Mise à jour de la position
            textPosition.x += textVelocity.x;
            textPosition.y += textVelocity.y;

            // Maintien du texte dans les limites de l'écran (optionnel)
            if (textPosition.x < 0) {
                textPosition.x = 0;
                textVelocity.x *= -0.5f; // Inversion et réduction de la vélocité en cas de collision
            }
            if (textPosition.x > screenWidth - textSize.x) {
                textPosition.x = screenWidth - textSize.x;
                textVelocity.x *= -0.5f;
            }
            if (textPosition.y < 0) {
                textPosition.y = 0;
                textVelocity.y *= -0.5f;
            }
            if (textPosition.y > screenHeight - textSize.y) {
                textPosition.y = screenHeight - textSize.y;
                textVelocity.y *= -0.5f;
            }
        }



        // Dessin
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTextEx(GetFontDefault(), text, textPosition, TEXT_SIZE, 0, BLACK);
            // Debug: Afficher la position de la souris
            //DrawText(TextFormat("Mouse: %f, %f", GetMousePosition().x, GetMousePosition().y), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Fermeture
    CloseWindow();

    return 0;
}

