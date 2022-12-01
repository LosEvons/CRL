#include "rogue.h"
#include "stdlib.h"

Level * initLevel(int roomCount){
    Level * newLevel;
    newLevel = malloc(sizeof(Level));
    newLevel->roomCount = roomCount;
    newLevel->rooms = malloc(sizeof(Room *) * roomCount);

    newLevel->player = playerSetUp();

    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++){
        for (x = 0; x < MAP_WIDTH; x++){
            newLevel->tiles[y][x][0] = createTemplateTile(STONE_WALL_TILE);
        }
    }
    Room * testRoom = initRoom(5, 10, 7, 7);
    newLevel->rooms[0] = testRoom;
    Room * testRoom2 = initRoom(10, 40, 6, 6);
    newLevel->rooms[1] = testRoom2;

    return newLevel;
}

int updateLevel(Level * level){
    int i;
    for (i = 0; i < level->roomCount; i++){
        Room * currentRoom = level->rooms[i];
        updateRoom(currentRoom, level);
    }
    buildCorridor(level->rooms[0], level->rooms[1], level);

    placePlayerInRoom(level->rooms[0], level->player);
    
    return 0;
}