/** @file state.c
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief game state module c file
 */


#include "system.h"
#include "pio.h"
#include "state.h"


static State_t STATE = {
    .isGameOver = false,
    .stageComplete = false,
    .gameReset = false
};


/** Game state initialiser
 */
void state_init (void)
{
    STATE.isGameOver = false;
    STATE.stageComplete = false;
    STATE.gameReset = false;
}


/** State of isGameOver getter
 */
bool state_isGameOver (void)
{
    return STATE.isGameOver;
}


/** State of stageComplete getter
 */
bool state_isStageComplete (void)
{
    return STATE.stageComplete;
}


/** State of gameReset getter
 */
bool state_hasGameReset (void)
{
    return STATE.gameReset;
}


/** State of isGameOver setter
 */
void state_endGame (void)
{
    STATE.isGameOver = true;
}


/** State of stageComplete setter
 */
void state_completeStage (void)
{
    STATE.stageComplete = true;
}


/** State of gameReset setter
 */
void state_resetGame (void)
{
    STATE.gameReset = true;
}


/** Press button to reset game
 */
void press_resetGame (void) {

    pio_config_set (BUTTON1_PIO, PIO_INPUT);
    if (pio_input_get (BUTTON1_PIO)) {
        state_resetGame ();
    }

}

