Self-Playing Game for Arduino GIGA R1 WiFi with GIGA Display Shield
Overview
This project is a self-playing game built for the Arduino GIGA R1 WiFi and the GIGA Display Shield. The game mimics classic brick breaker-style gameplay,
featuring paddle AI and advanced game physics. It includes multiple difficulty levels, dynamic paddle movement, randomized brick colors,
and persistent tracking of the highest level reached.

The game leverages the dual-core processing capability of the Arduino GIGA R1 WiFi for concurrent rendering and game logic,
with an additional core dedicated to updating the scoreboard. The project aims to demonstrate complex game development on embedded systems with minimal latency and smooth graphics.

Features
Self-Playing AI: The paddle automatically follows the ball, with AI logic that simulates human-like behavior and intelligent shot targeting.
Persistent High Score Tracking: The game tracks the highest level reached, and this value is stored persistently across games without resetting unless the device is restarted.
Multi-core Processing: Utilizes both cores of the Arduino GIGA R1 WiFi to handle game physics, rendering, and scoreboard updates independently, ensuring smooth performance.
Customizable Gameplay: Adjustable gravity, ball speed, paddle behavior, and scoring allow for easy tuning and scaling of the difficulty.
Arcade-style Graphics: Neon-colored bricks and an arcade-style scoreboard enhance the visual appeal. The game displays level transitions and game-over screens in a classic arcade fashion.
Hardware Used
Arduino GIGA R1 WiFi: The brain of the operation, handling multi-core tasks and controlling the game logic, rendering, and hardware communication.
GIGA Display Shield: An 800x480 TFT display provides a bright, colorful output for the game. This shield allows for complex animations, smooth transitions, and vibrant colors.
TFT Display: The GIGA Display is responsible for showing game elements, including bricks, paddle, ball, and scoreboard. Custom graphics functions are used to draw each element on the display.
Code Structure
The program leverages Scheduler.h to manage the multi-core capabilities of the Arduino GIGA R1 WiFi. Here’s a breakdown of the main components:

Core 1 (M7) – Rendering Task
Handles the visual updates for the game, including drawing the ball, paddle, bricks, and all other game objects.
This core ensures smooth rendering by minimizing screen refreshes, only redrawing the elements that need updates.

Core 2 (M7) – Game Logic Task
This core manages the game physics, including ball movement, collision detection, paddle AI, and scoring.
It ensures that the game logic is computed in real-time, adjusting ball speed, applying gravity, and managing brick states.

Core M4 – Scoreboard Update Task
Dedicated solely to updating the scoreboard values such as the current score, number of misses, current level, and the highest level reached.
The scoreboard is updated without interrupting the main gameplay, providing real-time feedback to the player.

Persistent Data
A unique feature of the game is the persistent high score tracking. The highest level reached (maxLevelReached) remains stored in memory across game sessions.
This value will only reset when the device is powered off, giving the player a sense of long-term progression.

Usage
Connect the Arduino GIGA R1 WiFi to your GIGA Display Shield.
Upload the code to the Arduino via the Arduino IDE.
Watch as the AI plays the game automatically, progressing through increasingly difficult levels.
The game will display the current score, misses, level, and the highest level reached on the scoreboard.
The highest level reached persists even after the game resets, as long as the device remains powered on.
Contributing
Feel free to contribute to this project by submitting pull requests or opening issues.

Acknowledgements
[Your Name]: Project creator and code implementation.
ChatGPT (OpenAI): Assisted in developing advanced features, including persistent data tracking, multi-core utilization,
and graphical optimizations.
