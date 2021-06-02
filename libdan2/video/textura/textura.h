#ifndef TEXTURA_SDL_H
#define TEXTURA_SDL_H

#include <SDL2/SDL.h>
#include "../utilidades_graficas_sdl/utilidades_graficas_sdl.h"

/*En la clase Textura vamos a encapsular no sólo la extructura SDL_Texture
sino también un puntero al renderer para el cual ha sido creada. Esto es así
porque para algunas operaciones sobre la textura tenemos que tener la 
referencia al mismo. 

Esconderíamos todas estas cosas tras una interface que establece un modo de 
trabajo único. Los constructores son restrictivos a este respecto para 
asegurarnos de que respetamos la secuencia necesaria.*/

namespace DLibV
{

class Textura
{
	private:

	SDL_Texture * textura;
	const SDL_Renderer * renderer;
	Uint32 formato;
	/*unsigned*/ int w;
	/*unsigned*/ int h;
	/*unsigned*/ int acceso;

	void inferir_propiedades()
	{
		SDL_QueryTexture(textura, &formato, &acceso, &w, &h);
	}

	public:

	const SDL_Renderer * acc_renderer() const {return renderer;}

	const SDL_Texture * acc_textura() const {return textura;}
	SDL_Texture * ref_textura() {return textura;}

	Uint32 acc_formato() const {return formato;}
	unsigned int acc_w() const {return w;}
	unsigned int acc_h() const {return h;}
	unsigned int acc_acceso() const {return acceso;}

	Textura(const SDL_Renderer * renderer, SDL_Surface * superficie);
	Textura(const SDL_Renderer * renderer, SDL_Texture * t);
	Textura(const Textura& t);
	~Textura();
	Textura& operator=(const Textura& t);
};

}

#endif
