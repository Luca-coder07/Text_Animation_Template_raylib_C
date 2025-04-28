#include <raylib.h>
#include <math.h> // Pour sin()

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 450
#define TEXT "Hello Raylib!"
#define FONT_SIZE 40
#define TEXT_COLOR WHITE

int main() {
    // Initialisation
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Texte qui Saute et Vibre");

    SetTargetFPS(60);

    // Variables pour l'animation
    float textX = WINDOW_WIDTH / 2.0f - MeasureText(TEXT, FONT_SIZE) / 2.0f;
    float textY = WINDOW_HEIGHT / 2.0f;
    float offsetY = 0.0f; // Déplacement vertical pour le saut
    float offsetRotation = 0.0f; // Rotation pour la vibration
    float time = 0.0f;

    // Boucle principale du jeu
    while (!WindowShouldClose()) {
        // Mise à jour
        time += GetFrameTime();

        // Animation de saut : Utiliser une fonction sinusoïdale pour un mouvement doux
        offsetY = sin(time * 5.0f) * 20.0f; // Vitesse * Amplitude

        // Animation de vibration : Petite rotation rapide
        offsetRotation = sin(time * 15.0f) * 2.0f; // Vitesse * Amplitude (de rotation)


        // Dessin
        BeginDrawing();

            ClearBackground(DARKGRAY);

            // Dessiner le texte animé
            DrawTextPro(GetFontDefault(),  // Police par défaut (vous pouvez charger une police spécifique)
                        TEXT,
                        (Vector2){textX, textY}, // Position (centre du texte)
                        (Vector2){MeasureText(TEXT, FONT_SIZE) / 2.0f, FONT_SIZE / 2.0f}, // Origine (centre du texte pour la rotation)
                        offsetRotation,           // Rotation
                        100.0f,
                        1.0f,                  // Echelle
                        TEXT_COLOR);

            // Afficher des informations de debug (optionnel)
            DrawText(TextFormat("Offset Y: %.2f", offsetY), 10, 10, 20, GREEN);
            DrawText(TextFormat("Rotation: %.2f", offsetRotation), 10, 40, 20, GREEN);

        EndDrawing();
    }

    // Fermeture
    CloseWindow();

    return 0;
}

