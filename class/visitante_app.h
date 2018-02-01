#ifndef VISITANTE_APP_H
#define VISITANTE_APP_H

#include "bonus.h"
#include "animales_voladores.h"
#include "decoraciones_moviles.h"
#include "mensajes_controlador.h"

class Visitante_generar_representables:public Visitante
{
	private:

	std::vector<const Representable*> v;

	public:

	std::vector<const Representable*> acc_vector_representables() const {return v;}
	Visitante_generar_representables(){}

	virtual void visitar(const Cerdito& r){v.push_back(&r);}
	virtual void visitar(const Vaquita& r){v.push_back(&r);}
	virtual void visitar(const Cerdito_tierra& r){v.push_back(&r);}
	virtual void visitar(const Vaquita_tierra& r){v.push_back(&r);}
	virtual void visitar(const Arco_iris& r){v.push_back(&r);}
	virtual void visitar(const Nube& r){v.push_back(&r);}
	virtual void visitar(const Bonus& r){v.push_back(&r);}
};

class Visitante_mensajes:public Visitante
{
	private:

	std::vector<Mensaje_controlador> v;

	public:

	std::vector<Mensaje_controlador> acc_vector_mensajes() const {return v;}
	Visitante_mensajes(){}

	virtual void visitar(const Cerdito& r)
	{
		float x=r.acc_x();
		float y=r.acc_y();
		v.push_back(Mensaje_controlador(Mensaje_controlador::T_ARCO_IRIS, x, y));
		if(r.es_para_borrar()) v.push_back(Mensaje_controlador(Mensaje_controlador::T_CERDITO_TIERRA, x, y));
//		if(r.evaluar_ovacion()) v.push_back(Mensaje_controlador(Mensaje_controlador::T_OVACION, 0, 0));

	}
	virtual void visitar(const Vaquita& r)
	{
		float x=r.acc_x();
		float y=r.acc_y();
		v.push_back(Mensaje_controlador(Mensaje_controlador::T_ARCO_IRIS, x, y));
		if(r.es_para_borrar()) v.push_back(Mensaje_controlador(Mensaje_controlador::T_VAQUITA_TIERRA, x, y));
//		if(r.evaluar_ovacion()) v.push_back(Mensaje_controlador(Mensaje_controlador::T_OVACION, 0, 0));
	}

	virtual void visitar(const Cerdito_tierra& r) 
	{
		if(r.es_para_borrar()) v.push_back(Mensaje_controlador(Mensaje_controlador::T_DEVOLVER_CERDITO, 0, 0));
	}

	virtual void visitar(const Vaquita_tierra& r) 
	{
		if(r.es_para_borrar()) v.push_back(Mensaje_controlador(Mensaje_controlador::T_DEVOLVER_VAQUITA, 0, 0));
	}

	virtual void visitar(const Arco_iris&) {}
	virtual void visitar(const Nube&) {}
	virtual void visitar(const Bonus&) {}
};

class Visitante_colisiones:public Visitante
{
	private:

	unsigned int puntuacion;
	std::vector<const Animal_volador*> animales;
	std::vector<const Bonus*> bonus;
	std::vector<const Actor*> para_borrar;

	public:

	std::vector<const Actor *> acc_para_borrar() const {return para_borrar;}
	Visitante_colisiones(): puntuacion(0) {}

	unsigned int acc_puntuacion() const {return puntuacion;}

	bool procesar()
	{
		if(!bonus.size()) return false;

		for(const Animal_volador * a : animales)
		{
			if(!bonus.size()) break;
			SDL_Rect caja_animal=a->acc_posicion();

			std::vector<const Bonus *>::iterator 	ini=bonus.begin(),
								fin=bonus.end();

			while(ini < fin)
			{
				SDL_Rect caja_bonus=(*ini)->acc_posicion();

				if(DLibH::Herramientas_SDL::rectangulos_superpuestos(caja_animal, caja_bonus))
				{
					puntuacion+=( (*ini)->acc_puntuacion() * a->acc_multiplicador_puntuacion());
					a->aumentar_multiplicador();
					para_borrar.push_back(*ini);
					ini=bonus.erase(ini);
					fin=bonus.end();
				}
				else ++ini;
			}
		}

		return para_borrar.size();
	}

	virtual void visitar(const Cerdito& r){animales.push_back(&r);}
	virtual void visitar(const Vaquita& r){animales.push_back(&r);}
	virtual void visitar(const Bonus& r){bonus.push_back(&r);}

	virtual void visitar(const Cerdito_tierra&){}
	virtual void visitar(const Vaquita_tierra&){}
	virtual void visitar(const Arco_iris&){}
	virtual void visitar(const Nube&){}

};
#endif
