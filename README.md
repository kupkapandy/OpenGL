# Voxel Engine with OpenGL - Documentation

##  Introduction
Being created for the purpose of learning OpenGL, and math behind 3D graphics

## Cloning and compiling
The project uses **Make**, as it's build system. To clone the repo use:

`$ git clone https://github.com/kupkapandy/voxel-engine.git -j4 --recurse-submodules`\
`$ make`

Also, be sure to the executable file (`$ ./bin/game`) from the root dir of the repo, or use

`$ make run -j4`\
`$ make clean && make run -j4`\

## Design and Implementation

### Textures
The voxel engine for now uses **texture atlas** for quick access of textures, so
we don't need to load a lot of textures.


