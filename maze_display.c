/** @file maze_display.c
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief maze display module
 */

#include "system.h"
#include "ledmat.h"
#include "maze_display.h"

#define TRAPS_NUM 7

// maze initial patterns
// !!!DONNOT MODIFY!!!
uint8_t STAGE1_PATTERN_INIT[5] = {
        0b1111111, //col-0
        0b0010100, //col-1
        0b1010101, //col-2
        0b0010001, //col-3
        0b1111111  //col-4
};

uint8_t STAGE2_PATTERN_INIT[5] = {
        0b0010111, //col-0
        0b0000111, //col-1
        0b1010000, //col-2
        0b0000111, //col-3
        0b0010111  //col-4
};

/**
 * Set stage patterns
 * Configuration note:
 * 1. column index is 0-4; row index is 0-6
 * 2. maze_pattern = {0b-row7-row6-row5-row4-row3-row2-row1, ..., ...}
 * 3. trap_locs = {{col, row}, {col, row}, ...}
 *    - to disable a trap, set it's loc to {9, 9}
 *    - to make two sets of traps flash alternatively, initialise one set of
 *      traps on and the other set of traps off in the maze_pattern
 */

// static uint8_t STAGE_NUM = 2;


static MazeStage_t STAGE1 = {
    .stage_name = STAGE_1,
    .maze_pattern = {
        0b1111111, //col-0
        0b0010100, //col-1
        0b1010101, //col-2
        0b0010001, //col-3
        0b1111111  //col-4
    },
    .playerStart_col = 2,
    .playerStart_row = 6,
    .playerFinish_col = 1,
    .playerFinish_row = 0,
    .trap_locs = {{1, 4}, {3, 2}, {9, 9}, {9, 9}, {9, 9}, {9, 9}, {9, 9}},
    .trapTick_max = 500
};


static MazeStage_t STAGE2 = {
    .stage_name = STAGE_2,
    .maze_pattern = {
        0b0010111, //col-0
        0b0000111, //col-1
        0b1010000, //col-2
        0b0000111, //col-3
        0b0010111  //col-4
    },
    .playerStart_col = 2,
    .playerStart_row = 6,
    .playerFinish_col = 2,
    .playerFinish_row = 0,
    .trap_locs = {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {2, 1}, {2, 2}},
    .trapTick_max = 200
};

static MazeStage_t FAIL = {
    .stage_name = FAIL_SYMBOL,
    .maze_pattern = {
        0b0100010, //col-0
        0b0010100, //col-1
        0b0001000, //col-2
        0b0010100, //col-3
        0b0100010  //col-4
    },
    .playerStart_col = 0,
    .playerStart_row = 0,
    .playerFinish_col = 0,
    .playerFinish_row = 0,
    .trap_locs = {{9, 9}, {9, 9}, {9, 9}, {9, 9}, {9, 9}, {9, 9}, {9, 9}},
    .trapTick_max = 500
};

static MazeStage_t WIN = {
    .stage_name = WIN_SYMBOL,
    .maze_pattern = {
        0b0000001, //col-0
        0b0000010, //col-1
        0b1000100, //col-2
        0b0101000, //col-3
        0b0010000  //col-4
    },
    .playerStart_col = 0,
    .playerStart_row = 0,
    .playerFinish_col = 0,
    .playerFinish_row = 0,
    .trap_locs = {{9, 9}, {9, 9}, {9, 9}, {9, 9}, {9, 9}, {9, 9}, {9, 9}},
    .trapTick_max = 500
};


static MazeStage_t* CURRENT_MAZE = &STAGE1;


/** Reset the stage maze_pattern to initial state
 * @parameter init_source maze_pattern
 */
void maze_initPattern (uint8_t init_source[5], uint8_t maze_pattern[5])
{
    for (uint8_t i = 0; i < LEDMAT_COLS_NUM; i++) {
        maze_pattern[i] = init_source[i];
    }
}


// Maze display initialiser
void mazeDisplay_init (void)
{
    ledmat_init ();
}


// Maze stage patterns initialiser
void mazePatterns_init (void)
{
    maze_initPattern (STAGE1_PATTERN_INIT, STAGE1.maze_pattern);
    maze_initPattern (STAGE2_PATTERN_INIT, STAGE2.maze_pattern);
}


/** Current maze stage
 * @parameter stage_index
 */
void maze_setStage (StageIndex_t stage_index)
{
    switch (stage_index) {
        case STAGE_1:
            CURRENT_MAZE = &STAGE1;
            break;
        case STAGE_2:
            CURRENT_MAZE = &STAGE2;
            break;
        case FAIL_SYMBOL:
            CURRENT_MAZE = &FAIL;
            break;
        case WIN_SYMBOL:
            CURRENT_MAZE = &WIN;
            break;
        default:
            CURRENT_MAZE = &STAGE1;
    }
}


/** Light display_col of current maze pattern
 *  Note: display_maze should be implemented in a while loop
 *        with a pacer
 */
void maze_display (void)
{
    static uint8_t display_col = 0;
    mazeDisplay_init (); // reduce ledmatix ghosting
    ledmat_display_column((CURRENT_MAZE->maze_pattern)[display_col],
            display_col);
    display_col++;

    // if current led column index is greater than max columns
    // reset current led column to 0
    if (display_col > (LEDMAT_COLS_NUM - 1)) {
        display_col = 0;
    }
}


/** LED dot location validity checker
 * @parameter col, row
 * @return bool
 */
bool isValid_dot (uint8_t col, uint8_t row)
{
    return (col < LEDMAT_COLS_NUM) && (row < LEDMAT_ROWS_NUM);
}


/** Current maze LED dot state getter
 * @parameter col, row
 * @return bool
 */
bool maze_dotState (uint8_t col, uint8_t row)
{
    bool result = false;

    if (isValid_dot (col, row) &&
            ((CURRENT_MAZE->maze_pattern)[col] & (1 << row)) != 0) {
        result = true;
    }

    return result;
}


/** Current maze LED dot setter
 * @parameter col, row
 */
void maze_setDot (uint8_t col, uint8_t row, bool state)
{
    if (isValid_dot (col, row)) {
        if (state) {
            (CURRENT_MAZE->maze_pattern)[col] |= (1 << row);
        } else {
            (CURRENT_MAZE->maze_pattern)[col] &= ~(1 << row);
        }
    }
}


/** Current maze LED dot state toggler
 * @parameter col, row
 */
void maze_toggleDot (uint8_t col, uint8_t row)
{
    if (maze_dotState (col, row)) {
        maze_setDot (col, row, false);
    } else {
        maze_setDot (col, row, true);
    }
}


/** Current maze player start column location getter
 */
uint8_t maze_playerStartCol (void)
{
    return CURRENT_MAZE->playerStart_col;
}


/** Current maze player start row location getter
 */
uint8_t maze_playerStartRow (void)
{
    return CURRENT_MAZE->playerStart_row;
}


/** Current maze player finish column location getter
 */
uint8_t maze_playerFinishCol (void)
{
    return CURRENT_MAZE->playerFinish_col;
}


/** Current maze player finish row location getter
 */
uint8_t maze_playerFinishRow (void)
{
    return CURRENT_MAZE->playerFinish_row;
}


/** Current maze stage name getter
 */
StageIndex_t maze_stageName (void)
{
    return CURRENT_MAZE->stage_name;
}


/** Dispaly maze traps
 */
void mazeDisplay_traps (void)
{
    for (uint8_t i = 0; i < TRAPS_NUM; i++) {
        maze_toggleDot (CURRENT_MAZE->trap_locs[i][0],
                CURRENT_MAZE->trap_locs[i][1]);
    }
}


/** Current maze trap tick max value getter
 */
uint16_t mazeTrap_maxTick (void)
{
    return (CURRENT_MAZE->trapTick_max);
}

