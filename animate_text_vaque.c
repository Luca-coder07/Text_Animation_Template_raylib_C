#include "raylib.h"
#include <math.h>
#include <string.h>

int main() {
  // Configuration
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Raylib - Effet Vague sur Texte");

  SetTargetFPS(60);

  // Texte à afficher
  const char* text = "Raylib - Effet Vague";
  int fontSize = 40;
  Color textColor = RAYWHITE;

  // Position initiale du texte (centrée)
  Vector2 textPosition = { (screenWidth - MeasureText(text, fontSize)) / 2, screenHeight / 2 };

  // Paramètres de l'effet vague
  float waveFrequency = 0.05f;
  float waveAmplitude = 10.0f;
  float waveSpeed = 1.0f; // Augmente pour une vague plus rapide
  float waveOffset = 0.0f;

  // Boucle principale du jeu
  while (!WindowShouldClose()) {
    // Mise à jour

    // Incrémenter l'offset pour animer la vague
    waveOffset += waveSpeed * GetFrameTime();

    // Dessin
    BeginDrawing();

    ClearBackground(DARKBLUE);

    // Dessiner chaque lettre avec un décalage vertical en fonction de l'effet vague
    for (int i = 0; i < strlen(text); ++i) {
      // Calculer la position de chaque lettre
      float x = textPosition.x + MeasureText(TextSubtext(text, 0, i), fontSize); // Position en fonction des lettres précédentes
      float y = textPosition.y + sinf(waveOffset + i * waveFrequency) * waveAmplitude; // Effet vague

      // Dessiner la lettre
      DrawText(TextSubtext(text, i, 1), x, y, fontSize, textColor);
    }

    // Afficher un texte d'instructions (optionnel)
    DrawText("Appuyez sur ECHAP pour quitter", 10, 10, 20, LIGHTGRAY);

    EndDrawing();
  }

  // Fermeture
  CloseWindow();

  return 0;
}

