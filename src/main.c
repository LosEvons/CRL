#include "stdio.h"

#include "curses.h"

#include "rogue.h"

int main(){
    int ch;
    int gameState = PLAYER_TURN;
    srand(time(NULL)); // seeding for random numbers
    screenSetUp();
    Level * level;
    level = initLevel(4);
    updateLevel(level);
    handleMainMenu(ch, gameState);

    while((ch = getch()) != 'q'){
        switch(gameState){
            case MAIN_MENU:
                gameState = handleMainMenu(ch, gameState);
                break;
            case PLAYER_TURN:
                handlePlayerTurn(ch, level);
                break;
        }
    }
    endwin();

    return 0;
}

int handlePlayerTurn(int ch, Level * level){
    // handling input
    Position * newPosition = handleMovementInput(ch, level->player);
    handlePlayerAction(newPosition, level->player, level);
    
    // rendering
    renderTiles(level);
    renderEntities(level);

    return 0;
}

int handleMainMenu(int ch, int gameState){
    renderMainMenu();
    int newGameState;
    newGameState = handleMainMenuInput(ch);
    if (newGameState)
        return newGameState;
    else
        return gameState;
}