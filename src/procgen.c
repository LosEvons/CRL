#include "rogue.h"

int generateRooms(int roomCount, Level * level){
    int i, j, y, x;
    for (i = 0; i < roomCount; i++){
        int height = rand() % (MAX_ROOM_HEIGHT - MIN_ROOM_HEIGHT) + MIN_ROOM_HEIGHT;
        int width = rand() % (MAX_ROOM_WIDTH - MIN_ROOM_WIDTH) + MIN_ROOM_WIDTH;
        int yPos = rand() % (MAP_HEIGHT - (MIN_ROOM_HEIGHT * 2)) + MIN_ROOM_HEIGHT;
        int xPos = rand() % (MAP_WIDTH - (MIN_ROOM_WIDTH * 2)) + MIN_ROOM_WIDTH;


        Room * newRoom = initRoom(yPos, xPos, height, width);
        if (checkRoomOverlap(newRoom, level) == 1){
            continue;
        }

        level->rooms[i] = newRoom;
    }

    return 0;
}