#ifndef LIENZO_H
#define LIENZO_H

#include "superficie.h"

/*
Esto es un caso especial... Básicamente un recurso gráfico que va a generar
una superificie de video vacía para poderla manipular.
*/

namespace DLibV
{

class Lienzo:public Superficie
{
	private:

	bool generado;
	Lienzo();

	public:
	

	~Lienzo();
	Lienzo(const Lienzo&);
	Lienzo& operator=(const Lienzo&);
	static Lienzo * generar_nuevo(int, int, const SDL_Surface *); 	//Se genera un recurso que NO se registraría... No me termina de gustar.
	static Lienzo * generar_nuevo(int, int, int bpp, Uint32 maskr, Uint32 maskg, Uint32 maskb, Uint32 maskalpha);
	static Lienzo * copiar_lienzo(const Lienzo&);

	bool es_generado() const {return this->generado;}
	int obtener_tipo(){return Superficie::T_LIENZO;}
	bool es_preparado() {return this->generado;}
};

} //Fin namespace DLibV

#endif
