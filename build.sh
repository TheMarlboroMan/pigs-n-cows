cd motor_sdl;
mkdir -p objects_motor_sdl
make -f makefile_motor_sdl
cp libDanSDL.a ../
cd ..
make
