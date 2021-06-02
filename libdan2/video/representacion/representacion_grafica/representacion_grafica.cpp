#include "representacion_grafica.h"

using namespace DLibV;

Representacion_grafica::Representacion_grafica()
	:Representacion(), textura(NULL), preparada(false)
{
	this->reiniciar_posicion();
	this->reiniciar_recorte();
}

Representacion_grafica::Representacion_grafica(const Representacion_grafica& o)
	:Representacion(o) ,textura(o.textura), preparada(o.preparada)
{

}

Representacion_grafica& Representacion_grafica::operator=(const Representacion_grafica& o)
{
	Representacion::operator=(o);
	textura=o.textura;
	preparada=o.preparada;

	return *this;
}

Representacion_grafica::~Representacion_grafica()
{
	//OJO: No se borra el recurso gráfico porque se asume que lo hemos
	//obtenido de un gestor de recursos. Esta clase base NO gestiona los
	//recursos asignados. Una superior, en cambio, si podría.
}

void Representacion_grafica::recorte_a_medidas_textura()
{
	establecer_recorte(0,0, textura->acc_w(), textura->acc_h());
}

bool Representacion_grafica::realizar_render(SDL_Renderer * p_renderer, SDL_Rect& rec, SDL_Rect& pos)
{
	SDL_Texture * tex=ref_textura_sdl();

	SDL_SetTextureAlphaMod(tex, acc_alpha());

	switch(acc_modo_blend())
	{
		case BLEND_NADA: SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE); break;
		case BLEND_ALPHA: SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND); break;
		case BLEND_SUMA: SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_ADD); break;
		case BLEND_MODULAR: SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_MOD); break;
	};

//	SDL_SetTextureColorMod(tex, acc_mod_color_r(), acc_mod_color_g(), acc_mod_color_b());

	if(!es_transformada())
	{
		return SDL_RenderCopy(p_renderer, tex, &rec,&pos) >= 0;
	}
	else
	{
		DLibV::Representacion_grafica_transformacion t=acc_transformacion();

		float angulo=t.obtener_angulo_rotacion();
		SDL_RendererFlip flip=t.obtener_flip();

		if(t.es_cambia_centro_rotacion())
		{
			SDL_Point centro=t.obtener_centro_rotacion();
			return SDL_RenderCopyEx(p_renderer, tex, &rec, &pos, angulo, &centro, flip) >= 0;
		}
		else
		{
			return SDL_RenderCopyEx(p_renderer, tex, &rec, &pos, angulo, NULL, flip) >= 0;
		}
	}
}

bool Representacion_grafica::volcado(SDL_Renderer * p_renderer)
{
	//Si no está en la pantalla no perdemos tiempo.
	if(!this->es_visible())
	{
		return false;
	}
	else
	{
		if(!this->es_preparada()) this->preparar();

		
		//Definimos aquí estas variables: puede que al "preparar" hayan cambiado los valores.
		SDL_Rect rec=acc_recorte();
		SDL_Rect pos=acc_posicion();
		SDL_Rect temp=DLibH::Herramientas_SDL::copiar_sdl_rect(pos, 0, 0);
		return realizar_render(p_renderer, rec, temp);
	}
}

bool Representacion_grafica::volcado(SDL_Renderer * p_renderer, const SDL_Rect& p_vista, const SDL_Rect& p_posicion, int desp_x, int desp_y)
{
	if(!this->es_visible())
	{
		return false;
	}
	else
	{	
		//Las representaciones estáticas están SIEMPRE en las mismas
		//posiciones para la cámara que la vea. Simplemente veremos
		//si está dentro de la caja de la cámara en 0,0.

		SDL_Rect pos=acc_posicion();
		bool en_toma=true;
		
		if(this->es_estatica())
		{
			SDL_Rect caja_cam=DLibH::Herramientas_SDL::nuevo_sdl_rect(0, 0, p_vista.w, p_vista.h);
			en_toma=DLibH::Herramientas_SDL::rectangulos_superpuestos(caja_cam, pos, true);
		}
		else
		{
			en_toma=DLibH::Herramientas_SDL::rectangulos_superpuestos(p_vista, pos, true);
		}

		if(!en_toma)
		{
			return false;
		}
		else
		{
			Sint16 t_x, t_y;

			if(!this->es_preparada()) this->preparar();

			SDL_Rect rec=acc_recorte();
			pos=acc_posicion();	//Again, por si al preparar ha cambiado.

			if(this->es_estatica())
			{
				t_x=p_posicion.x+desp_x;
				t_y=p_posicion.y+desp_y;
			}
			else
			{
				t_x=p_posicion.x-p_vista.x+desp_x;
				t_y=p_posicion.y-p_vista.y+desp_y;
			}

			pos.x+=t_x;
			pos.y+=t_y;
			SDL_Rect temp=DLibH::Herramientas_SDL::copiar_sdl_rect(pos, 0, 0);
			return realizar_render(p_renderer, rec, temp);
		}
	}
}

//Eso sólo deberíamos llamarlo en aquellas para las cuales hemos creado una
//textura que poseen. Si es parte de un recurso que no es de su propiedad
//te vas a encontrar con un problema.

void Representacion_grafica::liberar_textura()
{
	if(this->textura)
	{
		delete this->textura;
		this->textura=NULL;
	}
}

