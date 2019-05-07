#ifndef GAME_HPP
#define GAME_HPP
#include <SDL.h>
#include "sprite.h"
class Game{
    public:
        Game(){}
        ~Game(){}   
        void init(const char* title, int x, int y, int width, int height, bool fullscreen){
            if(SDL_Init(SDL_INIT_EVERYTHING)==0){
                std::cout<<"Juego ha arrancado!"<<std::endl;
                window = SDL_CreateWindow(title,x,y,width,height,fullscreen?SDL_WINDOW_FULLSCREEN:0);
                if(window){std::cout<<"Se ha creado la ventana"<<std::endl;}
                renderer = SDL_CreateRenderer(window,-1,0);
                if(renderer){
                    SDL_SetRenderDrawColor(renderer,255,255,255,255);
                    std::cout<<"Se ha creado el renderizador"<<std::endl;
                }
                isRunning = true;
            }else{isRunning=false;}
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
            cnt++;
            std::cout<<cnt<<std::endl;
        }
        void render(){
            SDL_RenderClear(renderer);
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
        int cnt = 0;
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
};
#endif
