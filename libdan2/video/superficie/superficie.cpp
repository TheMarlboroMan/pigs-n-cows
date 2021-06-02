#include "superficie.h"

using namespace DLibV;

Superficie::Superficie():color_transparencia(0), transparencia_activa(false)
{

}

Superficie::~Superficie()
{
	if(this->superficie)
	{
		SDL_FreeSurface(this->superficie);
		this->superficie=NULL;
	}

}

Superficie& Superficie::operator=(const Superficie& p_otro)
{	
	this->color_transparencia=p_otro.color_transparencia;
	this->transparencia_activa=p_otro.transparencia_activa;

	this->superficie=Utilidades_graficas_SDL::copiar_superficie(p_otro.superficie);

	return *this;
}

Uint32 Superficie::color(unsigned int r, unsigned int g, unsigned int b)
{
	return SDL_MapRGB(superficie->format, r, g, b);
}

void Superficie::establecer_transparencia(Uint32 color)
{
	if(this->superficie)
	{
		SDL_SetColorKey(superficie, SDL_TRUE, color);
	}
	else 
	{
		DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Superficie::establecer_transparencia(Uint8, Uint8, Uint8, bool) : No hay superficie para recurso"<<std::endl;
	}
}

void Superficie::establecer_transparencia(Uint8 r, Uint8 g, Uint8 b)
{
	establecer_transparencia(color(r, g, b));
}

void Superficie::rellenar(Uint8 r, Uint8 g, Uint8 b)
{
	if(this->superficie) 
	{
		this->rellenar(color(r,g,b));
	}
	else
	{
		DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Superficie::rellenar(Uint8, Uint8, Uint8) : No hay superficie para recurso"<<std::endl;
	}
}

void Superficie::rellenar(Uint32 c)
{
	if(this->superficie) 
	{
		SDL_FillRect(this->superficie, NULL, c);
	}
	else 
	{
		DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Superficie::rellenar(Uint32) : No hay superficie para recurso"<<std::endl;
	}
}

void Superficie::limpiar_transparencia()
{
	if(this->superficie) 
	{
		SDL_SetColorKey(superficie, SDL_FALSE, 0); 
		this->transparencia_activa=false;
		this->color_transparencia=false;
	}
	else 
	{
		DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Superficie::limpiar_transparencia() : No hay superficie para recurso"<<std::endl;
	}
}

void Superficie::establecer_alpha(Uint8 p_valor)
{
	SDL_SetSurfaceAlphaMod(this->superficie, p_valor);
}

void Superficie::copiar_desde(Superficie const& p_recurso)
{
	SDL_BlitSurface(p_recurso.acc_superficie(), NULL, this->superficie, NULL);
}

void Superficie::copiar_desde(Superficie const& p_recurso, SDL_Rect p_rect_origen)
{
	SDL_BlitSurface(p_recurso.acc_superficie(), &p_rect_origen, this->superficie, NULL);
}

void Superficie::copiar_desde(Superficie const& p_recurso, SDL_Rect p_rect_origen, SDL_Rect p_rect_destino)
{
	SDL_BlitSurface(p_recurso.acc_superficie(), &p_rect_origen, this->superficie, &p_rect_destino);
}
