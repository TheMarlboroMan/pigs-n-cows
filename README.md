# pigs-n-cows

Small children's game done in a morning. It was based around the idea of a casual game where you cannot lose.

## Building.

This thing depends on a very old libdanSDL for SDL1.2. Fortunately I could dig it up from my mailbox and patch it with a few missing features.

You must either do a build to use on the computer you are building or to create an AppImage from the build (the appimage has a particular path for the resources).

execute build.sh [regular|appimage]

## Creating the AppImage with linuxdeploy after building:

1) make sure you ran "build.sh appimage"!!!
2) Grab linuxdeploy from https://github.com/linuxdeploy/linuxdeploy/releases/tag/continuous use the architecture you need:
3) [path-to-linuxdeploy] --executable ./pigsncows --appdir AppDir -i ./linuxdeploy/pigsncows.png -d ./linuxdeploy/pigsncows.desktop
4) Copy the "data" directory and its contents into AppDir/usr/share
5) [path-to-linuxdeploy] --executable ./pigsncows --appdir AppDir -i ./linuxdeploy/pigsncows.png -d ./linuxdeploy/pigsncows.desktop --output appimage
