#ifndef BONUS_H
#define BONUS_H

#include "actor_movil.h"
#include "representable.h"

class Bonus:public Actor_movil, public Representable
{
	public:

	enum tipos {T_5=0, T_10, T_20, T_MAX};

	private:

	static const int W=16;
	static const int H=16;

	static const int X_INICIO=820;
	static const int MIN_Y=130;
	static const int MAX_Y=430;

	unsigned int tipo;
	float velocidad;

	private:

	virtual void gravedad(float delta) {}

	private:

	virtual void turno(float delta){integrar(delta, velocidad);}
	virtual bool evaluar_borrado(){return acc_x()+W <= 0;}

	public:

	virtual unsigned int obtener_recurso() const {return 1;}
	virtual unsigned int obtener_alpha() const {return 255;}

	virtual void configurar_posicion(SDL_Rect& r) const
	{
		r.x=(int) acc_x();
		r.y=(int) acc_y();
		r.w=W;
		r.h=H;
	}
	
	virtual void configurar_recorte(SDL_Rect& r) const
	{
		int x=0, y=0;

		switch(tipo)
		{
			case T_5: x=117; y=62; break;
			case T_10: x=133; y=62; break;
			case T_20: x=149; y=62; break;
		}

		r.x=x;
		r.y=y;
		r.w=W;
		r.h=H;
	}

	public:

	void configurar()
	{
		tipo=DLibH::Herramientas::obtener_aleatorio_tramo(T_5, T_MAX);
		
		switch(tipo)
		{
			case T_5: velocidad=50; break;
			case T_10: velocidad=100; break;
			case T_20: velocidad=200; break;
		}

		int y=DLibH::Herramientas::obtener_aleatorio_tramo(MIN_Y, MAX_Y);
		establecer_posicion(X_INICIO, y);
		establecer_vector_desde_angulo(270);
	}

	int acc_puntuacion() const
	{
		switch(tipo)
		{
			case T_5: return 5; break;
			case T_10: return 10; break;
			case T_20: return 20; break;
		}

		return 0;
	}

	Bonus(): Actor_movil(), Representable(), tipo(0), velocidad(0) {}
	virtual void aceptar_visitante(Visitante& v) const {v.visitar(*this);}	
	virtual SDL_Rect acc_posicion()const {return DLibH::Herramientas_SDL::nuevo_sdl_rect(acc_x(), acc_y(), W, H);}
};

#endif
