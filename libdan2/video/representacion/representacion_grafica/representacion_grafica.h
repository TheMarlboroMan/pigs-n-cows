#ifndef REPRESENTACION_GRAFICA_H
#define REPRESENTACION_GRAFICA_H

#include "../representacion.h"
#include "../../textura/textura.h"

/*
Es la clase base de todas las representaciones que usan un SDL_Texture 
(encapsulado en un recurso) para ser representado. 

Viene acompañada de una estructura de transformación que aprovecha algunas de las cualidades
de SDL_2*/

namespace DLibV
{

struct Representacion_grafica_transformacion
{
	private:

	bool invertir_horizontal;
	bool invertir_vertical;
	bool rotacion;
	bool cambiar_centro_rotacion;

	float angulo_rotacion;
	float x_centro_rotacion;
	float y_centro_rotacion;

	public:

	Representacion_grafica_transformacion():
		invertir_horizontal(false), invertir_vertical(false), rotacion(false),
		cambiar_centro_rotacion(false),
		angulo_rotacion(0.0), x_centro_rotacion(0.0), y_centro_rotacion(0.0)
	{}

	SDL_RendererFlip obtener_flip() const
	{
		int res=SDL_FLIP_NONE;

		if(invertir_horizontal || invertir_vertical)
		{
			if(invertir_horizontal && invertir_vertical) res=SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
			else if(invertir_horizontal) res=SDL_FLIP_HORIZONTAL;
			else res=SDL_FLIP_VERTICAL;
		}

		return (SDL_RendererFlip)res;
	}

	SDL_Point obtener_centro_rotacion() const
	{
		SDL_Point p;
		p.x=x_centro_rotacion;
		p.y=y_centro_rotacion;
		return p;
	}

	float obtener_angulo_rotacion() const 
	{
		if(rotacion) return angulo_rotacion;
		else return 0.0;
	}

	bool es_transformacion() const
	{
		return invertir_horizontal || invertir_vertical || rotacion;
	}

	void rotar(float v)
	{
		rotacion=true;
		angulo_rotacion=v;
	}

	void cancelar_rotar()
	{
		rotacion=false;
		angulo_rotacion=0.0;
	}

	bool es_cambia_centro_rotacion() const {return cambiar_centro_rotacion;}

	void establecer_invertir_horizontal(bool v) {invertir_horizontal=v;}
	void establecer_invertir_vertical(bool v) {invertir_vertical=v;}

	void centro_rotacion(float px, float py)
	{
		cambiar_centro_rotacion=true;
		x_centro_rotacion=px;
		y_centro_rotacion=py;
	}

	void cancelar_centro_rotacion()
	{
		cambiar_centro_rotacion=false;
		x_centro_rotacion=0.0;
		y_centro_rotacion=0.0;
	}

	void reiniciar()
	{
		invertir_horizontal=false;
		invertir_vertical=false;
		rotacion=false;
		cambiar_centro_rotacion=false;
		angulo_rotacion=0.0;
		x_centro_rotacion=0.0;
		y_centro_rotacion=0.0;
	}
};

class Representacion_grafica:public Representacion
{
	private:

	Representacion_grafica_transformacion transformacion;

	Textura * textura;	//Este es el puntero a su superficie de memoria.
	mutable bool preparada;	//Indica si la pantalla puede volcar o tiene que hacer una preparación propia.

	bool realizar_render(SDL_Renderer *, SDL_Rect& rec, SDL_Rect& pos);

	protected:

	void marcar_como_preparada() {this->preparada=true;}
	void marcar_como_no_preparada() {this->preparada=false;}
	void recorte_a_medidas_textura();
	void liberar_textura();
	void anular_textura() {textura=NULL;}

	virtual bool volcado(SDL_Renderer *);
	virtual bool volcado(SDL_Renderer *, const SDL_Rect&, const SDL_Rect&, int=0, int=0);

	public:

	bool es_preparada() const {return this->preparada;}

	Textura * ref_textura() const {return this->textura ? this->textura : NULL;}
	SDL_Texture * ref_textura_sdl() {return this->textura ? this->textura->ref_textura() : NULL;}
	Representacion_grafica();
	Representacion_grafica(const Representacion_grafica&);
	Representacion_grafica& operator=(const Representacion_grafica &);
	virtual ~Representacion_grafica();

	void reiniciar_transformacion() {transformacion.reiniciar();}
	void transformar_invertir_horizontal(bool v) {transformacion.establecer_invertir_horizontal(v);}
	void transformar_invertir_vertical(bool v) {transformacion.establecer_invertir_vertical(v);}
	void  transformar_rotar(float v) {transformacion.rotar(v);}
	void transformar_cancelar_rotar() {transformacion.cancelar_rotar();}
	void transformar_centro_rotacion(float x, float y) {transformacion.centro_rotacion(x, y);}
	void transformar_centro_rotacion_cancelar() {transformacion.cancelar_centro_rotacion();}
	bool es_transformada() const {return transformacion.es_transformacion();}

	Representacion_grafica_transformacion& acc_transformacion() {return transformacion;};

	virtual void establecer_textura(Textura const * p_textura) {this->textura=const_cast <Textura *> (p_textura);}
	virtual void preparar()=0;
};

} //Fin namespace DLibV

#endif
