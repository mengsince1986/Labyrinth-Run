/** @file maze_display.c
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief maze display module header
 */

#ifndef MAZE_DISPLAY_H
#define MAZE_DISPLAY_H

#include "system.h"


// Maze stage identifier type
typedef enum {STAGE_1 = 1, STAGE_2} StageIndex_t;


/** Maze stage struct type
 *  Configuration note:
 * 1. column index is 0-4; row index is 0-6
 * 2. maze_pattern = {0b-row7-row6-row5-row4-row3-row2-row1, ..., ...}
 * 3. start_loc = {row_index, col_index}
 * 4. pass_loc = {row_index, col_index}
 */
typedef struct
{
    uint8_t maze_pattern[5];
    uint8_t start_loc[2];
    uint8_t pass_loc[2];
} MazeStage_t;


// Maze display initialiser
void mazeDisplay_init (void);


/** Current maze stage setter
 * @parameter stage_index
 */
void maze_setStage (StageIndex_t stage_index);


// Display current maze pattern
void maze_display (void);


/** Current maze dot state getter
 * @parameter row_index, col_index
 * @return true(on)/false(off)
 */
bool maze_dotState (uint8_t row_index, uint8_t col_index);


/** Current maze dot updater
 * @parameter row_index, col_index
 */
void maze_updateDot (uint8_t row_index, uint8_t col_index);


#endif // MAZE_DISPLAY_H
