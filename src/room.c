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

Room * initDumRoom(){
    Room * newRoom;
    newRoom = malloc(sizeof(Room *));

    newRoom->position.y = -1;
    newRoom->position.x = -1;
    newRoom->height = -1;
    newRoom->width = -1;

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

int roomInBounds(Room * room){
    if (
        (room->position.y <= 0)
        || (room->position.x <= 0)
        || (room->position.y + room->height >= MAP_HEIGHT)
        || (room->position.x + room->width >= MAP_WIDTH)
        )
        return 2;
    else
        return 1; // is in bounds 
}

int positionInRoom(Position * position, Room * room){
    if (
        (
            (position->y >= room->position.y)
            && (position->y <= room->position.y + room->height)
        )
        &&
        (
            (position->x >= room->position.x)
            && (position->x <= room->position.x + room->width)
        )
    ){
        return 1;
    }
    return 0;
}
// 1 for north, 2 for west, 3 for south, 4 for east
int positionInWall(Position * position, Room * room){
    if(
        (position->y == room->position.y)
        && (
            (position->x >= room->position.x)
            && (position->x <= room->position.x + room->width)
        )
    ){
        return NORTH;
    }
    else if(
        (position->y == room->position.y + room->height)
        && (
            (position->x >= room->position.x)
            && (position->x <= room->position.x + room->width)
        )
    ){
        return SOUTH;
    }
    else if(
        (position->x == room->position.x)
        && (
            (position->y >= room->position.y)
            && (position->y <= room->position.y + room->height)
        )
    ){
        return WEST;
    }
    else if(
        (position->x == room->position.x + room->width)
        && (
            (position->y >= room->position.y)
            && (position->y <= room->position.y + room->height)
        )
    )  {
        return EAST;
    }
    else {
        return 0;
    }
}

int detectOverlap(Room * room1, Room * room2){
    if (
            (
                (room1->position.y + room1->height >= room2->position.y)
                && (room1->position.y <= room2->position.y + room2->height)
            ) 
            &&
            (
                (room1->position.x + room1->width >= room2->position.x)
                && (room1->position.x <= room2->position.x + room2->width)
            )
        ){
            return 2;
        } else{
            return 1;
        }
}