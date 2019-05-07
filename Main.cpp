#include"Esctructura.hpp"
int main(int argc , char *argv[]){
    inicio();
    cargarTexturas();
    draw();
    while(true){
        if(SDL_PollEvent(&event)&&event.type==SDL_QUIT){
            break;
        }else{
            //Hilo principal
        }
    }
    return close();
}