#include <raylib.h>
#include <stdlib.h>
#include <stdio.h> // Pour le debogage (facultatif)

#define NUM_FRAGMENTS 50 // Nombre de fragments

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float rotationSpeed;
    Color color;
    float lifespan;  // Durée de vie du fragment (en secondes)
} Fragment;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Fragmentation de Texte avec Raylib");

    SetTargetFPS(60);

    const char* text = "Fragmentation!";
    Font font = GetFontDefault();  // Ou chargez une police spécifique
    Vector2 textSize = MeasureTextEx(font, text, 40, 0); // Taille du texte (taille de police de 40 ici)
    Vector2 textPosition = {screenWidth / 2 - textSize.x / 2, screenHeight / 2 - textSize.y / 2};

    // Initialisation des fragments
    Fragment fragments[NUM_FRAGMENTS];
    bool fragmented = false; // Indique si la fragmentation a commencé
    float fragmentationTimer = 0.0f; // Temps écoulé depuis le début de la fragmentation
    float fragmentationDelay = 2.0f; // Délai avant le début de la fragmentation (en secondes)

    for (int i = 0; i < NUM_FRAGMENTS; i++) {
        fragments[i].position = textPosition; // Position initiale au centre du texte
        fragments[i].velocity.x = (float)(GetRandomValue(-100, 100)) / 100.0f * 200.0f; // Vitesse aléatoire X
        fragments[i].velocity.y = (float)(GetRandomValue(-100, 100)) / 100.0f * 200.0f; // Vitesse aléatoire Y
        fragments[i].rotation = (float)GetRandomValue(0, 360); // Rotation initiale aléatoire
        fragments[i].rotationSpeed = (float)(GetRandomValue(-100, 100)) / 100.0f * 100.0f; // Vitesse de rotation aléatoire
        fragments[i].color = WHITE; // Couleur initiale (peut être aléatoire ou basée sur une texture)
        fragments[i].lifespan = (float)GetRandomValue(200, 500) / 100.0f; // Durée de vie entre 2 et 5 secondes
    }



    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Mise à jour de la logique

        if (!fragmented && fragmentationTimer < fragmentationDelay) {
            fragmentationTimer += deltaTime;
        } else {
            fragmented = true; // Démarre la fragmentation après le délai

            for (int i = 0; i < NUM_FRAGMENTS; i++) {
                fragments[i].position.x += fragments[i].velocity.x * deltaTime;
                fragments[i].position.y += fragments[i].velocity.y * deltaTime;
                fragments[i].rotation += fragments[i].rotationSpeed * deltaTime;
                fragments[i].lifespan -= deltaTime;

                if (fragments[i].lifespan <= 0) {
                    fragments[i].color.a = 0; // Rend le fragment transparent
                } else {
                    // Fait disparaitre le fragment progressivement
                    fragments[i].color.a = (unsigned char)(fragments[i].lifespan / 5.0f * 255);  // Ajustez le 5.0f pour controler la vitesse de disparition
                }

                // Ralentissement progressif (frottement)
                fragments[i].velocity.x *= 0.98f;
                fragments[i].velocity.y *= 0.98f;
                fragments[i].rotationSpeed *= 0.98f;
            }
        }

        // Dessin
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (!fragmented) {
                // Afficher le texte normalement avant la fragmentation
                DrawTextEx(font, text, textPosition, 40, 0, BLACK);
            } else {
                // Dessiner les fragments
                for (int i = 0; i < NUM_FRAGMENTS; i++) {
                    if (fragments[i].color.a > 0) { // Ne dessine que les fragments visibles
                        DrawRectanglePro((Rectangle){fragments[i].position.x, fragments[i].position.y, 5, 5}, (Vector2){2.5, 2.5}, fragments[i].rotation, fragments[i].color); // Dessine un rectangle pour chaque fragment
                        // Vous pouvez remplacer DrawRectanglePro par d'autres primitives ou textures
                        // pour une fragmentation plus complexe.
                    }
                }
            }

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

