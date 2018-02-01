#ifndef DECORACIONES_H
#define DECORACIONES_H

#include "representable.h"

class Granja:public Representable
{
	virtual unsigned int obtener_recurso() const {return 1;}
	virtual unsigned int obtener_alpha() const {return 255;}

	virtual void configurar_posicion(SDL_Rect& r) const
	{
		r.x=20;
		r.y=490;
		r.w=90;
		r.h=50;
	}
	
	virtual void configurar_recorte(SDL_Rect& r) const
	{
		r.x=29;
		r.y=0;
		r.w=90;
		r.h=50;
	}

	public:

	Granja():Representable() {}
};

class Fondo:public Representable
{
	private:

	const static unsigned int W=800;
	const static unsigned int H=180;

	public:

	virtual unsigned int obtener_alpha() const {return 255;}
	virtual unsigned int obtener_recurso() const {return 2;}

	virtual void configurar_posicion(SDL_Rect& r) const
	{
		r.x=0;
		r.y=Definiciones::H_AREA - H;
		r.w=W;
		r.h=H;
	}
	
	virtual void configurar_recorte(SDL_Rect& r) const
	{
		r.x=0;
		r.y=0;
		r.w=W;
		r.h=H;
	}

	public:

	Fondo():Representable() {}
};

#endif
