/** @file player.c
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief player module header c file
 */

#include "system.h"
#include "navswitch.h"
#include "player.h"


// Default player struct
static Player_t PLAYER = {
    .previousCol = 2,
    .previousRow = 6,
    .playerCol = 2,
    .playerRow = 6,
};


/** Plyaer initialiser
 * @parameter col row
 */
void player_init (uint8_t col, uint8_t row)
{
    navswitch_init ();
    PLAYER.previousCol = col;
    PLAYER.previousRow = row;
    PLAYER.playerCol = col;
    PLAYER.playerRow = row;
}


/** Player current column location getter
 * @return col
 */
uint8_t player_col (void)
{
    return PLAYER.playerCol;
}

/** Player previous column location getter
 * @return col
 */
uint8_t player_previousCol (void)
{
    return PLAYER.previousCol;
}


/** Player row location getter
 * @return row
 */
uint8_t player_row (void)
{
    return PLAYER.playerRow;
}


/** Player previous row location getter
 * @return row
 */
uint8_t player_previousRow (void)
{
    return PLAYER.previousRow;
}


/** Player column validity checker
 * @parameter col
 * @return true if column is valid
 */
bool isValid_col (uint8_t col)
{
    return (col < LEDMAT_COLS_NUM);
}


/** Player column validity checker
 * @parameter col
 * @return true if column is valid
 */
bool isValid_row (uint8_t row)
{
    return (row < LEDMAT_ROWS_NUM);
}


/** Player column location setter
 * @parameter col
 */
void playerMoveTo_col (uint8_t col)
{
    if (isValid_col (col) && col != PLAYER.playerCol) {
        PLAYER.previousCol = PLAYER.playerCol;
        PLAYER.previousRow = PLAYER.playerRow;
        PLAYER.playerCol = col;
    }
}


/** Player row location setter
 * @parameter col
 */
void playerMoveTo_row (uint8_t row)
{
    if (isValid_row (row) && row != PLAYER.playerRow) {
        PLAYER.previousCol = PLAYER.playerCol;
        PLAYER.previousRow = PLAYER.playerRow;
        PLAYER.playerRow = row;
    }
}


/** Move player up
 */
void player_moveUp (void)
{
    playerMoveTo_row (PLAYER.playerRow - 1);
}


/** Move player down
 */
void player_moveDown (void)
{
    playerMoveTo_row (PLAYER.playerRow + 1);
}


/** Move player left
 */
void player_moveLeft (void)
{
    playerMoveTo_col (PLAYER.playerCol - 1);

}


/** Move player right
 */
void player_moveRight (void)
{
    playerMoveTo_col (PLAYER.playerCol + 1);

}


/** Player navigation location setter
 */
bool player_move (void)
{
    bool has_moved = false;
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        player_moveUp ();
        has_moved = true;
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        player_moveDown ();
        has_moved = true;
    }

    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        player_moveRight ();
        has_moved = true;
    }

    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        player_moveLeft ();
        has_moved = true;
    }
    return has_moved;
}
