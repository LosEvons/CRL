#include "rogue.h"

Player * playerSetUp(){
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position));
    newPlayer->sprite = '@';
    
    sprintf(newPlayer->sprite_string, "%c", newPlayer->sprite);

    return newPlayer;
}

int placePlayerInRoom(Room * room, Player * player){   
    Position * centerOfRoom = getRoomCenter(room);
    player->position->y = centerOfRoom->y;
    player->position->x = centerOfRoom->x;

    return 0;
}

int movePlayer(Position * newPosition, Level * level){
    level->player->position->y = newPosition->y;
    level->player->position->x = newPosition->x;

    return 0;
}

int playerSpriteRefresh(Player * player){
    mvprintw(player->position->y, player->position->x, player->sprite_string);
    move(player->position->y, player->position->x);

    return 0;
}

int handlePlayerAction(Position * newPosition, Player * player, Level * level){
    if (level->tiles[newPosition->y][newPosition->x][0]->collision == 1){
        return 1;
    }
    else {
        movePlayer(newPosition, level);
    }

    return 0;
}