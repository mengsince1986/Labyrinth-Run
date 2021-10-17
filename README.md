# UC 2021 ENCE260 Project

## Group 112
* Sophie Engel
* Meng Zhang

## How to install game MAZE112 on UCFK4 board?
1. Install AVR compilation tools on the computer (refer to UC ECE Wiki);
2. Connect UCFK4 board to the computer with a compatiable mini-USB cable;
3. Change directory to "group_112";
4. Start a terminal in current directory and run `make all` to compile the game;
5. In the terminal, run `make program` to install the game onto UCFK4 board.

## How to play game MAZE112?

MAZE112 is a multi-stage maze game. Player moves a dot by navswitch and tries to go through each maze without hitting the walls (including the boundaries of the LED display) and activated traps.

**Player**: a dot which can move with navswitch.
**Maze**: formed by lit led lights which are seen as walls.
**Entrance**: player usually starts at column 3 row 7 of the LED matrix.
**Exit**: located at the opposite side of the entrance, where there's no walls or traps.
**Traps**: blinking led lights which are activated when lit.
**Display Orientation**: the navswitch side as bottom.

* How to win a stage?
Player wins a stage by moving the dot from the maze entrance to the exit. The maze will be automatically updated if the player finishes a stage without failure. When the player finishes all the stages available, there will be a check shown on the display.

* How to fail a stage?
Player fails when moving the dot into a maze wall or an activated trap. When the player fails there will be a cross shown on the display.

* How to reset/restart the game?
Push the pushbutton any time you want to reset/restart the game.
