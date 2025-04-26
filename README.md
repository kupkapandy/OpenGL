# Voxel Engine with OpenGL - Documentation

##  Introduction
Being created for the purpose of learning OpenGL, and math behind 3D graphics

## Cloning and compiling
The project uses **Make**, as it's build system. To clone the repo use:

`$ git clone https://github.com/kupkapandy/voxel-engine.git -j4 --recurse-submodules`\

Also, be sure to run the executable file (`$ ./bin/game`) from the root dir of the repo, or use

`$ make run -j4`\
`$ make clean && make run -j4`

## TODO
- Refactor the whole thing;
- Change the rendering of cubes, so render only the faces that the user can see;

## Design and Implementation

### Rendering

#### Cubes

Each block is 1.0fx1.0fx1.0f cube.

Each block has its own pos in a chunk, blockID, blockAttributes and atlasIdx for texture.

#### Chunks
The engine is using **cubic chunks**.

The chunks will be a malloced (32768) 32*32*32*sizeof(cube) amount bytes,
and we will have maximally (will increase later) 8x8 chunks at peak.


### Textures
The voxel engine for now uses **texture atlas** for quick access of textures, so
we don't need to load a lot of textures.

### Translation units:

- render.c render.h - Rendering process, all about drawing

- camera.c camera.h - Camera stuff, proper update's, init etc.
- shader.c shader.h - Shader stuff
- window.c window.h - Init glad, glfw, mousecallbacks (not sure about callbacks)
- texture.c texture.h - Texture stuff, file loading, applying texture to vertices
- vao.c vao.h - vao
- vbo.c vbo.h - vbo

- chunk.c chunk.h - Chunking system, generating vec3 pos for blocks
- block.c block.h - Initalize all blocks so changing between them is easy
- world.c world.h - 

- util.h
- main.c

The struct that will calculate camera perspective needs to be global because of OpenGL callbacks
and their great ability to not return variables or pointer's. (I have read about some window pointers)


