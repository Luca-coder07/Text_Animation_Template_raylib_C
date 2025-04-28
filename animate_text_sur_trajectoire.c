#include "raylib.h"
#include <math.h>
#include <stdio.h>

// Définition de la structure pour la trajectoire de Bézier
typedef struct {
    Vector2 p0;
    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
} BezierCurve;

// Fonction pour calculer un point sur une courbe de Bézier
Vector2 BezierPoint(BezierCurve curve, float t) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Vector2 p = {0};
    p.x = uuu * curve.p0.x + 3 * uu * t * curve.p1.x + 3 * u * tt * curve.p2.x + ttt * curve.p3.x;
    p.y = uuu * curve.p0.y + 3 * uu * t * curve.p1.y + 3 * u * tt * curve.p2.y + ttt * curve.p3.y;

    return p;
}

// Fonction pour calculer un point sur une courbe sinusoïdale
Vector2 SinusoidalPoint(float t, float amplitude, float frequency, Vector2 center) {
    Vector2 p = {0};
    p.x = center.x + t;
    p.y = center.y + amplitude * sinf(frequency * t);

    return p;
}

int main(void) {
    // Configuration de la fenêtre
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib - Animation de Texte");

    SetTargetFPS(60);

    // Paramètres du texte
    const char* text = "Raylib est cool !";
    Vector2 textPosition = {0, 0}; // Position initiale
    Color textColor = WHITE;
    int fontSize = 20;

    // Trajectoire de Bézier
    BezierCurve bezierCurve = {
        {50, 50},   // Point de départ
        {200, 300}, // Point de contrôle 1
        {600, 100}, // Point de contrôle 2
        {750, 400}  // Point d'arrivée
    };

    // Paramètres de la courbe sinusoïdale
    float sinusoidalAmplitude = 50.0f;
    float sinusoidalFrequency = 0.1f;
    Vector2 sinusoidalCenter = {50, 225};

    // Variable pour suivre la progression de l'animation (0.0 à 1.0)
    float animationProgress = 0.0f;

    // Type de trajectoire : 0 = Bézier, 1 = Sinusoïdale
    int trajectoryType = 0;

    // Boucle principale du jeu
    while (!WindowShouldClose()) {
        // Mettre à jour
        animationProgress += 0.005f; // Augmenter la progression de l'animation

        if (animationProgress > 1.0f) {
            animationProgress = 0.0f; // Recommencer l'animation
        }

        // Calculer la position du texte en fonction de la trajectoire choisie
        if (trajectoryType == 0) {
            textPosition = BezierPoint(bezierCurve, animationProgress);
        } else {
            textPosition = SinusoidalPoint(animationProgress * 700, sinusoidalAmplitude, sinusoidalFrequency, sinusoidalCenter); // Ajustement pour la longueur
        }


        // Dessiner
        BeginDrawing();

        ClearBackground(BLACK);

        // Dessiner la courbe de Bézier (pour le débogage)
        if (trajectoryType == 0) {
            DrawLineBezier(bezierCurve.p0, bezierCurve.p1, 5, RED);
            DrawLineBezier(bezierCurve.p1, bezierCurve.p2, 5, RED);
            DrawLineBezier(bezierCurve.p2, bezierCurve.p3, 5, RED);
            DrawCircleV(bezierCurve.p0, 5, GREEN);
            DrawCircleV(bezierCurve.p1, 5, BLUE);
            DrawCircleV(bezierCurve.p2, 5, BLUE);
            DrawCircleV(bezierCurve.p3, 5, GREEN);
        }

        // Dessiner le texte à la position calculée
        DrawText(text, (int)textPosition.x, (int)textPosition.y, fontSize, textColor);

        // Changer de trajectoire en appuyant sur espace
        if (IsKeyPressed(KEY_SPACE)) {
            trajectoryType = (trajectoryType + 1) % 2;
        }
        DrawText("Appuyez sur ESPACE pour changer de trajectoire", 10, 10, 20, GRAY);


        EndDrawing();
    }

    // Fermer la fenêtre et libérer la mémoire
    CloseWindow();

    return 0;
}

