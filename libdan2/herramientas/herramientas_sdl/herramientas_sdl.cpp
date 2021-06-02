#include "herramientas_sdl.h"

using namespace DLibH;

void Herramientas_SDL::error()
{
	std::cout<<SDL_GetError();
}

bool Herramientas_SDL::iniciar_SDL(Uint32 p_flags)
{
	return SDL_Init(p_flags) >= 0;
}

void Herramientas_SDL::apagar_SDL()
{
	SDL_Quit();
}

bool Herramientas_SDL::arrancar_sistema_SDL(Uint32 p_flags)
{
	return SDL_InitSubSystem(p_flags)==0;
}

bool Herramientas_SDL::es_sistema_arrancado_SDL(Uint32 p_flags)
{
	return SDL_WasInit(p_flags)!=0;
}

void Herramientas_SDL::detener_sistema_SDL(Uint32 p_flags)
{
	SDL_QuitSubSystem(p_flags);
}

SDL_Rect Herramientas_SDL::copiar_sdl_rect(SDL_Rect const& p_original, Sint16 mod_x,  Sint16 mod_y, Uint16 mod_w, Uint16 mod_h)
{
	SDL_Rect resultado;
	resultado.x=p_original.x+mod_x;
	resultado.y=p_original.y+mod_y;
	resultado.w=p_original.w+mod_w;
	resultado.h=p_original.h+mod_h;

	return resultado;
}

SDL_Rect Herramientas_SDL::copiar_sdl_rect(SDL_Rect const* p_original, Sint16 mod_x,  Sint16 mod_y, Uint16 mod_w, Uint16 mod_h)
{
	return Herramientas_SDL::copiar_sdl_rect(*p_original, mod_x, mod_y, mod_w, mod_h);
}

SDL_Rect * Herramientas_SDL::copiar_sdl_rect_dinamico(SDL_Rect const& p_original, Sint16 mod_x,  Sint16 mod_y, Uint16 mod_w, Uint16 mod_h)
{
	SDL_Rect * resultado=new SDL_Rect();
	resultado->x=p_original.x+mod_x;
	resultado->y=p_original.y+mod_y;
	resultado->w=p_original.w+mod_w;
	resultado->h=p_original.h+mod_h;

	return resultado;
}

SDL_Rect * Herramientas_SDL::copiar_sdl_rect_dinamico(SDL_Rect const* p_original, Sint16 mod_x,  Sint16 mod_y, Uint16 mod_w, Uint16 mod_h)
{
	return Herramientas_SDL::copiar_sdl_rect_dinamico(*p_original, mod_x, mod_y, mod_w, mod_h);
}

SDL_Rect Herramientas_SDL::nuevo_sdl_rect(Sint16 mod_x, Sint16 mod_y, Uint16 mod_w, Uint16 mod_h)
{
	SDL_Rect resultado;
	resultado.x=mod_x;
	resultado.y=mod_y;
	resultado.w=mod_w;
	resultado.h=mod_h;

	return resultado;
}

 /*
Comprueba si dos rectángulos están superpuestos en sus dimensiones. El 
mátodo más rápido es el contrario: es decir, comprobar que NO se
superponen y luego negar el resultado.
Devuelve true si se superponen, false si no se superponen.
El tercer parámetro sirve para el tipo de comparación. Por defecto para
que haya colisión los valores tienen que superponerse y no simplemente
ser iguales.
*/

bool Herramientas_SDL::rectangulos_superpuestos(SDL_Rect const&plantilla, SDL_Rect const&comparado, bool roce_es_colision)
{
	Sint16 px=plantilla.x, py=plantilla.y, cx=comparado.x, cy=comparado.y;
	Uint16 pw=plantilla.w, ph=plantilla.h, cw=comparado.w, ch=comparado.h;


	return Herramientas::rectangulos_superpuestos(
			px, py, pw, ph,
			cx, cy, cw, ch,
			roce_es_colision);
}

bool Herramientas_SDL::segmentos_superpuestos(int aini, int afin, int bini, int bfin, bool roce_es_colision)
{
 	//Comparamos si está fuera y lo negamos...
        if(roce_es_colision)
        {
                return !( (bfin < aini) || (bini > afin) );
        }
        else
        {
                return !( (bfin <= aini) || (bini >= afin) );
        }
}

/*Con estos dos parámetros devuelve también la parte de las cajas que está DENTRO 
de la colisión dentro de esas propias cajas. Esto lo podemos usar para muchas
cosas luego, como para colisiones por píxeles y esas historias, o para determinar
el origen de una colisión.*/

bool Herramientas_SDL::rectangulos_superpuestos(const SDL_Rect& plantilla,  const SDL_Rect& comparado, SDL_Rect &resultado, bool roce_es_colision)
{
	Sint16 px=plantilla.x, py=plantilla.y, cx=comparado.x, cy=comparado.y, rx=resultado.x, ry=resultado.y;
	Uint16 pw=plantilla.w, ph=plantilla.h, cw=comparado.w, ch=comparado.h, rw=resultado.w, rh=resultado.h;

	bool res=Herramientas::rectangulos_superpuestos(
		px, py, pw, ph,
		cx, cy, cw, ch,
		rx, ry, rw, rh,
		roce_es_colision);

	resultado.x=rx;
	resultado.y=ry;
	resultado.w=rw;
	resultado.h=rh;

	return res;
}


/*
Calcula si las coordenadas dadas están dentro del bloque que
se pasa por referencia. Devuelve true si el par queda dentro del
rectángulo y false si queda fuera.
*/

bool Herramientas_SDL::punto_en_caja(SDL_Rect const& posicion, int x, int y)
{
	Sint16 px=posicion.x, py=posicion.y;
	Uint16 pw=posicion.w, ph=posicion.h;

	return Herramientas::punto_en_caja(px, py, pw, ph, x, y);
}

//Esto mide en relación con coordenadas de pantalla y no con un sistema
//cartesiano. Mide si la caja pequeña está contenida en la grande
//o si son iguales. En ambos casos devolvería verdadero.

bool Herramientas_SDL::caja_en_caja(SDL_Rect const& p_pequena, SDL_Rect const& p_grande)
{
	Sint16	px=p_pequena.x, py=p_pequena.y, gx=p_grande.x, gy=p_grande.y;
	Uint16	pw=p_pequena.w, ph=p_pequena.h, gw=p_grande.w, gh=p_grande.h;

	return Herramientas::caja_en_caja(px, py, pw, ph, gx, gy, gw, gh);
}

void Herramientas_SDL::copiar_caja_de_a(SDL_Rect const& p_origen, SDL_Rect & p_destino)
{
	p_destino.x=p_origen.x;
	p_destino.y=p_origen.y;
	p_destino.w=p_origen.w;
	p_destino.h=p_origen.h;
}

bool Herramientas_SDL::son_cajas_iguales(SDL_Rect const& p_a, SDL_Rect const& p_b)
{
	return p_a.x==p_b.x 
	&& p_a.y==p_b.y
	&& p_a.w==p_b.w
	&& p_a.h==p_b.h;
}

void Herramientas_SDL::describe_caja(SDL_Rect const & p_caja)
{
	std::cout<<p_caja.x<<","<<p_caja.y<<" ["<<p_caja.w<<"x"<<p_caja.h<<"]"<<std::endl; 
}
/*
float Herramientas_SDL::round(float r) {return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);}

void Herramientas_SDL::posicion_decimal_caja(SDL_Rect& p_caja, float p_x, float p_y)
{
	p_caja.x=Herramientas_SDL::round(p_x);
	p_caja.y=Herramientas_SDL::round(p_y);
}
*/
