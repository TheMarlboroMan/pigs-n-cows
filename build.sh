#!/bin/bash
if [[ $# -ne 1 ]]
then
	echo "usage: build.sh build|appimage"
fi;

case $1 in
	"build")
		echo "building as regular build"
	;;

	"appimage")
		echo "building as appimage build"
	;;

	*)
		echo "invalid build type"
		exit 1
	;;
esac

cd motor_sdl;
if [ -d objects_motor_sdl ]
then
	rm -rf objects_motor_sdl;
fi

if [ -f libDanSDL.a ]
then
	rm libDanSDL.a
fi

mkdir -p objects_motor_sdl
make -f makefile_motor_sdl
cp libDanSDL.a ../
cd ..
if [ -f pigsncows ];
then
	rm pigsncows;
fi;

if [[ "$1" == "build" ]]
then
	make BUILDTYPEFLAGS=
else
	make BUILDTYPEFLAGS=-DAS_APPIMAGE=1
fi;

