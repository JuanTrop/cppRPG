#include"Esctructura.hpp"
int main(){
    inicio();
    Piskel piskel = Piskel(0xff00ff00);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer,piskel.R,piskel.G,piskel.B,piskel.A);
    SDL_RenderClear(renderer);
    std::vector< std::vector<uint32_t> > aux = chunk(0);
    for(int x = 0; x<sprite.size()/256;x++){
        aux = chunk(x);
        for (int i = 0; i < 16; i++){
            for(int j = 0; j< 16; j++){
                piskel.update(aux[j][i]);
                SDL_SetRenderDrawColor(renderer,piskel.R,piskel.G,piskel.B,piskel.A);
                SDL_RenderDrawPoint(renderer,i+16*x,j);
            }
        }
    }
    SDL_RenderPresent(renderer);
    while(true){if(SDL_PollEvent(&event)&&event.type==SDL_QUIT){break;}}
    return close();
}