#ifndef PRIMITIVA_GRAFICA_CAJA_H
#define PRIMITIVA_GRAFICA_CAJA_H

/*
Simplemente hace un fillrect. Simple, rápido y efectivo.
*/

#include "../representacion_primitiva.h"

namespace DLibV
{
class Representacion_primitiva_caja:public Representacion_primitiva
{
	private:
	
	protected:

	void preparar_posicion();

	public:
	
	void preparar();
	bool es_estatica() const=0;

	bool volcado(SDL_Renderer *);
	bool volcado(SDL_Renderer *, const SDL_Rect&, const SDL_Rect&, int=0, int=0);

	Representacion_primitiva_caja(const SDL_Rect&, Uint8, Uint8, Uint8);
	Representacion_primitiva_caja(const Representacion_primitiva_caja&);
	virtual ~Representacion_primitiva_caja();
	Representacion_primitiva_caja& operator=(const Representacion_primitiva_caja&);
};

class Representacion_primitiva_caja_dinamica:public Representacion_primitiva_caja
{
	public:

	bool es_estatica() const {return false;}

	Representacion_primitiva_caja_dinamica(const SDL_Rect& p_pos, Uint8 pr, Uint8 pg, Uint8 pb):Representacion_primitiva_caja(p_pos, pr, pg, pb){}
	Representacion_primitiva_caja_dinamica(const Representacion_primitiva_caja_dinamica& p_otra):Representacion_primitiva_caja(p_otra) {}
	virtual ~Representacion_primitiva_caja_dinamica() {}
	Representacion_primitiva_caja_dinamica& operator=(const Representacion_primitiva_caja_dinamica& p_otro)
	{
		Representacion_primitiva_caja::operator=(p_otro);
		return *this;
	}
};

class Representacion_primitiva_caja_estatica:public Representacion_primitiva_caja
{
	public:

	bool es_estatica() const {return true;}

	Representacion_primitiva_caja_estatica(const SDL_Rect& p_pos, Uint8 pr, Uint8 pg, Uint8 pb):Representacion_primitiva_caja(p_pos, pr, pg, pb){}
	Representacion_primitiva_caja_estatica(const Representacion_primitiva_caja_estatica& p_otra):Representacion_primitiva_caja(p_otra) {}
	virtual ~Representacion_primitiva_caja_estatica() {}
	Representacion_primitiva_caja_estatica& operator=(const Representacion_primitiva_caja_estatica& p_otro)
	{
		Representacion_primitiva_caja::operator=(p_otro);
		return *this;
	}
};

}

#endif
