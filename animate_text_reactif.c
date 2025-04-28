#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define TEXT_ANIMATION_SPEED 2.0f  // Vitesse d'animation du texte
#define TEXT_COLOR_CHANGE_SPEED 1.0f  // Vitesse de changement de couleur

int main() {
  // Initialisation de Raylib
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "Texte Animé Reactif Raylib");

  SetTargetFPS(60);  // Définir le FPS cible

  // Texte à afficher
  const char* text = "Cliquez ici !";
  Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 30, 1); // Mesurer la taille du texte
  Vector2 textPosition = { screenWidth / 2 - textSize.x / 2, screenHeight / 2 - textSize.y / 2 };

  // Variables d'animation
  float textScale = 1.0f;
  float textRotation = 0.0f;
  Color textColor = WHITE;
  float colorHue = 0.0f; // Pour animer la couleur (HSB)
  bool isHovered = false;
  bool isClicked = false;

  // Boucle principale du jeu
  while (!WindowShouldClose()) {
    // -----------------------------------------------------
    // LOGIQUE DU JEU
    // -----------------------------------------------------

    // Détection du hover
    Rectangle textBounds = { textPosition.x, textPosition.y, textSize.x, textSize.y };
    Vector2 mousePosition = GetMousePosition();
    isHovered = CheckCollisionPointRec(mousePosition, textBounds);

    // Détection du clic
    if (isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      isClicked = true;
    } else {
      isClicked = false;
    }

    // Animation du texte

    //  * Echelle : pulse lorsque le curseur est dessus, grossit au clic
    if (isHovered) {
      textScale = 1.0f + sinf(GetTime() * TEXT_ANIMATION_SPEED) * 0.1f;
    } else {
      textScale = 1.0f;
    }
    if (isClicked) {
      textScale = 1.2f; // Grossir au clic
    }

    //  * Rotation : tourne lentement
    textRotation += 0.05f;
    if (textRotation > 360.0f) textRotation -= 360.0f;


    // Animation de la couleur
    colorHue += TEXT_COLOR_CHANGE_SPEED * GetFrameTime();
    if (colorHue > 360.0f) colorHue -= 360.0f;
    textColor = ColorFromHSV(colorHue, 1.0f, 1.0f); // Couleur changeante en HSV

    // Si le curseur est dessus, la couleur devient plus claire
    if (isHovered) {
        textColor = ColorBrightness(textColor, 0.2f); // Éclaircir la couleur
    }

    // -----------------------------------------------------
    // DESSIN
    // -----------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Dessiner le texte animé
    DrawTextEx(GetFontDefault(), text, textPosition, 30, 1, textColor);

    // Afficher le texte de debug (optionnel)
    char debugText[128];
    sprintf(debugText, "Hover: %s, Clicked: %s, Scale: %.2f", isHovered ? "true" : "false", isClicked ? "true" : "false", textScale);
    DrawText(debugText, 10, 10, 20, GRAY);

    EndDrawing();
  }

  // Fermeture de la fenêtre et libération des ressources
  CloseWindow();

  return 0;
}

