#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Structure pour représenter une particule
typedef struct {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float life;
    float size;
} Particle;

#define MAX_PARTICLES 200
Particle particles[MAX_PARTICLES];

// Paramètres du feu
#define EMITTER_POSITION (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() * 0.8f }
#define EMITTER_RADIUS 20
#define INITIAL_VELOCITY_RANGE 50.0f
#define PARTICLE_LIFE 1.5f
#define PARTICLE_SIZE_START 10.0f
#define PARTICLE_SIZE_END 1.0f
#define GRAVITY (Vector2){ 0.0f, -20.0f } // Gravité inversée pour faire monter les particules

// Fonction pour initialiser une particule
void InitParticle(Particle *particle) {
    particle->position = (Vector2){EMITTER_POSITION.x + GetRandomFloat(-EMITTER_RADIUS, EMITTER_RADIUS), EMITTER_POSITION.y + GetRandomFloat(-EMITTER_RADIUS, EMITTER_RADIUS)};
    particle->velocity = (Vector2){ GetRandomFloat(-INITIAL_VELOCITY_RANGE, INITIAL_VELOCITY_RANGE), GetRandomFloat(-INITIAL_VELOCITY_RANGE, INITIAL_VELOCITY_RANGE) };
    particle->life = PARTICLE_LIFE;
    particle->size = PARTICLE_SIZE_START;

    // Définir une couleur de feu (rouge à jaune)
    float colorBias = GetRandomFloat(0.0f, 1.0f);
    particle->color = ColorFromHSV(colorBias * 60.0f, 1.0f, 1.0f); // HSV pour un spectre de couleurs
}

int main() {
    // Initialisation
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Raylib Fire Text Animation");
    SetTargetFPS(60);

    // Initialiser les particules
    for (int i = 0; i < MAX_PARTICLES; i++) {
        InitParticle(&particles[i]);
    }

    // Texte à afficher
    const char *text = "FIRE TEXT";
    int fontSize = 80;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 0);
    Vector2 textPosition = { (screenWidth - textSize.x) / 2.0f, (screenHeight - textSize.y) / 4.0f };


    // Boucle principale du jeu
    while (!WindowShouldClose()) {
        // Mise à jour

        // Mettre à jour les particules
        for (int i = 0; i < MAX_PARTICLES; i++) {
            particles[i].position.x += particles[i].velocity.x * GetFrameTime();
            particles[i].position.y += particles[i].velocity.y * GetFrameTime();
            particles[i].velocity.x += GRAVITY.x * GetFrameTime();
            particles[i].velocity.y += GRAVITY.y * GetFrameTime();
            particles[i].life -= GetFrameTime();
            particles[i].size = Lerp(PARTICLE_SIZE_START, PARTICLE_SIZE_END, 1.0f - particles[i].life / PARTICLE_LIFE);


            // Mise à jour de la couleur (assombrissement)
            float lifeRatio = particles[i].life / PARTICLE_LIFE;
            particles[i].color.a = (unsigned char)(lifeRatio * 255);

            // Réinitialiser la particule si sa durée de vie est terminée
            if (particles[i].life <= 0.0f) {
                InitParticle(&particles[i]);
            }
        }

        // Dessin
        BeginDrawing();
            ClearBackground(BLACK);

            // Dessiner les particules
            for (int i = 0; i < MAX_PARTICLES; i++) {
                DrawCircleV(particles[i].position, particles[i].size, particles[i].color);
            }

            // Dessiner le texte (après les particules pour qu'il soit au dessus)
            DrawText(text, (int)textPosition.x, (int)textPosition.y, fontSize, WHITE); // Ou une couleur plus visible sur le fond noir

        EndDrawing();
    }

    // Fermeture
    CloseWindow();

    return 0;
}

