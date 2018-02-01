#ifndef MENSAJES_CONTROLADOR_H
#define MENSAJES_CONTROLADOR_H

class Mensaje_controlador
{
	public:

	enum tipos{
		T_ARCO_IRIS,
		T_CERDITO_TIERRA,
		T_VAQUITA_TIERRA,
		T_OVACION,
		T_DEVOLVER_CERDITO,
		T_DEVOLVER_VAQUITA
	};
	
	unsigned int tipo;
	float x;
	float y;

	Mensaje_controlador(unsigned int t, float px, float py):
		tipo(t),x(px), y(py){}
};

#endif
