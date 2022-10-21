# CppTris

The goal of this project is to create a version of Tetris that runs in a custom C++ engine using SDL with OpenGL for Rendering.

This is the third of a series of projects I've done over the years to remake Tetris in various graphics environments.

The other two are:
1. Java Processing - https://github.com/Bowers-L/TetrisPi
2. Game Boy Advance - https://github.com/Bowers-L/GBA-Tris

Note: This project is currently under development and only built for Windows / Visual Studio 2022.

If you want to compile the project in VS and run it, you must copy the SDL2.dll and SDL2_image.dll files, located under the "vendor/SDL2-2.24.0/lib" and "vendor/SDL2_image-2.6.2/lib" folders respectively, into the "bin" directory containing your executable. This will be fixed in the future once I integrate a build system into the project. Sorry for the inconvenience :(
