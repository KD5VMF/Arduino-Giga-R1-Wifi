#include <Arduino_GigaDisplay_GFX.h>
#include <Scheduler.h>

// Constants for display
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define BLOCK_SIZE 4  // Each sprite block will be 4x4 pixels

// Display object
GigaDisplay_GFX tft;

// Define three 8x8 alien sprites with distinct shapes and colors
const uint8_t alienSprite1[8][8] = {
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 2, 2, 2, 2, 1, 0},
  {1, 2, 3, 3, 3, 3, 2, 1},
  {1, 2, 3, 3, 3, 3, 2, 1},
  {1, 2, 2, 2, 2, 2, 2, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0}
};

const uint8_t alienSprite2[8][8] = {
  {0, 1, 1, 1, 1, 1, 1, 0},
  {1, 2, 2, 2, 2, 2, 2, 1},
  {2, 3, 3, 3, 3, 3, 3, 2},
  {2, 3, 0, 3, 3, 0, 3, 2},
  {2, 3, 3, 3, 3, 3, 3, 2},
  {1, 2, 3, 2, 2, 3, 2, 1},
  {0, 1, 2, 1, 1, 2, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0}
};

const uint8_t alienSprite3[8][8] = {
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 1, 1, 2, 2, 1, 1, 0},
  {1, 2, 2, 3, 3, 2, 2, 1},
  {1, 2, 3, 3, 3, 3, 2, 1},
  {1, 3, 3, 3, 3, 3, 3, 1},
  {1, 3, 3, 1, 1, 3, 3, 1},
  {0, 1, 3, 3, 3, 3, 1, 0},
  {0, 0, 1, 3, 3, 1, 0, 0}
};

// Helper function to map sprite values to colors
uint16_t getColorFromValue(uint8_t value, uint8_t alienType) {
  switch (value) {
    case 1: return tft.color565(255, 0, 0);   // Red for Alien 1
    case 2: 
      if (alienType == 1) return tft.color565(0, 255, 0);  // Green for Alien 1
      if (alienType == 2) return tft.color565(0, 0, 255);  // Blue for Alien 2
      if (alienType == 3) return tft.color565(255, 255, 0);  // Yellow for Alien 3
    case 3: 
      if (alienType == 2) return tft.color565(255, 255, 255);  // White for Alien 2
      if (alienType == 3) return tft.color565(255, 0, 255);    // Magenta for Alien 3
    default: return tft.color565(0, 0, 0);    // Black background
  }
}

// Draw an alien sprite on the screen using solid blocks instead of single pixels
void drawAlienSprite(int posX, int posY, const uint8_t sprite[8][8], uint8_t alienType) {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      uint8_t value = sprite[y][x];
      uint16_t color = getColorFromValue(value, alienType);
      // Draw a solid block for each sprite pixel
      tft.fillRect(posX + x * BLOCK_SIZE, posY + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, color);
    }
  }
}

void setup() {
  // Initialize display
  tft.begin();
  tft.setRotation(3);  // Adjust to screen orientation
  tft.fillScreen(tft.color565(0, 0, 0));  // Black background

  // Draw three alien sprites at specified positions
  drawAlienSprite(100, 100, alienSprite1, 1);  // Draw the red-green alien
  drawAlienSprite(200, 100, alienSprite2, 2);  // Draw the blue-white alien
  drawAlienSprite(300, 100, alienSprite3, 3);  // Draw the yellow-magenta alien
}

void loop() {
  // No need to redraw, static sprites for now
  delay(1000);  // Delay to slow down the loop
}
