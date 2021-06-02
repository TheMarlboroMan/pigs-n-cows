#ifndef CONTROLADOR_ARGUMENTOS_H
#define CONTROLADOR_ARGUMENTOS_H

#include <vector>
#include <string>
#include <iostream>

/*
Una clase simple que almacenará los argumentos que se pasen al programa.
*/

namespace DLibH
{

class Controlador_argumentos
{
	private:
	typedef std::vector<std::string> t_lista_argumentos;
	typedef std::string t_argumento;
	
	t_lista_argumentos argumentos;	

	public:

	Controlador_argumentos();
	Controlador_argumentos(int argc, char ** argv);
	~Controlador_argumentos();

	int buscar(const char * p_char) const;
	int buscar(t_argumento const& p_buscar) const;
	void inicializar(int argc, char ** argv);
	unsigned int obtener_cantidad() const;
	const t_argumento acc_argumento(unsigned int p_arg) const;
	const t_lista_argumentos& acc_argumentos() const;
};

}

#endif
