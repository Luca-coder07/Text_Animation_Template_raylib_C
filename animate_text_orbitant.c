#include "raylib.h"
#include <math.h>

#define TEXT_SIZE 20
#define ORBIT_RADIUS 100
#define ORBIT_SPEED 1.0f // Augmenter pour une orbite plus rapide
#define FADE_IN_DURATION 2.0f // Durée de l'animation de fondu en secondes

int main(void)
{
    // Initialisation
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib: Text Orbiting Object");

    // Coordonnées du centre de l'objet (autour duquel le texte orbite)
    Vector2 objectCenter = { screenWidth / 2.0f, screenHeight / 2.0f };
    Color objectColor = GREEN;

    // Texte à afficher et ses dimensions
    const char* text = "Orbiting Text!";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, TEXT_SIZE, 0);

    // Angle d'orbite et sa vitesse
    float orbitAngle = 0.0f;

    // Variable pour l'animation de fondu au début
    float fadeInAlpha = 0.0f;
    double startTime = GetTime();

    SetTargetFPS(60); // Définir le nombre d'images par seconde

    // Boucle principale du jeu
    while (!WindowShouldClose())    // Détecter si l'utilisateur a appuyé sur la touche ESC ou sur le bouton de fermeture de la fenêtre
    {
        // Mise à jour
        float currentTime = GetTime();

        // Animation de fondu (seulement au début)
        if (currentTime - startTime < FADE_IN_DURATION)
        {
            fadeInAlpha = (float)((currentTime - startTime) / FADE_IN_DURATION); // Normalisation de 0 à 1
            if (fadeInAlpha > 1.0f) fadeInAlpha = 1.0f; // S'assurer que alpha ne dépasse pas 1.0
        } else {
            fadeInAlpha = 1.0f; // S'assurer que l'alpha est à fond après la durée de l'animation
            // Mettre à jour l'angle d'orbite (seulement après le fondu)
            orbitAngle += ORBIT_SPEED * GetFrameTime();
        }

        // Calculer la position du texte en fonction de l'angle d'orbite
        Vector2 textPosition;
        textPosition.x = objectCenter.x + cosf(orbitAngle) * ORBIT_RADIUS - textSize.x / 2.0f;
        textPosition.y = objectCenter.y + sinf(orbitAngle) * ORBIT_RADIUS - textSize.y / 2.0f;

        // Dessin
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Dessiner l'objet au centre
            DrawCircleV(objectCenter, 20, objectColor);

            // Dessiner le texte en orbite avec l'alpha appliqué
            Color textColor = Fade(BLACK, fadeInAlpha); // Créer une couleur avec l'alpha
            DrawTextEx(GetFontDefault(), text, textPosition, TEXT_SIZE, 0, textColor);


            DrawFPS(10, 10); // Afficher les FPS pour le débogage

        EndDrawing();
    }

    // Fermeture
    CloseWindow();        // Fermer la fenêtre et le contexte OpenGL
    return 0;
}

