#include "raylib.h"

int main() {
  // Initialisation
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "Raylib - Fade In/Out Text");

  // Définition du texte et de sa position
  const char *text = "Hello Raylib!";
  Vector2 textPosition = {screenWidth / 2 - MeasureText(text, 40) / 2, screenHeight / 2 - 20}; // Centré

  // Variables pour l'animation du Fade In/Out
  float alpha = 0.0f; // Valeur alpha (opacité) initialisée à 0 (transparent)
  float fadeSpeed = 0.5f; // Vitesse du fade (ajustez pour modifier la vitesse)
  bool fadingIn = true; // Indique si on est en train de faire un Fade In

  SetTargetFPS(60); // Définir la fréquence d'images cible

  // Boucle principale du jeu
  while (!WindowShouldClose()) // Détecter la fermeture de la fenêtre
  {
    // Mise à jour (Update)
    // ----------------------------------------------------------

    // Contrôle de l'animation du Fade In/Out
    if (fadingIn) {
      alpha += fadeSpeed * GetFrameTime(); // Augmenter l'alpha
      if (alpha >= 1.0f) {
        alpha = 1.0f; // Limiter à 1.0 (complètement opaque)
        fadingIn = false; // Commencer le Fade Out
      }
    } else {
      alpha -= fadeSpeed * GetFrameTime(); // Diminuer l'alpha
      if (alpha <= 0.0f) {
        alpha = 0.0f; // Limiter à 0.0 (complètement transparent)
        fadingIn = true; // Recommencer le Fade In
      }
    }

    // ----------------------------------------------------------

    // Dessin (Draw)
    // ----------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE); // Effacer l'écran avec du blanc

    // Dessiner le texte avec la couleur et l'alpha
    Color textColor = BLACK; // Définir la couleur du texte (noir)
    textColor.a = (unsigned char)(alpha * 255); // Appliquer l'alpha à la couleur

    DrawText(text, textPosition.x, textPosition.y, 40, textColor);

    DrawText("Use ESC key to close the window", 10, 10, 20, LIGHTGRAY); // Instructions

    EndDrawing();
    // ----------------------------------------------------------
  }

  // Déchargement (De-Initialization)
  // ----------------------------------------------------------
  CloseWindow(); // Fermer la fenêtre et libérer la mémoire
  // ----------------------------------------------------------

  return 0;
}

