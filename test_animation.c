#include <raylib.h>
#include <stdio.h> // Pour les sprintf
#include <math.h>

#define MAX_LETTERS 256 // Nombre maximal de lettres dans le texte
#define GRAVITY 100.0f   // Accélération due à la gravité
#define BOUNCE_FACTOR 0.7f // Facteur de rebond

typedef struct {
    char letter;
    Vector2 position;
    Vector2 velocity;
    bool landed;
} FallingLetter;

int main(void)
{
    // Configuration de la fenêtre
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Falling Text with Raylib");

    // Le texte à faire tomber
    const char *text = "Hello Raylib!";
    int textLength = TextLength(text);

    // Tableau pour stocker les lettres qui tombent
    FallingLetter letters[MAX_LETTERS] = {0};

    // Initialisation des lettres
    for (int i = 0; i < textLength; i++)
    {
        letters[i].letter = text[i];
        letters[i].position.x = (float)i * 30.0f + screenWidth / 4.0f; // Position horizontale espacée
        letters[i].position.y = -50.0f; // Position initiale au-dessus de l'écran
        letters[i].velocity = (Vector2){0.0f, 0.0f}; // Vitesse initiale nulle
        letters[i].landed = false;
    }

    // Paramètres de rendu
    SetTargetFPS(60);

    // Boucle principale
    while (!WindowShouldClose())
    {
        // Mise à jour
        float deltaTime = GetFrameTime();

        // Mise à jour de la position et de la vitesse de chaque lettre
        for (int i = 0; i < textLength; i++)
        {
            if (!letters[i].landed)
            {
                // Appliquer la gravité
                letters[i].velocity.y += GRAVITY * deltaTime;

                // Mettre à jour la position
                letters[i].position.y += letters[i].velocity.y * deltaTime;

                // Détection de la collision avec le sol
                if (letters[i].position.y > screenHeight - 10.0f)
                {
                    letters[i].position.y = screenHeight - 10.0f; // Empêcher la lettre de passer à travers le sol
                    letters[i].velocity.y = -letters[i].velocity.y * BOUNCE_FACTOR; // Rebondir

                    // Si la vitesse verticale est faible, considérer la lettre comme ayant atterri
                    if (fabsf(letters[i].velocity.y) < 10.0f)
                    {
                        letters[i].landed = true;
                    }
                }
            }
        }

        // Rendu
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Dessiner chaque lettre
        for (int i = 0; i < textLength; i++)
        {
            char letterString[2] = {letters[i].letter, '\0'}; // Convertir un char en string
            DrawText(letterString, (int)letters[i].position.x, (int)letters[i].position.y, 20, BLACK);
        }

        DrawFPS(10, 10);

        EndDrawing();
    }

    // Fermeture
    CloseWindow();

    return 0;
}

