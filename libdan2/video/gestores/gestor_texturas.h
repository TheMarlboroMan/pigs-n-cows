#ifndef GESTOR_TEXTURAS_H
#define GESTOR_TEXTURAS_H

#include "../textura/textura.h"
#include "../../herramientas/templates/gestor_mapa_static.h"

namespace DLibV
{


class Gestor_texturas:public DLibH::Gestor_mapa_static<int, DLibV::Textura *>
{
	public:

	static int insertar(int, DLibV::Textura *);
	static DLibV::Textura * obtener(int);
	static void liberar();
	static int cantidad();
};

} //Fin namespace DLibV

#endif
