#ifndef SUPERFICIE_SDL_H
#define SUPERFICIE_SDL_H

#include <SDL2/SDL.h>
//#include <string>
//#include <fstream>
#include <iostream>
#include "../utilidades_graficas_sdl/utilidades_graficas_sdl.h"

//Wrapper para una superficie... La vamos a usar para algunas cosas muy
//concretas, como usar fuentes de bitmap.

namespace DLibV
{

class Superficie
{
	protected:

	SDL_Surface * superficie;
	Uint32 color_transparencia;
	bool transparencia_activa;

	public:

	enum T_TIPOS{T_IMAGEN=1, T_LIENZO=2};
	
	Superficie();
	virtual ~Superficie();
	Superficie& operator=(const Superficie&);
	
	SDL_Surface * acc_superficie() const {return this->superficie;}
	SDL_Surface * acc_superficie() {return this->superficie;}

	Uint32 color(unsigned int r, unsigned int g, unsigned int b);

	void establecer_transparencia(Uint32=0);
	void establecer_transparencia(Uint8=0, Uint8=255, Uint8=255);
	void rellenar(Uint8=0, Uint8=255, Uint8=255);
	void rellenar(Uint32 c);
	void limpiar_transparencia();
	void establecer_alpha(Uint8);
	void copiar_desde(Superficie const&);
	void copiar_desde(Superficie const&, SDL_Rect);
	void copiar_desde(Superficie const&, SDL_Rect, SDL_Rect);
	bool es_transparencia_activa() const {return this->transparencia_activa;}
	Uint32 acc_color_transparencia() const {return this->color_transparencia;}
	unsigned int acc_w() const {return superficie->w;}
	unsigned int acc_h() const {return superficie->h;}

	//Resulta ridículo que esto es lo único que hace abstracta a esta clase :D.
	virtual int obtener_tipo()=0;
	virtual bool es_preparado()=0;
};

} //Fin namespace DLibV
#endif
