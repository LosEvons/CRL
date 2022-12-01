#include "rogue.h"
#include "stdlib.h"
#include "stdio.h"

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

/* Get the direction and distance of two points */
Relation *  twoPointRelation(Position * point1, Position * point2){
    Relation * relations;
    relations = malloc(sizeof(Relation *));

    int dy = point1->y - point2->y;
    int dx = point1->x - point2->x;

    // looking for straight lines
    if (dy != 0 && dx == 0){
        relations->distance = abs(dy);
        if (dy < 0)
            relations->direction = NORTH;
        else
            relations->direction = SOUTH;
    } else if (dx != 0 && dy == 0){
        relations->distance = abs(dx);
        if (dx < 0)
            relations->direction = WEST;
        else
            relations->direction = EAST;
    } else {
        relations->distance = 0;
        relations->direction = 0;
    }
    
    return relations;
}