# pigs-n-cows

Small children's game done in a morning. It was based around the idea of a casual game where you cannot lose.

# Controls:

- up-down to aim
- left-right to toggle between pigs and cows (pigs fly further, cows grant more points)
- hold and release space to launch

## Building.

This thing depends on a very old libdanSDL for SDL1.2. Fortunately I could dig it up from my mailbox and patch it with a few missing features.

You must either do a build to use on the computer you are building or to create an AppImage from the build (the appimage has a particular path for the resources).

execute build.sh [regular|appimage]

## Creating the AppImage with linuxdeploy

run make_appimage.sh

