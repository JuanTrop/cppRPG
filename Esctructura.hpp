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
void inicio(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
		std::cerr<<"SDL no pudo inciar, Error: "<<SDL_GetError();
	}
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT,0,&window,&renderer);
}
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
	std::vector< std::vector<int> > mat = {
		{0,256,512,768,1024,1280,1536,1792,2048,2304,2560,2816,3072,3328,3584,3840},
		{1,257,513,769,1025,1281,1537,1793,2049,2305,2561,2817,3073,3329,3585,3841},
		{2,258,514,770,1026,1282,1538,1794,2050,2306,2562,2818,3074,3330,3586,3842},
		{3,259,515,771,1027,1283,1539,1795,2051,2307,2563,2819,3075,3331,3587,3843},
		{4,260,516,772,1028,1284,1540,1796,2052,2308,2564,2820,3076,3332,3588,3844},
		{5,261,517,773,1029,1285,1541,1797,2053,2309,2565,2821,3077,3333,3589,3845},
		{6,262,518,774,1030,1286,1542,1798,2054,2310,2566,2822,3078,3334,3590,3846},
		{7,263,519,775,1031,1287,1543,1799,2055,2311,2567,2823,3079,3335,3591,3847},
		{8,264,520,776,1032,1288,1544,1800,2056,2312,2568,2824,3080,3336,3592,3848},
		{9,265,521,777,1033,1289,1545,1801,2057,2313,2569,2825,3081,3337,3593,3849},
		{10,266,522,778,1034,1290,1546,1802,2058,2314,2570,2826,3082,3338,3594,3850},
		{11,267,523,779,1035,1291,1547,1803,2059,2315,2571,2827,3083,3339,3595,3851},
		{12,268,524,780,1036,1292,1548,1804,2060,2316,2572,2828,3084,3340,3596,3852},
		{13,269,525,781,1037,1293,1549,1805,2061,2317,2573,2829,3085,3341,3597,3853},
		{14,270,526,782,1038,1294,1550,1806,2062,2318,2574,2830,3086,3342,3598,3854},
		{15,271,527,783,1039,1295,1551,1807,2063,2319,2575,2831,3087,3343,3599,3855}
	};
	std::vector< std::vector<uint32_t> > res;
	for(int i=0;i<16;i++){
		std::vector<uint32_t> aux;
		res.push_back(aux);
		for(int j=0;j<16;j++){
			mat[i][j]+=16*n;
			res[i].push_back(sprite.at(mat[i][j]));
		}
	}
	return res;
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