#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <exception>
#include <array>
#include <string>

#include "libdan2/libDan2.h"
#include "libdan2/defDanSDL.h"

#include "class/definiciones.h"
#include "class/controlador.h"
#include "class/version.h"

#ifdef WINBUILD
	#include <libloaderapi.h>
#else
	#include <unistd.h>
#endif

//g++ main.cpp -Wno-deprecated -Wall -ansi -pedantic -std=c++0x -L. -lDanSDL -lSDL -lSDL_image -lSDL_mixer

//DLibH::Log_base LOG;
const float Definiciones::MAX_DELTA=0.030;
const float Apuntador::GRADOS_POR_SEGUNDO=40.0;
const float Apuntador::FUERZA_POR_SEGUNDO=300.0;

std::string ready_system();

int main(int argc, char ** argv) {

	try {

		if(!DLibH::Herramientas_SDL::iniciar_SDL(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK)) {
		
			throw std::runtime_error("cannot start SDL");
		}
		
		srand(time(NULL));
		const std::string executable_dir=ready_system();
		Controlador c{executable_dir};
		while(c.loop()){}
	
		DLibH::Log_motor::finalizar();
		DLibH::Herramientas_SDL::apagar_SDL();
	
		return 0;
	}
	catch(std::exception &e) {
	
		std::cerr<<"error: "<<e.what()<<std::endl;
		return 1;
	}
}

#ifdef WINBUILD

std::string ready_system() {

	std::array<char, 1024> buff;
	int bytes=GetModuleFileNameA(nullptr, buff.data(), 1024);

	std::string executable_path=std::string{std::begin(buff), std::begin(buff)+bytes};
	
	auto last_slash=executable_path.find_last_of("\\");
	std::string executable_dir=executable_path.substr(0, last_slash)+"\\";
	
	return executable_dir;
}

#else

std::string ready_system() {

	std::string executable_path, executable_dir;
	std::array<char, 1024> buff;

	int bytes=readlink("/proc/self/exe", buff.data(), 1024);
	if(-1==bytes) {

		std::cerr<<"could not locate proc/self/exe, error "<<errno<<std::endl;
		throw std::runtime_error("could not locate proc/self/exe");
	}

	executable_path=std::string{std::begin(buff), std::begin(buff)+bytes};
	auto last_slash=executable_path.find_last_of("/");
	executable_dir=executable_path.substr(0, last_slash)+"/";

	#ifdef AS_APPIMAGE
		executable_dir=executable_dir+"../share/"}
	#endif		
		
	return executable_dir;
}

#endif
