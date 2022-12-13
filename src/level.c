#include "rogue.h"
#include "stdlib.h"
#include "stdio.h"

Level * initLevel(int roomCount){
    Level * newLevel;
    newLevel = malloc(sizeof(Level));
    newLevel->roomCount = roomCount;
    newLevel->rooms = generateRooms(roomCount);
    newLevel->player = playerSetUp();

    int y, x;
    for (y = 0; y < MAP_HEIGHT; y++){
        for (x = 0; x < MAP_WIDTH; x++){
            newLevel->tiles[y][x][0] = createTemplateTile(EMPTY_TILE);
        }
    }

    return newLevel;
}

int updateLevel(Level * level){
    int i;
    for (i = 0; i < level->roomCount; i++){
        Room * currentRoom = level->rooms[i];
        updateRoom(currentRoom, level);
    }
    corridorConnect(level);

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

Room ** initializeRooms(Level * level){
    Room ** initRooms;
    initRooms = malloc(sizeof(Room) * level->roomCount);

    int i;
    for (i = 0; i < level->roomCount; i++){
        Room * dumRoom = initDumRoom();
        initRooms[i] = dumRoom;
    }
    return initRooms;
}

int checkRoomOverlap(Room * room, Room ** roomList, int roomCount){
    int i;
    for (i = 0; i < roomCount; i++){
        if (detectOverlap(room, roomList[i]) == 2){
            return 2;
        }
    }
    return 1; // no overlap
}

int positionInAnyRoom(Position * position, Level * level){
    int i;
    for (i = 0; i < level->roomCount; i++){
        if (positionInRoom(position, level->rooms[i]) == 1){
            return 1;
        }
    }
    return 0;
}

int positionInAnyWall(Position * position, Level * level){
    int i, inWall;
    for (i = 0; i < level->roomCount; i++){
        inWall = positionInWall(position, level->rooms[i]);
        if (inWall > 0)
            return inWall;
    }
    return 0;
}