#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tetris.h"

#define MAX_SPEED 100
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 25

int main() {
    char playAgain;
    do {
        int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
        int speed = 1;
        int tetrominoes[4][4][4] = {
            {
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            },
            {
                {0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0}
            },
            {
                {0, 0, 0, 0},
                {1, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0}
            },
            {
                {0, 0, 0, 0},
                {0, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0}
            },
        };
        int currentTetromino[4][4];
        int nextTetromino[4][4];
        int currentX, currentY;
        int score = 0;
        int rotationCount;
        int gameStatus = 1;

        printf("Enter the number of rotations for each Tetromino (1-4): ");
        scanf("%d", &rotationCount);
        rotationCount = (rotationCount % 4);

        srand(time(NULL));
        generateRandomTetromino(currentTetromino, tetrominoes, &currentX, &currentY);
        generateRandomTetromino(nextTetromino, tetrominoes, &currentX, &currentY);
        while (gameStatus) {
            printBoard(board, currentTetromino, nextTetromino, currentX, currentY, score);
            gameStatus = handleInput(&speed, board, currentTetromino, &currentX, &currentY, rotationCount);
            if(gameStatus) {
                gameStatus = fallTetromino(board, currentTetromino, nextTetromino, tetrominoes, &currentX, &currentY, &score, &speed);
            }
        }
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y' || playAgain == 'Y');
    return 0;
}