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

cd libdan2;
if [ -d objects ]
then
	rm -rf objects;
fi

if [ -f libDanSDL2legacy.a.a ]
then
	rm libDanSDL2legacy.a.a
fi

mkdir -p objects
make -f makefile_linux
cp libDanSDL2legacy.a ../
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

