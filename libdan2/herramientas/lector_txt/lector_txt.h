#ifndef LECTOR_TXT_LIBDAN2
#define LECTOR_TXT_LIBDAN2

#include <string>
#include <fstream>

namespace DLibH
{

class Lector_txt
{
	private:

	unsigned int numero_linea;
	char comentario;
	std::string linea_actual;
	std::ifstream archivo;

	public:

	Lector_txt();
	Lector_txt(const std::string& ruta, const char comentario);
	~Lector_txt();

	std::string leer_linea();
	void abrir_archivo(const std::string&);

	/*explicit*/ operator bool() const {return archivo.is_open();}
	bool is_eof() const {return archivo.eof();}
	unsigned int obtener_numero_linea() const {return numero_linea;}
	char obtener_comentario() const {return comentario;}
	const std::string& obtener_linea_actual() {return linea_actual;}
	void establecer_comentario(const char v) {comentario=v;}
};
}

#endif
