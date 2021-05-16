#ifndef APUNTADOR_H
#define APUNTADOR_H

class Apuntador
{
	public:

	static const unsigned int X=50;
	static const unsigned int Y=500;

	private:

	static const unsigned int LONGITUD_PUNTA_FLECHA=10;
	static const unsigned int MIN_ANGULO=5;
	static const unsigned int MAX_ANGULO=85;
	static const unsigned int MIN_FUERZA=200;
	static const unsigned int MAX_FUERZA=600;
	static const unsigned int MAX_L_FUERZA=700;
	static const float GRADOS_POR_SEGUNDO;
	static const float FUERZA_POR_SEGUNDO;

	float angulo; //En SDL 0 es derecha y 270 es arriba. Aquí lo almacenamos bien, pero
			//lo transformamos para mostrar.
	float fuerza;
	bool started{false};

	public:

	Apuntador():angulo(15.0), fuerza(MIN_FUERZA)
	{}

	void	cleanup() {

		angulo=15.0;
		fuerza=MIN_FUERZA;
		started=false;
	}

	void start() {started=true;}
	bool is_started() const {return started;}

	float acc_fuerza() const {return fuerza;}

	bool can_throw() const {return fuerza != MIN_FUERZA;}

	void reiniciar_fuerza() {fuerza=MIN_FUERZA;}

	void sumar_fuerza(float delta)
	{
		fuerza+=(delta * FUERZA_POR_SEGUNDO);
		if(fuerza >= MAX_FUERZA) fuerza=MAX_FUERZA;
	}

	void cambiar_angulo(short int direccion, float delta)
	{
		angulo+=(float)direccion * (delta * GRADOS_POR_SEGUNDO);
		if(angulo < MIN_ANGULO) angulo=MIN_ANGULO;
		else if(angulo > MAX_ANGULO) angulo=MAX_ANGULO;
	}

	void dibujar(DLibV::Pantalla& p, bool _can_throw)
	{
		float l_fuerza=(MAX_L_FUERZA - fuerza) / 10.0;

		Sint16 y=_can_throw ? 61 : 69;
		SDL_Rect posicion{X, Y, 8, 8},
				recorte{165, y, 8, 8};

		DLibV::Representacion_bitmap_dinamica rd;
		rd.establecer_alpha(128);
		rd.establecer_recurso(DLibV::Gestor_recursos_graficos::obtener(1));
		rd.establecer_recorte(recorte);

		auto radians=DLibH::Herramientas::grados_a_radianes(angulo-90.f);

		rd.volcar(p);

		for(int i=0; i<6; i++) {

			posicion.x+=cos(radians) * l_fuerza;
			posicion.y+=sin(radians) * l_fuerza;
			rd.establecer_posicion(posicion);
			rd.volcar(p);
		}
	}

	float acc_angulo() {return angulo;}
};

#endif
