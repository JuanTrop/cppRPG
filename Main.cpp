#include"Esctructura.hpp"
int main(int argc , char *argv[]){
    inicio();
    cargarTexturas();
    draw();
    SDL_RenderPresent(renderer);
    while(true){
        if(SDL_PollEvent(&event)&&event.type==SDL_QUIT){
            break;
        }
    }
    return close();
}