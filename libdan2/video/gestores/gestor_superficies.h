#ifndef GESTOR_SUPERFICIES_H
#define GESTOR_SUPERFICIES_H

#include "../superficie/superficie.h"
#include "../../herramientas/templates/gestor_mapa_static.h"

namespace DLibV
{


class Gestor_superficies:public DLibH::Gestor_mapa_static<int, DLibV::Superficie *>
{
	public:

	static int insertar(int, DLibV::Superficie *);
	static DLibV::Superficie * obtener(int);
	static void liberar();
	static int cantidad();
};

} //Fin namespace DLibV

#endif
