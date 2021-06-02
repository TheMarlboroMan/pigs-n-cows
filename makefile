all: pigsncows

#windows builds...
#DRIVE=C
#INCLUDES=/devel/include
#BUILDTYPEFLAGS=-DWINBUILD=1
#ARCHLINK=-lmingw32 -lSDLmain
#LIB=/devel/lib
#WINFLAGS=-I$(DRIVE):$(INCLUDES) -L$(DRIVE):$(LIB)

pigsncows:\
libDanSDL2legacy.a \
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
	g++ $(BUILDTYPEFLAGS) $(WINFLAGS) main.cpp -O3 -Wno-deprecated -Wall -ansi -pedantic -std=c++0x -L. $(ARCHLINK) -lDanSDL2legacy -lSDL2 -lSDL2_image -lSDL2_mixer -o pigsncows
