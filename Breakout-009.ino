#include <Scheduler.h>
#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

// Constants for the screen and game components
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define SCOREBOARD_WIDTH 140
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
int ballInitialSpeedX = 6;
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
float ballY = PADDLE_Y_POSITION - ballSize - 3;
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
#define BRICK_SPACING 6
int brickStrength[BRICK_ROWS][BRICK_COLUMNS];
uint16_t brickColors[BRICK_ROWS][BRICK_COLUMNS];
int maxBrickStrength = brickHitRequirement;

bool blockedGrid[BRICK_ROWS][BRICK_COLUMNS];

// Expanded Neon Colors for Bricks - 50 Colors
uint16_t neonColors[30] = {
    tft.color565(57, 255, 20),    // Neon green
    tft.color565(255, 0, 255),    // Neon magenta
    tft.color565(0, 255, 255),    // Neon cyan
    tft.color565(255, 255, 0),    // Neon yellow
    tft.color565(255, 105, 180),  // Neon pink
    tft.color565(255, 69, 0),     // Neon orange
    tft.color565(138, 43, 226),   // Neon purple
    tft.color565(124, 252, 0),    // Neon lime
    tft.color565(0, 191, 255),    // Neon sky blue
    tft.color565(255, 20, 147),   // Neon deep pink
    tft.color565(127, 255, 0),    // Chartreuse
    tft.color565(173, 255, 47),   // Green yellow
    tft.color565(34, 255, 150),   // Neon green light
    tft.color565(255, 140, 0),    // Dark orange (bright neon)
    tft.color565(255, 165, 0),    // Neon orange
    tft.color565(199, 21, 133),   // Neon raspberry
    tft.color565(255, 0, 127),    // Neon hot pink
    tft.color565(255, 110, 180),  // Neon rose
    tft.color565(0, 250, 154),    // Medium spring green (neon-like)
    tft.color565(102, 255, 178),  // Aquamarine (neon-like)
    tft.color565(240, 50, 230),   // Neon violet
    tft.color565(0, 255, 127),    // Spring green
    tft.color565(255, 99, 71),    // Neon tomato red
    tft.color565(255, 66, 244),   // Neon fuchsia
    tft.color565(255, 240, 31),   // Neon lemon
    tft.color565(255, 182, 193),  // Neon light pink
    tft.color565(173, 255, 47),   // Neon green yellow
    tft.color565(0, 255, 102),    // Neon mint green
    tft.color565(255, 20, 240),   // Neon purple-pink
    tft.color565(0, 128, 255)     // Neon blue
};

// Multi-hit combo tracking
int multiHitCount = 0;

// Colors
uint16_t paddleColor = tft.color565(255, 255, 255);
uint16_t ballColor = tft.color565(255, 255, 0);
uint16_t backgroundColor = tft.color565(0, 0, 0);
uint16_t brightGreen = tft.color565(57, 255, 20);  // Bright green color for instructions

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(backgroundColor);

  // Display the welcome screen with countdown
  displayWelcomeScreen();

  drawScoreboardLayout();
  initializeBricks();
  resetPaddleAndBall();
  drawBricks();
  drawPaddle();
  drawBall();

  graphicsReady = true;

  Scheduler.startLoop(core1Task);
  Scheduler.startLoop(core2Task);
  Scheduler.startLoop(coreM4Task);
}

void displayWelcomeScreen() {
  tft.fillScreen(backgroundColor);
  tft.setTextColor(brightGreen);
  tft.setTextSize(2);

  tft.setCursor(10, 20);
  tft.print("Welcome to Breakout-009!");

  tft.setCursor(10, 60);
  tft.print("Scoreboard and Scoring:");
  tft.setCursor(10, 100);
  tft.print("- Brick hit: 2 points");
  tft.setCursor(10, 130);
  tft.print("- Row cleared: 10 points");
  tft.setCursor(10, 160);
  tft.print("- Multi-brick bonus: 4 points per hit");

  tft.setCursor(10, 200);
  tft.print("Level Progression:");
  tft.setCursor(10, 230);
  tft.print("- Each level gets harder");
  tft.setCursor(10, 260);
  tft.print("- Ball speed increases");
  tft.setCursor(10, 290);
  tft.print("- Brick strength increases");

  tft.setCursor(10, 350);
  tft.print("Get ready!");

  // Display countdown timer using a non-blocking approach
  unsigned long previousMillis = millis();  // Store the current time
  int countdown = 35;

  while (countdown >= 0) {
    unsigned long currentMillis = millis();  // Get the current time

    if (currentMillis - previousMillis >= 1000) {
      // 1 second has passed
      previousMillis = currentMillis;

      // Clear the previous countdown text
      tft.fillRect(10, 400, 300, 40, backgroundColor);

      // Update and display the countdown
      tft.setCursor(10, 400);
      tft.setTextSize(3);
      tft.print("Starts in: ");
      tft.print(countdown);

      // Decrement the countdown
      countdown--;
    }
  }

  // After countdown, proceed to game setup
  tft.fillScreen(backgroundColor);
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
  tft.fillRoundRect(0, 0, SCOREBOARD_WIDTH, SCREEN_HEIGHT, 15, tft.color565(0, 0, 128));
  tft.setTextColor(tft.color565(255, 255, 255));
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
  tft.setTextColor(tft.color565(255, 215, 0));
  tft.setTextSize(3);
  tft.fillRect(10, 60, SCOREBOARD_WIDTH - 20, 50, tft.color565(0, 0, 128));
  tft.setCursor(10, 60);
  tft.print(score);

  tft.setTextColor(tft.color565(255, 0, 0));
  tft.fillRect(10, 160, SCOREBOARD_WIDTH - 20, 50, tft.color565(0, 0, 128));
  tft.setCursor(10, 160);
  tft.print(misses);

  tft.setTextColor(tft.color565(0, 255, 0));
  tft.fillRect(10, 260, SCOREBOARD_WIDTH - 20, 50, tft.color565(0, 0, 128));
  tft.setCursor(10, 260);
  tft.print(level);

  tft.setTextColor(tft.color565(255, 215, 0));
  tft.setTextSize(3);
  tft.fillRect(10, 360, SCOREBOARD_WIDTH - 20, 50, tft.color565(0, 0, 128));
  tft.setCursor(10, 360);
  tft.print(maxLevelReached);
}

void initializeBricks() {
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      // Ensure colors are chosen from the bright neonColors array (with 30 bright neon colors)
      uint16_t color = neonColors[random(0, 30)]; // Choose from the 30 neon colors
      
      // Avoid placing two identical colors adjacent to each other
      while ((col > 0 && color == brickColors[row][col - 1]) || 
             (row > 0 && color == brickColors[row - 1][col])) {
        color = neonColors[random(0, 30)]; // Re-select color if it's the same as adjacent bricks
      }

      brickColors[row][col] = color;
      brickStrength[row][col] = maxBrickStrength;
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
  clearPaddle();
  paddleX = SCREEN_WIDTH / 2 - paddleWidth / 2;
  ballX = SCREEN_WIDTH / 2;
  ballY = PADDLE_Y_POSITION - ballSize - 2;

  // Randomize ball direction on serve
  if (random(0, 2) == 0) {
    ballDX = ballInitialSpeedX;
  } else {
    ballDX = -ballInitialSpeedX;
  }

  ballDY = ballInitialSpeedY;
}

void drawPaddle() {
  clearPaddle();
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

  if (nextBallX <= SCOREBOARD_WIDTH + ballSize / 2 || nextBallX >= SCREEN_WIDTH - ballSize / 2) {
    ballDX = -ballDX;
  }

  if (nextBallY <= ballSize / 2) {
    ballDY = -ballDY;
  }

  if (abs(ballDY) < 1) {
    ballDY = (ballDY < 0) ? -2 : 2;
  }

  ballDY += gravity;
  if (ballDY > gravityMaxSpeed) {
    ballDY = gravityMaxSpeed;
  }

  ballX += ballDX * ballSpeedMultiplier;
  ballY += ballDY * ballSpeedMultiplier;

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
      delay(2000);
    }
    updateScoreboardFlag = true;
    multiHitCount = 0;
  }

  drawBall();
}

void checkCollisions() {
  if (ballY + ballSize / 2 >= PADDLE_Y_POSITION && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
    ballDY = -ballDY;
    increaseBallSpeed();
    multiHitCount = 0;
  }

  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      if (brickStrength[row][col] > 0) {
        int brickX = SCOREBOARD_WIDTH + col * (BRICK_WIDTH + BRICK_SPACING);
        int brickY = row * (BRICK_HEIGHT + BRICK_SPACING) + 50;

        if (ballX + ballSize / 2 > brickX && ballX - ballSize / 2 < brickX + BRICK_WIDTH &&
            ballY + ballSize / 2 > brickY && ballY - ballSize / 2 < brickY + BRICK_HEIGHT) {

          float ballCenterX = ballX;
          float ballCenterY = ballY;
          float brickCenterX = brickX + BRICK_WIDTH / 2;
          float brickCenterY = brickY + BRICK_HEIGHT / 2;

          if (abs(ballCenterX - brickCenterX) > abs(ballCenterY - brickCenterY)) {
            ballDX = -ballDX;
          } else {
            ballDY = -ballDY;
          }

          brickStrength[row][col]--;
          if (brickStrength[row][col] <= 0) {
            tft.fillRoundRect(brickX, brickY, BRICK_WIDTH, BRICK_HEIGHT, 10, backgroundColor);
            score += pointsPerBrickHit;
            multiHitCount++;
            score += multiHitCount * multiBrickBonus;
            updateScoreboardFlag = true;

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

  maxBrickStrength++;

  if (level > maxLevelReached) {
    maxLevelReached = level;
  }

  ballSpeedMultiplier = 1.0;
  ballDX = ballInitialSpeedX;
  ballDY = ballInitialSpeedY;

  initializeBricks();
  resetPaddleAndBall();
  drawBricks();
  drawPaddle();
  drawBall();
  delay(2000);

  updateScoreboardFlag = true;
}

void resetGame() {
  score = 0;
  misses = 0;
  maxBrickStrength = brickHitRequirement;

  ballSpeedMultiplier = 1.0;
  ballDX = ballInitialSpeedX;
  ballDY = ballInitialSpeedY;

  level = 1;
  initializeBricks();
  resetPaddleAndBall();
  drawBricks();
  drawPaddle();
  drawBall();

  delay(2000);
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
