#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

// Constants for the screen and grid
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define GRID_SIZE 3
#define CELL_SIZE 100

// Grid position
#define GRID_ORIGIN_X (SCREEN_WIDTH / 2) - 150  // Centered on the right side
#define GRID_ORIGIN_Y (SCREEN_HEIGHT / 2) - 150

#define SCOREBOARD_WIDTH 120

// Game speed (0 = Very slow, 10 = Very fast but watchable)
int gameSpeed = 4;  // Adjust from 0 (very slow) to 10 (very fast)

// Game data
char board[GRID_SIZE][GRID_SIZE];
int playerScore = 0;
int aiScore = 0;
int drawCount = 0;

// Symbols
#define PLAYER_SYMBOL 'X'
#define AI_SYMBOL 'O'

// Bright Colors
uint16_t gridColor = tft.color565(0, 255, 255);  // Cyan grid lines
uint16_t playerColor = tft.color565(255, 0, 255);  // Magenta for Player X
uint16_t aiColor = tft.color565(0, 255, 0);  // Green for AI O
uint16_t scoreboardColor = tft.color565(255, 255, 0);  // Yellow for scoreboard text
uint16_t winnerColor = tft.color565(255, 0, 0);  // Red for winner announcement

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(tft.color565(0, 0, 0));

  // Draw the initial Tic-Tac-Toe grid and scoreboard
  drawGrid();
  drawScoreboard();

  // Initialize an empty board
  resetBoard();
}

void loop() {
  // Main game loop
  if (!isGameOver()) {
    delay(map(gameSpeed, 0, 10, 1000, 30));  // Adjustable game speed for player turns (maps from slowest to fastest)
    playerMove();
    if (!isGameOver()) {
      delay(map(gameSpeed, 0, 10, 1000, 30));  // Adjustable game speed for AI turns
      aiMove();
    }
  } else {
    // Handle game over state
    showWinner();
    delay(3000);  // Delay before resetting the game
    resetBoard();
    tft.fillScreen(tft.color565(0, 0, 0));
    drawGrid();
    drawScoreboard();
  }
}

void drawGrid() {
  // Draw vertical lines
  for (int i = 1; i < GRID_SIZE; i++) {
    tft.drawLine(GRID_ORIGIN_X + i * CELL_SIZE, GRID_ORIGIN_Y, GRID_ORIGIN_X + i * CELL_SIZE, GRID_ORIGIN_Y + GRID_SIZE * CELL_SIZE, gridColor);
  }

  // Draw horizontal lines
  for (int i = 1; i < GRID_SIZE; i++) {
    tft.drawLine(GRID_ORIGIN_X, GRID_ORIGIN_Y + i * CELL_SIZE, GRID_ORIGIN_X + GRID_SIZE * CELL_SIZE, GRID_ORIGIN_Y + i * CELL_SIZE, gridColor);
  }
}

void drawScoreboard() {
  tft.setTextColor(scoreboardColor);
  tft.setTextSize(2);

  // Clear scoreboard area before redrawing
  tft.fillRect(0, 0, SCOREBOARD_WIDTH, SCREEN_HEIGHT, tft.color565(0, 0, 0));

  // Player score
  tft.setCursor(10, 30);
  tft.print("Player:");
  tft.setCursor(10, 60);
  tft.print(playerScore);

  // AI score
  tft.setCursor(10, 120);
  tft.print("AI:");
  tft.setCursor(10, 150);
  tft.print(aiScore);

  // Draw count
  tft.setCursor(10, 210);
  tft.print("Draws:");
  tft.setCursor(10, 240);
  tft.print(drawCount);
}

void resetBoard() {
  // Reset the board to an empty state
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      board[i][j] = ' ';
    }
  }
}

bool isGameOver() {
  // Check for a win or a draw
  if (checkWin(PLAYER_SYMBOL)) {
    playerScore++;
    return true;
  } else if (checkWin(AI_SYMBOL)) {
    aiScore++;
    return true;
  } else if (isBoardFull()) {
    drawCount++;
    return true;
  }
  return false;
}

bool checkWin(char symbol) {
  // Check rows and columns for a win
  for (int i = 0; i < GRID_SIZE; i++) {
    if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) || 
        (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)) {
      return true;
    }
  }

  // Check diagonals for a win
  if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) || 
      (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
    return true;
  }

  return false;
}

bool isBoardFull() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (board[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

void showWinner() {
  tft.setTextColor(winnerColor);
  tft.setTextSize(2);

  tft.fillRect(0, SCREEN_HEIGHT - 60, SCREEN_WIDTH, 60, tft.color565(0, 0, 0));  // Clear the area
  if (checkWin(PLAYER_SYMBOL)) {
    tft.setCursor(10, SCREEN_HEIGHT - 50);
    tft.print("Player Wins!");
  } else if (checkWin(AI_SYMBOL)) {
    tft.setCursor(10, SCREEN_HEIGHT - 50);
    tft.print("AI Wins!");
  } else {
    tft.setCursor(10, SCREEN_HEIGHT - 50);
    tft.print("It's a Draw!");
  }
}

void playerMove() {
  int row, col;
  
  // Improved AI for the player (blocking and winning)
  if (findWinningMove(PLAYER_SYMBOL, row, col) || findWinningMove(AI_SYMBOL, row, col)) {
    board[row][col] = PLAYER_SYMBOL;
  } else {
    // Random move as fallback
    do {
      row = random(0, GRID_SIZE);
      col = random(0, GRID_SIZE);
    } while (board[row][col] != ' ');
    board[row][col] = PLAYER_SYMBOL;
  }
  
  drawSymbol(row, col, PLAYER_SYMBOL, playerColor);
}

void aiMove() {
  int row, col;
  
  // Improved AI: Tries to block the player or win
  if (findWinningMove(AI_SYMBOL, row, col) || findWinningMove(PLAYER_SYMBOL, row, col)) {
    board[row][col] = AI_SYMBOL;
  } else {
    // Random move as fallback
    do {
      row = random(0, GRID_SIZE);
      col = random(0, GRID_SIZE);
    } while (board[row][col] != ' ');
    board[row][col] = AI_SYMBOL;
  }
  
  drawSymbol(row, col, AI_SYMBOL, aiColor);
}

bool findWinningMove(char symbol, int &row, int &col) {
  // Check for a winning move or block opponent
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = symbol;  // Temporarily place the symbol

        if (checkWin(symbol)) {  // Check if this move results in a win
          row = i;
          col = j;
          board[i][j] = ' ';  // Reset to empty
          return true;
        }

        board[i][j] = ' ';  // Reset to empty
      }
    }
  }
  return false;
}

void drawSymbol(int row, int col, char symbol, uint16_t color) {
  int x = GRID_ORIGIN_X + col * CELL_SIZE + CELL_SIZE / 2 - 15;
  int y = GRID_ORIGIN_Y + row * CELL_SIZE + CELL_SIZE / 2 - 15;

  tft.setTextSize(4);
  tft.setTextColor(color);

  tft.setCursor(x, y);
  tft.print(symbol);
}
