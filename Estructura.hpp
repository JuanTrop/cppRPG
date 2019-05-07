#ifndef ESTRUCTURA_HPP
#define ESTRUCTURA_HPP

#include<SDL.h>
#include"sprite.h"

uint8_t Rojo(uint32_t data)	{return (uint8_t)(data);}
uint8_t Verde(uint32_t data){return (uint8_t)(data>>8);}
uint8_t Azul(uint32_t data)	{return (uint8_t)(data>>16);}
uint8_t Alfa(uint32_t data)	{return (uint8_t)(data>>24);}
std::vector< std::vector<uint32_t> > chunk(int n){
	std::vector< std::vector<uint32_t> > res(16,std::vector<uint32_t>(16,0));
	for(int i = 0 ; i < 16; i++){
		for(int j = 0 ; j < 16; j++){
			res[i][j] = sprite.at((i+256*j)+16*n);
		}
	}
	return res;
}
#endif /*ESTRUCTURA_HPP*/
