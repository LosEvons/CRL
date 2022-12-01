#include "stdio.h"

#include "curses.h"

#include "rogue.h"

int main(){
    int ch;
    srand(time(NULL)); // seeding for random numbers
    screenSetUp();
    Level * level;
    level = initLevel(2);
    updateLevel(level);
    renderTiles(level);
    renderEntities(level);
    buildCorridor(level->rooms[0], level->rooms[1], level);

    while((ch = getch()) != 'q'){
        // handling input
        Position * newPosition = handleMovementInput(ch, level->player);
        handlePlayerAction(newPosition, level->player, level);
        
        // rendering
        renderTiles(level);
        renderEntities(level);
    }
    endwin();

    return 0;
}