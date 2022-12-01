#include "stdio.h"

#include "curses.h"

#include "rogue.h"

int main(){
    int ch;
    screenSetUp();
    Level * level;
    level = initLevel(1);
    updateLevel(level);
    renderTiles(level);
    renderEntities(level);

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