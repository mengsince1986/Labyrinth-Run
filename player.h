/** @file player.h
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief player module header
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "system.h"

/** Player struct type
 */
typedef struct
{
    uint8_t previousCol;
    uint8_t previousRow;
    uint8_t playerCol;
    uint8_t playerRow;
} Player_t;


/** Plyaer initialiser
 * @parameter col row
 */
void player_init (uint8_t col, uint8_t row);


/** Player column location getter
 * @return col
 */
uint8_t player_col (void);


/** Player previous column location getter
 * @return col
 */
uint8_t player_previousCol (void);



/** Player row location getter
 * @return row
 */
uint8_t player_row (void);


/** Player previous row location getter
 * @return row
 */
uint8_t player_previousRow (void);


/** Player navigation location setter
 */
bool player_move (void);


#endif // PLAYER_H
