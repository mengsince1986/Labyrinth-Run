/** @file game.c
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief A simple maze game with different stages
 */


#include "system.h"
#include "pacer.h"
#include "maze_display.h"
#include "player.h"
// #include "navswitch.h"


int main (void)
{
    // navigate task peroid
    uint16_t nav_tick = 0;
    uint16_t nav_tick_max = 40;

    // trap configuration
    uint16_t trap_tick = 0;
    uint16_t trap_tick_max = 500;
    uint8_t trap_col = 1;
    uint8_t trap_row = 3;

    // initialise program
    system_init ();
    // navswitch_init ();
    pacer_init (500);
    mazeDisplay_init ();
    maze_setStage (STAGE_1);
    player_init (maze_playerStartCol(), maze_playerStartRow());


    while (1)
    {
        pacer_wait ();

        // run display
        maze_display ();

        // run trap
        trap_tick++;
        if (trap_tick >= trap_tick_max) {
            trap_tick = 0;
            maze_toggleDot (trap_col, trap_row);
        }

        // move player
        nav_tick++;
        if (nav_tick >= nav_tick_max) {
            nav_tick = 0;
            if (player_move ()) {
                maze_setDot (player_previousCol (), player_previousRow (), false);
                maze_setDot (player_col (), player_row (), true);
            }
        }

        /*

        // move player
        nav_tick++;
        if (nav_tick >= 40) {
            nav_tick = 0;
            navswitch_update ();
            // if NORTH is pressed
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                // update maze_pattern
                maze_pattern[player_loc[0]] &= ~(1<<player_loc[1]); // turnoff player's previous position
                // update player location
                player_loc[1] -= 1;
                // update maze_pattern
                maze_pattern[player_loc[0]] |= (1<<player_loc[1]); // turn on player's new position

            }
            // if SOUTH is pressed
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                // update maze_pattern
                maze_pattern[player_loc[0]] &= ~(1<<player_loc[1]); // turnoff player's previous position
                // update player location
                player_loc[1] += 1;
                // update maze_pattern
                maze_pattern[player_loc[0]] |= (1<<player_loc[1]); // turn on player's new position
            }
            // if EAST is pressed
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                // update maze_pattern
                maze_pattern[player_loc[0]] &= ~(1<<player_loc[1]); // turnoff player's previous position
                // update player location
                player_loc[0] += 1;
                // update maze_pattern
                maze_pattern[player_loc[0]] |= (1<<player_loc[1]); // turn on player's new position
            }
            // if WEST is pressed
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                // update maze_pattern
                maze_pattern[player_loc[0]] &= ~(1<<player_loc[1]); // turnoff player's previous position
                // update player location
                player_loc[0] -= 1;
                // update maze_pattern
                maze_pattern[player_loc[0]] |= (1<<player_loc[1]); // turn on player's new position
            }
        }

        */

    }
}
