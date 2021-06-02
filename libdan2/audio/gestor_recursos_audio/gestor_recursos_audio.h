#ifndef GESTOR_RECURSOS_SONIDO_H
#define GESTOR_RECURSOS_SONIDO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../sonido/sonido.h"
#include "../musica/musica.h"
#include "../../herramientas/templates/gestor_mapa_static.h"

namespace DLibA
{

class Gestor_recursos_audio
{
	private:

	class Gestor_recursos_sonido:public DLibH::Gestor_mapa_static<int, Sonido *>
	{
		public:

		static int insertar(int p_clave, const char * p_ruta);
		static Sonido * obtener(int p_clave);
	};

	class Gestor_recursos_musica:public DLibH::Gestor_mapa_static<int, Musica *>
	{
		public:

		static int insertar(int p_clave, const char * p_ruta);
		static Musica * obtener(int p_clave);
	};

	Gestor_recursos_audio();

	static Gestor_recursos_sonido sonidos;
	static Gestor_recursos_musica musicas;
	
	public:

	static void liberar();
	static int insertar_sonido(int p_clave, const char * p_ruta);
	static Sonido * obtener_sonido(int p_clave);
	static int insertar_musica(int p_clave, const char * p_ruta);
	static Musica * obtener_musica(int p_clave);
};

}

#endif
