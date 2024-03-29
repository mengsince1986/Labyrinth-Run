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

/**
 * Update the display of traps and check if player is in traps
 */
void updateCheck_traps (void)
{
    ActiveTrap_locs_t activeTraps =  mazeDisplay_traps ();
    for (uint8_t i = 0; i < TRAPS_NUM; i++) {
        if (activeTraps.locs[i][0] == player_col () &&
                activeTraps.locs[i][1] == player_row ()) {
            state_endGame ();
        }
    }
}


/**
 * Update the display of player and check if player moves to walls/traps
 */
void updateCheck_playerMove (void)
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
    mazePatterns_init ();
    maze_setStage (STAGE_1);
    player_init (maze_playerStartCol(), maze_playerStartRow());
    state_init ();

    // initialise player move frequency tick starter and max tick
    uint16_t nav_tick = 0;
    uint16_t nav_tick_max = navDelay;

    // initialise trap frequency tick starter
    uint16_t trap_tick = 0;

    while (1)
    {
        pacer_wait ();

        // check if reset game
        if (state_hasGameReset ()) {
            state_init ();
            mazeDisplay_init ();
            mazePatterns_init ();
            maze_setStage (STAGE_1);
            player_init (maze_playerStartCol(), maze_playerStartRow());
        }

        // check if game over
        if (state_isGameOver ()) {

            if (!state_isStageComplete ()) {
                maze_setStage (FAIL_SYMBOL);
            } else if (state_isStageComplete ()) {
                maze_setStage (WIN_SYMBOL);
            }
            press_resetGame ();
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

            press_resetGame ();
            // run trap
            trap_tick++;
            if (trap_tick >= mazeTrap_maxTick ()) {
                trap_tick = 0;
                updateCheck_traps ();
            }

            // move player
            nav_tick++;
            if (nav_tick >= nav_tick_max) {
                nav_tick = 0;
                if (player_move ()) {
                    updateCheck_playerMove ();
                }
            }
        }
    }
}
