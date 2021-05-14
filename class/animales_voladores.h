#ifndef ANIMALES_VOLADORES_H
#define ANIMALES_VOLADORES_H

#include "actor_movil.h"
#include "representable.h"

class Animal_volador:public Actor_movil, public Representable
{
	private:

	static const int MIN_Y=512;
//	static const int Y_OVACION=300;

	float angulo;
	float velocidad;
	mutable unsigned int multiplicador_puntuacion;
//	mutable bool ovacionado;

	//Implementacion
	private:

	virtual float peso() const =0;

	virtual void gravedad(float delta)
	{
		DLibH::Vector_2d v=acc_vector();
		v.y+=peso() * delta;

		if(v.y > 30.0) v.y=30.0;
		mut_vector(v);
	}

	private:

	virtual void turno(float delta){integrar(delta, velocidad);}
	virtual bool evaluar_borrado(){return acc_y() >= MIN_Y;}

	public:

	int acc_multiplicador_puntuacion() const {return multiplicador_puntuacion;}
	void aumentar_multiplicador() const {++multiplicador_puntuacion;} //Vaya timo XD!.

	void configurar(float va, float vv)
	{
		angulo=va;
		velocidad=vv;
		establecer_vector_desde_angulo(angulo);
	}
	Animal_volador(unsigned int mp): Actor_movil(), angulo(0), velocidad(0), multiplicador_puntuacion(mp) /*ovacionado(false)*/ {}
};

class Cerdito:public Animal_volador
{
	private:

	static const int W=26;
	static const int H=14;

	static const int RX=0;
	static const int RY=0;

	private:

	virtual float peso() const {return 0.6;}

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
		r.x=RX;
		r.y=RY;
		r.w=W;
		r.h=H;
	}

	Cerdito():Animal_volador(1){}
	virtual void aceptar_visitante(Visitante& v) const {v.visitar(*this);}
	virtual SDL_Rect acc_posicion()const {return DLibH::Herramientas_SDL::nuevo_sdl_rect(acc_x(), acc_y(), W, H);}
};

class Vaquita:public Animal_volador
{
	private:

	static const int W=25;
	static const int H=21;

	static const int RX=0;
	static const int RY=14;

	private:

	virtual float peso() const {return 0.8;}

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
		r.x=RX;
		r.y=RY;
		r.w=W;
		r.h=H;
	}

	Vaquita():Animal_volador(2){}
	virtual void aceptar_visitante(Visitante& v) const {v.visitar(*this);}
	virtual SDL_Rect acc_posicion()const {return DLibH::Herramientas_SDL::nuevo_sdl_rect(acc_x(), acc_y(), W, H);}
};


#endif
