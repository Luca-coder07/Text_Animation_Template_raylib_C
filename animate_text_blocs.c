#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Structure pour un bloc tetris (simple carré)
typedef struct {
    int x;
    int y;
    Color color;
} Block;

// Constantes
#define BLOCK_SIZE 20
#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define TEXT_TO_ANIMATE "RAYLIB"
#define ANIMATION_FRAMES 60 // Nombre de frames pour l'animation d'apparition

// Définition des couleurs des blocs (on utilise des couleurs vives)
Color blockColors[] = {
    RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE, PINK
};

// Fonction pour créer un bloc
Block CreateBlock(int x, int y, Color color) {
    Block block;
    block.x = x;
    block.y = y;
    block.color = color;
    return block;
}

int main() {
    // Initialisation
    const int screenWidth = GRID_WIDTH * BLOCK_SIZE;
    const int screenHeight = GRID_HEIGHT * BLOCK_SIZE;

    InitWindow(screenWidth, screenHeight, "Tetris Text Animation");

    SetTargetFPS(60);

    // Génération du texte en blocs
    Block textBlocks[100]; // On alloue de la place pour potentiellement plus de blocs que nécessaire
    int blockCount = 0;

    // Définir la position du texte (centré horizontalement, en haut verticalement)
    int textX = (GRID_WIDTH - (int)TextLength(TEXT_TO_ANIMATE)) * BLOCK_SIZE / 2;
    int textY = BLOCK_SIZE * 2; // un peu en dessous du haut de l'écran.

    // Tableau pour stocker le texte en tant que caractères individuels.
    int textLen = TextLength(TEXT_TO_ANIMATE);

    // On stocke les caractères du texte dans un tableau, plus simple à manipuler.
    char textChars[textLen + 1];
    strcpy(textChars, TEXT_TO_ANIMATE); // Important : copier le texte dans le tableau.

    // Création du texte en blocs
    for (int i = 0; i < textLen; i++) {
        // Un switch/case pour définir la forme des lettres avec des blocs.
        switch (textChars[i]) {
            case 'R':
                // Forme du R (exemple très simple, à affiner)
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY, RED);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + BLOCK_SIZE, RED);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + 2 * BLOCK_SIZE, RED);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY, RED);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY + BLOCK_SIZE, RED);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY, RED);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY + 2* BLOCK_SIZE, RED);
                break;
            case 'A':
                // Forme du A (exemple très simple, à affiner)
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY, GREEN);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY, GREEN);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY, GREEN);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + BLOCK_SIZE, GREEN);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY + BLOCK_SIZE, GREEN);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + 2 * BLOCK_SIZE, GREEN);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY + 2 * BLOCK_SIZE, GREEN);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY + 2 * BLOCK_SIZE, GREEN);
                break;
            case 'Y':
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY, BLUE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY, BLUE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY, BLUE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY + BLOCK_SIZE, BLUE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY + 2 * BLOCK_SIZE, BLUE);
                break;
             case 'L':
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY, YELLOW);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + BLOCK_SIZE, YELLOW);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + 2 * BLOCK_SIZE, YELLOW);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY + 2 * BLOCK_SIZE, YELLOW);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY + 2 * BLOCK_SIZE, YELLOW);
                break;
            case 'I':
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY, PURPLE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + BLOCK_SIZE, PURPLE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + 2 * BLOCK_SIZE, PURPLE);
                break;
            case 'B':
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY, ORANGE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + BLOCK_SIZE, ORANGE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2, textY + 2 * BLOCK_SIZE, ORANGE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY, ORANGE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + BLOCK_SIZE, textY + BLOCK_SIZE, ORANGE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY, ORANGE);
                textBlocks[blockCount++] = CreateBlock(textX + i * 4 * BLOCK_SIZE / 2 + 2 * BLOCK_SIZE, textY + 2* BLOCK_SIZE, ORANGE);
                break;
            default:
                // Si on rencontre un caractère non défini, on ne fait rien
                break;
        }
    }

    // Animation variables
    int animationCounter = 0;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        animationCounter++;

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);

            // Animation de l'apparition des blocs
            for (int i = 0; i < blockCount; i++) {
                // Afficher les blocs progressivement, en fonction de l'animationCounter
                if (animationCounter > i * ANIMATION_FRAMES / blockCount) { //On fait apparaître chaque bloc en N frames
                    DrawRectangle(textBlocks[i].x, textBlocks[i].y, BLOCK_SIZE, BLOCK_SIZE, textBlocks[i].color);
                } else {
                    // Optionnellement, afficher un effet avant l'apparition (ex: un rectangle plus petit, semi-transparent, etc.)
                   DrawRectangle(textBlocks[i].x, textBlocks[i].y, 1, 1, Fade(textBlocks[i].color, 0.1f));
                }
            }


        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}

