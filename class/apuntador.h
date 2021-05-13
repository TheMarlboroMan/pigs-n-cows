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

	void dibujar(DLibV::Pantalla& p)
	{
		float t_angulo=angulo-90;
		float rad=DLibH::Herramientas::grados_a_radianes(t_angulo);
		float l_fuerza=(MAX_L_FUERZA - fuerza) / 7.0;
		Uint32 color=DLibV::Gestor_color::color(32, 32, 220);

		int x=X+4;
		int y=Y+4;

		int x2=X+(cos(rad) * l_fuerza);
		int y2=Y+(sin(rad) * l_fuerza);

		//Dibujamos la línea principal.
		DLibV::Primitiva_grafica_linea_estatica l(x, y, x2, y2, color);
		l.volcar(p);

		//Y ahora las líneas secundarias, que van del centro 90 grados para cada lado.

		rad=DLibH::Herramientas::grados_a_radianes(t_angulo-150);
		int xflechaizq=x2+(cos(rad) * LONGITUD_PUNTA_FLECHA);
		int yflechaizq=y2+(sin(rad) * LONGITUD_PUNTA_FLECHA);

		DLibV::Primitiva_grafica_linea_estatica l2(x2, y2, xflechaizq, yflechaizq, color);
		l2.volcar(p);

		rad=DLibH::Herramientas::grados_a_radianes(t_angulo+150);
		int xflechader=x2+(cos(rad) * LONGITUD_PUNTA_FLECHA);
		int yflechader=y2+(sin(rad) * LONGITUD_PUNTA_FLECHA);

		DLibV::Primitiva_grafica_linea_estatica l3(x2, y2, xflechader, yflechader, color);
		l3.volcar(p);
	}

	float acc_angulo() {return angulo;}
};

#endif
