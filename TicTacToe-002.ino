#include <Scheduler.h>
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

#define SCOREBOARD_WIDTH 150

// Game speed (0 = Very slow, 10 = Very fast but controlled)
int gameSpeed = 9;  // Adjust from 0 (slow) to 10 (fast), but with AI thinking delays

// Game data
char board[GRID_SIZE][GRID_SIZE];
volatile int m4Score = 0;
volatile int m7Score = 0;
volatile int drawCount = 0;
volatile int gameCount = 0;  // Track the number of games played

// Symbols
#define M4_SYMBOL 'X'
#define M7_SYMBOL 'O'

// Turn tracking
volatile bool m4Turn = true;  // Start with M4 player

// Bright Colors
uint16_t gridColor = tft.color565(0, 255, 255);  // Cyan grid lines
uint16_t m4Color = tft.color565(255, 0, 255);    // Magenta for M4 Player X
uint16_t m7Color = tft.color565(0, 255, 0);      // Green for M7 Player O
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

  // Start the Scheduler for multiple core tasks
  Scheduler.startLoop(m4CoreTask);  // M4 Core task for one player
  Scheduler.startLoop(m7Core1Task); // M7 Core 1 task for another player
  Scheduler.startLoop(m7Core2Task); // M7 Core 2 task for managing the scoreboard and game tracking
}

void loop() {
  // Main loop remains empty as the Scheduler handles the game
}

void m4CoreTask() {
  // Main loop for M4 player
  while (true) {
    if (m4Turn && !isGameOver()) {
      delay(map(gameSpeed, 0, 10, 3000, 1000));  // Delay simulating thinking time for M4
      m4Move();
      m4Turn = false;  // Switch turn to M7
      delay(500);      // Wait briefly before M7's turn
    }
  }
}

void m7Core1Task() {
  // Main loop for M7 player
  while (true) {
    if (!m4Turn && !isGameOver()) {
      delay(map(gameSpeed, 0, 10, 3000, 1000));  // Delay simulating thinking time for M7
      m7Move();
      m4Turn = true;  // Switch turn back to M4
      delay(500);     // Wait briefly before M4's turn
    }
  }
}

void m7Core2Task() {
  // Scoreboard management and game tracking
  while (true) {
    if (isGameOver()) {
      // Handle game over state and reset
      showWinner();
      delay(3000);  // Delay before resetting the game to give time for observation
      resetBoard();
      tft.fillScreen(tft.color565(0, 0, 0));
      drawGrid();
      drawScoreboard();
      gameCount++;
      m4Turn = true;  // Start with M4 again after game reset
      delay(2000);  // Delay between games
    }
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

  // M4 player score with symbol
  tft.setCursor(10, 30);
  tft.print("M4 (X):");
  tft.setCursor(10, 60);
  tft.print(m4Score);

  // M7 player score with symbol
  tft.setCursor(10, 120);
  tft.print("M7 (O):");
  tft.setCursor(10, 150);
  tft.print(m7Score);

  // Draw count
  tft.setCursor(10, 210);
  tft.print("Draws:");
  tft.setCursor(10, 240);
  tft.print(drawCount);

  // Game count
  tft.setCursor(10, 300);
  tft.print("Games Played:");
  tft.setCursor(10, 330);
  tft.print(gameCount);
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
  if (checkWin(M4_SYMBOL)) {
    m4Score++;  // Award 1 point to M4
    return true;
  } else if (checkWin(M7_SYMBOL)) {
    m7Score++;  // Award 1 point to M7
    return true;
  } else if (isBoardFull()) {
    drawCount++;  // Correctly increment draw count by 1
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
  if (checkWin(M4_SYMBOL)) {
    tft.setCursor(10, SCREEN_HEIGHT - 50);
    tft.print("M4 Wins!");
  } else if (checkWin(M7_SYMBOL)) {
    tft.setCursor(10, SCREEN_HEIGHT - 50);
    tft.print("M7 Wins!");
  } else {
    tft.setCursor(10, SCREEN_HEIGHT - 50);
    tft.print("It's a Draw!");
  }
}

void m4Move() {
  int row, col;

  // Smarter AI for M4: Try to win, block, or plan
  if (findWinningMove(M4_SYMBOL, row, col)) {  // Offensive: Try to win
    board[row][col] = M4_SYMBOL;
  } else if (findWinningMove(M7_SYMBOL, row, col)) {  // Defensive: Block M7's win
    board[row][col] = M4_SYMBOL;
  } else {
    // Create a random move fallback if no smart move
    do {
      row = random(0, GRID_SIZE);
      col = random(0, GRID_SIZE);
    } while (board[row][col] != ' ');
    board[row][col] = M4_SYMBOL;
  }

  drawSymbol(row, col, M4_SYMBOL, m4Color);
}

void m7Move() {
  int row, col;

  // Smarter AI for M7: Try to win, block, or plan
  if (findWinningMove(M7_SYMBOL, row, col)) {  // Offensive: Try to win
    board[row][col] = M7_SYMBOL;
  } else if (findWinningMove(M4_SYMBOL, row, col)) {  // Defensive: Block M4's win
    board[row][col] = M7_SYMBOL;
  } else {
    // Create a random move fallback if no smart move
    do {
      row = random(0, GRID_SIZE);
      col = random(0, GRID_SIZE);
    } while (board[row][col] != ' ');
    board[row][col] = M7_SYMBOL;
  }

  drawSymbol(row, col, M7_SYMBOL, m7Color);
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
