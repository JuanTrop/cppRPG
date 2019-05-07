#include<iostream>
#include"Game.hpp"
#include"Estructura.hpp"
Game *game = nullptr;
int main(int argc , char *argv[]){
    game = new Game();
    game->init("Juego",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,false);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    return EXIT_SUCCESS;
}
