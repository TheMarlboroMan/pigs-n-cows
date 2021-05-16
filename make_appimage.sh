#!/bin/bash

if [[ $# -ne 1 ]]
then
	echo "usage: make_appimage.sh path_to_linuxdeploy"
fi;

./build.sh appimage
$1 --appdir AppDir
cp -r data AppDir/usr/share
$1 --executable ./pigsncows --appdir AppDir -i ./linuxdeploy/pigsncows.png -d ./linuxdeploy/pigsncows.desktop --output appimag
