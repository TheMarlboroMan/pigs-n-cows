#ifndef REPRESENTABLE_H
#define REPRESENTABLE_H

class Representable
{
	public:

	Representable() {}

	virtual unsigned int obtener_alpha() const =0;
	virtual unsigned int obtener_recurso() const =0;
	virtual void configurar_posicion(SDL_Rect&) const =0;
	virtual void configurar_recorte(SDL_Rect&) const =0;
};


#endif
