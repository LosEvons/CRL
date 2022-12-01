#include "rogue.h"

Tile * createTemplateTile(int type){
    Tile * newTile;
    newTile =  malloc(sizeof(Tile *));
    newTile->type = type;
    switch(type){
        case EMPTY_TILE:
            newTile->sprite = ' ';
            newTile->collision = 0;
            break; // empty
        
        case V_WALL_TILE:
            newTile->sprite = '|';
            newTile->collision = 1;
            break; // vertical wall

        case H_WALL_TILE:
            newTile->sprite = '-';
            newTile->collision = 1;
            break; // horizontal wall
        
        case C_WALL_TILE:
            newTile->sprite = 'O';
            newTile->collision = 1;
            break; // corner wall 
        
        case FLOOR_TILE:
            newTile->sprite = '.';
            newTile->collision = 0;
            break; // floor
        case STONE_WALL_TILE:
            newTile->sprite = '#';
            newTile->collision = 1;
            break; // stone wall

        case DOOR_TILE:
            newTile->sprite = '+';
            newTile->collision = 0;

        default:
            newTile->sprite = '?';
            newTile->collision = 0;
            break;
    }
    sprintf(newTile->sprite_string, "%c", newTile->sprite);

    return newTile;
}

Tile * createUniqueTile(char sprite, int collision){
    Tile * newTile;
    newTile = malloc(sizeof(Tile *));
    newTile->sprite = sprite;
    newTile->collision = collision;
    
    sprintf(newTile->sprite_string, "%c", newTile->sprite);

    return newTile;

}