#ifndef PANTALLA_H
#define PANTALLA_H

#include <SDL2/SDL.h>
#include <iostream>
//#include <vector>
#include "../utilidades_graficas_sdl/utilidades_graficas_sdl.h"
#include "../camara/camara.h"
//#include "../representacion/representacion.h"

namespace DLibV
{

class Pantalla
{
	public:

	enum modos_ventana {
		M_VENTANA, //La ventana se creará como ventana.
		M_PANTALLA_COMPLETA_RESOLUCION, //La ventana pasa a fullscreen con cambio de resolución incluido.
		M_PANTALLA_COMPLETA_SIMULADA, //La pantalla pasa a fullscreen simulando el cambio de resolución.
		M_MAX_MODO};

	private:

	//Propiedades...	

	SDL_Window * ventana;
	SDL_Renderer * renderer;
	SDL_Rect simulacro_caja; //El simulacro de caja es un rectángulo con las medidas de la pantalla, para controlar lo que se muestra o no.
	unsigned int volcados;	//Volcados desde el último flipe.

	int w; //Ancho y alto de la ventana...
	int h;
	unsigned short int modo_ventana;
	bool comprobar_en_toma;

	int w_logico; //Ancho y alto del renderer.
	int h_logico;

	//Métodos privados.

	void cortar_caja_a_pantalla(SDL_Rect *);
	void configurar();
	
	public:

	//Interfaz pública.

	Pantalla(int=640, int=400, short unsigned int=M_VENTANA);
	~Pantalla();

	SDL_Window * acc_ventana() const {return this->ventana;}
	SDL_Renderer * acc_renderer() const {return this->renderer;}
	unsigned int acc_volcados() const {return this->volcados;}
	void establecer_titulo(const char * p_cadena);
	unsigned short int acc_modo_ventana() const {return modo_ventana;}

	void inicializar();
	void inicializar(int, int);
	void establecer_modo_ventana(unsigned int);
	void establecer_medidas_logicas(int, int);
	void rellenar(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Rect const&);
	void limpiar(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void actualizar();

//TODO?????
//	SDL_PixelFormat * obtener_formato_pixeles() {return this->superficie->format;}
//TODO?????

	void preparar_para_camara(Camara const&);
	void establecer_clip_para_camara(Camara const&);
	void establecer_clip(SDL_Rect);
	void reiniciar_clip_completo();
	const SDL_Rect acc_simulacro_caja() {return this->simulacro_caja;}
};

} //Fin namespace DLibV

#endif
