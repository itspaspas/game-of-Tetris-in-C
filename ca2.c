#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAX_SPEED 100
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 25

void generateRandomTetromino(int tetromino[4][4], int tetrominoes[4][4][4], int* currentX, int* currentY) {
    int randomIndex = rand() % 4;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tetromino[i][j] = tetrominoes[randomIndex][i][j];
        }
    }
    *currentX = BOARD_WIDTH / 2 - 2;
    *currentY = 0;
}

int checkCollision(int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentTetromino[i][j] != 0 && (board[y + i][x + j] != 0 || x + j < 0 || x + j >= BOARD_WIDTH || y + i >= BOARD_HEIGHT)) {
                return 1;
            }
        }
    }
    return 0;
}

void rotateTetromino(int currentTetromino[4][4], int board[BOARD_HEIGHT][BOARD_WIDTH], int* currentX, int* currentY, int rotationCount) {
    int temp[4][4];
    for (int r = 0; r < rotationCount; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[i][j] = currentTetromino[i][j];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentTetromino[i][j] = temp[3 - j][i];
            }
        }
        if (checkCollision(board, currentTetromino, *currentX, *currentY)) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    currentTetromino[i][j] = temp[i][j];
                }
            }
            break;
        }
    }
}

void moveTetromino(int dx, int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int* currentX, int* currentY) {
    if (!checkCollision(board, currentTetromino, *currentX + dx, *currentY)) {
        *currentX += dx;
    }
}

void fallTetromino(int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int nextTetromino[4][4], int tetrominoes[4][4][4], int* currentX, int* currentY, int* score, int* speed) {
    if (!checkCollision(board, currentTetromino, *currentX, *currentY + 1)) {
        (*currentY)++;
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (currentTetromino[i][j] != 0) {
                    board[*currentY + i][*currentX + j] = 1;
                }
            }
        }
        int linesCleared = 0;
        for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
            int lineFilled = 1;
            for (int j = 0; j < BOARD_WIDTH; j++) {
                if (board[i][j] == 0) {
                    lineFilled = 0;
                    break;
                }
            }
            if (lineFilled) {
                linesCleared++;
                for (int k = i; k > 0; k--) {
                    for (int j = 0; j < BOARD_WIDTH; j++) {
                        board[k][j] = board[k - 1][j];
                    }
                }
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    board[0][j] = 0;
                }
                i++; // Check the same line again in case it's also filled
            }
        }
        *score += linesCleared * 10;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentTetromino[i][j] = nextTetromino[i][j];
            }
        }
        generateRandomTetromino(nextTetromino, tetrominoes, currentX, currentY);
        *speed = 1;
        if (checkCollision(board, currentTetromino, *currentX, *currentY)) {
            // Game over
            printf("Game Over\n");
            exit(0);
        }
    }
    Sleep(1000/(*speed));
}

void printBoard(int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int nextTetromino[4][4], int currentX, int currentY, int score) {
    system("cls"); // Clear the console
    int padding = 10; // Adjust this value to move the board left or right
    // Print top padding
    for (int i = 0; i < padding; i++) {
        printf("\n");
    }
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        // Print left padding
        for (int j = 0; j < padding; j++) {
            printf(" ");
        }
        printf("|"); // Print left border
        for (int j = 0; j < BOARD_WIDTH; j++) {
            // If the current block is part of the tetromino and it's within the board
            if (i >= currentY && i < currentY + 4 && j >= currentX && j < currentX + 4 && currentTetromino[i - currentY][j - currentX] != 0) {
                printf("[]");
            } else if (board[i][j] == 0) {
                printf("  ");
            } else {
                printf("[]");
            }
        }
        printf("|\n"); // Print right border
    }
    // Print left padding
    for (int j = 0; j < padding; j++) {
        printf(" ");
    }
    // Print bottom border
    for (int i = 0; i < BOARD_WIDTH + 2; i++) {
        printf("--");
    }
    printf("\n");
    printf("Score: %d\n", score);
    printf("Next Tetromino:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (nextTetromino[i][j] != 0) {
                printf("[]");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void handleInput(int* speed, int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int* currentX, int* currentY, int rotationCount) {
    if (kbhit()) {
        char key = getch();
        switch (key) {
            case 'a':
                moveTetromino(-1, board, currentTetromino, currentX, currentY);
                break;
            case 'd':
                moveTetromino(1, board, currentTetromino, currentX, currentY);
                break;
            case 's':
                if (*speed < MAX_SPEED) {
                    (*speed)++; // Increase the speed
                }
                else {
                    *speed = 1; // Reset the speed if it reaches the maximum
                }
                break;

            case ' ':
                rotateTetromino(currentTetromino, board, currentX, currentY, rotationCount);
                break;
            default:
                break;
        }
    }
}



int main() {
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

    printf("Enter the number of rotations for each Tetromino (1-4): ");
    scanf("%d", &rotationCount);
    rotationCount = (rotationCount % 4);

    srand(time(NULL));
    generateRandomTetromino(currentTetromino, tetrominoes, &currentX, &currentY);
    generateRandomTetromino(nextTetromino, tetrominoes, &currentX, &currentY);
    while (1) {
        printBoard(board, currentTetromino, nextTetromino, currentX, currentY, score);
        handleInput(&speed, board, currentTetromino, &currentX, &currentY, rotationCount);
        fallTetromino(board, currentTetromino, nextTetromino, tetrominoes, &currentX, &currentY, &score, &speed);
    }
    return 0;
}