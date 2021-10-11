/** @file state.c
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief game state module header c file
 */


#include "system.h"
#include "state.h"


static State_t STATE = {
    .isGameOver = false,
    .stageComplete = false
};


/** Game state initialiser
 */
void state_init (void)
{
    STATE.isGameOver = false;
    STATE.stageComplete = false;
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
