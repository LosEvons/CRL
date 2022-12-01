#ifndef ROGUE_H
#define ROGUE_H

#include "stdlib.h"
#include "curses.h"
#include "time.h"

/* World variables */
#define MAP_HEIGHT 25
#define MAP_WIDTH 100

/* Define different tiles */
#define EMPTY_TILE 0
#define V_WALL_TILE 1
#define H_WALL_TILE 2
#define C_WALL_TILE 3
#define FLOOR_TILE 4
#define STONE_WALL_TILE 5
#define DOOR_TILE 6

/*    STRUCTURE DECLARATIONS    */
typedef struct Position{
    int y;
    int x;
} Position;

typedef struct Player{
    struct Position * position;
    char sprite;
    char sprite_string[2];
} Player;

typedef struct Tile{
    int type; //use tile definitions for clarity
    int collision;
    char sprite;
    char sprite_string[2];
} Tile;

typedef struct Level{
    struct Tile * tiles[MAP_HEIGHT][MAP_WIDTH][1];
    struct Room ** rooms;
    int roomCount;
    Player * player;
} Level;

typedef struct Room{
    struct Position position;
    int height;
    int width;
} Room;

/*    FUNCTION DECLARATIONS    */

/* Screen Functions */
int screenSetUp();
int renderTiles(Level * level);
int renderEntities(Level * level);

/* Tile Functions*/
Tile * createTemplateTile(int type);
Tile * createUniqueTile(char sprite, int collision);

/* Level Functions */
Level * initLevel(int roomCount);
int updateLevel(Level * level);

/* Room Functions */
Room * initRoom(int y, int x, int h, int w);
Position * getRoomCenter(Room * room);
int assignRoomTiles(Room * room, Level * level);

/* Player Functions */
Player * playerSetUp();
int placePlayerInRoom(Room * room, Player * player);
int movePlayer(Position * newPosition, Level * level);
int playerSpriteRefresh(Player * player);
int handlePlayerAction(Position * newPosition, Player * player, Level * level);

/* Input Handler Functions*/
Position * handleMovementInput(int input, Player * player);

#endif