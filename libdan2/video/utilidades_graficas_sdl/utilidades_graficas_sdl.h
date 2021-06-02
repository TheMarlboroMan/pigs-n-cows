#ifndef Utilidades_graficas_SDL_H
#define Utilidades_graficas_SDL_H

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../herramientas/log_base/log_base.h"
#include "../../herramientas/herramientas/herramientas.h"
//#include "../../herramientas/debug/debug.h"

namespace DLibV
{

class Utilidades_graficas_SDL
{
	private:
	
	Utilidades_graficas_SDL()
	{
		//Ahahahaaaaaa!!!.
	}

	public:

	enum Inversion_superficie
	{
		HORIZONTAL=1,
		VERTICAL=2
	};

	static void mostrar_ocultar_cursor(bool);

	static SDL_Surface * nueva_superficie_formato(SDL_Surface const * origen);
	static SDL_Surface * nueva_superficie_formato(SDL_Surface const * origen, const SDL_Rect& caja, Uint32 flags=0, Uint32 color=0);
	static SDL_Surface * copiar_superficie(const SDL_Surface * origen);
	static SDL_Surface * copiar_superficie(const SDL_Surface * origen, const SDL_Rect& caja, Uint32 flags=0, Uint32 color=0);
	static SDL_Surface * cargar_imagen(const char *, const SDL_Window * ventana);
	static SDL_Texture * copiar_textura(const SDL_Renderer * renderer, const SDL_Texture * textura);
	static SDL_Texture * cargar_textura_desde_superficie(const SDL_Renderer * renderer, const SDL_Surface * superficie);
	static SDL_Texture * crear_textura(const SDL_Renderer * renderer, int pw, int ph, Uint32 pformat, int paccess=SDL_TEXTUREACCESS_TARGET);

	static Uint32 SDL_GetPixel(SDL_Surface *, int, int);
};

} //Fin namespace DLibV
#endif
