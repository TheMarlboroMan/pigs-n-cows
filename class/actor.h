#ifndef ACTOR_H
#define ACTOR_H

#include "visitante.h"

class Actor
{
	private:

	float x;
	float y;
	bool para_borrar;

	virtual void turno(float)=0;
	virtual bool evaluar_borrado()=0;

	public:

	virtual SDL_Rect acc_posicion()const=0;


	public:

	virtual ~Actor() {};
	void mut_x(float v) {x=v;}
	void mut_y(float v) {y=v;}

	float acc_x() const {return x;}
	float acc_y() const {return y;}
	bool es_para_borrar() const {return para_borrar;}

	Actor():x(0.0), y(0.0), para_borrar(false) {}

	void establecer_posicion(float px, float py)
	{
		x=px;
		y=py;
	}

	void paso(float delta)
	{
		turno(delta);
		para_borrar=evaluar_borrado();
	}

	virtual void aceptar_visitante(Visitante& v) const =0;

	void forzar_borrado() {para_borrar=true;}
};

#endif
