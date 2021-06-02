#include "representacion_primitiva.h"

using namespace DLibV;

Representacion_primitiva::Representacion_primitiva(Uint8 pr, Uint8 pg, Uint8 pb)
	:Representacion(), r(pr), g(pg), b(pb),
	recomponer_recorte_con_posicion(true), parametro_metodo_pixeles(NULL)
{

}

Representacion_primitiva::Representacion_primitiva(const Representacion_primitiva& p_otra)
	:Representacion(p_otra),
	r(p_otra.r), g(p_otra.g), b(p_otra.b),
	recomponer_recorte_con_posicion(p_otra.recomponer_recorte_con_posicion),
	parametro_metodo_pixeles(p_otra.parametro_metodo_pixeles)
{

}

Representacion_primitiva& Representacion_primitiva::operator=(const Representacion_primitiva& p_otra)
{
	Representacion::operator=(p_otra);
	r=p_otra.r;
	g=p_otra.g;
	b=p_otra.b;
	recomponer_recorte_con_posicion=p_otra.recomponer_recorte_con_posicion;
	parametro_metodo_pixeles=p_otra.parametro_metodo_pixeles;

	return *this;
}

Representacion_primitiva::~Representacion_primitiva()
{
	this->parametro_metodo_pixeles=NULL;
}

void Representacion_primitiva::recorte_a_posicion()
{
	SDL_Rect pos=acc_posicion();

	//Ojo con esto: si no tiene valor lo ponemos a 1. Esto puede ser
	//en cuyo caso se calcularía el ancho o alto como cero.
	//el caso de una línea completamente vertical u horizontal, por ejemplo,

	int w=pos.w ? pos.w : 1;
	int h=pos.h ? pos.h : 1;
	
	establecer_recorte(0, 0, w, h);
}

/* Esto se usa para obtener la caja de dibujo final de una primitiva gráfica
una vez aplicadas las posibles transformaciones de cámaras y demás. Esta caja
se usa en los métodos que manipulan los píxeles de la superficie en las
primitivas. Devolverá falso si no se puede dibujar y verdadero si se puede. 
El primer parámetro es de lectura y escritura: en él se devolverá la caja si es 
dibujable.
*/

bool Representacion_primitiva::determinar_caja_dibujo_final(SDL_Rect &p_caja, SDL_Rect const& p_posicion, SDL_Rect const& p_vista)
{
	//Usando los datos que tenemos calculamos el tamaño de la caja en 
	//la que vamos a dibujar. Lo hemos hecho con papel cuadriculado y puro empirismo.

	SDL_Rect pos=acc_posicion();
	SDL_Rect rec=acc_recorte();

	int x_caja=p_posicion.x+pos.x+rec.x-p_vista.x;
	int y_caja=p_posicion.y+pos.y+rec.y-p_vista.y;
	SDL_Rect p_caja_dibujo=DLibH::Herramientas_SDL::nuevo_sdl_rect(x_caja, y_caja, rec.w, rec.h);

	//Y ahora hacemos la intersección con la parte "dibujable":
	if(!DLibH::Herramientas_SDL::rectangulos_superpuestos(p_caja_dibujo, p_posicion, p_caja))
	{
		//Si no saldría pasamos.
		return false;
	}
	else
	{
		return true;
	}
}
