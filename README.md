# pigs-n-cows

Small children's game done in a morning. It was based around the idea of a casual game where you cannot lose.

##Building.

This thing depends on a very old libdanSDL for SDL1.2. Fortunately I could dig it up from my mailbox and patch it with a few missing features.

a)

- execute build.sh

b)

- 1 cd into motor_sdl
- 2 make -f makefile_motor_sdl
- 3 copy the resulting library file to the root of the project (cp libDanSDL.a ../)
- 4 cd into the project root.
- 5 make
- 6 ./pigs.out

##Creating the AppImage with linuxdeploy after building:

Grab linuxdeploy from here, use the architecture you need:

https://github.com/linuxdeploy/linuxdeploy/releases/tag/continuous

[path-to-linuxdeploy] --executable ./pigsncows --appdir AppDir -i ./linuxdeploy/pigsncows.png -d ./linuxdeploy/pigsncows.desktop --output appimage
