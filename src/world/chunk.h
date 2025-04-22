#ifndef CHUNK_H
#define CHUNK_H

#include "../util/util.h"
#include "../block/block.h"
#include "../gfx/camera.h"

#define CHUNKCNT 4
#define CHUNKCNTCUBIC CHUNKCNT * CHUNKCNT * CHUNKCNT
#define CHUNKSIZE 16
#define CHUNKSIZECUBIC CHUNKSIZE * CHUNKSIZE * CHUNKSIZE

// uint16_t *chunks[CHUNKAMMOUNT * CHUNKAMMOUNT];

struct chunk {
  /* The chunks array that will hold a pointer to a chunk
   * that will be malloced by createChunk(), and deleted by
   * deleteChunk()
  */

  struct cube block[CHUNKSIZECUBIC];
  vec3 posInWorld;

};

void initChunks();
void createChunk();
void deleteChunk(uint16_t chunkIdx);
void deleteChunks();

#endif
