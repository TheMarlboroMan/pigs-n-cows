#include "gestor_superficies.h"

using namespace DLibV;

int Gestor_superficies::insertar(int p_clave, DLibV::Superficie * p_rec)
{
	int resultado=DLibH::Gestor_mapa_static<int, DLibV::Superficie *>::insertar(p_clave, p_rec);
	return resultado;
}

/*Ojo: cosa puede ser NULL una vez que todo esto haya finalizado. Habría que hacer
control de errores en el código cliente*/

DLibV::Superficie * Gestor_superficies::obtener(int p_clave)
{
	DLibV::Superficie * resultado=DLibH::Gestor_mapa_static<int, DLibV::Superficie *>::obtener(p_clave);
	return resultado;
}

void Gestor_superficies::liberar()
{
	if(DLibH::Gestor_mapa_static<int, DLibV::Superficie *>::cantidad()) 
		DLibH::Gestor_mapa_static<int, DLibV::Superficie *>::vaciar();
}

int Gestor_superficies::cantidad()
{
	return DLibH::Gestor_mapa_static<int, DLibV::Superficie *>::cantidad();
}
