#include "representacion_primitiva_caja.h"

using namespace DLibV;

Representacion_primitiva_caja::Representacion_primitiva_caja(const SDL_Rect& p_pos, Uint8 pr, Uint8 pg, Uint8 pb)
	:Representacion_primitiva(pr, pg, pb)
{
	establecer_posicion(p_pos);
	this->preparar_posicion();
}

Representacion_primitiva_caja::Representacion_primitiva_caja(const Representacion_primitiva_caja& p_otra)
	:Representacion_primitiva(p_otra)
{

}

Representacion_primitiva_caja& Representacion_primitiva_caja::operator=(const Representacion_primitiva_caja& p_otro)
{
	Representacion_primitiva::operator=(p_otro);
	return *this;
}

Representacion_primitiva_caja::~Representacion_primitiva_caja()
{

}

bool Representacion_primitiva_caja::volcado(SDL_Renderer * p_renderer)
{
	if(!es_visible()) return false;
	SDL_Rect pos=acc_posicion();

	Uint8 alpha=acc_alpha();
	if(alpha) SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_BLEND);
	else SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_NONE);

	SDL_SetRenderDrawColor(p_renderer, acc_r(), acc_g(), acc_b(), alpha);
	SDL_RenderFillRect(p_renderer, &pos);
	return true;
}

bool Representacion_primitiva_caja::volcado(SDL_Renderer * p_renderer, const SDL_Rect& p_vista, const SDL_Rect& p_posicion, int desp_x, int desp_y)
{
	if(!es_visible()) return false;

	SDL_Rect caja;
	SDL_Rect pos=acc_posicion();
	caja.x=pos.x+p_posicion.x-p_vista.x;
	caja.y=pos.y+p_posicion.y-p_vista.y;
	caja.w=pos.w;
	caja.h=pos.h;

	Uint8 alpha=acc_alpha();
	if(alpha) SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_BLEND);
	else SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_NONE);

	SDL_SetRenderDrawColor(p_renderer, acc_r(), acc_g(), acc_b(), alpha);
	SDL_RenderFillRect(p_renderer, &caja);
	return true;
}

void Representacion_primitiva_caja::preparar_posicion()
{
	//No hace nada.
}	
