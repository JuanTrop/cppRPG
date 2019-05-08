#ifndef ESTRUCTURA_HPP
#define ESTRUCTURA_HPP

#include <SDL2/SDL.h>
#include <algorithm>
#include "sprite.h"
const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;
uint8_t Rojo(uint32_t data)	{return (uint8_t)(data);}
uint8_t Verde(uint32_t data){return (uint8_t)(data>>8);}
uint8_t Azul(uint32_t data)	{return (uint8_t)(data>>16);}
uint8_t Alfa(uint32_t data)	{return (uint8_t)(data>>24);}
template<class T>
std::vector<std::vector<T>> escalado(std::vector<std::vector<T>> matrix, int x, int y){
	std::vector<std::vector<T>> res;
	std::for_each(matrix.begin(),matrix.end(),[&res,y](std::vector<T>& vec){
		for(int i = 0; i <= y; i++){res.push_back(vec);}
	});
	std::for_each(res.begin(),res.end(),[x](std::vector<T>& vec){
		std::vector<T> aux;
		for(int i=0;i<vec.size();i++){
			for(int j=0;j<=x;j++){aux.push_back(vec[i]);}
		}
		vec = aux;
	});
	return res;
}

std::vector< std::vector<uint32_t> > chunk(int n){
	std::vector< std::vector<uint32_t> > res(16,std::vector<uint32_t>(16,0));
	for(int i = 0 ; i < 16; i++){
		for(int j = 0 ; j < 16; j++){
			res[i][j] = sprite.at(i+16*(16*j+n));
		}
	}
	return res;
}
#endif /*ESTRUCTURA_HPP*/
