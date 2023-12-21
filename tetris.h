#define MAX_SPEED 100
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 25

void generateRandomTetromino(int tetromino[4][4], int tetrominoes[4][4][4], int* currentX, int* currentY);
int checkCollision(int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int x, int y);
void rotateTetromino(int currentTetromino[4][4], int board[BOARD_HEIGHT][BOARD_WIDTH], int* currentX, int* currentY, int rotationCount);
void moveTetromino(int dx, int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int* currentX, int* currentY);
int fallTetromino(int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int nextTetromino[4][4], int tetrominoes[4][4][4], int* currentX, int* currentY, int* score, int* speed);
void printBoard(int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int nextTetromino[4][4], int currentX, int currentY, int score);
int handleInput(int* speed, int board[BOARD_HEIGHT][BOARD_WIDTH], int currentTetromino[4][4], int* currentX, int* currentY, int rotationCount);
