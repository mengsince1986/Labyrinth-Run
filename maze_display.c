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

#define DISABLE_LOC 9

// maze initial patterns
// !!!DO NOT MODIFY!!!
uint8_t STAGE1_PATTERN_INIT[LEDMAT_COLS_NUM] = {
        0b1111111, //col-0
        0b0010100, //col-1
        0b1010101, //col-2
        0b0010001, //col-3
        0b1111111  //col-4
};

uint8_t STAGE2_PATTERN_INIT[LEDMAT_COLS_NUM] = {
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
 *    - to disable a trap, set it's loc to {DISABLE_LOC, DISABLE_LOC}
 *    - to make two sets of traps flash alternatively, initialise one set of
 *      traps on and the other set of traps off in the maze_pattern
 * 4. trapTick_max: set the frequency of traps, the lower the value the higher
 *                  the frequency
 */


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
    .trap_locs = {{1, 4}, {3, 2}, {DISABLE_LOC, DISABLE_LOC},
        {DISABLE_LOC, DISABLE_LOC}, {DISABLE_LOC, DISABLE_LOC},
        {DISABLE_LOC, DISABLE_LOC}, {DISABLE_LOC, DISABLE_LOC}},
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

static MazeStage_t STAGE3 = {
    .stage_name = STAGE_3,
    .maze_pattern = {
        0b1111111, //col-0
        0b0000001, //col-1
        0b0011100, //col-2
        0b0000001, //col-3
        0b1111111  //col-4
    },
    .playerStart_col = 2,
    .playerStart_row = 6,
    .playerFinish_col = 2,
    .playerFinish_row = 0,
    .trap_locs = {{1, 4}, {1, 2}, {3, 3}, {3, 2}},
    .trapTick_max = 200
};

static MazeStage_t STAGE4 = {
    .stage_name = STAGE_4,
    .maze_pattern = {
        0b0000001, //col-0
        0b0111101, //col-1
        0b0000000, //col-2
        0b0111101, //col-3
        0b0000001  //col-4
    },
    .playerStart_col = 2,
    .playerStart_row = 6,
    .playerFinish_col = 2,
    .playerFinish_row = 0,
    .trap_locs = {{0, 1}, {2, 4}, {2, 3}, {2, 1}, {4, 1}},
    .trapTick_max = 200
};

static MazeStage_t STAGE5 = {
    .stage_name = STAGE_5,
    .maze_pattern = {
        0b0000011, //col-0
        0b0101011, //col-1
        0b0101000, //col-2
        0b0101011, //col-3
        0b1100011  //col-4
    },
    .playerStart_col = 2,
    .playerStart_row = 6,
    .playerFinish_col = 2,
    .playerFinish_row = 0,
    .trap_locs = {{0, 6}, {0, 3}, {0, 2}, {2, 2}, {3, 4}, {4, 4}},
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
    .trap_locs = {{DISABLE_LOC, DISABLE_LOC}, {DISABLE_LOC, DISABLE_LOC},
        {DISABLE_LOC, DISABLE_LOC}, {DISABLE_LOC, DISABLE_LOC},
        {DISABLE_LOC, DISABLE_LOC}, {DISABLE_LOC, DISABLE_LOC},
        {DISABLE_LOC, DISABLE_LOC}},
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
    .trap_locs = {{DISABLE_LOC, DISABLE_LOC}, {DISABLE_LOC, DISABLE_LOC},
        {DISABLE_LOC, DISABLE_LOC}, {DISABLE_LOC, DISABLE_LOC},
        {DISABLE_LOC, DISABLE_LOC}, {DISABLE_LOC, DISABLE_LOC},
        {DISABLE_LOC, DISABLE_LOC}},
    .trapTick_max = 500
};


static MazeStage_t* CURRENT_MAZE = &STAGE1;


/** Reset the stage maze_pattern to initial state
 * @parameter init_source maze_pattern
 */
void maze_initPattern (uint8_t init_source[LEDMAT_COLS_NUM],
        uint8_t maze_pattern[LEDMAT_COLS_NUM])
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
//    maze_initPattern (STAGE3_PATTERN_INIT, STAGE3.maze_pattern);
//    maze_initPattern (STAGE4_PATTERN_INIT, STAGE4.maze_pattern);
//    maze_initPattern (STAGE5_PATTERN_INIT, STAGE5.maze_pattern);
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
        case STAGE_3:
            CURRENT_MAZE = &STAGE3;
            break;
        case STAGE_4:
            CURRENT_MAZE = &STAGE4;
            break;
        case STAGE_5:
            CURRENT_MAZE = &STAGE5;
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
ActiveTrap_locs_t mazeDisplay_traps (void)
{
    ActiveTrap_locs_t active_traps;
    for (uint8_t i = 0; i < TRAPS_NUM; i++) {
        maze_toggleDot (CURRENT_MAZE->trap_locs[i][0],
                CURRENT_MAZE->trap_locs[i][1]);
        if (maze_dotState (CURRENT_MAZE->trap_locs[i][0],
                    CURRENT_MAZE->trap_locs[i][1])) {
            active_traps.locs[i][0] = CURRENT_MAZE->trap_locs[i][0];
            active_traps.locs[i][1] = CURRENT_MAZE->trap_locs[i][1];
        } else {
            active_traps.locs[i][0] = DISABLE_LOC;
            active_traps.locs[i][1] = DISABLE_LOC;
        }
    }
    return active_traps;
}


/** Current maze trap tick max value getter
 */
uint16_t mazeTrap_maxTick (void)
{
    return (CURRENT_MAZE->trapTick_max);
}

