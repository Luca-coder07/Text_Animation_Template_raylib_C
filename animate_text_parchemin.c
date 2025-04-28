#include "raylib.h"
#include <stdio.h> // Pour utiliser fprintf (erreur)

// Structures de données
typedef struct {
    char* text;
    int current_char_index;
    float timer;
    float char_delay;
} ScrollText;

// Fonction pour initialiser le texte parchemin
void InitScrollText(ScrollText* scroll_text, const char* text, float char_delay) {
    scroll_text->text = TextCopy(text); // Important: Copier le texte, sinon pointeur vers texte statique!
    scroll_text->current_char_index = 0;
    scroll_text->timer = 0.0f;
    scroll_text->char_delay = char_delay;
}

// Fonction pour mettre à jour l'animation du texte
void UpdateScrollText(ScrollText* scroll_text, float delta_time) {
    scroll_text->timer += delta_time;

    if (scroll_text->current_char_index < TextLength(scroll_text->text) && scroll_text->timer >= scroll_text->char_delay) {
        scroll_text->current_char_index++;
        scroll_text->timer = 0.0f;
    }
}

// Fonction pour dessiner le texte parchemin
void DrawScrollText(ScrollText scroll_text, Vector2 position, int fontSize, Color color) {
    char* displayed_text = TextSubtext(scroll_text.text, 0, scroll_text.current_char_index); // Récupère seulement la partie du texte déjà "déroulée"
    DrawText(displayed_text, (int)position.x, (int)position.y, fontSize, color);
    MemFree(displayed_text); // Important: Libérer la mémoire allouée par TextSubtext
}


int main() {
    // Configuration de Raylib
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Texte Parchemin Animé");

    SetTargetFPS(60);

    // Initialisation du texte parchemin
    ScrollText scroll_text;
    const char* my_text = "Il etait une fois, dans un royaume lointain...";
    float char_delay = 0.05f; // Délai entre l'affichage de chaque caractère
    InitScrollText(&scroll_text, my_text, char_delay);


    // Chargement de la texture de parchemin (optionnel, mais rend l'effet plus joli)
    Texture2D parchmentTexture = LoadTexture("parchment.png"); // Remplacez par le chemin de votre image

    if (parchmentTexture.id == 0) {
        fprintf(stderr, "Erreur: Impossible de charger la texture 'parchment.png'.  Assurez-vous que le fichier existe et que le chemin est correct.\n");
        // On continue sans la texture mais on signale l'erreur.
    }

    // Boucle principale du jeu
    while (!WindowShouldClose()) {
        // Mise à jour
        float deltaTime = GetFrameTime();
        UpdateScrollText(&scroll_text, deltaTime);


        // Dessin
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Dessiner la texture de parchemin (si elle a été chargée)
        if (parchmentTexture.id != 0) {
            DrawTexture(parchmentTexture, 0, 0, WHITE); // Dessine la texture pleine taille
        } else {
             DrawRectangle(0, 0, screenWidth, screenHeight, BEIGE); // Fond beige si pas de texture
        }


        // Dessiner le texte parchemin
        Vector2 textPosition = {50, 50};
        int fontSize = 20;
        Color textColor = DARKGRAY;
        DrawScrollText(scroll_text, textPosition, fontSize, textColor);

        EndDrawing();
    }

    // Déchargement de la mémoire
    UnloadTexture(parchmentTexture); // Libérer la texture
    MemFree(scroll_text.text);     // Libérer le texte
    CloseWindow();

    return 0;
}

