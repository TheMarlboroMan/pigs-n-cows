#ifndef CIELO_H
#define CIELO_H

#include "definiciones.h"

class Cielo
{
	private:

	struct Estrella
	{
		unsigned int x, y;
		Estrella(unsigned int px, unsigned int py):x(px), y(py){};
	};

	enum momentos {M_AMANECER, M_MEDIODIA, M_ATARDECER, M_NOCHE, M_MAX};
	static const unsigned int FRANJAS=8;
	static const int FACTOR_DISMINUIR_COLOR=10;
	static const int SEGUNDOS_PARTE_DIA=20;
	static const unsigned int MAX_ESTRELLAS=60;

	Uint32 COLOR_AMANECER;
	Uint32 COLOR_MEDIODIA;
	Uint32 COLOR_ATARDECER;
	Uint32 COLOR_NOCHE;
	Uint32 COLOR_ESTRELLA;

	float t;
	Uint32 color_actual;
	Uint32 color_transicion;
	unsigned int momento;
	bool en_transicion;
	std::vector<Estrella> estrellas;

	void definir_colores()
	{
		COLOR_AMANECER=DLibV::Gestor_color::color(0, 172, 186);
		COLOR_MEDIODIA=DLibV::Gestor_color::color(0, 211, 228);
		COLOR_ATARDECER=DLibV::Gestor_color::color(248, 147, 28);
		COLOR_NOCHE=DLibV::Gestor_color::color(8, 24, 74);
		COLOR_ESTRELLA=DLibV::Gestor_color::color(192, 192, 192);
	}

	void transicion_colores()
	{
		if(color_transicion==color_actual) 
		{
			en_transicion=false;
		}
		else
		{
			auto trans=[](Uint8& co, Uint8 cd)
			{
				if(co != cd)
				{
					if(co < cd) ++co;
					else --co;
				}
			};

			Uint8 	ra=0, ga=0, ba=0, 
				rd=0, gd=0, bd=0;

			SDL_GetRGB(color_transicion, DLibV::Gestor_color::obtener_formato(), &ra, &ga, &ba);
			SDL_GetRGB(color_actual, DLibV::Gestor_color::obtener_formato(), &rd, &gd, &bd);

			trans(ra, rd);
			trans(ga, gd);
			trans(ba, bd);

			color_transicion=DLibV::Gestor_color::color(ra, ga, ba);
		}
	}
	
	void disminuir_colores(Uint8& r, Uint8& g, Uint8& b)
	{
		if(r <= FACTOR_DISMINUIR_COLOR) r=0;
		else r-=FACTOR_DISMINUIR_COLOR;

		if(g <= FACTOR_DISMINUIR_COLOR) g=0;
		else g-=FACTOR_DISMINUIR_COLOR;

		if(b <= FACTOR_DISMINUIR_COLOR) b=0;
		else b-=FACTOR_DISMINUIR_COLOR;
	}

	public:

	Cielo():COLOR_AMANECER(0), COLOR_MEDIODIA(0), COLOR_ATARDECER(0), COLOR_NOCHE(0), COLOR_ESTRELLA(0),
	t(0), color_actual(0), color_transicion(0), momento(M_AMANECER), en_transicion(false)
	{}

	void configurar()
	{
		definir_colores();
		color_actual=COLOR_AMANECER;
		
		estrellas.clear();
		unsigned int i=0;
		while(i < MAX_ESTRELLAS)
		{
			estrellas.push_back(Estrella(
				DLibH::Herramientas::obtener_aleatorio_tramo(0, Definiciones::W_AREA),
				DLibH::Herramientas::obtener_aleatorio_tramo(0, 500)));
			++i;
		}
	}

	void dibujar(DLibV::Pantalla& p)
	{
		unsigned int h_franja=Definiciones::H_AREA / FRANJAS;
		unsigned int y=0, i=0;
		Uint8 r=0, g=0, b=0;
		Uint32 color=en_transicion ? color_transicion : color_actual;
		SDL_GetRGB(color, DLibV::Gestor_color::obtener_formato(), &r, &g, &b);

		while(i < FRANJAS)
		{
			p.rellenar(r, g, b, 0, y, Definiciones::W_AREA, h_franja);
			disminuir_colores(r, g, b);
			y+=h_franja;
			++i;
		}

		if(momento==M_NOCHE)
		{
			dibujar_estrellas(p);
		}
	}

	void dibujar_estrellas(DLibV::Pantalla& p)
	{
		for(Estrella& e : estrellas)
			DLibV::Utilidades_graficas_SDL::SDL_PutPixel(p.acc_superficie(), e.x, e.y, COLOR_ESTRELLA);
	}

	void turno(float delta)
	{
		t+=delta;
		if(en_transicion) transicion_colores();

		if(t >= SEGUNDOS_PARTE_DIA)
		{
			t=0.0;
			++momento;
			if(momento >= M_MAX) momento=M_AMANECER;
			color_transicion=color_actual;
			en_transicion=true;
			switch(momento)	
			{
				case M_AMANECER: color_actual=COLOR_AMANECER; break;
				case M_MEDIODIA: color_actual=COLOR_MEDIODIA; break;
				case M_ATARDECER: color_actual=COLOR_ATARDECER; break;
				case M_NOCHE: color_actual=COLOR_NOCHE; break;
			}	
		}
	}
};

#endif
