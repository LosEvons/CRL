#include "rogue.h"

Room * initRoom(int y, int x, int h, int w){
    Room * newRoom;
    newRoom = malloc(sizeof(Room *));
    
    newRoom->position.y = y;
    newRoom->position.x = x;
    newRoom->height = h;
    newRoom->width = w;

    return newRoom;
}

Position * getRoomCenter(Room * room){
    int y_center, x_center;
    Position * center_position;
    center_position = malloc(sizeof(Position));

    y_center = room->position.y + (room->height / 2);
    x_center = room->position.x + (room->width / 2);

    center_position->y = y_center;
    center_position->x = x_center;

    return center_position;
}

int updateRoom(Room * room, Level * level){
    assignRoomWallTiles(room, level);
    assignRoomFloorTiles(room, level);

    return 0;
}

int assignRoomFloorTiles(Room * room, Level * level){
    int x, y;
    for (y = 1; y < room->height; y++){
        for (x = 1; x < room->width; x++){
            level->tiles[room->position.y + y][room->position.x + x][0] = createTemplateTile(FLOOR_TILE);
        }
    }

    return 0;
}

int assignRoomWallTiles(Room * room, Level * level){
    int x, y;
    // Corners
    level->tiles[room->position.y][room->position.x][0] = createTemplateTile(C_WALL_TILE);
    level->tiles[room->position.y + room->height][room->position.x][0] = createTemplateTile(C_WALL_TILE);
    level->tiles[room->position.y][room->position.x + room->width][0] = createTemplateTile(C_WALL_TILE);
    level->tiles[room->position.y + room->height][room->position.x + room->width][0] = createTemplateTile(C_WALL_TILE);

    // Verticals
    for (y = 0; y < (room->height - 1); y++){
        level->tiles[room->position.y + 1 + y][room->position.x][0] = createTemplateTile(V_WALL_TILE);
        level->tiles[room->position.y + 1 + y][room->position.x + room->width][0] = createTemplateTile(V_WALL_TILE);
    }

    // Horizontals
    for (x = 0; x < (room->width - 1); x++){
        level->tiles[room->position.y ][room->position.x + 1 + x][0] = createTemplateTile(H_WALL_TILE);
        level->tiles[room->position.y + room->height][room->position.x + 1 + x][0] = createTemplateTile(H_WALL_TILE);
    }

    return 0;
}

int buildCorridor(Room * room1, Room * room2, Level * level){
    Position * start = getRoomCenter(room1);
    Position * end = getRoomCenter(room2);
    
    Position * midpoint;
    midpoint = malloc(sizeof(Position *));

    int startDirection = rand() % 2;
    if (startDirection == 0) {
        midpoint->y = start->y;
        midpoint->x = end->x;
    } else if (startDirection == 1){
        midpoint->y = end->y;
        midpoint->x = start->x;
    } else {
        return 1;
    }
    //level->tiles[midpoint->y][midpoint->x][0] = createTemplateTile(FLOOR_TILE);
    
    Relation * relations = twoPointRelation(midpoint, start);
    tunnelInDirection(relations, start, level);
    relations = twoPointRelation(end, midpoint);
    tunnelInDirection(relations, midpoint, level);
    free(relations);

    return 0;
}

int tunnelInDirection(Relation * relations, Position * start, Level * level){
    int i;
    if (relations->direction == 0 || relations->distance == 0){
        return 1;
    }

    switch(relations->direction){
        case NORTH:
            for (i = 0; i < relations->distance; i++)
                level->tiles[start->y - i][start->x][0] = createTemplateTile(FLOOR_TILE);
            break;

        case WEST:
            for (i = 0; i < relations->distance; i++)
                level->tiles[start->y][start->x - i][0] = createTemplateTile(FLOOR_TILE);
            break;

        case SOUTH:
            for (i = 0; i < relations->distance; i++)
                level->tiles[start->y + i][start->x][0] = createTemplateTile(FLOOR_TILE);
            break;

        case EAST:
            for (i = 0; i < relations->distance; i++)
                level->tiles[start->y][start->x + i][0] = createTemplateTile(FLOOR_TILE);
            break; 
    }

    return 0;
}