/** @file game.c
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief A simple maze game with multiple stages
 */


#include "system.h"
#include "pacer.h"
#include "maze_display.h"
#include "player.h"
#include "state.h"

#define defaultFreq 500

int main (void)
{
    // initialise program
    system_init ();
    // navswitch_init ();
    pacer_init (defaultFreq);
    mazeDisplay_init ();
    maze_setStage (STAGE_1);
    player_init (maze_playerStartCol(), maze_playerStartRow());
    state_init ();

    // player move config
    uint16_t nav_tick = 0;
    uint16_t nav_tick_max = 40;

    // trap config
    uint16_t trap_tick = 0;
    uint16_t trap_tick_max = 500;
    uint8_t trap_col = 1;
    uint8_t trap_row = 3;

    while (!(state_isGameOver()))
    {
        /*
        // check if current stage completed
        if (state_isStageComplete ()) {
            mazeDisplay_init ();
            maze_setStage (STAGE_2);
            player_init (maze_playerStartCol(), maze_playerStartRow());
            state_init ();
        }
        */

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
                // turn off player's previous location
                maze_setDot (player_previousCol (), player_previousRow (), false);

                // set stage completed if player move into complete location
                if ((player_col () == maze_playerFinishCol ()) &&
                        player_row () == maze_playerFinishRow ()) {
                    state_completeStage ();
                    state_endGame ();
                    /**
                    if (maze_stageName () >= GAME_OVER) {
                        state_endGame ();
                    }
                    */
                }

                // set game over if player move into wall or traps
                // or crash into boundaries twice
                if (maze_dotState (player_col (), player_row ())) {
                    state_endGame ();
                }

                // turn on player's current location
                maze_setDot (player_col (), player_row (), true);

            }
        }
    }

    // End Game
    mazeDisplay_init ();
    maze_setStage (GAME_OVER);
    while (1) {
        maze_display ();
    }
}
