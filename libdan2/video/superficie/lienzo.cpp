#include "lienzo.h"

using namespace DLibV;

Lienzo::Lienzo():Superficie()
{
	this->generado=false;
}

Lienzo::Lienzo(const Lienzo& p_otro)
{
	Superficie::operator=(p_otro);
	this->generado=p_otro.generado;
}

Lienzo::~Lienzo()
{	

}

Lienzo * Lienzo::generar_nuevo(int p_ancho, int p_alto, const SDL_Surface * superficie)
{
	return generar_nuevo(p_ancho, p_alto, superficie->format->BitsPerPixel, superficie->format->Rmask, superficie->format->Gmask, superficie->format->Bmask, superficie->format->Amask);
}

Lienzo * Lienzo::generar_nuevo(int p_ancho, int p_alto, int bpp, Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
	Lienzo * resultado=NULL;
	resultado=new Lienzo();
	resultado->generado=true;
	resultado->superficie=SDL_CreateRGBSurface(0, p_ancho, p_alto, bpp, r, g, b, a);
	return resultado;
}

Lienzo& Lienzo::operator=(const Lienzo& p_otro)
{
	Superficie::operator=(p_otro);
	this->generado=p_otro.generado;
	return *this;
}

