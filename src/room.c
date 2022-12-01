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