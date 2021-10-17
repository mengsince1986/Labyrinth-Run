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

#define TRAPS_NUM 7
#define LOC_DIMENSION 2


/**Maze stage identifier type
 * Always add new stage to enum
 */
typedef enum {STAGE_1 = 1, STAGE_2, STAGE_3, STAGE_4, STAGE_5, FAIL_SYMBOL, WIN_SYMBOL} StageIndex_t;


/**
 * Set stage patterns
 * Configuration note:
 * 1. column index is 0-4; row index is 0-6
 * 2. maze_pattern = {0b-row7-row6-row5-row4-row3-row2-row1, ..., ...}
 * 3. trap_locs = {{col, row}, {col, row}, ...}
 *    - to disable a trap, set it's loc to {DISABLE_LOC, DISABLE_LOC}
 *    - to make two sets of traps flash alternatively, initialise one set of
 *      traps on and the other set of traps off in the maze_pattern
 * 4. trapTick_max: set the frequency of traps, the lower the value the higher
 *                  the frequency
 */

typedef struct
{
    StageIndex_t stage_name;
    uint8_t maze_pattern[LEDMAT_COLS_NUM];
    uint8_t playerStart_col;
    uint8_t playerStart_row;
    uint8_t playerFinish_col;
    uint8_t playerFinish_row;
    uint8_t trap_locs[TRAPS_NUM][LOC_DIMENSION];
    uint16_t trapTick_max;
} MazeStage_t;


typedef struct {
    uint8_t locs[TRAPS_NUM][LOC_DIMENSION];
} ActiveTrap_locs_t;


// Maze display initialiser
void mazeDisplay_init (void);


// Maze stage patterns initialiser
void mazePatterns_init (void);


/** Current maze stage setter
 * @parameter stage_index
 */
void maze_setStage (StageIndex_t stage_index);


// Display current maze pattern
void maze_display (void);


/** Current maze LED dot state getter
 * @parameter row_index, col_index
 * @return true(on)/false(off)
 */
bool maze_dotState (uint8_t col, uint8_t row);


/** Current maze LED dot setter
 * @parameter col, row, state
 */
void maze_setDot (uint8_t col, uint8_t row, bool state);


/** Current maze player start column location getter
 */
uint8_t maze_playerStartCol (void);


/** Current maze player start row location getter
 */
uint8_t maze_playerStartRow (void);


/** Current maze player finish column location getter
 */
uint8_t maze_playerFinishCol (void);


/** Current maze player finish row location getter
 */
uint8_t maze_playerFinishRow (void);


/** Current maze stage name getter
 */
StageIndex_t maze_stageName (void);


/** Dispaly maze traps
 */
ActiveTrap_locs_t mazeDisplay_traps (void);


/** Current maze trap tick max value getter
 */
uint16_t mazeTrap_maxTick (void);


#endif // MAZE_DISPLAY_H
