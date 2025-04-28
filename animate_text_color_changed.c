#include "raylib.h"

#define NUM_LETTERS 10 // Nombre de lettres dans le texte (exemple)

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Text Animation");

    // Texte à animer
    const char text[] = "RAYLIB TEXT"; // Un exemple de texte
    int textLength = TextLength(text); // Obtient la longueur réelle du texte

    // Couleurs pour chaque lettre
    Color letterColors[textLength];
    for (int i = 0; i < textLength; i++)
    {
        letterColors[i] = RED; // Initialisation à rouge
    }

    // Propriétés de l'animation
    float colorChangeSpeed = 2.0f; // Vitesse du changement de couleur
    float hueOffset[textLength]; // Décalage de teinte pour chaque lettre
    for (int i = 0; i < textLength; i++)
    {
        hueOffset[i] = GetRandomValue(0, 360); // Décalage initial aléatoire
    }

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Mettre à jour les couleurs de chaque lettre
        for (int i = 0; i < textLength; i++)
        {
            hueOffset[i] += colorChangeSpeed * GetFrameTime(); // Incrémenter le décalage de teinte

            // Boucler autour de 360 degrés
            if (hueOffset[i] > 360)
            {
                hueOffset[i] -= 360;
            }

            // Convertir la teinte en couleur RGB
            letterColors[i] = ColorFromHSV(hueOffset[i], 1.0f, 1.0f);
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Afficher le texte lettre par lettre
            int xOffset = 100; // Position de départ X
            int yOffset = 200; // Position Y
            int fontSize = 40;

            for (int i = 0; i < textLength; i++)
            {
                char letter[2] = { text[i], '\0' }; // Créer une chaîne d'un seul caractère

                // Dessiner chaque lettre avec sa couleur individuelle
                DrawText(letter, xOffset, yOffset, fontSize, letterColors[i]);

                // Avancer la position X pour la prochaine lettre
                xOffset += MeasureText(letter, fontSize);
            }

            DrawText("Press ESC to exit", 10, 10, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

