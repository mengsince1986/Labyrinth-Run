# Labyrinth Run

## Authors
* Meng Zhang
* Sophie Engel

## How to install game Labyrinth Run on UCFK4 board?
1. Install AVR compilation tools(refer to UC ECE Wiki);
2. Connect UCFK4 board to the computer with a compatiable mini-USB cable;
3. Change directory to folder *src*;
4. Start a terminal in current directory and run `make all` to compile the game;
5. In the terminal, run `make program` to install the game onto UCFK4 board.

## What is Labyrinth Run?

You have been stranded, lost in a labyrinth. You need to find your way out and get back to the real world, however, this Labyrinth is laden with deadly traps. To navigate your way out, skillfully avoid the traps and don't walk into any walls... else you may meet your demise!

## How do you play the game?

Labyrinth Run is a multi-stage maze game. The player moves their 'player character', represented by a dot, by using the navswitch. The aim is to complete each stage by navigating through the maze without hitting any walls (including the boundaries of the LED display) and activated traps.

* **Player**: a dot which can move with navswitch.
* **Maze**: formed by lit led lights which are seen as walls.
* **Entrance**: player usually starts at column 3 row 7 (index 2, 6) of the LED matrix.
* **Exit**: located at the opposite side of the entrance, where there's no walls or traps.
* **Traps**: blinking led lights which are lit when activated.
* **Display Orientation**: the navswitch side as bottom, the player begins the game on the left side and moves through the maze to the right.

1. How to win a stage?

Player wins a stage by moving the dot from the maze entrance to the exit. The maze will be automatically updated if the player finishes a stage without failure. When the player finishes all the stages available, there will be a tick symbol shown on the display.

2. How to fail a stage?

Player fails when moving the dot into a maze wall or an activated trap. When the player fails there will be a cross symbol shown on the display.

3. How to reset/restart the game?

Push the pushbutton any time you want to reset/restart the game. Also press the pushbutton to exit out of the tick or cross symbol display.
