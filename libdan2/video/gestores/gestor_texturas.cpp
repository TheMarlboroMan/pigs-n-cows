#include "gestor_texturas.h"

using namespace DLibV;

int Gestor_texturas::insertar(int p_clave, DLibV::Textura * p_rec)
{
	int resultado=DLibH::Gestor_mapa_static<int, DLibV::Textura *>::insertar(p_clave, p_rec);
	return resultado;
}

/*Ojo: cosa puede ser NULL una vez que todo esto haya finalizado. Habría que hacer
control de errores en el código cliente*/

DLibV::Textura * Gestor_texturas::obtener(int p_clave)
{
	DLibV::Textura * resultado=DLibH::Gestor_mapa_static<int, DLibV::Textura *>::obtener(p_clave);
	return resultado;
}

void Gestor_texturas::liberar()
{
	if(DLibH::Gestor_mapa_static<int, DLibV::Textura *>::cantidad()) 
		DLibH::Gestor_mapa_static<int, DLibV::Textura *>::vaciar();
}

int Gestor_texturas::cantidad()
{
	return DLibH::Gestor_mapa_static<int, DLibV::Textura *>::cantidad();
}
