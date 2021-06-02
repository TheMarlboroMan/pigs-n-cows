#include "representacion_texto.h"

using namespace DLibV;

Representacion_texto::Representacion_texto(const SDL_Renderer * r, const DLibV::Superficie * p_rep)
	:Representacion_grafica(),
	ancho_glifo(0), alto_glifo(0), interlineado(0), interletra(0), cadena(""),
	ancho_area(0), alto_area(0),
	color_fondo(0), 
	renderer(r),
	superficie_texto(NULL), 
	superficie_alfabeto(NULL)
{
	this->establecer_recurso_fuente(p_rep);
}

Representacion_texto::Representacion_texto(const Representacion_texto& p_otra)
	:
	Representacion_grafica(p_otra),
	ancho_glifo(p_otra.ancho_glifo), 
	alto_glifo(p_otra.alto_glifo), 
	interlineado(p_otra.interlineado), 
	interletra(p_otra.interletra), 
	cadena(p_otra.cadena),
	ancho_area(p_otra.ancho_area), 
	alto_area(p_otra.alto_area),
	color_fondo(p_otra.color_fondo), 
	renderer(p_otra.renderer),
	superficie_texto(NULL),
	superficie_alfabeto(p_otra.superficie_alfabeto)
{
	this->establecer_posicion(p_otra.acc_posicion());
	iniciar_recurso();
	preparar();
}

Representacion_texto::~Representacion_texto()
{
	liberar_textura();
	liberar_superficie_texto();
	superficie_alfabeto=NULL;	
}

Representacion_texto& Representacion_texto::operator=(const Representacion_texto& p_otra)
{
	Representacion_grafica::operator=(p_otra);

	ancho_glifo=p_otra.ancho_glifo;
	alto_glifo=p_otra.alto_glifo;
	interlineado=p_otra.interlineado;
	interletra=p_otra.interletra;
	cadena=std::string(p_otra.cadena);
	ancho_area=p_otra.ancho_area;
	alto_area=p_otra.alto_area;
	renderer=p_otra.renderer;
	superficie_texto=NULL;
	superficie_alfabeto=p_otra.superficie_alfabeto;
	iniciar_recurso();
	preparar();

	return *this;
}

void Representacion_texto::liberar_superficie_texto()
{
	if(superficie_texto) 
	{
		delete superficie_texto; //Ojo, es DLibV::Superficie, no SDL_Surface.
		superficie_texto=NULL;
	}
}


bool Representacion_texto::establecer_recorte_para_glifo(unsigned char p_char, SDL_Rect & p_caja_glifo)
{
	//Convertimos el código a las coordenadas que necesitamos...
	unsigned char codigo=p_char;
	bool resultado=false;

	switch(codigo)
	{
		case 10: resultado=false; break; //No imprimiremos nada.
			
		default:
			unsigned int fila=floor(codigo/T_GLIFOS_FILA);
			unsigned int columna=codigo % (T_GLIFOS_FILA);
			unsigned int p_x=columna * this->ancho_glifo;
			unsigned int p_y=fila * this->alto_glifo;

			p_caja_glifo.x=p_x;
			p_caja_glifo.y=p_y;

			resultado=true;	//Imprimiremos.
		break;
	}

	return resultado;	
}

/*
Este método se encarga de actualizar la posición de dibujo en función del 
carácter que se haya pasado. Básicamente, para una nueva línea vamos a saltar
a otra línea y para el resto vamos a ir hacia adelante.
*/

void Representacion_texto::establecer_posicion_para_glifo(unsigned char p_char, SDL_Rect & p_posicion_cursor, unsigned int x_original)
{
	switch(p_char)
	{
		case 10:
			p_posicion_cursor.y+=this->alto_glifo+this->interlineado;
			p_posicion_cursor.x=x_original;
		break;
			
		default:
			p_posicion_cursor.x+=this->ancho_glifo+this->interletra;
		break;
	}
}

/*En este método inicializamos la superficie en blanco a partir de la cual
vamos a generar la textura luego... Simplemente la creamos en su tamaño
y le damos el color de fondo.*/

void Representacion_texto::iniciar_recurso()
{
	//Este recurso es único, no se almacena...
	//A partir de este momento esta clase es RESPONSABLE de
	//liberarlo. 

	if(!superficie_texto && superficie_alfabeto)
	{
		superficie_texto=DLibV::Lienzo::generar_nuevo(ancho_area, alto_area, superficie_alfabeto->acc_superficie());

		//El orden de los factores altera (y mucho) el producto:
		//si le decimos que establezca la clave de color sin
		//antes asignar un recurso explotará. Asignar la clave
		//de color tiene como conscuencia que se aplica a la
		//superficie de forma instantánea. 

//		this->establecer_recurso(l);
//		Representacion_manual::establecer_clave_color(this->superficie_alfabeto);
//		this->color_fondo=Representacion_manual::acc_clave_color();
//		this->ref_recurso()->rellenar(this->color_fondo);

		color_fondo=superficie_alfabeto->acc_color_transparencia();


		superficie_texto->establecer_transparencia(color_fondo);
		superficie_texto->rellenar(color_fondo);

		//Al crear la superficie ya le damos un ancho y alto. Ojo a las flags: no la estamos moviendo.
		this->establecer_posicion(0,0,this->ancho_area, this->alto_area, FRECT_W | FRECT_H);
	}
}


void Representacion_texto::establecer_dimensiones_area(unsigned int p_ancho, unsigned int p_alto)
{
	this->ancho_area=p_ancho;
	this->alto_area=p_alto;
	Representacion_grafica::marcar_como_no_preparada();
}

/*Esta escribe realmente el texto...*/

void Representacion_texto::preparar()
{
	if(superficie_alfabeto && superficie_texto)
	{			
		unsigned int x_retorno_carro=0;
		unsigned char c, c_aux;

//		this->ref_recurso()->rellenar(this->color_fondo);

		SDL_Rect caja_glifo; 			
		caja_glifo.x=0;
		caja_glifo.y=0;
		caja_glifo.w=this->ancho_glifo;
		caja_glifo.h=this->alto_glifo;

		SDL_Rect posicion_cursor=caja_glifo;
		x_retorno_carro=caja_glifo.x;

		std::string::iterator it=this->cadena.begin(),
					fin=this->cadena.end();

		//Se hace blit en la superficie intermedia...

		for(;it < fin; it++)
		{
			c=(unsigned char)*it;

			if(DLibH::Herramientas::es_inicio_utf8_2b(c))
			{
				it++;
				c_aux=*it;

				c=DLibH::Herramientas::utf8_2b_a_uchar(c, c_aux);
			}

			//OJO: No podemos mover el cursor ANTES de pintar... En este método se
			//seleccionaría la posición pero el movimiento sería después.

			if(this->establecer_recorte_para_glifo(c, caja_glifo))
			{
				SDL_BlitSurface(superficie_alfabeto->acc_superficie(), &caja_glifo, superficie_texto->acc_superficie(), &posicion_cursor);
			}

			//Luego, haya que dibujar o no, movemos el cursor.
			this->establecer_posicion_para_glifo(c, posicion_cursor, x_retorno_carro);
		}

		SDL_Surface * sur=superficie_texto->acc_superficie();

		//A partir de este momento la textura es propiedad del objeto.
		DLibV::Textura * tex=new DLibV::Textura(renderer, sur);
		establecer_textura(tex);
		establecer_modo_blend(Representacion::BLEND_ALPHA);

		establecer_recorte(0, 0, ancho_area, alto_area);
		liberar_superficie_texto();

		marcar_como_preparada();
	}
	else
	{
		DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Representacion_texto::preparar() NO HAY RECURSO"<<std::endl;
	}
}

/*
Establece el recurso gráfico que será la fuente y también el ancho y alto
de los glifos a partir del tamaño de dicho recurso.
*/

void Representacion_texto::establecer_recurso_fuente(DLibV::Superficie const * p_recurso)
{
	superficie_alfabeto=p_recurso;	//Esto es la superficie de alfabeto.

	//Establecer tamaño de glifos... Debe haber 16 filas y 16 columnas.
	ancho_glifo=superficie_alfabeto->acc_w() / 16;
	alto_glifo=superficie_alfabeto->acc_h() / 16;
}

/*Destruye el original y pone el nuevo...*/

void Representacion_texto::modificar_fuente(DLibV::Superficie const * p_recurso)
{
	this->establecer_recurso_fuente(p_recurso);
	this->asignar(this->cadena);
}

////////////////////////////////////////////////////////////////////////
//Estos métodos afectan a la cadena.

void Representacion_texto::asignar(const char * p_param)
{
	this->cadena.assign(p_param);
	Representacion_grafica::marcar_como_no_preparada();
}

void Representacion_texto::asignar(const char p_param)
{
	//Hay que joderse...
	std::string cosa("");
	cosa+=p_param;

	this->cadena.assign(cosa);
	Representacion_grafica::marcar_como_no_preparada();
}


void Representacion_texto::asignar(std::string const& p_param)
{
	this->cadena=p_param;
	Representacion_grafica::marcar_como_no_preparada();
}
