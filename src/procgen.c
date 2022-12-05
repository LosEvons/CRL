#include "rogue.h"

Room ** generateRooms(int roomCount){
    Room ** gendRooms;
    gendRooms = malloc(sizeof(Room *) *roomCount);
    int i, j;
    for (i = 0; i < roomCount; i++){
        while(1){
            int height = rand() % (MAX_ROOM_HEIGHT - MIN_ROOM_HEIGHT) + MIN_ROOM_HEIGHT;
            int width = rand() % (MAX_ROOM_WIDTH - MIN_ROOM_WIDTH) + MIN_ROOM_WIDTH;
            int yPos = rand() % (MAP_HEIGHT - (MIN_ROOM_HEIGHT * 2)) + MIN_ROOM_HEIGHT;
            int xPos = rand() % (MAP_WIDTH - (MIN_ROOM_WIDTH * 2)) + MIN_ROOM_WIDTH;

            Room * newRoom = initRoom(yPos, xPos, height, width);

            if (i == 0){ // First room always initializes if in bounds
                if (roomInBounds(newRoom) == 1){
                    gendRooms[i] = newRoom;
                    break;
                } else{
                    continue;
                }
            } else{
                if ((roomInBounds(newRoom) == 1) && (checkRoomOverlap(newRoom, gendRooms, i) == 1)){
                    gendRooms[i] = newRoom;
                    break;
                } else {
                    continue;
                }
            }
        }
    }    

    return gendRooms;   
}

int corridorConnect(Level * level){
    int i;
    for (i = 0; i < (level->roomCount - 1); i++){
        buildCorridor(level->rooms[i], level->rooms[i + 1], level);
    }

    return 0;
}