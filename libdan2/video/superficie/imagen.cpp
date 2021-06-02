#include "imagen.h"

using namespace DLibV;

//Toma propiedad del puntero a partir de este momento..

Imagen::Imagen(SDL_Surface * p_superficie):Superficie()
{
	this->superficie=p_superficie;
}

Imagen::Imagen(char const * p_ruta, SDL_Window * ventana):Superficie()
{
	this->superficie=Utilidades_graficas_SDL::cargar_imagen(p_ruta, ventana);
}

Imagen::Imagen(std::string const & p_ruta, SDL_Window * ventana):Superficie()
{
	this->superficie=Utilidades_graficas_SDL::cargar_imagen(p_ruta.c_str(), ventana);
}

Imagen& Imagen::operator=(const Imagen& p_otro)
{
	Superficie::operator=(p_otro);
	return *this;
}

Imagen::Imagen(const Imagen& p_otro)
{
	Superficie::operator=(p_otro);
}


Imagen::~Imagen()
{

}
