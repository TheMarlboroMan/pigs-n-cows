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
#include "version.h"


class Controlador
{
	private:

	DLibV::Pantalla pantalla;
	DLibH::Controlador_fps_SDL control_frames;
	DLibI::Controles_SDL controles_sdl;
	DLibA::Controlador_audio_SDL * controlador_audio;
	DLibA::Cola_sonido cola_sonido;

	std::vector<Actor *> actores;
	std::vector<Actor *> nubes;

	Marcadores marcadores;
	Apuntador apuntador;
	Cielo cielo;

	enum class states{intro, help, game};

	float t;
	bool pantalla_completa;
	states state{states::intro};
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

		auto load_texture=[&](const std::string _path, int _id, int r, int g, int b) {
		
			SDL_Surface * superficie=DLibV::Utilidades_graficas_SDL::cargar_imagen(_path.c_str(), nullptr);

			if(!superficie) {			
				throw std::runtime_error("could not load image path");
			}
			
			SDL_SetColorKey(superficie, SDL_TRUE, SDL_MapRGB(superficie->format, r, g, b));
			DLibV::Textura * t=new DLibV::Textura(pantalla.acc_renderer(), superficie);

			if(DLibV::Gestor_texturas::insertar(_id, t)==-1) {
			
				throw std::runtime_error("could not upload texture");				
			}
		};
		
		auto load_surface=[&](const std::string _path, int _id, int r, int g, int b) {
		
			//SDL_Surface * superficie=DLibV::Utilidades_graficas_SDL::cargar_imagen(ruta.c_str(), pantalla.acc_ventana());
			SDL_Surface * superficie=DLibV::Utilidades_graficas_SDL::cargar_imagen(_path.c_str(), nullptr);

			if(!superficie) {
				throw std::runtime_error("could not load image path for surface");			
			}
			
			SDL_SetColorKey(superficie, SDL_TRUE, SDL_MapRGB(superficie->format, r, g, b));
			DLibV::Imagen * t=new DLibV::Imagen(superficie);

			if(DLibV::Gestor_superficies::insertar(_id, t)==-1) {
			
				throw std::runtime_error("could not upload surface");
			}
		};
		
		load_texture(app_path+"data/img.png", 1, r, g, b);
		load_texture(app_path+"data/fondo.png", 2, r, g, b);		
		load_texture(app_path+"data/logo.png", 4, r, g, b);
		load_surface(app_path+"data/fuente.png", 3, 0, 0, 0);		

		cielo.configurar();
	}

	void representar()
	{
		std::vector<const Representable *> rep;

		SDL_Rect posicion, recorte;
		DLibV::Representacion_bitmap_dinamica rd;

		auto draw=[&](const Representable * const r) {

			r->configurar_posicion(posicion);
			r->configurar_recorte(recorte);

			rd.establecer_textura(DLibV::Gestor_texturas::obtener(r->obtener_recurso()));
			rd.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
			rd.establecer_alpha(r->obtener_alpha());
			rd.establecer_recorte(recorte);
			rd.establecer_posicion(posicion);
			rd.volcar(pantalla);
		};

		cielo.dibujar(pantalla);

		Fondo f;
		draw(&f);

		Visitante_generar_representables vis;

		for(Actor * a : nubes) {
			a->aceptar_visitante(vis);
		}

		for(Actor * a : actores) {
			a->aceptar_visitante(vis);
		}

		const std::vector<const Representable *> ract=vis.acc_vector_representables();
		for(const Representable * const r : ract) {
			rep.push_back(r);
		}

		switch(state) {

			case states::game: {

				Granja g;
				draw(&g);

				for(const Representable * const r : rep) {
					draw(r);
				}

				apuntador.dibujar(pantalla, marcadores.hay_animales_disponibles());
				marcadores.dibujar(pantalla);
			}
			break;
			case states::intro: {

				for(const Representable * const r : rep) {
					draw(r);
				}

				Logo l;
				draw(&l);

				std::string cadena=" FRIENDLY UNIVERSE\n\n\nPRESS SPACE TO PLAY\n\n PRESS H FOR HELP";
				DLibV::Representacion_texto_auto_estatica txt(
					pantalla.acc_renderer(),
					DLibV::Gestor_superficies::obtener(3), 
					cadena
				);
				txt.establecer_posicion(250, 350);
				txt.volcar(pantalla);

				std::string version="2014 The Marlboro Man. v"
					+std::to_string(major_version)
					+"."
					+std::to_string(minor_version)
					+"."
					+std::to_string(patch_version);

				DLibV::Representacion_texto_auto_estatica vtxt(
					pantalla.acc_renderer(),
					DLibV::Gestor_superficies::obtener(3), 
					version
				);
				
				vtxt.establecer_posicion(320, 580);
				vtxt.volcar(pantalla);
			}
			break;
			case states::help: {

				for(const Representable * const r : rep) {
					draw(r);
				}

				std::string cadena=""
"               HELP:\n\n"
"  HOLD AND RELEASE SPACE TO LAUNCH\n"
"       UP-DOWN ARROWS TO AIM\n"
"LEFT-RIGHT ARROWS TO SWITCH ANIMALS\n"
"       HIT BALLOONS TO SCORE\n"
"CHAIN BALLOONS FOR SCORE MULTIPLIERS\n"
"         PIGS FLY FURTHER\n"
"       COWS GRANT MORE SCORE\n"
"ACCUMULATE SCORE TO WIN MORE ANIMALS\n"
"      F TO TOGGLE FULLSCREEN\n\n"
"        PRESS ESC TO RETURN";

				DLibV::Representacion_texto_auto_estatica txt(
					pantalla.acc_renderer(),
					DLibV::Gestor_superficies::obtener(3), 
					cadena
				);
				txt.establecer_posicion(120, 200);
				txt.volcar(pantalla);
			}
			break;
		}

		pantalla.actualizar();
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

	void paso(float delta) 	{

		t+=delta;
		cielo.turno(delta);

		//Procesar pasos.
		for(Actor * a : nubes) {
			a->paso(delta);
		}

		//Procesar los borrados.
		{
			std::vector<Actor *>::iterator ini=nubes.begin(),
						fin=nubes.end();

			while(ini < fin)
			{
				Actor * a=(*ini);

				if(a->es_para_borrar())
				{
					delete a;
					ini=nubes.erase(ini);
					fin=nubes.end();
				}
				else
				{
					++ini;
				}
			}
		}


		if(t >= 1.000)
		{
			nueva_nube();

			if(state==states::game) {

				nuevo_bonus();
			}

			t=0.0;
		}

		if(state!=states::game) {

			return;
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
			nubes.push_back(n);
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
		pantalla.inicializar(Definiciones::W_AREA, Definiciones::H_AREA);
		if(pantalla_completa) {
		
			pantalla.establecer_modo_ventana(DLibV::Pantalla::M_PANTALLA_COMPLETA_SIMULADA);
		}
	}

	void cambiar_pantalla_completa()
	{
		pantalla_completa=!pantalla_completa;
		inicializar_pantalla();
	}

	void cleanup() {

		for(Actor * a : actores) {

			delete a;
		}

		actores.clear();
		marcadores.cleanup();
	}

	public:

	Controlador(
		const std::string _app_path
	):
		control_frames(60),
		t(0.0),
		pantalla_completa(false),
		app_path(_app_path)
	{
		control_frames.inicializar();

		inicializar_pantalla();
		pantalla.establecer_titulo("Pigs and Cows - friendly universe");
		DLibV::Utilidades_graficas_SDL::mostrar_ocultar_cursor(false);

		inicializar_recursos_graficos();
		inicializar_recursos_audio();
	}

	bool intro_loop() {

		float delta=control_frames.obtener_delta();
		if(delta > Definiciones::MAX_DELTA) delta=Definiciones::MAX_DELTA;

		paso(delta);
		representar();

		control_frames.turno();
		controles_sdl.recoger();

		if(controles_sdl.es_tecla_down(SDL_SCANCODE_F)) cambiar_pantalla_completa();

		if(controles_sdl.es_tecla_down(SDL_SCANCODE_SPACE)) {

			state=states::game;
			return true;
		}

		if(controles_sdl.es_tecla_down(SDL_SCANCODE_H)) {

			state=states::help;
			return true;
		}

		if(controles_sdl.es_senal_salida() ||
			controles_sdl.es_tecla_down(SDL_SCANCODE_ESCAPE))
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

		//prevent the same keypress to start the game from triggering a throw.
		if(!apuntador.is_started()) {

			if(controles_sdl.es_tecla_down(SDL_SCANCODE_SPACE)) {

				apuntador.start();
			}

		}
		else {

			if(controles_sdl.es_tecla_pulsada(SDL_SCANCODE_SPACE)) {

				apuntador.sumar_fuerza(delta);
			}
			else if(controles_sdl.es_tecla_up(SDL_SCANCODE_SPACE))
			{
				if(apuntador.can_throw()) {

					if(marcadores.hay_animales_disponibles()) {

						nuevo_animal();
					}

					apuntador.reiniciar_fuerza();
				}
			}
		}

		if(controles_sdl.es_tecla_down(SDL_SCANCODE_F)) cambiar_pantalla_completa();

		if(controles_sdl.es_tecla_pulsada(SDL_SCANCODE_UP)) apuntador.cambiar_angulo(-1, delta);
		else if(controles_sdl.es_tecla_pulsada(SDL_SCANCODE_DOWN)) apuntador.cambiar_angulo(1, delta);

		if(controles_sdl.es_tecla_down(SDL_SCANCODE_LEFT)) marcadores.cambiar_tipo_animal(-1);
		else if(controles_sdl.es_tecla_down(SDL_SCANCODE_RIGHT)) marcadores.cambiar_tipo_animal(1);

		if(controles_sdl.es_senal_salida()) {

			return false;
		}

		if(controles_sdl.es_tecla_down(SDL_SCANCODE_ESCAPE)) {

			state=states::intro;
			cleanup();
		}

		return true;
	}

	bool help_loop() {

		float delta=control_frames.obtener_delta();
		if(delta > Definiciones::MAX_DELTA) delta=Definiciones::MAX_DELTA;

		paso(delta);
		representar();

		control_frames.turno();
		controles_sdl.recoger();

		if(controles_sdl.es_tecla_down(SDL_SCANCODE_F)) cambiar_pantalla_completa();

		if(controles_sdl.es_senal_salida()) {

			return false;
		}

		if(controles_sdl.es_tecla_down(SDL_SCANCODE_ESCAPE)) {

			state=states::intro;
		}

		return true;
	}

	bool loop() {

		switch(state) {
			case states::intro: return intro_loop();
			case states::help: return help_loop();
			case states::game: return game_loop();
		}

		return false;
	}

};


#endif
