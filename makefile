all: pigsncows

pigsncows:\
libDanSDL.a \
main.cpp \
class/cielo.h\
class/controlador.h\
class/actor.h\
class/marcadores.h\
class/actor_movil.h\
class/bonus.h\
class/animales_tierra.h\
class/animales_voladores.h\
class/apuntador.h\
class/decoraciones.h\
class/decoraciones_moviles.h\
class/definiciones.h\
class/mensajes_controlador.h\
class/representable.h\
class/visitante.h\
class/visitante_app.h
	g++ main.cpp -O3 -Wno-deprecated -Wall -ansi -pedantic -std=c++0x -L. -lDanSDL -lSDL -lSDL_image -lSDL_mixer -o pigsncows
