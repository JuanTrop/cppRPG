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
void inicio(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
		std::cerr<<"SDL no pudo inciar, Error: "<<SDL_GetError();
	}
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_WIDTH,0,&window,&renderer);
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
std::vector< std::vector<uint32_t> > chunk (int n){
	std::vector< std::vector<int> > mat = {
		{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
		{256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271},
		{512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527},
		{768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783},
		{1024,1025,1026,1027,1028,1029,1030,1031,1032,1033,1034,1035,1036,1037,1038,1039},
		{1280,1281,1282,1283,1284,1285,1286,1287,1288,1289,1290,1291,1292,1293,1294,1295},
		{1536,1537,1538,1539,1540,1541,1542,1543,1544,1545,1546,1547,1548,1549,1550,1551},
		{1792,1793,1794,1795,1796,1797,1798,1799,1800,1801,1802,1803,1804,1805,1806,1807},
		{2048,2049,2050,2051,2052,2053,2054,2055,2056,2057,2058,2059,2060,2061,2062,2063},
		{2304,2305,2306,2307,2308,2309,2310,2311,2312,2313,2314,2315,2316,2317,2318,2319},
		{2560,2561,2562,2563,2564,2565,2566,2567,2568,2569,2570,2571,2572,2573,2574,2575},
		{2816,2817,2818,2819,2820,2821,2822,2823,2824,2825,2826,2827,2828,2829,2830,2831},
		{3072,3073,3074,3075,3076,3077,3078,3079,3080,3081,3082,3083,3084,3085,3086,3087},
		{3328,3329,3330,3331,3332,3333,3334,3335,3336,3337,3338,3339,3340,3341,3342,3343},
		{3584,3585,3586,3587,3588,3589,3590,3591,3592,3593,3594,3595,3596,3597,3598,3599},
		{3840,3841,3842,3843,3844,3845,3846,3847,3848,3849,3850,3851,3852,3853,3854,3855}
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
struct Data{
	//Puede ser entidad fija, paso, obstaculo, etc
	std::string type;
	Data(std::string type){
		this->type = type;
	}
	

};
struct Capa{
	std::vector< std::vector<Data>> data;
	Capa(int x, int y){

	}
};
struct Mapeo{
	std::vector<Capa> capa;
};
bool loadMap(){
	//Dibujar capas de mapeo
	return true;
}
bool executeGame(){
	
}
bool close(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}