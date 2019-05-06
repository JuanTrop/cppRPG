#include"Esctructura.hpp"
int main(int argc , char *argv[]){
    inicio();
    //Permitir sobreposición
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer,piskel.R,piskel.G,piskel.B,piskel.A);
    SDL_RenderClear(renderer);
    cargarTexturas();
    draw();
    SDL_RenderPresent(renderer);
    while(true){if(SDL_PollEvent(&event)&&event.type==SDL_QUIT){break;}}
    return close();
}