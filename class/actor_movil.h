#ifndef ACTOR_MOVIL_H
#define ACTOR_MOVIL_H

#include "actor.h"

class Actor_movil:public Actor
{
	private:
	
	DLibH::Vector_2d vector;

	virtual void gravedad(float)=0;

	protected:

	void integrar(float delta, float vel)
	{
		gravedad(delta);

		float x=acc_x();
		float y=acc_y();

		float vx=vector.x;
		float vy=vector.y;

		float vvx=vx * vel;
		float vvy=vy * vel;

		float dx=vvx * delta;
		float dy=vvy * delta;

		mut_x(x+dx);
		mut_y(y+dy);		
	}

	public:

	DLibH::Vector_2d acc_vector() const {return vector;}
	void mut_vector(const DLibH::Vector_2d& v) {vector=v;}
	void establecer_vector_desde_angulo(float a) 
	{
		vector=DLibH::Vector_2d::vector_unidad_para_angulo(a);
		vector.y=-vector.y; //Compensar el sistema de coordenadas.
	}

	Actor_movil():Actor(), vector(0.0, 0.0) {}
};

#endif
