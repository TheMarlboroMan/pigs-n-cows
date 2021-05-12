#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <string>
#include "visitante.h"
#include "animales_voladores.h"
#include "animales_tierra.h"
#include "decoraciones.h"
#include "decoraciones_moviles.h"
#include "visitante_app.h"
#include "cielo.h"
#include "apuntador.h"
#include "marcadores.h"
#include "bonus.h"


class Controlador
{
	private:

	DLibV::Pantalla pantalla;
	DLibH::Controlador_fps_SDL control_frames;
	DLibI::Controles_SDL controles_sdl;
	DLibA::Controlador_audio_SDL * controlador_audio;
	DLibA::Cola_sonido cola_sonido;

	std::vector<Actor *> actores;

	Marcadores marcadores;
	Apuntador apuntador;
	Cielo cielo;

	float t;
	bool pantalla_completa,
	intro{true};
	const std::string app_path;

	enum sonidos
	{
		SND_CERDITO=1,
		SND_VAQUITA,
		SND_OVACION,
		SND_BONUS
	};


	void inicializar_recursos_audio()
	{
		DLibA::Controlador_audio_SDL::configurar_ratio(41000);
		DLibA::Controlador_audio_SDL::configurar_salidas(2);
		DLibA::Controlador_audio_SDL::configurar_buffers(8);
		DLibA::Controlador_audio_SDL::configurar_canales_audio(8);

		controlador_audio=DLibA::Controlador_audio_SDL::obtener();
		controlador_audio->iniciar();

		std::string pig_snd=app_path+"data/cerdito.ogg";
		std::string cow_snd=app_path+"data/vaquita.ogg";
		std::string applause_snd=app_path+"data/ovacion.ogg";
		std::string item_snd=app_path+"data/item.ogg";

		DLibA::Gestor_recursos_audio::insertar_sonido(SND_CERDITO, pig_snd.c_str());
		DLibA::Gestor_recursos_audio::insertar_sonido(SND_VAQUITA, cow_snd.c_str());
		DLibA::Gestor_recursos_audio::insertar_sonido(SND_OVACION, applause_snd.c_str());
		DLibA::Gestor_recursos_audio::insertar_sonido(SND_BONUS, item_snd.c_str());
	}

	void inicializar_recursos_graficos()
	{
		unsigned int r=0;
		unsigned int g=255;
		unsigned int b=255;

		DLibV::Imagen * img=NULL;
		DLibV::Imagen * img2=NULL;
		DLibV::Imagen * img3=NULL;
		DLibV::Imagen * img4=NULL;

		img=new DLibV::Imagen(app_path+"data/img.png");
		if(DLibV::Gestor_recursos_graficos::insertar(1, img)!=-1)
		{
			DLibV::Gestor_recursos_graficos::obtener(1)->establecer_transparencia(r, g, b);
		}

		img2=new DLibV::Imagen(app_path+"data/fondo.png");
		if(DLibV::Gestor_recursos_graficos::insertar(2, img2)!=-1)
		{
			DLibV::Gestor_recursos_graficos::obtener(2)->establecer_transparencia(r, g, b);
		}

		img3=new DLibV::Imagen(app_path+"data/fuente.png");
		if(DLibV::Gestor_recursos_graficos::insertar(3, img3)!=-1)
		{
			DLibV::Gestor_recursos_graficos::obtener(3)->establecer_transparencia(0, 0, 0);
		}

		img4=new DLibV::Imagen(app_path+"data/logo.png");
		if(DLibV::Gestor_recursos_graficos::insertar(4, img4)!=-1)
		{
			DLibV::Gestor_recursos_graficos::obtener(4)->establecer_transparencia(r, g, b);
		}

		cielo.configurar();
	}

	void representar()
	{
		std::vector<const Representable *> rep;

		Fondo f;
		rep.push_back(&f);

		Visitante_generar_representables vis;
		for(Actor * a : actores) a->aceptar_visitante(vis);
		const std::vector<const Representable *> ract=vis.acc_vector_representables();
		for(const Representable * const r : ract) rep.push_back(r);

		SDL_Rect posicion;
		SDL_Rect recorte;
		unsigned int recurso=0;
		unsigned int alpha=0;

		DLibV::Representacion_bitmap_dinamica rd;
		cielo.dibujar(pantalla);

		Granja g;
		rep.push_back(&g);

		Logo l;
		if(intro) {

			rep.push_back(&l);
		}

		for(const Representable * const r : rep)
		{
			alpha=r->obtener_alpha();
			recurso=r->obtener_recurso();
			r->configurar_posicion(posicion);
			r->configurar_recorte(recorte);

			rd.establecer_alpha(alpha);
			rd.establecer_recurso(DLibV::Gestor_recursos_graficos::obtener(recurso));
			rd.establecer_recorte(recorte);
			rd.establecer_posicion(posicion);
			rd.volcar(pantalla);
		}

		if(!intro) {
	
			apuntador.dibujar(pantalla);
			marcadores.dibujar(pantalla);
		}
		else {

			std::string cadena=" FRIENDLY UNIVERSE\n\nPRESS SPACE TO PLAY";
			DLibV::Representacion_texto_auto_estatica txt(DLibV::Gestor_recursos_graficos::obtener(3), cadena);
			txt.establecer_posicion(280, 420);
			txt.volcar(pantalla);
		}

		pantalla.flipar();
	}

	void interpretar_mensaje(const Mensaje_controlador& m)
	{
		switch(m.tipo)
		{
			case Mensaje_controlador::T_ARCO_IRIS:
				nuevo_arco_iris(m.x, m.y);
			break;

			case Mensaje_controlador::T_CERDITO_TIERRA:
				nuevo_cerdito_tierra(m.x, m.y);
			break;

			case Mensaje_controlador::T_VAQUITA_TIERRA:
				nueva_vaquita_tierra(m.x, m.y);
			break;

			case Mensaje_controlador::T_DEVOLVER_CERDITO:
				marcadores.devolver_cerdito();
			break;

			case Mensaje_controlador::T_DEVOLVER_VAQUITA:
				marcadores.devolver_vaquita();
			break;

/*			case Mensaje_controlador::T_OVACION:
			{
				DLibA::Estructura_sonido es(DLibA::Gestor_recursos_audio::obtener_sonido(SND_OVACION));
				controlador_audio->reproducir_sonido(es);
			}
			break;
*/
		}
	}

	void paso(float delta)
	{
		t+=delta;
		cielo.turno(delta);

		if(t >= 1.000)
		{
			nueva_nube();
			nuevo_bonus();

			t=0.0;
		}

		//Procesar pasos.
		for(Actor * a : actores) a->paso(delta);

		//Procesar las colisiones...
		Visitante_colisiones vcol;
		for(Actor * a : actores) a->aceptar_visitante(vcol);
		if(vcol.procesar())
		{
			std::vector<const Actor *> para_borrar=vcol.acc_para_borrar();
			for(const Actor * ab : para_borrar)
				for(Actor * a : actores)
					if( &(*a)== &(*ab) ) a->forzar_borrado();

			unsigned int puntos_obtenidos=vcol.acc_puntuacion();
			if(puntos_obtenidos)
			{

				int id_sonido=SND_BONUS;
				if(marcadores.sumar_puntuacion(puntos_obtenidos))
				{
					id_sonido=SND_OVACION;
					marcadores.aumentar_disponibles();
				}
				DLibA::Estructura_sonido es(DLibA::Gestor_recursos_audio::obtener_sonido(id_sonido));
				controlador_audio->reproducir_sonido(es);
			}
		}

		//Procesar el turno de mensaje de cada uno...
		Visitante_mensajes vis;
		for(Actor * a : actores) a->aceptar_visitante(vis);

		const std::vector<Mensaje_controlador> vm=vis.acc_vector_mensajes();
		for(const Mensaje_controlador m : vm) interpretar_mensaje(m);

		//Procesar los borrados.
		std::vector<Actor *>::iterator ini=actores.begin(),
						fin=actores.end();

		while(ini < fin)
		{
			Actor * a=(*ini);

			if(a->es_para_borrar())
			{
				delete a;
				ini=actores.erase(ini);
				fin=actores.end();
			}
			else
			{
				++ini;
			}
		}
	}

	void nuevo_arco_iris(float x, float y)
	{
		Arco_iris * a=new Arco_iris();
		a->establecer_posicion(x, y);
		actores.push_back(a);
	}

	void nuevo_cerdito_tierra(float x, float y)
	{
		float velocidad=DLibH::Herramientas::obtener_aleatorio_tramo(60, 200);

		Cerdito_tierra * c=new Cerdito_tierra();
		c->establecer_posicion(x, y);
		c->configurar(velocidad);
		actores.push_back(c);
	}

	void nueva_vaquita_tierra(float x, float y)
	{
		float velocidad=DLibH::Herramientas::obtener_aleatorio_tramo(40, 120);

		Vaquita_tierra * c=new Vaquita_tierra();
		c->establecer_posicion(x, y);
		c->configurar(velocidad);
		actores.push_back(c);
	}

	void nuevo_animal()
	{
		Animal_volador * c=NULL;

		unsigned int tipo_animal=marcadores.acc_tipo_animal_actual();
		unsigned int id_sonido=0;
		switch(tipo_animal)
		{
			case Marcadores::T_VAQUITA:
				c=new Vaquita();
				id_sonido=SND_VAQUITA;
				marcadores.lanzar_vaquita();
			break;


			case Marcadores::T_CERDITO:
				c=new Cerdito();
				id_sonido=SND_CERDITO;
				marcadores.lanzar_cerdito();
			break;
		}

		if(id_sonido)
		{
			DLibA::Estructura_sonido es(DLibA::Gestor_recursos_audio::obtener_sonido(id_sonido));
			controlador_audio->reproducir_sonido(es);
		}

		if(c)
		{
			c->establecer_posicion(Apuntador::X, Apuntador::Y);
			float angulo=apuntador.acc_angulo(); //Transformacion del ángulo.
			float velocidad=apuntador.acc_fuerza(); //DLibH::Herramientas::obtener_aleatorio_tramo(200, 600);
			c->configurar(angulo, velocidad);
			actores.push_back(c);
		}
	}

	void nueva_nube()
	{
		int tirada=DLibH::Herramientas::obtener_aleatorio_tramo(0, 10);

		if(tirada >= 5)
		{
			Nube * n=new Nube();
			n->configurar();
			actores.push_back(n);
		}
	}

	void nuevo_bonus()
	{
		int tirada=DLibH::Herramientas::obtener_aleatorio_tramo(0, 10);

		if(tirada >= 3)
		{
			Bonus * b=new Bonus();
			b->configurar();
			actores.push_back(b);
		}
	}

	void inicializar_pantalla()
	{
		unsigned int flags_video=SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT;
		if(pantalla_completa) flags_video=flags_video | SDL_FULLSCREEN;
		pantalla.inicializar(Definiciones::W_AREA, Definiciones::H_AREA, 0, flags_video);
	}

	void cambiar_pantalla_completa()
	{
		pantalla_completa=!pantalla_completa;
		inicializar_pantalla();
	}

	public:

	Controlador(
		const std::string _app_path
	):
		control_frames(60),
		t(0.0),
		pantalla_completa(false),
#ifdef AS_APPIMAGE
		app_path{_app_path+"../share/"}
#else
		app_path(_app_path)
#endif
	{
		control_frames.inicializar();

		inicializar_pantalla();
		pantalla.establecer_titulo("Pigs and Cows - friendly universe");
		DLibV::Utilidades_graficas_SDL::mostrar_ocultar_cursor(false);
		DLibV::Gestor_color::establecer_formato(pantalla.obtener_formato_pixeles());

		inicializar_recursos_graficos();
		inicializar_recursos_audio();
	}

	bool intro_loop() {

		float delta=control_frames.obtener_delta();
		if(delta > Definiciones::MAX_DELTA) delta=Definiciones::MAX_DELTA;

//		paso(delta);
		representar();

		control_frames.turno();
		controles_sdl.recoger();

		if(controles_sdl.es_tecla_down(SDLK_SPACE)) {

			intro=false;
			return true;
		}

		if(controles_sdl.es_senal_salida() ||
			controles_sdl.es_tecla_down(SDLK_ESCAPE))
		{
			return false;
		}

		return true;
	}

	bool game_loop()
	{
		float delta=control_frames.obtener_delta();
		if(delta > Definiciones::MAX_DELTA) delta=Definiciones::MAX_DELTA;

		paso(delta);
		representar();

		control_frames.turno();
		controles_sdl.recoger();

		if(controles_sdl.es_tecla_pulsada(SDLK_SPACE)) apuntador.sumar_fuerza(delta);
		else if(controles_sdl.es_tecla_up(SDLK_SPACE))
		{
			if(marcadores.hay_animales_disponibles()) nuevo_animal();
			apuntador.reiniciar_fuerza();
		}

		if(controles_sdl.es_tecla_down(SDLK_f)) cambiar_pantalla_completa();
		if(controles_sdl.es_tecla_pulsada(SDLK_UP)) apuntador.cambiar_angulo(-1, delta);
		else if(controles_sdl.es_tecla_pulsada(SDLK_DOWN)) apuntador.cambiar_angulo(1, delta);

		if(controles_sdl.es_tecla_down(SDLK_LEFT)) marcadores.cambiar_tipo_animal(-1);
		else if(controles_sdl.es_tecla_down(SDLK_RIGHT)) marcadores.cambiar_tipo_animal(1);

		if(controles_sdl.es_senal_salida() ||
			controles_sdl.es_tecla_down(SDLK_ESCAPE))
		{
			return false;
		}

		return true;
	}

	bool loop() {

		return intro ? intro_loop() : game_loop();
	}
	
};


#endif
