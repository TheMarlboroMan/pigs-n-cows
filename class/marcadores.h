#ifndef MARCADORES_H
#define MARCADORES_H

class Marcadores
{
	public:

	enum tipos_animal{T_CERDITO=0, T_VAQUITA, 
		T_MAX_ANIMAL};

	private:

	static const int X_CAJA=20;
	static const int Y_CAJA=200;	
	static const int W_CAJA=22;
	static const int H_CAJA=202;

	static const int X_SIMBOLO=20;
	static const int Y_SIMBOLO=20;	
	static const int W_SIMBOLO=26;
	static const int H_SIMBOLO=26;

	static const int X_SIMBOLO_CERDITO=146;
	static const int Y_SIMBOLO_CERDITO=35;	
	static const int X_SIMBOLO_VAQUITA=119;
	static const int Y_SIMBOLO_VAQUITA=35;	

	static const int X_TEXTO=40;
	static const int Y_TEXTO=26;	

	static const int INI_MAX_VAQUITAS=2;
	static const int INI_MAX_CERDITOS=6;

	static const unsigned int MAX_PUNTUACION=200;

	int tipo_animal_actual;

	unsigned int vaquitas;
	unsigned int cerditos;

	unsigned int max_vaquitas;
	unsigned int max_cerditos;

	unsigned int puntuacion,
				running_score;
	
	public:

	Marcadores():
		tipo_animal_actual(T_CERDITO),
		vaquitas(INI_MAX_VAQUITAS), 
		cerditos(INI_MAX_CERDITOS), 
		max_vaquitas(INI_MAX_VAQUITAS), 
		max_cerditos(INI_MAX_CERDITOS),
		puntuacion(0),
		running_score(0)
	{}

	void		cleanup() {

		tipo_animal_actual=T_CERDITO;
		vaquitas=INI_MAX_VAQUITAS;
		cerditos=INI_MAX_CERDITOS;
		max_vaquitas=INI_MAX_VAQUITAS;
		max_cerditos=INI_MAX_CERDITOS;
		puntuacion=0;
		running_score=0;
	}

	unsigned int acc_tipo_animal_actual() {return tipo_animal_actual;}
//	unsigned int acc_vaquitas() {return vaquitas;}
//	unsigned int acc_cerditos() {return cerditos;}
/*
	unsigned int acc_cantidad_animal_actual() const
	{
		switch(tipo_animal_actual)
		{
			case T_CERDITO: return cerditos; break;
			case T_VAQUITA: return vaquitas; break;
			default: return 0; break;
		}
	}	
*/
	bool hay_animales_disponibles() const
	{
		switch(tipo_animal_actual)
		{
			case T_CERDITO: return cerditos; break;
			case T_VAQUITA: return vaquitas; break;
			default: return false; break;
		}
	}

	void aumentar_disponibles()
	{
		++vaquitas;
		++cerditos;
		++max_vaquitas;
		++max_cerditos;
	}

	void devolver_vaquita() {++vaquitas;}
	void devolver_cerdito() {++cerditos;}
	void lanzar_vaquita() {--vaquitas;}
	void lanzar_cerdito() {--cerditos;}

	bool sumar_puntuacion(int c)
	{
		running_score+=c;
		puntuacion+=c;
		if(puntuacion >= MAX_PUNTUACION)
		{
			puntuacion=0;
			return true;
		}
		return false;
	}

	void cambiar_tipo_animal(unsigned int dir)
	{
		tipo_animal_actual+=dir;
		if(tipo_animal_actual <= 0) tipo_animal_actual=T_MAX_ANIMAL-1;
		else if(tipo_animal_actual >= T_MAX_ANIMAL) tipo_animal_actual=T_CERDITO;
	}

	void dibujar(DLibV::Pantalla& pantalla)
	{
		int x=0, y=0, cantidad=0, total=0;
		
		switch(tipo_animal_actual)
		{
			case T_CERDITO:
				x=X_SIMBOLO_CERDITO;
				y=Y_SIMBOLO_CERDITO;
				cantidad=cerditos;
				total=max_cerditos;
			break;

			case T_VAQUITA:
				x=X_SIMBOLO_VAQUITA;
				y=Y_SIMBOLO_VAQUITA;
				cantidad=vaquitas;
				total=max_vaquitas;
			break;
		}

		DLibV::Representacion_bitmap_dinamica rd;	
		rd.establecer_recurso(DLibV::Gestor_recursos_graficos::obtener(1));
		rd.establecer_recorte(x, y, W_SIMBOLO, H_SIMBOLO);
		rd.establecer_posicion(X_SIMBOLO, Y_SIMBOLO, W_SIMBOLO, H_SIMBOLO);
		rd.volcar(pantalla);

		std::string cadena=" X "+
			DLibH::Herramientas::entero_a_cadena(cantidad)+
			" / "+
			DLibH::Herramientas::entero_a_cadena(total)+
			" SCORE: "+
			DLibH::Herramientas::entero_a_cadena(running_score);

		DLibV::Representacion_texto_auto_estatica txt(DLibV::Gestor_recursos_graficos::obtener(3), cadena);
		txt.establecer_posicion(X_TEXTO, Y_TEXTO);
		txt.volcar(pantalla);

		SDL_Rect rect=DLibH::Herramientas_SDL::nuevo_sdl_rect(X_CAJA, Y_CAJA, W_CAJA, H_CAJA);
		DLibV::Primitiva_grafica_caja_estatica caja=DLibV::Primitiva_grafica_caja_estatica(rect, DLibV::Gestor_color::color(255, 255, 255));
		caja.establecer_alpha(128);
		caja.volcar(pantalla);
	
		if(puntuacion)
		{
			int y_puntos=Y_CAJA+H_CAJA-puntuacion-1;
			rect=DLibH::Herramientas_SDL::nuevo_sdl_rect(X_CAJA+1, y_puntos, W_CAJA-2, puntuacion);
			DLibV::Primitiva_grafica_caja_estatica caja2=DLibV::Primitiva_grafica_caja_estatica(rect, DLibV::Gestor_color::color(220, 155, 2));
			caja2.establecer_alpha(128);
			caja2.volcar(pantalla);
		}
	}	
};

#endif
