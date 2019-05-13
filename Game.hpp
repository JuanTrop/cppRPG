#ifndef GAME_HPP
#define GAME_HPP
#include "Estructura.hpp"
class Game{
    public:
        Game(){}
        ~Game(){}   
        int cnt = 0;
        void init(const char* title, int width, int height, bool fullscreen){
            if(SDL_Init(SDL_INIT_EVERYTHING)==0){
                std::cout<<"Juego ha arrancado!"<<std::endl;
                window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,fullscreen?SDL_WINDOW_FULLSCREEN:0);
                if(window){std::cout<<"Se ha creado la ventana"<<std::endl;}
                renderer = SDL_CreateRenderer(window,-1,0);
                SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
                if(renderer){
                    SDL_SetRenderDrawColor(renderer,255,255,255,255);
                    std::cout<<"Se ha creado el renderizador"<<std::endl;
                }
                isRunning = true;
            }else{
                isRunning=false;
            }
        }
        void handleEvents(){
            SDL_Event event;
            SDL_PollEvent(&event);
            switch(event.type){
                case SDL_QUIT:isRunning = false;break;
                default:break;
            }
        }
        void update(){
            //Refrescar mapa
            //cnt++;std::cout<<cnt<<std::endl;
        }
        void render(){
            //std::vector<std::vector<uint32_t>> f = escalado(scale2x(scale2x(scale2x(chunk(1)))),0,0);
            std::vector<std::vector<uint32_t>> f = escalado(scale3x(scale2x(chunk(1))),0,0);
            SDL_SetRenderDrawColor(renderer,255,255,255,0);
            SDL_RenderClear(renderer);
            for(size_t i=0; i<f.size(); i++){
                for(size_t j=0; j<f[i].size(); j++){
                    SDL_SetRenderDrawColor(renderer,Rojo(f[i][j]),Verde(f[i][j]),Azul(f[i][j]),Alfa(f[i][j]));
                    SDL_RenderDrawPoint(renderer,i+cnt,j+cnt/2);
                }
            }
            cnt+=cnt>(800-88)?0:1;
            SDL_RenderPresent(renderer);
        }
        void clean(){
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
            std::cout<<"Juego cerrado"<<std::endl;
        }
        bool running(){return isRunning;}
    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::vector<std::vector<bloque>> mapa;
};
#endif
