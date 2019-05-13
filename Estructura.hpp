#ifndef ESTRUCTURA_HPP
#define ESTRUCTURA_HPP
#include <SDL2/SDL.h>
#include <algorithm>
#include <utility>
#include "sprite.h"
const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;
uint8_t Rojo(uint32_t data)	{return (uint8_t)(data);}
uint8_t Verde(uint32_t data){return (uint8_t)(data>>8);}
uint8_t Azul(uint32_t data)	{return (uint8_t)(data>>16);}
uint8_t Alfa(uint32_t data)	{return (uint8_t)(data>>24);}
template<class T>
std::vector<std::vector<T>> flip(std::vector< std::vector<T> > m, bool x, bool y){
	if(x){std::reverse(std::begin(m),std::end(m));}
	if(y){for(size_t i=0; i<m.size();i++){std::reverse(std::begin(m[i]),std::end(m[i]));}}
	return m;
}
template<class T>
std::vector<std::vector<T>> escalado(std::vector<std::vector<T>> matrix, int x, int y){
	matrix = flip(matrix,x<0,y<0);
	std::vector<std::vector<T>> res;
	std::for_each(std::begin(matrix),std::end(matrix),[&res,y](std::vector<T>& vec){
		for(size_t i = 0; i <= std::abs(y); i++){
			res.push_back(vec);
		}
	});
	std::for_each(std::begin(res),std::end(res),[x](std::vector<T>& vec){
		std::vector<T> aux;
		for(size_t i = 0; i < vec.size(); i++){
			for(size_t j = 0; j <= std::abs(x); j++){
				aux.push_back(vec[i]);
			}
		}
		vec = aux;
	});
	return res;
}
template<class T>
std::vector<std::vector<T>> scale2x(std::vector<std::vector<T>> mat){
	std::vector<std::vector<T>> aux(mat.size()*2,std::vector<T>(mat[0].size()*2));
	T B,D,E,F,H;
	T *E0,*E1,*E2,*E3;
	for(size_t i=0; i<mat.size();i++){
		for(size_t j=0; j<mat[i].size();j++){
			E0 = &aux[2*i][2*j];	E1 = &aux[2*i][2*j+1];
			E2 = &aux[2*i+1][2*j];	E3 = &aux[2*i+1][2*j+1];
			E = mat[i][j];
			B = i==0?E:mat[i-1][j];	D = j==0?E:mat[i][j-1];
			F = j==(mat[i].size()-1)?E:mat[i][j+1];	H = i==(mat.size()-1)?E:mat[i+1][j];
			if (B != H && D != F) {
				*E0 = D == B ? D : E;
				*E1 = B == F ? F : E;
				*E2 = D == H ? D : E;
				*E3 = H == F ? F : E;
			}else {*E0 = *E1 = *E2 = *E3 = E;}
		}
	}
	return aux;
}
template<class T>
std::vector<std::vector<T>> scale3x(std::vector<std::vector<T>> mat){
std::vector<std::vector<T>> aux(mat.size()*3,std::vector<T>(mat[0].size()*3));
	T A,B,C,D,E,F,G,H,I;
	T *E0,*E1,*E2,*E3,*E4,*E5,*E6,*E7,*E8;
	for(size_t i=0; i<mat.size();i++){
		for(size_t j=0; j<mat[i].size();j++){
			E0 = &aux[3*i][3*j];	E1 = &aux[3*i][3*j+1];	E2 = &aux[3*i][3*j+2];
			E3 = &aux[3*i+1][3*j];	E4 = &aux[3*i+1][3*j+1];	E5 = &aux[3*i+1][3*j+2];
			E6 = &aux[3*i+2][3*j];	E7 = &aux[3*i+2][3*j+1];	E8 = &aux[3*i+2][3*j+2];
			E = mat[i][j];
			A = i==0|j==0?E:mat[i-1][j-1];
			B = i==0?E:mat[i-1][j];
			C = (i==0|j==(mat[i].size()-1))?E:mat[i-1][j+1];
			D = j==0?E:mat[i][j-1];
			F = j==(mat[i].size()-1)?E:mat[i][j+1];
			G = (i==(mat.size()-1)|j==0)?E:mat[i+1][j-1];
			H = i==(mat.size()-1)?E:mat[i+1][j];
			I = (i==(mat.size()-1)|j==(mat[i].size()-1))?E:mat[i+1][j+1];
			if (B != H && D != F) {
				*E0 = D == B ? D : E;
				*E1 = (D == B && E != C) || (B == F && E != A) ? B : E;
				*E2 = B == F ? F : E;
				*E3 = (D == B && E != G) || (D == H && E != A) ? D : E;
				*E4 = E;
				*E5 = (B == F && E != I) || (H == F && E != C) ? F : E;
				*E6 = D == H ? D : E;
				*E7 = (D == H && E != I) || (H == F && E != G) ? H : E;
				*E8 = H == F ? F : E;
			} else {
				*E0 = *E1 = *E2 = *E3 = *E4 = *E5 = *E6 = *E7 = *E8 = E;
			}
		}
	}
	return aux;
}
std::vector< std::vector<uint32_t> > chunk(size_t n){
	std::vector< std::vector<uint32_t> > res(16,std::vector<uint32_t>(16,0));
	for(size_t i = 0 ; i < 16; i++){
		for(size_t j = 0 ; j < 16; j++){
			res[i][j] = sprite.at(i+16*(16*j+(n>=sprite.size()/256?0:n)));
		}
	}
	return res;
}
struct bloque{
	private:
		bool giroX, giroY, colision;;
		int textura;
	public:
		bloque(int textura, bool giroX, bool giroY, int musica_fondo, int musica_batalla, int musica_jefe){
			this->textura=textura;
			this->giroX=giroX;	this->giroY=giroY;
			this->musica_jefe = musica_jefe;
			this->musica_batalla = musica_batalla;
			this->musica_jefe = musica_jefe;
		}
		~bloque(){
			giroX = giroY = colision = false;
			textura = musica_fondo = musica_batalla = musica_jefe = 0;
			delete &giroX, &giroY, &colision, &textura, &musica_fondo, &musica_batalla, &musica_jefe;
		};
		std::vector<std::vector<uint32_t>> getImg(){
			return flip(chunk(textura),giroX,giroY);
		}
		int musica_fondo;
		int musica_batalla;
		int musica_jefe;
};
struct nivel{
	std::vector<std::vector<bloque>> mapa;

};
#endif /*ESTRUCTURA_HPP*/