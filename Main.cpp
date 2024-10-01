#include "GameWindow.h"

int main(){
    GameWindow *DodgeGame = new GameWindow();
    DodgeGame->game_play();

    delete DodgeGame;
    return 0;
}
