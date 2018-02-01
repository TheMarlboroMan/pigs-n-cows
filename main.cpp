#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <exception>

#include "motor_sdl/libDanSDL.h"
#include "motor_sdl/defDanSDL.h"

#include "class/definiciones.h"
#include "class/controlador.h"

//g++ main.cpp -Wno-deprecated -Wall -ansi -pedantic -std=c++0x -L. -lDanSDL -lSDL -lSDL_image -lSDL_mixer

//DLibH::Log_base LOG;
const float Definiciones::MAX_DELTA=0.030;
const float Apuntador::GRADOS_POR_SEGUNDO=40.0;
const float Apuntador::FUERZA_POR_SEGUNDO=300.0;

int main(int argc, char ** argv)
{
	if(DLibH::Herramientas_SDL::iniciar_SDL(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK))
	{
//		LOG.inicializar("info.log");
//		LOG.activar();
//		DLibH::Log_motor::arrancar("log_motor.log");

		srand(time(NULL));

		Controlador c;
		while(c.loop()){}
	}
	
	DLibH::Log_motor::finalizar();
	DLibH::Herramientas_SDL::apagar_SDL();

	return 0;
}
