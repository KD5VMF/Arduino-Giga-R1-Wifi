#include <Scheduler.h>
#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

// Constants for the screen and game components
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define SCOREBOARD_WIDTH 150  // Width for cartoon style
#define MAX_LEVEL 100

// Scoring and game variables (for easy tuning)
int pointsPerRowCleared = 1;        
int pointsPerBrickHit = 1;          
int multiBrickBonus = 2;            
int missPenalty = 125;               
int pointsToLose = 0;               

// Gravity and physics variables
float gravity = 0.1;               
float gravityMaxSpeed = 10;         

// Shared variables for communication between M7 and M4 cores
volatile int score = 0;
volatile int misses = 0;
volatile int level = 1;
volatile int maxLevelReached = 1;   
volatile bool updateScoreboardFlag = false;  
volatile bool graphicsReady = false;  // Flag for initial rendering completion

// Customizable Variables
int ballInitialSpeedX = 5;
int ballInitialSpeedY = -5;
int ballSize = 10;
int initialPlayerAccuracy = 3;
int initialPlayerIntelligence = 2;
int initialPaddleSpeed = 14;
int paddleWidth = 100;
int brickHitRequirement = 1;

// Dynamic Ball Speed Adjustments
float ballSpeedMultiplier = 1.0;
float ballSpeedIncrement = 0.1;
float ballSpeedDecrement = 0.05;
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
#define BRICK_ROWS 4
#define BRICK_COLUMNS 5
#define BRICK_WIDTH 115
#define BRICK_HEIGHT 50
#define BRICK_SPACING 7
int brickStrength[BRICK_ROWS][BRICK_COLUMNS];
uint16_t brickColors[BRICK_ROWS][BRICK_COLUMNS];
int maxBrickStrength = brickHitRequirement;

// Loop detection properties
float previousBallDX[3] = {0, 0, 0};
float previousBallDY[3] = {0, 0, 0};
int loopCount = 0;

// Neon colors for bricks - Expanded to 35 colors
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
    // Additional neon colors
    tft.color565(127, 255, 212), // Aquamarine
    tft.color565(0, 255, 127),   // Spring green
    tft.color565(255, 215, 0),   // Gold
    tft.color565(173, 216, 230), // Light blue
    tft.color565(250, 128, 114), // Salmon
    tft.color565(255, 160, 122), // Light salmon
    tft.color565(32, 178, 170),  // Light sea green
    tft.color565(240, 230, 140), // Khaki
    tft.color565(152, 251, 152), // Pale green
    tft.color565(144, 238, 144), // Light green
    tft.color565(0, 255, 127),   // Spring Green
    tft.color565(135, 206, 250), // Light sky blue
    tft.color565(135, 206, 235), // Sky blue
    tft.color565(173, 216, 230), // Light blue
    tft.color565(240, 128, 128), // Light coral
    tft.color565(255, 218, 185), // Peach puff
    tft.color565(189, 183, 107), // Dark khaki
    tft.color565(238, 232, 170), // Pale goldenrod
    tft.color565(250, 250, 210), // Light goldenrod yellow
    tft.color565(245, 245, 220), // Beige
    tft.color565(255, 245, 238), // Seashell
    tft.color565(255, 222, 173), // Navajo white
    tft.color565(253, 245, 230)  // Old lace
};

// Multi-hit combo tracking
int multiHitCount = 0;  // <<<<<<<<<<<<<<<<<<<< This variable is now declared

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

  // Initialize game - make sure max level is only set once at start
  if (maxLevelReached == 1) {
    maxLevelReached = 1;  // Only reset at first setup
  }

  // Draw the static scoreboard layout
  drawScoreboardLayout();

  // Initialize game
  initializeBricks();
  drawBricks();
  drawPaddle();
  drawBall();

  graphicsReady = true;  // Indicate that the initial graphics have been drawn

  // Start tasks on cores
  Scheduler.startLoop(core1Task);  
  Scheduler.startLoop(core2Task);  
  Scheduler.startLoop(coreM4Task);  
}

void loop() {
  // Main loop remains empty because tasks are assigned to cores
}

void core1Task() {
  // Rendering loop (Core 1) for game graphics (excluding scoreboard)
  while (true) {
    if (graphicsReady) {  // Wait for graphics to be ready
      updateDisplay();
    }
    delay(1);  
  }
}

void core2Task() {
  // Game logic loop (Core 2)
  while (true) {
    if (graphicsReady) {  // Ensure game logic doesn't start until graphics are ready
      moveBall();
      checkCollisions();
      updatePaddleAI();
      checkLevelProgression();
    }
    delay(1);  
  }
}

void coreM4Task() {
  // Scoreboard update loop on M4 core
  while (true) {
    if (updateScoreboardFlag) {
      updateScoreboard();  
      updateScoreboardFlag = false;  
    }
    delay(20);  
  }
}

void drawScoreboardLayout() {
  // Draw a cartoon-style scoreboard with a blue background and rounded edges
  tft.fillRoundRect(0, 0, SCOREBOARD_WIDTH, SCREEN_HEIGHT, 15, scoreboardBackgroundColor);

  tft.setTextColor(scoreboardTextColor);
  tft.setTextSize(2);  

  // Labels
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
  // Only update the score, misses, level, and max level values without clearing the entire scoreboard
  tft.setTextColor(scoreColor);
  tft.setTextSize(3);  

  // Draw score
  tft.fillRect(10, 60, SCOREBOARD_WIDTH - 20, 50, scoreboardBackgroundColor);  
  tft.setCursor(10, 60);
  tft.print(score);

  // Draw misses
  tft.setTextColor(missesColor);
  tft.fillRect(10, 160, SCOREBOARD_WIDTH - 20, 50, scoreboardBackgroundColor);  
  tft.setCursor(10, 160);
  tft.print(misses);

  // Draw level
  tft.setTextColor(levelColor);
  tft.fillRect(10, 260, SCOREBOARD_WIDTH - 20, 50, scoreboardBackgroundColor);  
  tft.setCursor(10, 260);
  tft.print(level);

  // Draw highest level reached
  tft.setTextColor(tft.color565(255, 215, 0));  
  tft.setTextSize(3);  
  tft.fillRect(10, 360, SCOREBOARD_WIDTH - 20, 50, scoreboardBackgroundColor);  
  tft.setCursor(10, 360);
  tft.print(maxLevelReached);
}

void initializeBricks() {
  // Initialize bricks with random neon colors and increasing toughness
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      brickStrength[row][col] = maxBrickStrength;
      brickColors[row][col] = neonColors[random(0, sizeof(neonColors) / sizeof(neonColors[0]))];  
    }
  }
}

void drawBricks() {
  // Redraw all bricks without clearing the entire screen
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      if (brickStrength[row][col] > 0) {
        int x = SCOREBOARD_WIDTH + col * (BRICK_WIDTH + BRICK_SPACING);
        int y = row * (BRICK_HEIGHT + BRICK_SPACING) + 50;

        // Redraw the brick only if it is present
        tft.fillRoundRect(x, y, BRICK_WIDTH, BRICK_HEIGHT, 10, brickColors[row][col]);
      }
    }
  }
}

void drawPaddle() {
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

  // Gravity effect
  ballDY += gravity;
  if (ballDY > gravityMaxSpeed) {
    ballDY = gravityMaxSpeed;  
  }

  // Track ball direction history
  previousBallDX[loopCount % 3] = ballDX;
  previousBallDY[loopCount % 3] = ballDY;

  // Detect repetitive movement pattern
  if (loopCount >= 3 && 
      previousBallDX[0] == previousBallDX[1] && 
      previousBallDX[1] == previousBallDX[2] &&
      previousBallDY[0] == previousBallDY[1] &&
      previousBallDY[1] == previousBallDY[2]) {
      
      // Apply a small random nudge to the ball's direction to break the loop
      ballDX += random(-1, 2) * 0.1;
      ballDY += random(-1, 2) * 0.1;
  }

  loopCount++;

  // Update ball position based on dynamic speed and gravity
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

  // Ball out of bounds (missed paddle)
  if (ballY >= SCREEN_HEIGHT) {
    misses++;  

    score -= missPenalty;
    if (score < pointsToLose) score = pointsToLose;  

    if (score == pointsToLose) {
      gameOver();  
    } else {
      resetBall();  
    }

    updateScoreboardFlag = true;  

    multiHitCount = 0;
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
  // Ball and paddle collision
  if (ballY + ballSize / 2 >= PADDLE_Y_POSITION && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
    ballDY = -ballDY;
    increaseBallSpeed();
    multiHitCount = 0;  
  }

  // Ball and brick collision (Solid Bricks)
  for (int row = 0; row < BRICK_ROWS; row++) {
    for (int col = 0; col < BRICK_COLUMNS; col++) {
      if (brickStrength[row][col] > 0) {
        int brickX = SCOREBOARD_WIDTH + col * (BRICK_WIDTH + BRICK_SPACING);
        int brickY = row * (BRICK_HEIGHT + BRICK_SPACING) + 50;

        if (ballX + ballSize / 2 >= brickX && ballX - ballSize / 2 <= brickX + BRICK_WIDTH &&
            ballY + ballSize / 2 >= brickY && ballY - ballSize / 2 <= brickY + BRICK_HEIGHT) {
          
          // Solid brick collision logic
          if (abs(ballX - (brickX + BRICK_WIDTH / 2)) > abs(ballY - (brickY + BRICK_HEIGHT / 2))) {
            ballDX = -ballDX;  // Reflect horizontally
          } else {
            ballDY = -ballDY;  // Reflect vertically
          }

          brickStrength[row][col] -= 1;
          if (brickStrength[row][col] <= 0) {
            tft.fillRoundRect(brickX, brickY, BRICK_WIDTH, BRICK_HEIGHT, 10, backgroundColor);  // Clear the brick

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

  ballDX += (ballDX > 0) ? 0.5 : -0.5;  
  ballDY += (ballDY > 0) ? 0.5 : -0.5;
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

void gameOver() {
  tft.fillScreen(backgroundColor);  
  tft.setTextSize(4);  
  tft.setTextColor(tft.color565(255, 0, 0));  
  tft.setCursor(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 30);
  tft.print("GAME OVER");

  delay(2000);

  resetGame();
}

void extractRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
  r = (color >> 11) & 0x1F; 
  g = (color >> 5) & 0x3F;  
  b = color & 0x1F;         

  r = (r * 255) / 31;
  g = (g * 255) / 63;
  b = (b * 255) / 31;
}
