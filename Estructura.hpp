#ifndef ESTRUCTURA_HPP
#define ESTRUCTURA_HPP
#include <SDL2/SDL.h>
#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>
#include "sprite.h"
const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;
class Matriz{
		size_t ancho;
		size_t altura;
		std::vector<uint32_t> vec;
	public:
		Matriz(size_t x,size_t y)
		:	ancho(x),
			altura(y),
			vec(altura*ancho)
		{}
		uint32_t &celda(size_t x, size_t y) noexcept{return vec[y * ancho + x];}
		const uint32_t &celda(size_t x, size_t y) const noexcept{return vec[y * ancho + x];}
		//Para usar métodos de vectores
		std::vector<uint32_t>& raw(){return vec;}
		size_t getAncho(){return ancho;}
		size_t getAltura(){return altura;}
};
	uint8_t Rojo(uint32_t data){return (uint8_t)(data);}
	uint8_t Verde(uint32_t data){return (uint8_t)(data>>8);}
	uint8_t Azul(uint32_t data){return (uint8_t)(data>>16);}
	uint8_t Alfa(uint32_t data){return (uint8_t)(data>>24);}
/*
----Función Eliminada hasta realizar compatible con Matriz----
Matriz escalado(Matriz m, int x, int y){
	m.flip(x<0,y<0);
	Matriz res(m.getAncho()*(std::abs(x)+1),m.getAltura()*(std::abs(y)+1));	
	std::for_each(std::begin(m.raw()),std::end(m.raw()),[&res,x](uint32_t dato){
		for(size_t i=0; i<std::abs(x);i++){res.raw().emplace_back(dato);}
	});
	return res;
}*/
void flip(Matriz &vec, bool x, bool y){
	if(x!=y){
		for(size_t i=0;i<vec.raw().size();i+=vec.getAncho()){
			std::reverse(vec.raw().begin()+i,vec.raw().begin()+i+vec.getAncho());
		}
	}
	if(y){std::reverse(vec.raw().begin(),vec.raw().end());}
}
Matriz scale2x(Matriz mat){
	Matriz aux(mat.getAncho()*2,mat.getAltura()*2);
	uint32_t B,D,E,F,H;
	uint32_t *E0,*E1,*E2,*E3;
	for(size_t i=0; i<mat.getAltura();i++){
		for(size_t j=0; j<mat.getAncho();j++){
			E0 = &aux.celda(2*i,2*j);	E1 = &aux.celda(2*i,2*j+1);
			E2 = &aux.celda(2*i+1,2*j);	E3 = &aux.celda(2*i+1,2*j+1);
			E = mat.celda(i,j);
			B = i==0?E:mat.celda(i-1,j);					D = j==0?E:mat.celda(i,j-1);
			F = j==(mat.getAncho()-1)?E:mat.celda(i,j+1);	H = i==(mat.getAltura()-1)?E:mat.celda(i+1,j);
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
Matriz scale3x(Matriz mat){
	Matriz aux(mat.getAncho()*3,mat.getAltura()*3);
	uint32_t A,B,C,D,E,F,G,H,I;
	uint32_t *E0,*E1,*E2,*E3,*E4,*E5,*E6,*E7,*E8;
	for(size_t i=0; i<mat.getAltura();i++){
		for(size_t j=0; j<mat.getAncho();j++){
			E0 = &aux.celda(3*i,3*j);	E1 = &aux.celda(3*i,3*j+1);		E2 = &aux.celda(3*i,3*j+2);
			E3 = &aux.celda(3*i+1,3*j);	E4 = &aux.celda(3*i+1,3*j+1);	E5 = &aux.celda(3*i+1,3*j+2);
			E6 = &aux.celda(3*i+2,3*j);	E7 = &aux.celda(3*i+2,3*j+1);	E8 = &aux.celda(3*i+2,3*j+2);
			E = mat.celda(i,j);
			A = i==0|j==0?E:mat.celda(i-1,j-1);
			B = i==0?E:mat.celda(i-1,j);
			C = (i==0|j==(mat.getAncho()-1))?E:mat.celda(i-1,j+1);
			D = j==0?E:mat.celda(i,j-1);
			F = j==(mat.getAncho()-1)?E:mat.celda(i,j+1);
			G = (i==(mat.getAltura()-1)|j==0)?E:mat.celda(i+1,j-1);
			H = i==(mat.getAltura()-1)?E:mat.celda(i+1,j);
			I = (i==(mat.getAltura()-1)|j==(mat.getAncho()-1))?E:mat.celda(i+1,j+1);
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
Matriz chunk(size_t n){
	Matriz res(16,16);
	for(size_t i = 0 ; i < 16; i++){
		for(size_t j = 0 ; j < 16; j++){
			res.celda(i,j) = sprite[(i+16*(16*j+(n>=sprite.size()/256?0:n)))];
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
		//std::vector<std::vector<uint32_t>> getImg(){return flip(chunk(textura),giroX,giroY);}
		int musica_fondo;
		int musica_batalla;
		int musica_jefe;
};
struct nivel{
	std::vector<std::vector<bloque>> mapa;

};
#endif /*ESTRUCTURA_HPP*/