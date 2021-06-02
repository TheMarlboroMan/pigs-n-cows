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

	ldv::rgb_color COLOR_AMANECER;
	ldv::rgb_color COLOR_MEDIODIA;
	ldv::rgb_color COLOR_ATARDECER;
	ldv::rgb_color COLOR_NOCHE;
	ldv::rgb_color COLOR_ESTRELLA;

	float t;
	ldv::rgb_color color_actual;
	ldv::rgb_color color_transicion;
	unsigned int momento;
	bool en_transicion;
	std::vector<Estrella> estrellas;

	void definir_colores()
	{
		COLOR_AMANECER=ldv::rgb8(0, 172, 186);
		COLOR_MEDIODIA=ldv::rgb8(0, 211, 228);
		COLOR_ATARDECER=ldv::rgb8(248, 147, 28);
		COLOR_NOCHE=ldv::rgb8(8, 24, 74);
		COLOR_ESTRELLA=ldv::rgb8(192, 192, 192);
	}

	void transicion_colores()
	{
		if(color_transicion==color_actual) 
		{
			en_transicion=false;
		}
		else
		{
			auto trans=[](int& co, int cd)
			{
				if(co != cd)
				{
					if(co < cd) ++co;
					else --co;
				}
			};

//			Uint8 	ra=0, ga=0, ba=0, 
//				rd=0, gd=0, bd=0;

//			SDL_GetRGB(color_transicion, DLibV::Gestor_color::obtener_formato(), &ra, &ga, &ba);
//			SDL_GetRGB(color_actual, DLibV::Gestor_color::obtener_formato(), &rd, &gd, &bd);

			int ra=ldv::colorif(color_transicion.r), 
				ga=ldv::colorif(color_transicion.g), 
				ba=ldv::colorif(color_transicion.b), 
				rd=ldv::colorif(color_actual.r), 
				gd=ldv::colorif(color_actual.g), 
				bd=ldv::colorif(color_actual.b);

			trans(ra, rd);
			trans(ga, gd);
			trans(ba, bd);

			color_transicion=ldv::rgb8(ra, ga, ba);
		}
	}
	
	void disminuir_colores(int& r, int& g, int& b)
	{
		if(r <= FACTOR_DISMINUIR_COLOR) r=0;
		else r-=FACTOR_DISMINUIR_COLOR;

		if(g <= FACTOR_DISMINUIR_COLOR) g=0;
		else g-=FACTOR_DISMINUIR_COLOR;

		if(b <= FACTOR_DISMINUIR_COLOR) b=0;
		else b-=FACTOR_DISMINUIR_COLOR;
	}

	public:

	Cielo():
		COLOR_AMANECER(ldv::rgb8(0,0,0)), 
		COLOR_MEDIODIA(ldv::rgb8(0,0,0)), 
		COLOR_ATARDECER(ldv::rgb8(0,0,0)), 
		COLOR_NOCHE(ldv::rgb8(0,0,0)), 
		COLOR_ESTRELLA(ldv::rgb8(0,0,0)),
		t(0),
		color_actual(ldv::rgb8(0,0,0)), 
		color_transicion(ldv::rgb8(0,0,0)), 
		momento(M_AMANECER), 
		en_transicion(false)
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
		int h_franja=Definiciones::H_AREA / FRANJAS;
		int y=0, i=0;
		int r=0, g=0, b=0;
		auto color=en_transicion ? color_transicion : color_actual;
		r=ldv::colorif(color.r);
		g=ldv::colorif(color.g);
		b=ldv::colorif(color.b);

		while((unsigned)i < FRANJAS) {
		
			DLibV::Representacion_primitiva_caja_estatica box(
				{0, y, Definiciones::W_AREA, h_franja},
				r, g, b
			);
		
			box.volcar(p);
			
			disminuir_colores(r, g, b);
			y+=h_franja;
			++i;
		}

		if(momento==M_NOCHE) {
		
			dibujar_estrellas(p);
		}
	}

	void dibujar_estrellas(DLibV::Pantalla& p)
	{
		
		auto r=ldv::colorif(COLOR_ESTRELLA.r),
		g=ldv::colorif(COLOR_ESTRELLA.g),
		b=ldv::colorif(COLOR_ESTRELLA.b);
		
		for(Estrella& e : estrellas) {
		
			DLibV::Representacion_primitiva_caja_estatica box(
				{(int)e.x, (int)e.y, 1, 1},
				r, g, b
			);
		
			box.volcar(p);		
		}
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
