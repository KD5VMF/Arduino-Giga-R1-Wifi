#include <Scheduler.h>
#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

// Constants for the screen and game components
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define SCOREBOARD_WIDTH 120
#define MAX_LEVEL 100

// Shared variables for communication between M7 and M4 cores
volatile int score = 0;
volatile int misses = 0;
volatile int level = 1;
volatile bool updateScoreboardFlag = false;  // Flag to trigger scoreboard update on M4

// Customizable Variables
int ballInitialSpeedX = 5;
int ballInitialSpeedY = -5;
int ballSize = 10;
int initialPlayerAccuracy = 3;
int initialPlayerIntelligence = 2;
int initialPaddleSpeed = 14;
int paddleWidth = 100;
int brickHitRequirement = 1;
int pointsPerBrickHit = 2;
int pointsLostPerMiss = 1;

// Dynamic Ball Speed Adjustments
float ballSpeedMultiplier = 1.0;
float ballSpeedIncrement = 0.2;
float ballSpeedDecrement = 0.1;
float ballSpeedMax = 8.0;
float ballSpeedMin = 1.0;

// Paddle properties
#define PADDLE_HEIGHT 10
#define PADDLE_Y_POSITION (SCREEN_HEIGHT - 40)
int paddleX = SCREEN_WIDTH / 2 - paddleWidth / 2;

// Ball properties
float ballX = SCREEN_WIDTH / 2;
float ballY = SCREEN_HEIGHT / 2;
float ballDX = ballInitialSpeedX * ballSpeedMultiplier;
float ballDY = ballInitialSpeedY * ballSpeedMultiplier;

// Paddle AI properties
int playerAccuracy = initialPlayerAccuracy;
int playerIntelligence = initialPlayerIntelligence;
int paddleSpeed = initialPaddleSpeed;

// Brick properties
#define BRICK_ROWS 5
#define BRICK_COLUMNS 5
#define BRICK_WIDTH 100
#define BRICK_HEIGHT 20
#define BRICK_SPACING 10
int brickStrength[BRICK_ROWS][BRICK_COLUMNS];
int maxBrickStrength = brickHitRequirement;

// Colors
uint16_t paddleColor = tft.color565(255, 255, 0);
uint16_t ballColor = tft.color565(255, 255, 255);
uint16_t backgroundColor = tft.color565(0, 0, 0);

// Function Prototypes
void core1Task();
void core2Task();
void coreM4Task();
void drawPaddle();
void clearPaddle();
void drawBall();
void clearBall();
void moveBall();
void resetBall();
void checkCollisions();
void updatePaddleAI();
void increaseBallSpeed();
void decreaseBallSpeed();
void checkLevelProgression();
void drawBricks();
void initializeBricks();
void updateDisplay();
void showLevelText();
void resetGame();

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(backgroundColor);

  // Initialize game
  initializeBricks();
  drawBricks();
  drawPaddle();
  drawBall();

  // Start tasks on cores
  Scheduler.startLoop(core1Task);  // M7 Core 1: Rendering task
  Scheduler.startLoop(core2Task);  // M7 Core 2: Game logic task
  Scheduler.startLoop(coreM4Task);  // M4 Core: Scoreboard updates
}

void loop() {
  // Main loop remains empty because tasks are assigned to cores
}

void core1Task() {
  // Rendering loop (Core 1) for game graphics (excluding scoreboard)
  while (true) {
    updateDisplay();
    delay(5);  // Control game rendering speed
  }
}

void core2Task() {
  // Game logic loop (Core 2)
  while (true) {
    moveBall();
    checkCollisions();
    updatePaddleAI();
    checkLevelProgression();
    delay(5);  // Control game logic speed
  }
}

void coreM4Task() {
  // Scoreboard update loop on M4 core
  while (true) {
    if (updateScoreboardFlag) {
      drawScoreboard();
      updateScoreboardFlag = false;  // Reset flag after update
    }
    delay(20);  // Control scoreboard update rate
  }
}

void drawScoreboard() {
  tft.setTextColor(tft.color565(255, 255, 255));
  tft.setTextSize(2);

  // Clear scoreboard area before redrawing
  tft.fillRect(0, 0, SCOREBOARD_WIDTH, SCREEN_HEIGHT, backgroundColor);

  // Draw score
  tft.setCursor(10, 30);
  tft.print("Score:");
  tft.setCursor(10, 60);
  tft.print(score);

  // Draw misses
  tft.setCursor(10, 130);
  tft.print("Misses:");
  tft.setCursor(10, 160);
  tft.print(misses);

  // Draw level
  tft.setCursor(10, 230);
  tft.print("Level:");
  tft.setCursor(10, 260);
  tft.print(level);
}

void initializeBricks() {
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      brickStrength[row][col] = maxBrickStrength;
    }
  }
}

void drawBricks() {
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      if (brickStrength[row][col] > 0) {
        int x = SCOREBOARD_WIDTH + col * (BRICK_WIDTH + BRICK_SPACING);
        int y = row * (BRICK_HEIGHT + BRICK_SPACING) + 50;
        uint16_t brickColor = getBrickColor(brickStrength[row][col]);
        tft.fillRect(x, y, BRICK_WIDTH, BRICK_HEIGHT, brickColor);
      }
    }
  }
}

uint16_t getBrickColor(int strength) {
  switch (strength) {
    case 1: return tft.color565(0, 255, 255);  // Cyan
    case 2: return tft.color565(255, 165, 0);  // Orange
    case 3: return tft.color565(255, 0, 0);    // Red
    default: return tft.color565(255, 255, 255); // White for tougher bricks
  }
}

void drawPaddle() {
  tft.fillRect(paddleX, PADDLE_Y_POSITION, paddleWidth, PADDLE_HEIGHT, paddleColor);
}

void clearPaddle() {
  tft.fillRect(paddleX, PADDLE_Y_POSITION, paddleWidth, PADDLE_HEIGHT, backgroundColor);
}

void drawBall() {
  tft.fillCircle(ballX, ballY, ballSize / 2, ballColor);
}

void clearBall() {
  tft.fillCircle(ballX, ballY, ballSize / 2, backgroundColor);
}

void moveBall() {
  clearBall();

  // Update ball position
  ballX += ballDX * ballSpeedMultiplier;
  ballY += ballDY * ballSpeedMultiplier;

  // Ball collision with walls
  if (ballX <= SCOREBOARD_WIDTH + ballSize / 2) {
    ballX = SCOREBOARD_WIDTH + ballSize / 2;
    ballDX = -ballDX;
  }
  if (ballX >= SCREEN_WIDTH - ballSize / 2) {
    ballX = SCREEN_WIDTH - ballSize / 2;
    ballDX = -ballDX;
  }
  if (ballY <= ballSize / 2) {
    ballY = ballSize / 2;
    ballDY = -ballDY;
  }

  // Ball out of bounds
  if (ballY >= SCREEN_HEIGHT) {
    misses++;
    score -= pointsLostPerMiss;
    if (score < 0) score = 0;
    resetBall();
    updateScoreboardFlag = true;  // Trigger scoreboard update
  }

  drawBall();
}

void resetBall() {
  ballX = SCREEN_WIDTH / 2;
  ballY = SCREEN_HEIGHT / 2;
  ballSpeedMultiplier = 1.0;
  ballDX = ballInitialSpeedX;
  ballDY = ballInitialSpeedY;
  drawBall();
}

void checkCollisions() {
  if (ballY + ballSize / 2 >= PADDLE_Y_POSITION && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
    ballDY = -ballDY;
    increaseBallSpeed();
  }

  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      if (brickStrength[row][col] > 0) {
        int brickX = SCOREBOARD_WIDTH + col * (BRICK_WIDTH + BRICK_SPACING);
        int brickY = row * (BRICK_HEIGHT + BRICK_SPACING) + 50;
        bool hittingTop = (ballY <= brickY + BRICK_HEIGHT / 2);
        if (ballX >= brickX && ballX <= brickX + BRICK_WIDTH && ballY >= brickY && ballY <= brickY + BRICK_HEIGHT) {
          brickStrength[row][col] -= hittingTop ? 1 / 3.0 : 1;
          ballDY = -ballDY;
          score += pointsPerBrickHit;
          if (brickStrength[row][col] <= 0) {
            tft.fillRect(brickX, brickY, BRICK_WIDTH, BRICK_HEIGHT, backgroundColor);
            decreaseBallSpeed();
          }
          updateScoreboardFlag = true;
          return;
        }
      }
    }
  }
}

void updatePaddleAI() {
  clearPaddle();
  int targetX = ballX + ballDX * playerIntelligence;
  if (targetX < paddleX + paddleWidth / 2 - playerAccuracy && paddleX > SCOREBOARD_WIDTH) {
    paddleX -= paddleSpeed;
  } else if (targetX > paddleX + paddleWidth / 2 + playerAccuracy && paddleX < SCREEN_WIDTH - paddleWidth) {
    paddleX += paddleSpeed;
  }
  drawPaddle();
}

void increaseBallSpeed() {
  ballSpeedMultiplier += ballSpeedIncrement;
  if (ballSpeedMultiplier > ballSpeedMax) {
    ballSpeedMultiplier = ballSpeedMax;
  }
}

void decreaseBallSpeed() {
  ballSpeedMultiplier -= ballSpeedDecrement;
  if (ballSpeedMultiplier < ballSpeedMin) {
    ballSpeedMultiplier = ballSpeedMin;
  }
}

void checkLevelProgression() {
  bool allBricksCleared = true;
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      if (brickStrength[row][col] > 0) {
        allBricksCleared = false;
        break;
      }
    }
  }
  if (allBricksCleared) {
    showLevelText();
    nextLevel();
  }
}

void showLevelText() {
  tft.setCursor(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2);
  tft.setTextColor(tft.color565(0, 255, 0));
  tft.setTextSize(3);
  tft.print("Level ");
  tft.print(level + 1);
  delay(2000);
  tft.fillScreen(backgroundColor);
}

void updateDisplay() {
  drawBricks();
}

void nextLevel() {
  level++;
  if (level > MAX_LEVEL) {
    resetGame();
    return;
  }
  maxBrickStrength++;
  ballDX += (ballDX > 0) ? 1 : -1;
  ballDY += (ballDY > 0) ? 1 : -1;
  initializeBricks();
  resetBall();
  updateScoreboardFlag = true;
}

void resetGame() {
  level = 1;
  score = 0;
  misses = 0;
  maxBrickStrength = brickHitRequirement;
  initializeBricks();
  resetBall();
  updateScoreboardFlag = true;
}
