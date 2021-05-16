#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <exception>
#include <array>
#include <unistd.h>

#include "motor_sdl/libDanSDL.h"
#include "motor_sdl/defDanSDL.h"

#include "class/definiciones.h"
#include "class/controlador.h"
#include "class/version.h"

//g++ main.cpp -Wno-deprecated -Wall -ansi -pedantic -std=c++0x -L. -lDanSDL -lSDL -lSDL_image -lSDL_mixer

//DLibH::Log_base LOG;
const float Definiciones::MAX_DELTA=0.030;
const float Apuntador::GRADOS_POR_SEGUNDO=40.0;
const float Apuntador::FUERZA_POR_SEGUNDO=300.0;

int main(int argc, char ** argv)
{
	std::string executable_path, executable_dir;

	{
		std::array<char, 1024> buff;

		int bytes=readlink("/proc/self/exe", buff.data(), 1024);
		if(-1==bytes) {

			std::cerr<<"could not locate proc/self/exe, error "<<errno<<std::endl;
			return 1;
		}

		executable_path=std::string{std::begin(buff), std::begin(buff)+bytes};
		auto last_slash=executable_path.find_last_of("/");
		executable_dir=executable_path.substr(0, last_slash)+"/";
		std::cout<<"running from "<<executable_dir<<std::endl;
	}

	if(DLibH::Herramientas_SDL::iniciar_SDL(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK))
	{
//		LOG.inicializar("info.log");
//		LOG.activar();
//		DLibH::Log_motor::arrancar("log_motor.log");

		srand(time(NULL));

		Controlador c{executable_dir};
		while(c.loop()){}
	}

	DLibH::Log_motor::finalizar();
	DLibH::Herramientas_SDL::apagar_SDL();

	return 0;
}
