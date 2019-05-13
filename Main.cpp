#include <iostream>
#include "Game.hpp"
Game *game = nullptr;
int main(int argc , char *argv[]){
    uint32_t frameStart;
    int frameTime;
    game = new Game();
    game->init("Juego",SCREEN_WIDTH,SCREEN_HEIGHT,false);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
        SDL_Delay(1.3);
        if(game->cnt==(800-88)){break;}
    }
    game->clean();
    return EXIT_SUCCESS;
}
