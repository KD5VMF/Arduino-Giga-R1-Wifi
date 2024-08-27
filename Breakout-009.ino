#include <Scheduler.h>
#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

// Constants for the screen and game components
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define SCOREBOARD_WIDTH 150
#define MAX_LEVEL 100

// Scoring and game variables
int pointsPerRowCleared = 10;
int pointsPerBrickHit = 2;
int multiBrickBonus = 4;
int missPenalty = 125;
int pointsToLose = 0;

// Gravity and physics variables
float gravity = 0.04;
float gravityMaxSpeed = 4;

// Shared variables for communication between M7 and M4 cores
volatile int score = 0;
volatile int misses = 0;
volatile int level = 1;
volatile int maxLevelReached = 1;  // This will track the highest level achieved
volatile bool updateScoreboardFlag = false;
volatile bool graphicsReady = false;

// Customizable Variables
int ballInitialSpeedX = 5;
int ballInitialSpeedY = -6;
int ballSize = 10;
int initialPlayerAccuracy = 3;
int initialPlayerIntelligence = 2;
int initialPaddleSpeed = 14;
int paddleWidth = 100;
int brickHitRequirement = 1;

// Dynamic Ball Speed Adjustments
float ballSpeedMultiplier = 1.0;
float ballSpeedIncrement = 0.05;
float ballSpeedDecrement = 0.02;
float ballSpeedMax = 6.0;
float ballSpeedMin = 1.0;

// Paddle properties
#define PADDLE_HEIGHT 10
#define PADDLE_Y_POSITION (SCREEN_HEIGHT - 40)
int paddleX = SCREEN_WIDTH / 2 - paddleWidth / 2;

// Ball properties
float ballX = SCREEN_WIDTH / 2;
float ballY = PADDLE_Y_POSITION - ballSize - 2;
float ballDX = ballInitialSpeedX * ballSpeedMultiplier;
float ballDY = ballInitialSpeedY * ballSpeedMultiplier;

// Paddle AI properties
int playerAccuracy = initialPlayerAccuracy;
int playerIntelligence = initialPlayerIntelligence;
int paddleSpeed = initialPaddleSpeed;

// Brick properties
#define BRICK_ROWS 3
#define BRICK_COLUMNS 5
#define BRICK_WIDTH 115
#define BRICK_HEIGHT 50
#define BRICK_SPACING 7
int brickStrength[BRICK_ROWS][BRICK_COLUMNS];
uint16_t brickColors[BRICK_ROWS][BRICK_COLUMNS];
int maxBrickStrength = brickHitRequirement;

bool blockedGrid[BRICK_ROWS][BRICK_COLUMNS];

// Neon colors for bricks
uint16_t neonColors[] = {
    tft.color565(57, 255, 20),   // Neon green
    tft.color565(255, 0, 255),   // Neon magenta
    tft.color565(0, 255, 255),   // Neon cyan
    tft.color565(255, 255, 0),   // Neon yellow
    tft.color565(255, 105, 180), // Neon pink
    tft.color565(255, 69, 0),    // Neon orange
    tft.color565(138, 43, 226),  // Neon purple
    tft.color565(124, 252, 0),   // Neon lime
    tft.color565(0, 191, 255),   // Neon sky blue
    tft.color565(255, 20, 147),  // Neon deep pink
};

// Multi-hit combo tracking
int multiHitCount = 0;

// Colors
uint16_t paddleColor = tft.color565(255, 255, 255);
uint16_t ballColor = tft.color565(255, 255, 0);
uint16_t backgroundColor = tft.color565(0, 0, 0);
uint16_t scoreboardBackgroundColor = tft.color565(0, 0, 128);
uint16_t scoreboardTextColor = tft.color565(255, 255, 255);
uint16_t scoreColor = tft.color565(255, 215, 0);
uint16_t missesColor = tft.color565(255, 0, 0);
uint16_t levelColor = tft.color565(0, 255, 0);

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(backgroundColor);

  if (maxLevelReached == 1) {
    maxLevelReached = 1;
  }

  drawScoreboardLayout();
  initializeBricks();
  resetPaddleAndBall();
  drawBricks();
  drawPaddle();
  drawBall();

  // Delay to allow players to see the setup before the game starts
  delay(2000);

  graphicsReady = true;

  Scheduler.startLoop(core1Task);
  Scheduler.startLoop(core2Task);
  Scheduler.startLoop(coreM4Task);
}

void loop() {
}

void core1Task() {
  while (true) {
    if (graphicsReady) {
      updateDisplay();
    }
    delay(1);
  }
}

void core2Task() {
  while (true) {
    if (graphicsReady) {
      moveBall();
      checkCollisions();
      updatePaddleAI();
      checkLevelProgression();
    }
    delay(1);
  }
}

void coreM4Task() {
  while (true) {
    if (updateScoreboardFlag) {
      updateScoreboard();
      updateScoreboardFlag = false;
    }
    delay(20);
  }
}

void drawScoreboardLayout() {
  tft.fillRoundRect(0, 0, SCOREBOARD_WIDTH, SCREEN_HEIGHT, 15, scoreboardBackgroundColor);
  tft.setTextColor(scoreboardTextColor);
  tft.setTextSize(2);

  tft.setCursor(10, 20);
  tft.print("Score");
  tft.setCursor(10, 120);
  tft.print("Misses");
  tft.setCursor(10, 220);
  tft.print("Level");
  tft.setCursor(10, 320);
  tft.print("Max Level");
}

void updateScoreboard() {
  tft.setTextColor(scoreColor);
  tft.setTextSize(3);
  tft.fillRect(10, 60, SCOREBOARD_WIDTH - 20, 50, scoreboardBackgroundColor);
  tft.setCursor(10, 60);
  tft.print(score);

  tft.setTextColor(missesColor);
  tft.fillRect(10, 160, SCOREBOARD_WIDTH - 20, 50, scoreboardBackgroundColor);
  tft.setCursor(10, 160);
  tft.print(misses);

  tft.setTextColor(levelColor);
  tft.fillRect(10, 260, SCOREBOARD_WIDTH - 20, 50, scoreboardBackgroundColor);
  tft.setCursor(10, 260);
  tft.print(level);

  tft.setTextColor(tft.color565(255, 215, 0));
  tft.setTextSize(3);
  tft.fillRect(10, 360, SCOREBOARD_WIDTH - 20, 50, scoreboardBackgroundColor);
  tft.setCursor(10, 360);
  tft.print(maxLevelReached);
}

void initializeBricks() {
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      brickStrength[row][col] = maxBrickStrength;
      brickColors[row][col] = neonColors[random(0, sizeof(neonColors) / sizeof(neonColors[0]))];
      blockedGrid[row][col] = true;
    }
  }
}

void drawBricks() {
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      if (brickStrength[row][col] > 0) {
        int x = SCOREBOARD_WIDTH + col * (BRICK_WIDTH + BRICK_SPACING);
        int y = row * (BRICK_HEIGHT + BRICK_SPACING) + 50;
        tft.fillRoundRect(x, y, BRICK_WIDTH, BRICK_HEIGHT, 10, brickColors[row][col]);
      }
    }
  }
}

void resetPaddleAndBall() {
  // Clear the old paddle to prevent ghosting issues
  clearPaddle();

  // Center the paddle and reset the ball above the paddle
  paddleX = SCREEN_WIDTH / 2 - paddleWidth / 2;
  ballX = SCREEN_WIDTH / 2;
  ballY = PADDLE_Y_POSITION - ballSize - 2;

  ballDX = ballInitialSpeedX;
  ballDY = ballInitialSpeedY;
}

void drawPaddle() {
  clearPaddle();  // Clear previous paddle before drawing the new one
  tft.fillRoundRect(paddleX, PADDLE_Y_POSITION, paddleWidth, PADDLE_HEIGHT, 5, paddleColor);
}

void clearPaddle() {
  tft.fillRoundRect(paddleX, PADDLE_Y_POSITION, paddleWidth, PADDLE_HEIGHT, 5, backgroundColor);
}

void drawBall() {
  tft.fillCircle(ballX, ballY, ballSize / 2, ballColor);
}

void clearBall() {
  tft.fillCircle(ballX, ballY, ballSize / 2, backgroundColor);
}

void moveBall() {
  clearBall();

  float nextBallX = ballX + ballDX * ballSpeedMultiplier;
  float nextBallY = ballY + ballDY * ballSpeedMultiplier;

  // Handle wall collisions
  if (nextBallX <= SCOREBOARD_WIDTH + ballSize / 2 || nextBallX >= SCREEN_WIDTH - ballSize / 2) {
    ballDX = -ballDX;  // Reflect horizontally
  }

  if (nextBallY <= ballSize / 2) {
    ballDY = -ballDY;  // Reflect vertically
  }

  // Ensure consistent upward motion (up power) if ball is stuck in horizontal bouncing
  if (abs(ballDY) < 1) {
    ballDY = (ballDY < 0) ? -2 : 2;  // Add upward force if ball's vertical speed is too low
  }

  ballDY += gravity;
  if (ballDY > gravityMaxSpeed) {
    ballDY = gravityMaxSpeed;  // Cap gravity speed
  }

  ballX += ballDX * ballSpeedMultiplier;
  ballY += ballDY * ballSpeedMultiplier;

  // Ball out of bounds (missed paddle)
  if (ballY >= SCREEN_HEIGHT) {
    misses++;
    score -= missPenalty;
    if (score < pointsToLose) score = pointsToLose;
    if (score == pointsToLose) {
      gameOver();
    } else {
      resetPaddleAndBall();
      drawPaddle();
      drawBall();
      delay(2000);  // Delay before starting again
    }
    updateScoreboardFlag = true;
    multiHitCount = 0;  // Reset multi-hit combo count
  }

  drawBall();
}

void checkCollisions() {
  // Ball and paddle collision
  if (ballY + ballSize / 2 >= PADDLE_Y_POSITION && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
    ballDY = -ballDY;
    increaseBallSpeed();
    multiHitCount = 0;  // Reset combo count
  }

  // Ball and brick collision detection
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      if (brickStrength[row][col] > 0) {
        int brickX = SCOREBOARD_WIDTH + col * (BRICK_WIDTH + BRICK_SPACING);
        int brickY = row * (BRICK_HEIGHT + BRICK_SPACING) + 50;

        // Collision detection and prevent ball from passing through bricks
        if (ballX + ballSize / 2 > brickX && ballX - ballSize / 2 < brickX + BRICK_WIDTH &&
            ballY + ballSize / 2 > brickY && ballY - ballSize / 2 < brickY + BRICK_HEIGHT) {

          // Handle collision based on ball direction and brick sides
          float ballCenterX = ballX;
          float ballCenterY = ballY;
          float brickCenterX = brickX + BRICK_WIDTH / 2;
          float brickCenterY = brickY + BRICK_HEIGHT / 2;

          // Horizontal or vertical reflection based on closest edge
          if (abs(ballCenterX - brickCenterX) > abs(ballCenterY - brickCenterY)) {
            ballDX = -ballDX;  // Reflect horizontally
          } else {
            ballDY = -ballDY;  // Reflect vertically
          }

          // Reduce brick strength and check for destruction
          brickStrength[row][col]--;
          if (brickStrength[row][col] <= 0) {
            tft.fillRoundRect(brickX, brickY, BRICK_WIDTH, BRICK_HEIGHT, 10, backgroundColor);  // Clear the brick
            score += pointsPerBrickHit;
            multiHitCount++;
            score += multiHitCount * multiBrickBonus;
            updateScoreboardFlag = true;

            // Check if the entire row is cleared
            bool rowCleared = true;
            for (int c = 0; c < BRICK_COLUMNS; c++) {
              if (brickStrength[row][c] > 0) {
                rowCleared = false;
                break;
              }
            }
            if (rowCleared) {
              score += pointsPerRowCleared;
              updateScoreboardFlag = true;
            }
          }
          return;  // Only process one collision per frame
        }
      }
    }
  }
}

void updatePaddleAI() {
  clearPaddle();  // Clear previous paddle position to avoid ghosting
  int targetX = ballX + ballDX * playerIntelligence;

  if (targetX < paddleX + paddleWidth / 2 - playerAccuracy && paddleX > SCOREBOARD_WIDTH) {
    paddleX -= paddleSpeed;
  } else if (targetX > paddleX + paddleWidth / 2 + playerAccuracy && paddleX < SCREEN_WIDTH - paddleWidth) {
    paddleX += paddleSpeed;
  }
  drawPaddle();  // Redraw the paddle at the new position
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
  tft.fillScreen(backgroundColor);
  drawScoreboardLayout();

  tft.setTextSize(4);
  tft.setTextColor(tft.color565(255, 0, 0));

  tft.setCursor(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 30);
  tft.print("LEVEL ");
  tft.print(level + 1);

  delay(2000);

  tft.fillScreen(backgroundColor);
  drawScoreboardLayout();
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

  maxBrickStrength++;  // Increment brick strength on each level

  if (level > maxLevelReached) {
    maxLevelReached = level;
  }

  // Reset ball speed and gravity settings for the new level
  ballSpeedMultiplier = 1.0;
  ballDX = ballInitialSpeedX;
  ballDY = ballInitialSpeedY;

  initializeBricks();
  resetPaddleAndBall();
  drawBricks();
  drawPaddle();
  drawBall();
  delay(2000);  // Delay before starting the next level

  updateScoreboardFlag = true;
}

void resetGame() {
  score = 0;
  misses = 0;
  maxBrickStrength = brickHitRequirement;

  // Reset game-specific variables
  ballSpeedMultiplier = 1.0;
  ballDX = ballInitialSpeedX;
  ballDY = ballInitialSpeedY;

  level = 1;  // Reset level to 1
  initializeBricks();
  resetPaddleAndBall();
  drawBricks();
  drawPaddle();
  drawBall();

  delay(2000);  // Delay before starting the new game
  updateScoreboardFlag = true;
}

void gameOver() {
  tft.fillScreen(backgroundColor);
  tft.setTextSize(4);
  tft.setTextColor(tft.color565(255, 0, 0));
  tft.setCursor(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 30);
  tft.print("GAME OVER");

  delay(2000);

  resetGame();
}