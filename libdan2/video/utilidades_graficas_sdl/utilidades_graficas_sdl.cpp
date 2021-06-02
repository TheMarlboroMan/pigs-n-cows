#include "utilidades_graficas_sdl.h"

using namespace DLibV;


SDL_Surface * Utilidades_graficas_SDL::nueva_superficie_formato(SDL_Surface const * p_origen)
{
	SDL_Rect caja;
	caja.x=0;
	caja.y=0;
	caja.w=p_origen->w;
	caja.h=p_origen->h;

	return nueva_superficie_formato(p_origen, caja, 0, 0);
}

SDL_Surface * Utilidades_graficas_SDL::nueva_superficie_formato(SDL_Surface const * p_origen, const SDL_Rect& p_caja, Uint32 p_flags, Uint32 p_color)
{
	SDL_Surface * origen=const_cast <SDL_Surface *> (p_origen);
	SDL_Surface * copia=NULL;

	copia=SDL_CreateRGBSurface(
//		origen->flags|p_flags,
		p_flags,
		p_caja.w, p_caja.h, origen->format->BitsPerPixel,
		origen->format->Rmask, origen->format->Gmask, origen->format->Bmask, origen->format->Amask);

	SDL_FillRect(copia, NULL, p_color);

	return copia;
}

SDL_Surface * Utilidades_graficas_SDL::copiar_superficie(SDL_Surface const * p_origen)
{
	SDL_Rect p_caja;
	p_caja.x=0;
	p_caja.y=0;
	p_caja.w=p_origen->w;
	p_caja.h=p_origen->h;

	Uint32 p_flags=p_origen->flags;	
	Uint32 p_color=0;	

	return copiar_superficie(p_origen, p_caja, p_flags, p_color);
}

SDL_Surface * Utilidades_graficas_SDL::copiar_superficie(SDL_Surface const * p_origen, const SDL_Rect& p_caja, Uint32 p_flags, Uint32 p_color)
{
	SDL_Surface * copia=Utilidades_graficas_SDL::nueva_superficie_formato(p_origen, p_caja, p_flags, p_color);
	SDL_Surface * origen=const_cast <SDL_Surface *> (p_origen);
	SDL_Rect * caja=const_cast <SDL_Rect *> (&p_caja);

	if(copia)
	{
		SDL_BlitSurface(origen, caja, copia, NULL);
	}

	return copia;
}

SDL_Surface * Utilidades_graficas_SDL::cargar_imagen(const char * cadena, const SDL_Window * ventana)
{
	SDL_Surface * temporal=IMG_Load(cadena);
	if (!temporal) {
			DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Utilidades_graficas_SDL::cargar_imagen() : Imagen no cargada:"<<cadena<<std::endl;
			return NULL;
	}
	else {
		
		if(!ventana) {
			return temporal;
		}
		else {
		
			Uint32 formato=SDL_GetWindowPixelFormat(const_cast<SDL_Window *>(ventana));
			SDL_Surface * optimizada=SDL_ConvertSurfaceFormat(temporal, formato, 0);
        	        SDL_FreeSurface(temporal);
			return optimizada;
		}
	}
}

void Utilidades_graficas_SDL::mostrar_ocultar_cursor(bool p_modo)
{
	SDL_ShowCursor(p_modo);
}

SDL_Texture * Utilidades_graficas_SDL::cargar_textura_desde_superficie(const SDL_Renderer * renderer, const SDL_Surface * superficie)
{
	SDL_Renderer * ren=const_cast<SDL_Renderer *>(renderer);
	SDL_Surface * sur=const_cast<SDL_Surface *>(superficie);
	SDL_Texture * textura=SDL_CreateTextureFromSurface(ren, sur);

	if(!textura)
	{
		DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Utilidades_graficas_SDL::cargar_textura_desde_superficie() : textura no cargada"<<std::endl;
		return NULL;
	}
	else
	{
		return textura;
	}
}

SDL_Texture * Utilidades_graficas_SDL::copiar_textura(const SDL_Renderer * renderer, const SDL_Texture * textura)
{	
	SDL_Renderer * ren=const_cast<SDL_Renderer *>(renderer);
	SDL_Texture * tex=const_cast<SDL_Texture *>(textura);

	Uint32 pformat=0;
	int pa=0, pw=0, ph=0;

	if(SDL_QueryTexture(tex, &pformat, &pa, &pw, &ph) < 0)
	{
		DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Utilidades_graficas_SDL::copiar textura : fallo al lanzar QueryTexture"<<std::endl;
		return NULL;
	}
	else
	{
		SDL_Texture * resultado=SDL_CreateTexture(ren, pformat, SDL_TEXTUREACCESS_TARGET, pw, ph);

		if(!resultado)
		{
			DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Utilidades_graficas_SDL::copiar textura : fallo al crear textura"<<std::endl;
			return NULL;
		}
		else
		{
			if(SDL_SetRenderTarget(ren, resultado) < 0)
			{
				DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Utilidades_graficas_SDL::copiar textura : error al apuntar textura como target"<<std::endl;
				return NULL;
			}
			else if(SDL_RenderCopy(ren, resultado, NULL, NULL) < 0)
			{
				DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Utilidades_graficas_SDL::copiar textura : fallo volcar textura"<<std::endl;
				return NULL;
			}
			else if(SDL_SetRenderTarget(ren, NULL) < 0)
			{
				DLibH::Log_motor::L()<<DLibH::Log_base_n(1)<<DLibH::Log_base_t()<<"Utilidades_graficas_SDL::copiar textura : error al restaurar target"<<std::endl;
				return NULL;
			}
		}

		return resultado;
	}
}

SDL_Texture * Utilidades_graficas_SDL::crear_textura(const SDL_Renderer * renderer, int pw, int ph, Uint32 pformat, int paccess)
{
	SDL_Renderer * ren=const_cast<SDL_Renderer *>(renderer);
	SDL_Texture * resultado=SDL_CreateTexture(ren, pformat, paccess, pw, ph);
	return resultado;
}

Uint32 Utilidades_graficas_SDL::SDL_GetPixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	
	/* Here p is the address to the pixel we want to retrieve */
	if(SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if(SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

	switch(bpp) 
	{
		case 1:
			return *p;
		break;

		case 2:
			return *(Uint16 *)p;
		break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) return p[0] << 16 | p[1] << 8 | p[2];
			else return p[0] | p[1] << 8 | p[2] << 16;
		break;

		case 4:
			return *(Uint32 *)p;
		break;

		default:
			return 0;       /* shouldn't happen, but avoids warnings */
		break;
	}
}
