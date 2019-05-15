#include <iostream>
#include "Game.hpp"
Game *game = nullptr;
int main(int argc , char *argv[]){
    game = new Game();
    game->init("Juego",SCREEN_WIDTH,SCREEN_HEIGHT,false);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
        if(game->cnt==(1)){break;}
    }
    game->clean();
    return EXIT_SUCCESS;
}
