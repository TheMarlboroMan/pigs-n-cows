#include "textura.h"

using namespace DLibV;

Textura::Textura(const SDL_Renderer * renderer, SDL_Surface * superficie):
	textura(DLibV::Utilidades_graficas_SDL::cargar_textura_desde_superficie(renderer, superficie)),
	renderer(renderer), formato(0), w(0), h(0), acceso(0)
{
	inferir_propiedades();
}

Textura::Textura(const SDL_Renderer * renderer, SDL_Texture * t):
	textura(t), renderer(renderer), formato(0), w(0), h(0), acceso(0)
{
	inferir_propiedades();
}


Textura::Textura(const Textura& t):
	textura(t.textura), renderer(t.renderer), formato(t.formato), w(t.w), h(t.h), acceso(t.acceso)
{

}

Textura::~Textura()
{
	SDL_DestroyTexture(textura);
	renderer=NULL;
}
	
Textura& Textura::operator=(const Textura& t)
{
	renderer=t.renderer;
	formato=t.formato;
	w=t.w;
	h=t.h;
	acceso=t.acceso;
	textura=DLibV::Utilidades_graficas_SDL::copiar_textura(renderer, t.textura);
	return *this;
}
