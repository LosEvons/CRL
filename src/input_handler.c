#include "rogue.h"
#include "keybinds.h"

Position * handleMovementInput(int input, Player * player){
    Position * newPosition;
    newPosition = malloc(sizeof(Position));
    newPosition->y = player->position->y;
    newPosition->x = player->position->x;
    
    switch(input){
        case MOVE_UP_KEY:
            newPosition->y -= 1;
            break;
        
        case MOVE_DOWN_KEY:
            newPosition->y += 1;
            break;

        case MOVE_LEFT_KEY:
            newPosition->x -= 1;
            break;

        case MOVE_RIGHT_KEY:
            newPosition->x += 1;
            break;

        default:
            break;
    }

    return newPosition;
}