Breakout-009
Overview
Breakout-009 is a modern adaptation of the classic arcade game Breakout, built for Arduino GigaDisplay with multiple levels of difficulty, smooth gameplay mechanics, and intuitive controls. Players control a paddle to bounce a ball and destroy a series of bricks. As players progress through levels, the game's difficulty gradually increases by adjusting ball speed and brick durability. The goal is to clear all the bricks on each level while avoiding missing the ball with the paddle.

Features
Multiple Levels: Breakout-009 includes up to 100 levels, with gradually increasing difficulty.
Paddle and Ball Dynamics: Smooth and responsive paddle movement and physics-based ball behavior.
Dynamic Difficulty Scaling: Ball speed and brick durability increase incrementally as you progress, providing a consistent challenge.
Score Tracking: Keeps track of the player's score and the maximum level reached.
Game Over and Restart: Automatically resets the game after a loss, retaining the highest level reached during the session.
Gameplay Mechanics
Ball Movement: The ball moves based on physics with adjustable speed and gravity. The ball's vertical motion ("up power") is automatically adjusted if the ball gets stuck in horizontal bounces.
Paddle Control: The paddle is AI-controlled and can also be moved using game logic. It clears and redraws itself smoothly to prevent any visual artifacts or ghosting.
Bricks: The game features multiple rows of bricks, each with varying colors and durability. The durability increases as the player progresses through levels.
Scoring: Players earn points for breaking bricks and clearing rows. Bonus points are awarded for combos and multi-brick hits.
Hardware Requirements
Arduino GigaDisplay: This game is optimized for the Arduino GigaDisplay, using the GigaDisplay_GFX library for rendering graphics.

Installation
Clone the repository:
git clone https://github.com/yourusername/Breakout-009.git
cd Breakout-009


Set up Arduino:

Ensure you have the necessary Arduino libraries installed:
Arduino_GigaDisplay_GFX
Scheduler
Ensure your hardware is properly connected (Arduino GigaDisplay).
Upload the Game:

Open the .ino file in the Arduino IDE.
Connect your Arduino board.
Upload the code to your board.
Gameplay Instructions
Objective: Use the paddle to bounce the ball and break all the bricks on the screen. Clear the level by destroying all bricks while avoiding the ball falling past the paddle.

Scoring:

Breaking a brick earns points.
Clearing a row gives bonus points.
Combos (hitting multiple bricks consecutively) grant additional points.
Progression: The game gets harder as you advance. Ball speed increases slightly with each level, and bricks become tougher to break. The game will reset upon losing all lives, but it will retain the maximum level reached during that session.

Game Over: When the player misses the ball, the game will display a "Game Over" message, wait for a few seconds, and then restart the game, retaining the maximum level achieved. All game parameters will reset as if starting fresh.

Code Structure
setup(): Initializes the game components, setting up the paddle, ball, bricks, and scoreboard.

loop(): The main loop is managed by Scheduler, delegating tasks to multiple cores for smooth gameplay and rendering.

moveBall(): Handles ball physics, gravity, wall collisions, and interaction with the paddle. The ball's vertical speed is adjusted when it becomes too low to ensure consistent upward motion.

checkCollisions(): Checks for collisions between the ball and bricks or paddle, reflecting the ball accordingly and reducing brick strength.

nextLevel(): Advances the game to the next level by resetting the bricks, paddle, and ball while increasing difficulty.

resetGame(): Resets all game variables to their initial states (except maxLevelReached) for a fresh start after Game Over.

Troubleshooting
Ball Gets Stuck Bouncing Horizontally: The game automatically adjusts the ball’s vertical speed if it gets stuck bouncing without enough upward momentum.

Game Not Restarting Properly: Ensure that all relevant variables are being reset during the resetGame() function. Check for any uninitialized variables.

Ghosting of Paddle: The paddle clears itself before moving to its new position, preventing ghosting or leaving visual artifacts behind.

License
This project is licensed under the MIT License. See the LICENSE file for details.

