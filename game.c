/** @file game.c
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief A simple maze game with different stages
 */

// API modules
#include "system.h"
#include "ledmat.h"
#include "pacer.h"
#include "navswitch.h"

// Game modules

// Fi was here

// maze patterns
uint8_t maze_pattern[] =
{
    0b0001110, 0b0000010, 0b1001011, 0b0001000, 0b0111011
};

// player
uint8_t player_loc[] = {2, 7};

int main (void)
{
    // current led matrix column
    uint8_t current_col = 0;

    // navigate task peroid
    uint8_t nav_tick = 0;

    // trap
    // trap task period
    uint16_t trap_tick = 0;
    // trap status
    uint8_t trap_on = 0;
    // trap location
    uint8_t trap_loc[] = {1, 3};

    // initialise program
    system_init ();
    ledmat_init ();
    navswitch_init ();

    pacer_init (400);


    while (1)
    {
        pacer_wait ();

        // display maze_pattern
        ledmat_init ();
        ledmat_display_column(maze_pattern[current_col], current_col);
        current_col++;
        // if current led column is greater than max columns
        // reset current led column to 0
        if (current_col > (LEDMAT_COLS_NUM - 1)) {
            current_col = 0;
        }

        // display trap
        trap_tick++;
        if (trap_tick >= 1000) {
            trap_tick = 0;
            if (trap_on) {
                // turn off trap
                maze_pattern[trap_loc[0]] &= ~(1<<trap_loc[1]);
                trap_on = 0;
            } else {
                // turn on trap
                maze_pattern[trap_loc[0]] |= (1<<trap_loc[1]);
                trap_on = 1;
            }
        }


        // move player (can only move up)
        nav_tick++;
        if (nav_tick >= 40) {
            nav_tick = 0;
            navswitch_update ();
            /* if NORTH is pressed.  */
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                // update maze_pattern
                maze_pattern[player_loc[0]] &= ~(1<<player_loc[1]); // turnoff player's previous position
                // update player location
                player_loc[1] -= 1;
                // update maze_pattern
                maze_pattern[player_loc[0]] |= (1<<player_loc[1]); // turn on player's new position

            }
            /* if SOUTH is pressed.  */
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                // update maze_pattern
                maze_pattern[player_loc[0]] &= ~(1<<player_loc[1]); // turnoff player's previous position
                // update player location
                player_loc[1] += 1;
                // update maze_pattern
                maze_pattern[player_loc[0]] |= (1<<player_loc[1]); // turn on player's new position
            }
            /* if EAST is pressed.  */
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                // update maze_pattern
                maze_pattern[player_loc[0]] &= ~(1<<player_loc[1]); // turnoff player's previous position
                // update player location
                player_loc[0] += 1;
                // update maze_pattern
                maze_pattern[player_loc[0]] |= (1<<player_loc[1]); // turn on player's new position
            }
            /* if WEST is pressed.  */
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                // update maze_pattern
                maze_pattern[player_loc[0]] &= ~(1<<player_loc[1]); // turnoff player's previous position
                // update player location
                player_loc[0] -= 1;
                // update maze_pattern
                maze_pattern[player_loc[0]] |= (1<<player_loc[1]); // turn on player's new position
            }
        }

    }
}
