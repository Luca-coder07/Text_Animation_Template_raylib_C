#include "raylib.h"
#include <stdio.h>  // Pour sprintf

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define TEXT_SIZE 20
#define SCROLL_SPEED 1.0f // Augmenter pour un defilement plus rapide
#define FADE_DURATION 3.0f // Duree de l'effet de fondu (en secondes)

int main(void)
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib - Star Wars Text Scroll");

    SetTargetFPS(60);

    // Text to scroll (vous pouvez utiliser un long paragraphe)
    const char* text =
        "Il y a bien longtemps, dans une galaxie lointaine, tres lointaine...\n\n"
        "Un grand trouble regne dans la Republique Galactique.\n"
        "Les impots sur les routes commerciales vers les etoiles lointaines\n"
        "sont un sujet de controverse croissante.\n\n"
        "Avides, la Confederation du Commerce a bloqué la petite planete\n"
        "Naboo avec une flotte de puissants vaisseaux de guerre mortels.\n\n"
        "Alors que le Congres de la Republique se debat interminablement avec cette serie\n"
        "d'evenements effrayants, la chanceliere supreme a secrete\n"
        "envoye deux chevaliers Jedi, les gardiens de la paix et de la justice dans la\n"
        "galaxie, pour regler le conflit...";

    // Variables for scrolling effect
    float scrollY = (float)SCREEN_HEIGHT; // Commencer hors de l'ecran
    float fadeTimer = 0.0f; // Timer pour l'effet de fondu

    // Camera setup to achieve the perspective effect
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT }; // Centre de l'ecran
    camera.target = (Vector2){ 0, 0 }; // Point focal (bas du texte)
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        float deltaTime = GetFrameTime();

        //Scrolling
        scrollY -= SCROLL_SPEED;

        // Effet de fondu
        fadeTimer += deltaTime;

        // Ajustement automatique de la position du texte
        float textHeight = MeasureTextEx(GetFontDefault(), text, TEXT_SIZE, 1.0f).y;

        // Fin du defilement (remise a zero) -  optionnel
        if (scrollY < -textHeight * 2) // *2 pour laisser un peu de temps avant de recommencer
        {
            scrollY = (float)SCREEN_HEIGHT;
        }



        // Draw
        BeginDrawing();

            ClearBackground(BLACK);

            // Application de la camera pour la perspective
            BeginMode2D(camera);

                // Dessiner le texte
                float textY = scrollY;
                const char* currentChar = text;

                while (*currentChar != '\0')
                {
                    // Detecter les sauts de ligne pour ajuster la position Y
                    if (*currentChar == '\n')
                    {
                        textY += TEXT_SIZE * 1.5f; // Espacement pour la lisibilite
                    }
                    else
                    {
                        DrawTextEx(GetFontDefault(), (char[]){ *currentChar, '\0' }, (Vector2){ -MeasureTextEx(GetFontDefault(), (char[]){ *currentChar, '\0' }, TEXT_SIZE, 1.0f).x / 2.0f, textY }, TEXT_SIZE, 1.0f, WHITE);
                    }
                    currentChar++;
                }

            EndMode2D();

            //  Fondu au debut (optionnel)
            if (fadeTimer < FADE_DURATION)
            {
                float alpha = fadeTimer / FADE_DURATION;
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 1.0f - alpha));
            }


            // Debug information (optionnel)
            char debugText[100];
            sprintf(debugText, "ScrollY: %.2f", scrollY);
            DrawText(debugText, 10, 10, 10, GREEN);


        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

