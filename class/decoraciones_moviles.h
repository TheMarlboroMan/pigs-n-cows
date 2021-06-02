#ifndef DECORACIONES_MOVILES_H
#define DECORACIONES_MOVILES_H

#include "actor_movil.h"
#include "representable.h"

class Nube:public Actor_movil, public Representable
{
	private:

	static const int W1=47;
	static const int H1=18;
	static const int X1=0;
	static const int Y1=52;

	static const int W2=66;
	static const int H2=29;
	static const int X2=50;
	static const int Y2=52;

	static const int MIN_VELOCIDAD=10;
	static const int MAX_VELOCIDAD=100;

	float velocidad;
	int tipo;
	int w;
	int h;

	virtual unsigned int obtener_recurso() const {return 1;}
	virtual Uint8 obtener_alpha() const {return 128;}

	virtual void configurar_posicion(SDL_Rect& r) const
	{
		r.x=acc_x();
		r.y=acc_y();
		r.w=w;
		r.h=h;
	}
	
	virtual void configurar_recorte(SDL_Rect& r) const
	{
		r.x=tipo ? X1 : X2;
		r.y=tipo ? Y1 : Y2;
		r.w=w;
		r.h=h;
	}

	private:
	virtual void gravedad(float) {}
	virtual void turno(float d){integrar(d, velocidad);}
	virtual bool evaluar_borrado() {return acc_x()+w <= 0.0;}

	public:

	/////////

	Nube():Actor_movil(), Representable(), velocidad(0.0), w(0), h(0)
	{
		establecer_vector_desde_angulo(270);
	}

	void configurar()
	{
		int x=Definiciones::W_AREA;
		int y=DLibH::Herramientas::obtener_aleatorio_tramo(20, 340);
		velocidad=DLibH::Herramientas::obtener_aleatorio_tramo(MIN_VELOCIDAD, MAX_VELOCIDAD);
		establecer_posicion(x, y);
		tipo=DLibH::Herramientas::obtener_aleatorio_tramo(0, 10) % 2 ? 1 : 0;

		if(tipo)
		{
			w=W1; h=H1;
		}
		else
		{
			w=W2; h=H2;
		}
	}

	virtual void aceptar_visitante(Visitante& v) const {v.visitar(*this);}	
	virtual SDL_Rect acc_posicion()const {return DLibH::Herramientas_SDL::nuevo_sdl_rect(acc_x(), acc_y(), 1, 1);}
};

class Arco_iris:public Actor, public Representable
{
	private:

	static const int W=16;
	static const int H=16;

	float tiempo;

	public:

	virtual unsigned int obtener_recurso() const {return 1;}
	virtual Uint8 obtener_alpha() const {return 3;}

	virtual void configurar_posicion(SDL_Rect& r) const
	{
		r.x=acc_x();
		r.y=acc_y();
		r.w=W;
		r.h=H;
	}
	
	virtual void configurar_recorte(SDL_Rect& r) const
	{
		r.x=0;
		r.y=36;
		r.w=W;
		r.h=H;
	}

	public:

	private:

	virtual void turno(float delta){tiempo-=delta;}
	virtual bool evaluar_borrado(){return tiempo <= 0.0;}

	public:

	Arco_iris():Actor(), Representable(), tiempo(1.0) {}
	virtual void aceptar_visitante(Visitante& v) const {v.visitar(*this);}	
	virtual SDL_Rect acc_posicion()const {return DLibH::Herramientas_SDL::nuevo_sdl_rect(acc_x(), acc_y(), W, H);}
};

#endif
