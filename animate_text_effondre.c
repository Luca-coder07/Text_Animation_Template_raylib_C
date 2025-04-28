#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LETTERS 20  // Longueur maximale du texte

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float rotationSpeed;
    Color color;
    bool isActive;
} LetterParticle;

int main() {
    // Configuration
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Texte Effondrant Raylib");

    SetTargetFPS(60);

    // Texte à afficher
    const char *text = "Raylib!";
    int textLength = strlen(text);

    // Paramètres du texte
    int fontSize = 60;
    Font font = GetFontDefault();  // Utiliser la police par défaut

    // Position du texte au centre de l'écran
    Vector2 textPosition = { (float)(screenWidth - MeasureText(text, fontSize)) / 2.0f, (float)(screenHeight - fontSize) / 2.0f };


    // Initialisation des particules (une par lettre)
    LetterParticle particles[MAX_LETTERS];
    for (int i = 0; i < textLength; i++) {
        particles[i].position = Vector2Add(textPosition, (Vector2){(float)MeasureText(TextSubtext(text, 0, i), fontSize), 0.0f});

        particles[i].velocity = (Vector2){ (float)(GetRandomValue(-50, 50) / 100.0f * 200), (float)(GetRandomValue(-50, 50) / 100.0f * 200)}; // Vitesse aléatoire
        particles[i].rotation = 0.0f;
        particles[i].rotationSpeed = (float)(GetRandomValue(-100, 100) / 100.0f * 360); // Rotation aléatoire
        particles[i].color = RAYWHITE;
        particles[i].isActive = true;
    }

    // Boucle principale
    while (!WindowShouldClose()) {
        // Mettre à jour
        float deltaTime = GetFrameTime();

        // Mise à jour des particules
        for (int i = 0; i < textLength; i++) {
            if (particles[i].isActive) {
                particles[i].position.x += particles[i].velocity.x * deltaTime;
                particles[i].position.y += particles[i].velocity.y * deltaTime;
                particles[i].rotation += particles[i].rotationSpeed * deltaTime;

                // Ralentir progressivement la vitesse
                particles[i].velocity.x *= 0.98f;
                particles[i].velocity.y *= 0.98f;

                // Diminuer l'opacité pour un effet de disparition
                particles[i].color.a -= (unsigned char)(255.0f * deltaTime * 0.5f); // Réduit l'alpha progressivement

                // Désactiver la particule si elle est complètement transparente
                if (particles[i].color.a <= 0) {
                    particles[i].isActive = false;
                }
            }
        }



        // Dessiner
        BeginDrawing();

            ClearBackground(BLACK);


            // Dessiner les lettres en tant que particules
            for (int i = 0; i < textLength; i++) {
                if (particles[i].isActive) {
                   DrawTextEx(font, TextSubtext(text, i, 1), particles[i].position, fontSize, 0, Fade(particles[i].color, (float)particles[i].color.a/255.0f));
                    //DrawRectanglePro((Rectangle){particles[i].position.x, particles[i].position.y, 10, 10}, (Vector2){5,5}, particles[i].rotation, particles[i].color); // Pour debug
                }
            }

            // Afficher le nombre de FPS
            DrawFPS(10, 10);

        EndDrawing();
    }

    // Fermer la fenêtre et libérer la mémoire
    CloseWindow();

    return 0;
}

