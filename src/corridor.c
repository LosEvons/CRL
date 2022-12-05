#include "rogue.h"

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
    
    Relation * relations = twoPointRelation(midpoint, start);
    tunnelInDirection(relations, start, level);
    relations = twoPointRelation(end, midpoint);
    tunnelInDirection(relations, midpoint, level);
    free(relations);
    free(start);
    free(end);
    free(midpoint);
    return 0;
}

int tunnelThroughWall(Position * position, int wallOrientation, Level * level){
    if ((wallOrientation == NORTH) || (wallOrientation == SOUTH)){
        level->tiles[position->y][position->x + 1][0] = createTemplateTile(C_WALL_TILE);
        level->tiles[position->y][position->x - 1][0] = createTemplateTile(C_WALL_TILE);
    }

    if ((wallOrientation == WEST) || (wallOrientation == EAST)){
        level->tiles[position->y + 1][position->x][0] = createTemplateTile(C_WALL_TILE);
        level->tiles[position->y - 1][position->x][0] = createTemplateTile(C_WALL_TILE);
    }
    return 0;
}

int tunnelInDirection(Relation * relations, Position * start, Level * level){
    int i, j, wallCollision;
    if (relations->direction == 0 || relations->distance == 0){
        return 1;
    }

    Position * currentPosition;
    currentPosition = malloc(sizeof(Position *));

    switch(relations->direction){
        case NORTH:
            for (i = 0; i < relations->distance; i++){
                level->tiles[start->y - i][start->x][0] = createTemplateTile(FLOOR_TILE);

                currentPosition->y = start->y - i;
                currentPosition->x = start->x;
                
                wallCollision = positionInAnyWall(currentPosition, level);
                if (wallCollision > 0){
                    tunnelThroughWall(currentPosition, wallCollision, level);
                    continue;
                }

                if (positionInAnyRoom(currentPosition, level) == 1)
                    continue;
                if ((i + 1) == relations->distance){
                    level->tiles[start->y - i - 2][start->x][0] = createTemplateTile(H_WALL_TILE);
                    continue;
                }

                if (i != 0){
                    level->tiles[start->y - i][start->x - 1][0] = createTemplateTile(V_WALL_TILE);
                    level->tiles[start->y - i][start->x + 1][0] = createTemplateTile(V_WALL_TILE);
                } else {
                    level->tiles[start->y + 1][start->x][0] = createTemplateTile(H_WALL_TILE);
                }
            }
            free(currentPosition);
            break;

        case WEST:
            for (i = 0; i < relations->distance; i++){
                level->tiles[start->y][start->x - i][0] = createTemplateTile(FLOOR_TILE);

                currentPosition->y = start->y;
                currentPosition->x = start->x - i;

                wallCollision = positionInAnyWall(currentPosition, level);
                if (wallCollision > 0){
                    tunnelThroughWall(currentPosition, wallCollision, level);
                    continue;
                }

                if (positionInAnyRoom(currentPosition, level) == 1)
                    continue;
                if((i + 1) == relations->distance){
                    level->tiles[start->y][start->x - i - 1][0] = createTemplateTile(V_WALL_TILE);
                    continue;
                }

                if(i != 0){
                    level->tiles[start->y + 1][start->x - i][0] = createTemplateTile(H_WALL_TILE);
                    level->tiles[start->y - 1][start->x - i][0] = createTemplateTile(H_WALL_TILE);
                } else {
                    level->tiles[start->y][start->x + 1][0] = createTemplateTile(V_WALL_TILE);
                }
            }
            free(currentPosition);
            break;

        case SOUTH:
            for (i = 0; i < relations->distance; i++){
                level->tiles[start->y + i][start->x][0] = createTemplateTile(FLOOR_TILE);

                currentPosition->y = start->y + i;
                currentPosition->x = start->x;

                wallCollision = positionInAnyWall(currentPosition, level);
                if (wallCollision > 0){
                    tunnelThroughWall(currentPosition, wallCollision, level);
                    continue;
                }

                if (positionInAnyRoom(currentPosition, level) == 1)
                    continue;
                if ((i + 1) == relations->distance){
                    level->tiles[start->y + i + 1][start->x][0] = createTemplateTile(H_WALL_TILE);
                    continue;
                }

                if (i != 0){
                    level->tiles[start->y + i][start->x - 1][0] = createTemplateTile(V_WALL_TILE);
                    level->tiles[start->y + i][start->x + 1][0] = createTemplateTile(V_WALL_TILE);

                } else {
                    level->tiles[start->y - 1][start->x][0] = createTemplateTile(H_WALL_TILE);
                }
            }
            free(currentPosition);
            break;

        case EAST:
            for (i = 0; i < relations->distance; i++){
                level->tiles[start->y][start->x + i][0] = createTemplateTile(FLOOR_TILE);

                currentPosition->y = start->y;
                currentPosition->x = start->x + i;

                wallCollision = positionInAnyWall(currentPosition, level);
                if (wallCollision > 0){
                    tunnelThroughWall(currentPosition, wallCollision, level);
                    continue;
                }

                if (positionInAnyRoom(currentPosition, level) == 1)
                    continue;
                if((i + 1) == relations->distance){
                    level->tiles[start->y][start->x + i + 1][0] = createTemplateTile(V_WALL_TILE);
                    continue;
                }

                if(i != 0){
                    level->tiles[start->y + 1][start->x + i][0] = createTemplateTile(H_WALL_TILE);
                    level->tiles[start->y - 1][start->x + i][0] = createTemplateTile(H_WALL_TILE);
                } else {
                    level->tiles[start->y][start->x - 1][0] = createTemplateTile(V_WALL_TILE);
                }
            }
            free(currentPosition);
            break; 
    }
    return 0;
}