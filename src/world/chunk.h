#ifndef CHUNK_H
#define CHUNK_H

#include "../util/util.h"
#include "../block/block.h"
#include "../block/debug.h"
#include "../gfx/camera.h"

#define CHUNKCNT 2
#define CHUNKCNTCUBIC CHUNKCNT * CHUNKCNT * CHUNKCNT
#define CHUNKSIZE 16
#define CHUNKSIZECUBIC CHUNKSIZE * CHUNKSIZE * CHUNKSIZE

// uint16_t *chunks[CHUNKAMMOUNT * CHUNKAMMOUNT];

struct chunk {
  /* The chunks array that will hold a pointer to a chunk
   * that will be malloced by createChunk(), and deleted by
   * deleteChunk()
  */

  struct block block[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE];
  vec3 posInWorld;

};

struct vector {
  struct vertex *vector;
  size_t currentLen;
  size_t amountOfElements;
};

void createChunk();
void deleteChunk(uint16_t chunkIdx);
void deleteChunks();
void updateFaces(struct vector *verticesRender, uint32_t *indicesRender, uint32_t *indexIdx, uint32_t chunkID, ivec3 pos, uint8_t offset);

#endif
