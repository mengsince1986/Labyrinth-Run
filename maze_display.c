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
const uint8_t STAGE_NUM = 2;

static MazeStage_t STAGE1 = {
    .maze_pattern = {
        0b0001110, //col-1
        0b0000010, //col-2
        0b1001011, //col-3
        0b0001000, //col-4
        0b0111011  //col-5
    },
    .start_loc = {2, 6},
    .pass_loc = {3, 0}
};


static MazeStage_t STAGE2 = {
    .maze_pattern = {
        0b0001000, //col-1
        0b0001000, //col-2
        0b1000000, //col-3
        0b0001001, //col-4
        0b0001000  //col-5
    },
    .start_loc = {2, 7},
    .pass_loc = {4, 1}
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
    ledmat_display_column((CURRENT_MAZE->maze_pattern)[display_col],
            display_col);
    display_col++;

    // if current column index is greater than max columns
    // reset current led column to 0
    if (display_col > (LEDMAT_COLS_NUM - 1)) {
        display_col = 0;
    }
}

