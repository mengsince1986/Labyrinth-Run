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

/**
 * Set stage patterns
 * Configuration note:
 * 1. column index is 0-4; row index is 0-6
 * 2. maze_pattern = {0b-row7-row6-row5-row4-row3-row2-row1, ..., ...}
 * 3. start_loc = {row_index, col_index}
 * 4. pass_loc = {row_index, col_index}
 */

// static uint8_t STAGE_NUM = 2;

static MazeStage_t STAGE1 = {
    .stage_name = STAGE_1,
    .maze_pattern = {
        0b0001110, //col-0
        0b0000010, //col-1
        0b1001011, //col-2
        0b0001000, //col-3
        0b0111011  //col-4
    },
    .playerStart_col = 2,
    .playerStart_row = 6,
    .playerFinish_col = 3,
    .playerFinish_row = 0
};


static MazeStage_t STAGE2 = {
    .stage_name = STAGE_2,
    .maze_pattern = {
        0b0001000, //col-0
        0b0001000, //col-1
        0b0000000, //col-2
        0b1001001, //col-3
        0b0001000  //col-4
    },
    .playerStart_col = 3,
    .playerStart_row = 6,
    .playerFinish_col = 4,
    .playerFinish_row = 0
};


static MazeStage_t OVER = {
    .stage_name = GAME_OVER,
    .maze_pattern = {
     0x30, 0x46, 0x40, 0x46, 0x30 // smiley face
    },
    .playerStart_col = 0,
    .playerStart_row = 0,
    .playerFinish_col = 0,
    .playerFinish_row = 0
};

static MazeStage_t* CURRENT_MAZE = &STAGE1;


// Maze display initialiser
void mazeDisplay_init (void)
{
    ledmat_init ();
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
        //case STAGE_3:
        //    CURRENT_MAZE = &STAGE3;
        //    break;
        case GAME_OVER:
            CURRENT_MAZE = &OVER;
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
