#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<sstream>
#include<SDL2/SDL.h>
#include"sprite.h"
SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;
const int WINDOW_WIDTH=600;
const int WINDOW_HEIGHT=400;
//Vector de texturas
std::vector< std::vector< std::vector< uint32_t > > > texturas;
template <typename T>
std::string Str(const T & t){
	std::ostringstream os;
	os << t;
	return os.str();
}
struct Piskel {
	uint8_t R,G,B,A;
	Piskel(uint32_t data){
		R = data; G = data>>8; B = data>>16; A = data>>24;
	}
	Piskel(uint8_t r,uint8_t g,uint8_t b,uint8_t a){
		R=r;G=g;B=b;A=a;
	}
    void update(uint32_t data){
        R = data; G = data>>8; B = data>>16; A = data>>24;
    }
	std::string show(){
		return Str(unsigned(R))+" "+Str(unsigned(G))+" "+Str(unsigned(B))+" "+Str(unsigned(A));
	}
};
Piskel piskel = Piskel(0xff00ff00);
std::vector< std::vector<uint32_t> > chunk(int n){
	std::vector< std::vector<uint32_t> > res(16,std::vector<uint32_t>(16,0));
	int i=0 , j=0;
	std::for_each(res.begin(),res.end(),[&i,&j,n](std::vector<uint32_t>& res){
		j=0;
		std::for_each(res.begin(),res.end(),[i,&j,n](uint32_t& res){
			res = sprite.at((i+256*j)+16*n);
			j++;
		});
		i++;
	});
	return res;
}
void inicio(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
		std::cerr<<"SDL no pudo inciar, Error: "<<SDL_GetError();
	}
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT,0,&window,&renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer,piskel.R,piskel.G,piskel.B,piskel.A);
    SDL_RenderClear(renderer);
}
//Almacenar texturas en memoria
void cargarTexturas(){for(int i=0; i<NumTexturas; i++){texturas.push_back(chunk(i));}}

//Dibuja
void draw(){
	std::for_each(texturas.begin(),texturas.end(),[](std::vector<std::vector<uint32_t>> texturas)->void {
		static int n = 0;
		for (int i = 0; i < 16; i++){
			for(int j = 0; j < 16; j++){
				piskel.update(texturas[i][j]);
				SDL_SetRenderDrawColor(renderer,piskel.R,piskel.G,piskel.B,piskel.A);
				SDL_RenderDrawPoint(renderer,i+16*(n),j);
			}
		}
		n++;
	});
}

int menu(){
	return 1;
}
void jugar(){
}
void cargar_partida(){
}
void opciones(){
}
bool executeGame(){
	while(true){
		switch(menu()){
			case 1:jugar();break;
			case 2:cargar_partida();break;
			case 3:opciones();break;
			default:return 3;
		}
	}
}
bool close(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}