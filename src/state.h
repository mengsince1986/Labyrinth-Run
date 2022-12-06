/** @file state.h
 *  @group 112
 *  @author Meng Zhang
 *  @author Sophie Engel
 *  @date October 2021
 *  @brief game state module header
 */

#ifndef STATE_H
#define STATE_H

#include "system.h"

/** Game state struct type
 */
typedef struct
{
    bool isGameOver;
    bool stageComplete;
    bool gameReset;
} State_t;


/** Game state initialiser
 */
void state_init (void);


/** State of isGameOver getter
 */
bool state_isGameOver (void);


/** State of stageComplete getter
 */
bool state_isStageComplete (void);


/** State of gameReset getter
 */
bool state_hasGameReset (void);


/** State of isGameOver setter
 */
void state_endGame (void);


/** State of stageComplete setter
 */
void state_completeStage (void);


/** Press button to reset game
 */
void press_resetGame (void);

#endif //STATE_H
