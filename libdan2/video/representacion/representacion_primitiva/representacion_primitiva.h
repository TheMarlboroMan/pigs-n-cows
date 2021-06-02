#ifndef REPRESENTACION_PRIMITIVA_H
#define REPRESENTACION_PRIMITIVA_H

#include "../representacion.h"
#include "../../../herramientas/herramientas_sdl/herramientas_sdl.h"

/*Esto será una clase abstracta que podremos usar para volcar
en una pantalla... De por si no hay nada de código aquí, solo
los esqueletos de lo que vamos a usar más adelante.
*/

namespace DLibV
{

class Representacion_primitiva:public Representacion
{
	private:

	Uint8 r, g, b;
	bool recomponer_recorte_con_posicion;

	//Esto es un puntero void a algo que podemos pasar al método de turno,
	//por si acaso queremos hacer algo más sofisticado. Todas las
	//clases que deriven de esta podrían hacer uso de este puntero.
	
	void * parametro_metodo_pixeles;

	protected:

	virtual void preparar_posicion()=0; //Este método es obligatorio implementarlo para decirle cómo de grande es la caja.

	bool determinar_caja_dibujo_final(SDL_Rect &, SDL_Rect const&, SDL_Rect const&);
	
	public:

	Representacion_primitiva(Uint8, Uint8, Uint8);
	Representacion_primitiva(const Representacion_primitiva&);
	Representacion_primitiva& operator=(const Representacion_primitiva&);
	virtual ~Representacion_primitiva();

	void establecer_parametro_metodo_pixeles(void * p_param) {this->parametro_metodo_pixeles=p_param;}
	Uint8 acc_r() const {return r;}
	Uint8 acc_g() const {return g;}
	Uint8 acc_b() const {return b;}
	bool es_recomponer_recorte_con_posicion() const {return recomponer_recorte_con_posicion;}
	void * acc_parametro_metodo_pixeles() const {return this->parametro_metodo_pixeles;}

	void mut_recomponer_recorte_con_posicion(bool p_valor) {this->recomponer_recorte_con_posicion=p_valor;}	
	void mut_r(Uint8 v) {r=v;}
	void mut_g(Uint8 v) {g=v;}
	void mut_b(Uint8 v) {b=v;}
	void mut_rgb(Uint8 pr, Uint8 pg, Uint8 pb) 
	{
		r=pr;
		g=pg;
		b=pb;
	}
	void recorte_a_posicion();
};

} //Fin namespace DLibV

#endif
