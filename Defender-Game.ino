#include <Scheduler.h>
#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

// Constants for 800x480 screen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 15
#define BULLET_WIDTH 5
#define BULLET_HEIGHT 5

#define ENEMY_WIDTH 25
#define ENEMY_HEIGHT 25
#define TERRAIN_HEIGHT 100

#define MAX_BULLETS 10
#define MAX_ENEMIES_PER_LEVEL 10
#define MAX_GROUND_ENEMIES 3
#define NUM_FAST_ENEMIES 3

#define INITIAL_LIVES 3
#define INITIAL_ENEMY_SPEED -3
#define MAX_LEVELS 100

// Structs for Player, Enemies, and Bullets
struct GameObject {
  int x, y;
  int width, height;
  int dx, dy;
  bool isAlive;
};

struct Bullet {
  int x, y;
  int dx;
  bool isFired;
};

GameObject player;
Bullet playerBullets[MAX_BULLETS];

GameObject enemies[MAX_ENEMIES_PER_LEVEL];  // Regular enemies
GameObject groundEnemies[MAX_GROUND_ENEMIES]; // Ground enemies
GameObject fastEnemies[NUM_FAST_ENEMIES];   // Fast enemies

int terrainOffset = 0;
int terrainSpeed = 2;
int playerLives = INITIAL_LIVES;
int score = 0;
int currentLevel = 1;
bool gameOver = false;
bool movingUp = true;
int enemySpeed = INITIAL_ENEMY_SPEED;
int enemiesToSpawn = MAX_ENEMIES_PER_LEVEL;

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(tft.color565(0, 0, 0));

  // Initialize Player
  player.x = 50;
  player.y = SCREEN_HEIGHT / 2;
  player.width = PLAYER_WIDTH;
  player.height = PLAYER_HEIGHT;
  player.dy = 3;
  player.isAlive = true;

  // Initialize Enemies
  initializeEnemies();

  // Start rendering and physics tasks
  Scheduler.startLoop(renderTask);
  Scheduler.startLoop(physicsTask);
}

void loop() {
  // Empty loop, required by Arduino framework
}

void initializeEnemies() {
  // Initialize airborne enemies
  for (int i = 0; i < MAX_ENEMIES_PER_LEVEL; i++) {
    enemies[i].x = random(SCREEN_WIDTH, SCREEN_WIDTH + 300);
    enemies[i].y = random(50, SCREEN_HEIGHT - 200);
    enemies[i].width = ENEMY_WIDTH;
    enemies[i].height = ENEMY_HEIGHT;
    enemies[i].dx = enemySpeed;
    enemies[i].isAlive = true;
  }

  // Initialize ground enemies
  for (int i = 0; i < MAX_GROUND_ENEMIES; i++) {
    groundEnemies[i].x = random(SCREEN_WIDTH, SCREEN_WIDTH + 400);
    groundEnemies[i].y = SCREEN_HEIGHT - TERRAIN_HEIGHT - ENEMY_HEIGHT;
    groundEnemies[i].width = ENEMY_WIDTH;
    groundEnemies[i].height = ENEMY_HEIGHT;
    groundEnemies[i].dx = enemySpeed - 1;
    groundEnemies[i].isAlive = true;
  }

  // Initialize fast enemies
  for (int i = 0; i < NUM_FAST_ENEMIES; i++) {
    fastEnemies[i].x = random(SCREEN_WIDTH, SCREEN_WIDTH + 400);
    fastEnemies[i].y = random(50, SCREEN_HEIGHT - 200);
    fastEnemies[i].width = ENEMY_WIDTH;
    fastEnemies[i].height = ENEMY_HEIGHT;
    fastEnemies[i].dx = enemySpeed - 4;
    fastEnemies[i].isAlive = true;
  }
}

void renderTask() {
  while (true) {
    if (!gameOver) {
      tft.fillScreen(tft.color565(0, 0, 0));
      
      // Draw Terrain
      drawTerrain();

      // Draw Player Ship
      if (player.isAlive) {
        tft.fillRect(player.x, player.y, player.width, player.height, tft.color565(0, 0, 255));
      }

      // Draw Enemies
      drawEnemies(enemies, MAX_ENEMIES_PER_LEVEL, tft.color565(255, 0, 0));
      drawEnemies(groundEnemies, MAX_GROUND_ENEMIES, tft.color565(0, 255, 0));
      drawEnemies(fastEnemies, NUM_FAST_ENEMIES, tft.color565(255, 255, 0));

      // Draw Bullets
      for (int i = 0; i < MAX_BULLETS; i++) {
        if (playerBullets[i].isFired) {
          tft.fillRect(playerBullets[i].x, playerBullets[i].y, BULLET_WIDTH, BULLET_HEIGHT, tft.color565(255, 255, 255));
        }
      }

      // Draw UI
      drawUI();

      delay(50);
    } else {
      showGameOverScreen();
    }
  }
}

void drawTerrain() {
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    int terrainY = SCREEN_HEIGHT - TERRAIN_HEIGHT + (int)(50 * sin((i + terrainOffset) * 0.02));
    tft.drawLine(i, terrainY, i, SCREEN_HEIGHT, tft.color565(139, 69, 19));
  }
  terrainOffset += terrainSpeed;
}

void drawUI() {
  tft.setCursor(10, 10);
  tft.setTextColor(tft.color565(255, 255, 255));
  tft.setTextSize(2);
  tft.print("Lives: ");
  tft.print(playerLives);
  tft.setCursor(200, 10);
  tft.print("Score: ");
  tft.print(score);
  tft.setCursor(400, 10);
  tft.print("Level: ");
  tft.print(currentLevel);
}

void showGameOverScreen() {
  tft.fillScreen(tft.color565(0, 0, 0));
  tft.setCursor(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2);
  tft.setTextColor(tft.color565(255, 0, 0));
  tft.setTextSize(3);
  tft.print("GAME OVER!");
  delay(3000);
  // Reset the game
  restartGame();
}

void restartGame() {
  score = 0;
  playerLives = INITIAL_LIVES;
  currentLevel = 1;
  enemySpeed = INITIAL_ENEMY_SPEED;
  enemiesToSpawn = MAX_ENEMIES_PER_LEVEL;
  initializeEnemies();
  player.isAlive = true;
  gameOver = false;
}

void physicsTask() {
  while (true) {
    if (!gameOver) {
      // Handle Player Movement (Vertical only)
      if (player.isAlive) {
        // Move the player up or down based on current direction
        if (movingUp) {
          player.y -= player.dy;
          if (player.y <= 0) {
            player.y = 0;
            movingUp = false;
          }
        } else {
          player.y += player.dy;
          if (player.y >= SCREEN_HEIGHT - player.height) {
            player.y = SCREEN_HEIGHT - player.height;
            movingUp = true;
          }
        }

        // Simulate player shooting
        firePlayerBullet();
      }

      // Handle Bullet Movement
      updateBullets();

      // Move Enemies and Check for Collisions
      updateEnemies();

      checkCollisions();

      delay(20);
    }
  }
}

void firePlayerBullet() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!playerBullets[i].isFired) {
      playerBullets[i].x = player.x + player.width;
      playerBullets[i].y = player.y + player.height / 2;
      playerBullets[i].dx = 6;
      playerBullets[i].isFired = true;
      break;
    }
  }
}

void updateBullets() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (playerBullets[i].isFired) {
      playerBullets[i].x += playerBullets[i].dx;
      if (playerBullets[i].x > SCREEN_WIDTH) {
        playerBullets[i].isFired = false;
      }
    }
  }
}

void updateEnemies() {
  moveEnemies(enemies, MAX_ENEMIES_PER_LEVEL);
  moveEnemies(groundEnemies, MAX_GROUND_ENEMIES);
  moveEnemies(fastEnemies, NUM_FAST_ENEMIES);

  if (checkAllEnemiesDefeated()) {
    nextLevel();
  }
}

void moveEnemies(GameObject enemyArray[], int numEnemies) {
  for (int i = 0; i < numEnemies; i++) {
    if (enemyArray[i].isAlive) {
      enemyArray[i].x += enemyArray[i].dx;
      if (enemyArray[i].x < -ENEMY_WIDTH) {
        enemyArray[i].x = random(SCREEN_WIDTH, SCREEN_WIDTH + 300);
        enemyArray[i].y = random(50, SCREEN_HEIGHT - 200);
      }
    }
  }
}

void drawEnemies(GameObject enemyArray[], int numEnemies, uint16_t color) {
  for (int i = 0; i < numEnemies; i++) {
    if (enemyArray[i].isAlive) {
      tft.fillRect(enemyArray[i].x, enemyArray[i].y, enemyArray[i].width, enemyArray[i].height, color);
    }
  }
}

bool checkAllEnemiesDefeated() {
  for (int i = 0; i < MAX_ENEMIES_PER_LEVEL; i++) {
    if (enemies[i].isAlive) {
      return false;
    }
  }

  for (int i = 0; i < MAX_GROUND_ENEMIES; i++) {
    if (groundEnemies[i].isAlive) {
      return false;
    }
  }

  for (int i = 0; i < NUM_FAST_ENEMIES; i++) {
    if (fastEnemies[i].isAlive) {
      return false;
    }
  }

  return true;
}

void nextLevel() {
  currentLevel++;
  score += 100;
  enemySpeed -= 1;
  enemiesToSpawn = MAX_ENEMIES_PER_LEVEL + (currentLevel / 10);  // Scale the number of enemies

  if (currentLevel > MAX_LEVELS) {
    currentLevel = 1;  // Reset levels after 100
  }

  initializeEnemies();
}

void checkCollisions() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (playerBullets[i].isFired) {
      checkBulletCollisionsWithEnemies(playerBullets[i], enemies, MAX_ENEMIES_PER_LEVEL, 10);
      checkBulletCollisionsWithEnemies(playerBullets[i], groundEnemies, MAX_GROUND_ENEMIES, 20);
      checkBulletCollisionsWithEnemies(playerBullets[i], fastEnemies, NUM_FAST_ENEMIES, 30);
    }
  }

  checkPlayerCollisionsWithEnemies(enemies, MAX_ENEMIES_PER_LEVEL);
  checkPlayerCollisionsWithEnemies(groundEnemies, MAX_GROUND_ENEMIES);
  checkPlayerCollisionsWithEnemies(fastEnemies, NUM_FAST_ENEMIES);
}

void checkBulletCollisionsWithEnemies(Bullet &bullet, GameObject enemyArray[], int numEnemies, int scoreValue) {
  for (int i = 0; i < numEnemies; i++) {
    if (enemyArray[i].isAlive && checkCollision(bullet, enemyArray[i])) {
      enemyArray[i].isAlive = false;
      bullet.isFired = false;
      score += scoreValue;
    }
  }
}

void checkPlayerCollisionsWithEnemies(GameObject enemyArray[], int numEnemies) {
  for (int i = 0; i < numEnemies; i++) {
    if (enemyArray[i].isAlive && checkCollision(player, enemyArray[i])) {
      playerDies();
    }
  }
}

bool checkCollision(Bullet bullet, GameObject object) {
  return (bullet.x > object.x && bullet.x < object.x + object.width &&
          bullet.y > object.y && bullet.y < object.y + object.height);
}

bool checkCollision(GameObject obj1, GameObject obj2) {
  return (obj1.x < obj2.x + obj2.width && obj1.x + obj1.width > obj2.x &&
          obj1.y < obj2.y + obj2.height && obj1.y + obj1.height > obj2.y);
}

void playerDies() {
  playerLives--;
  if (playerLives <= 0) {
    player.isAlive = false;
    gameOver = true;
  } else {
    player.y = SCREEN_HEIGHT / 2;
  }
}
