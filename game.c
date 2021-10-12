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
#define navDelay 40
#define trapDelay 500


void update_playerMove (void)
{
    // turn off player's previous location
    maze_setDot (player_previousCol (), player_previousRow (),
            false);

    // check game state
    // set stage completed if player move into complete location
    // and set game over if no more stages availabe
    if ((player_col () == maze_playerFinishCol ()) &&
            player_row () == maze_playerFinishRow ()) {
        state_completeStage ();

        if (maze_stageName () >= (FAIL_SYMBOL - 1)) {
            state_endGame ();
        }
    }

    // set fail symbol display if player move into wall or traps
    if (maze_dotState (player_col (), player_row ())) {
        state_endGame ();
    }

    // turn on player's current location
    maze_setDot (player_col (), player_row (), true);
}


int main (void)
{
    // initialise program
    system_init ();
    pacer_init (defaultFreq);
    mazeDisplay_init ();
    maze_setStage (STAGE_1);
    player_init (maze_playerStartCol(), maze_playerStartRow());
    state_init ();

    // player move config
    uint16_t nav_tick = 0;
    uint16_t nav_tick_max = navDelay;

    // trap config
    uint16_t trap_tick = 0;
    uint16_t trap_tick_max = trapDelay;

    while (1)
    {
        pacer_wait ();

        // check if game is over
        if (state_isGameOver ()) {

            if (!state_isStageComplete ()) {
                maze_setStage (FAIL_SYMBOL);
            } else if (state_isStageComplete ()) {
                maze_setStage (WIN_SYMBOL);
            }
        }

        // check if stage is completed
        if (!(state_isGameOver ()) && (state_isStageComplete ())) {
            maze_setStage (maze_stageName () + 1);
            player_init (maze_playerStartCol(), maze_playerStartRow());
            state_init ();
        }

        // run display
        mazeDisplay_init ();
        maze_display ();

        if (!(state_isGameOver())) {

            // run trap
            trap_tick++;
            if (trap_tick >= trap_tick_max) {
                trap_tick = 0;
                mazeDisplay_traps ();
            }

            // move player
            nav_tick++;
            if (nav_tick >= nav_tick_max) {
                nav_tick = 0;
                if (player_move ()) {
                    update_playerMove ();
                }
            }
        }
    }
}
