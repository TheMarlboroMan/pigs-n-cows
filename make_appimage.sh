#!/bin/bash

if [[ $# -ne 1 ]]
then
	echo "usage: make_appimage.sh path_to_linuxdeploy"
	exit 1
fi;

#export SIGN=1
#export SIGN_KEY=0xLAST8CHARSOFGPGKEYID

./build.sh appimage
$1 --appdir AppDir
cp -r data AppDir/usr/share
mkdir -p AppDir/usr/share/metainfo
cp linuxdeploy/*.xml AppDir/usr/share/metainfo/
$1 --executable ./pigsncows --appdir AppDir -i ./linuxdeploy/pigsncows.png -d ./linuxdeploy/pigsncows.desktop --output appimage
exit 0
