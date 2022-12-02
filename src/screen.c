#include "rogue.h"

int screenSetUp(){
    initscr();
    noecho();
    refresh();

    return 0;
}

int renderTiles(Level * level){
    int x, y;
    for (y = 0; y < MAP_HEIGHT; y++){
        for (x = 0; x < MAP_WIDTH; x++){
            mvprintw(y, x, level->tiles[y][x][0]->sprite_string);
        }
    }

    return 0;
}

int renderEntities(Level * level){
    playerSpriteRefresh(level->player);
    
    return 0;
}