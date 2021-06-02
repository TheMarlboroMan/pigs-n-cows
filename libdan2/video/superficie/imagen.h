#ifndef IMAGEN_SDL_H
#define IMAGEN_SDL_H

#include "superficie.h"

/*
La imagen es un recurso gráfico que carga un bitmap. Más fácil imposible.
*/

namespace DLibV
{

class Imagen:public Superficie
{
	public:

	Imagen(SDL_Surface *);
	Imagen(char const *, SDL_Window *);
	Imagen(std::string const&, SDL_Window *);
	Imagen(const Imagen&);
	Imagen& operator=(const Imagen&);
	~Imagen();

	int obtener_tipo(){return Superficie::T_IMAGEN;}
	bool es_preparado() {return this->superficie!=NULL;}
};

} //Fin namespace DLibV

#endif
