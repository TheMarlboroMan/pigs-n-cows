#ifndef ANIMALES_TIERRA_H
#define ANIMALES_TIERRA_H

class Animal_tierra:public Actor_movil, public Representable
{
	private:

	static const unsigned int FIN_CAMINO=50;
	float velocidad;
	float t;

	public:

	float acc_t() const {return t;}

	//Implementacion
	virtual void gravedad(float delta) {}

	private:

	virtual void turno(float delta)
	{
		t+=delta;
		integrar(delta, velocidad);
	}
	virtual bool evaluar_borrado(){return acc_x() <= FIN_CAMINO;}

	public:

	void configurar(float v)
	{
		velocidad=v;
		establecer_vector_desde_angulo(270);
	}

	Animal_tierra(): Actor_movil(), velocidad(0.0) {}
};

class Cerdito_tierra:public Animal_tierra
{
	private:
	static const int W=27;
	static const int H=14;

	static const int XP1=119;
	static const int YP1=0;
	static const int XP2=145;
	static const int YP2=0;

	public:

	virtual unsigned int obtener_recurso() const {return 1;}
	virtual Uint8 obtener_alpha() const {return 255;}

	virtual void configurar_posicion(SDL_Rect& r) const
	{
		r.x=(int) acc_x();
		r.y=(int) acc_y();
		r.w=W;
		r.h=H;
	}
	
	virtual void configurar_recorte(SDL_Rect& r) const
	{
		float mod_paso=fmod(acc_t(), 0.200);

		r.x=mod_paso <= 0.100 ? XP1 : XP2;
		r.y=mod_paso <= 0.100 ? YP1 : YP2;
		r.w=W;
		r.h=H;
	}

	virtual void aceptar_visitante(Visitante& v) const {v.visitar(*this);}	
	virtual SDL_Rect acc_posicion()const {return DLibH::Herramientas_SDL::nuevo_sdl_rect(acc_x(), acc_y(), W, H);}
};


class Vaquita_tierra:public Animal_tierra
{
	private:
	static const int W=25;
	static const int H=21;

	static const int XP1=120;
	static const int YP1=14;
	static const int XP2=145;
	static const int YP2=14;

	public:

	virtual unsigned int obtener_recurso() const {return 1;}
	virtual Uint8 obtener_alpha() const {return 255;}

	virtual void configurar_posicion(SDL_Rect& r) const
	{
		r.x=(int) acc_x();
		r.y=(int) acc_y();
		r.w=W;
		r.h=H;
	}
	
	virtual void configurar_recorte(SDL_Rect& r) const
	{
		float mod_paso=fmod(acc_t(), 0.200);

		r.x=mod_paso <= 0.100 ? XP1 : XP2;
		r.y=mod_paso <= 0.100 ? YP1 : YP2;
		r.w=W;
		r.h=H;
	}

	virtual void aceptar_visitante(Visitante& v) const {v.visitar(*this);}	
	virtual SDL_Rect acc_posicion()const {return DLibH::Herramientas_SDL::nuevo_sdl_rect(acc_x(), acc_y(), W, H);}
};

#endif
