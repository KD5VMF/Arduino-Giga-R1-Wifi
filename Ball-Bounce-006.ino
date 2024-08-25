#include <Scheduler.h>
#include <Arduino_GigaDisplay_GFX.h>

GigaDisplay_GFX tft;

#define NUM_BALLS 25
#define BALL_RADIUS 10
#define BALL_SPEED_MIN 1
#define BALL_SPEED_MAX 10

struct Ball {
  int x, y;
  int dx, dy;
  int prevX, prevY;  // Store previous positions for efficient clearing
  uint16_t color;
};

Ball balls[NUM_BALLS];

// Array of 30 bright neon colors
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
  tft.color565(0, 255, 127),   // Neon spring green
  tft.color565(173, 255, 47),  // Neon yellow-green
  tft.color565(75, 0, 130),    // Indigo
  tft.color565(255, 0, 102),   // Neon rose
  tft.color565(240, 230, 140), // Neon khaki
  tft.color565(32, 178, 170),  // Light sea green
  tft.color565(50, 205, 50),   // Neon lawn green
  tft.color565(255, 182, 193), // Neon light pink
  tft.color565(127, 255, 212), // Neon aquamarine
  tft.color565(0, 255, 0),     // Bright neon green
  tft.color565(250, 128, 114), // Neon salmon
  tft.color565(0, 206, 209),   // Neon dark turquoise
  tft.color565(255, 165, 0),   // Neon gold orange
  tft.color565(255, 105, 97),  // Neon light coral
  tft.color565(0, 100, 0),     // Dark green
  tft.color565(255, 215, 0),   // Neon gold
  tft.color565(186, 85, 211),  // Medium orchid
  tft.color565(72, 209, 204),  // Neon turquoise
  tft.color565(255, 99, 71),   // Neon tomato red
  tft.color565(199, 21, 133)   // Neon raspberry
};

void setup() {
  tft.begin();
  tft.fillScreen(tft.color565(0, 0, 0));  // Fill screen with black

  for (int i = 0; i < NUM_BALLS; i++) {
    balls[i].x = random(BALL_RADIUS, tft.width() - BALL_RADIUS);
    balls[i].y = random(BALL_RADIUS, tft.height() - BALL_RADIUS);
    balls[i].dx = random(BALL_SPEED_MIN, BALL_SPEED_MAX);
    balls[i].dy = random(BALL_SPEED_MIN, BALL_SPEED_MAX);
    balls[i].prevX = balls[i].x;
    balls[i].prevY = balls[i].y;
    balls[i].color = neonColors[random(0, sizeof(neonColors) / sizeof(neonColors[0]))];  // Assign random neon color
  }

  // Start tasks
  Scheduler.startLoop(renderTask);  // Render task
  Scheduler.startLoop(moveTask);    // Move task
}

void loop() {
  // The main loop remains empty
}

void moveTask() {
  while (true) {
    for (int i = 0; i < NUM_BALLS; i++) {
      moveBall(balls[i]);
      checkCollision(i);
    }
    delay(10);  // Reduce delay for smoother movement
  }
}

void renderTask() {
  while (true) {
    for (int i = 0; i < NUM_BALLS; i++) {
      // Clear previous ball position
      tft.fillCircle(balls[i].prevX, balls[i].prevY, BALL_RADIUS, tft.color565(0, 0, 0));

      // Draw ball at new position
      tft.fillCircle(balls[i].x, balls[i].y, BALL_RADIUS, balls[i].color);

      // Update previous position
      balls[i].prevX = balls[i].x;
      balls[i].prevY = balls[i].y;
    }

    delay(20);  // Adjust delay for smoother rendering
  }
}

void moveBall(Ball &ball) {
  ball.x += ball.dx;
  ball.y += ball.dy;

  // Correct ball position if it exceeds bounds to prevent it from getting stuck
  if (ball.x < BALL_RADIUS) {
    ball.x = BALL_RADIUS;
    ball.dx = -ball.dx;
  } else if (ball.x > tft.width() - BALL_RADIUS) {
    ball.x = tft.width() - BALL_RADIUS;
    ball.dx = -ball.dx;
  }

  if (ball.y < BALL_RADIUS) {
    ball.y = BALL_RADIUS;
    ball.dy = -ball.dy;
  } else if (ball.y > tft.height() - BALL_RADIUS) {
    ball.y = tft.height() - BALL_RADIUS;
    ball.dy = -ball.dy;
  }
}

void checkCollision(int index) {
  for (int i = 0; i < NUM_BALLS; i++) {
    if (i != index) {
      int dx = balls[index].x - balls[i].x;
      int dy = balls[index].y - balls[i].y;
      int distance = sqrt(dx * dx + dy * dy);

      if (distance < 2 * BALL_RADIUS) {
        // Swap velocities for simple collision
        int tempDx = balls[index].dx;
        int tempDy = balls[index].dy;
        balls[index].dx = balls[i].dx;
        balls[index].dy = balls[i].dy;
        balls[i].dx = tempDx;
        balls[i].dy = tempDy;

        // Bounce back a little after collision to prevent sticking
        balls[index].x += balls[index].dx;
        balls[index].y += balls[index].dy;
        balls[i].x += balls[i].dx;
        balls[i].y += balls[i].dy;
      }
    }
  }
}
