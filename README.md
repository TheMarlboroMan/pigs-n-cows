# pigs-n-cows

Small children's game done in a morning. It was based around the idea of a casual game where you cannot lose.

# How to play

- up-down to aim.
- left-right to toggle between pigs and cows (pigs fly further, cows grant more points).
- hold and release space to launch.
- aim for the incoming ballons.
- hit more than one ballon with the same animal to rack up combo points.
- cows grant more points than pigs, but cannot fly as far.
- fill up the score bar to raise the maximum number of animals.
- the game never ends, just chill.

## Building.

You must either do a build to use on the computer you are building or to create an AppImage from the build (the appimage has a particular path for the resources).

execute build.sh [regular|appimage]

The build system is far from perfect and may give you some headaches. If you just want to play, consider getting a pre-made package from the releases page on this project on github. I should be also be on itch.io and gamejolt.com.

## Creating the AppImage with linuxdeploy

run make_appimage.sh

## Changelog

- Somewhere around... the 2000s, the game is done.
- May 2021, cleanup for appimage, title and help screen added, small improvements.
- Jun 2021, ported to SDL2.
- Sep 2022, licensing and archiving
