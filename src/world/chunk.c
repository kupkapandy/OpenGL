#include "../gfx/render.h"
#include "chunk.h"

struct renderer renderer;

void createChunk(){
  size_t bytesToMalloc = sizeof(struct chunk);
  struct block debugBlock = initBlockDebug();

  for(int i = 0; i < CHUNKCNTCUBIC; ++i){
    renderer.chunks[i] = malloc(bytesToMalloc);
      renderer.chunks[i]->posInWorld[0] = (float)(int)(i / (CHUNKCNT * CHUNKCNT)) * CHUNKSIZE;
      renderer.chunks[i]->posInWorld[1] = -(float)(int)((i / CHUNKCNT) % CHUNKCNT) * CHUNKSIZE;
      renderer.chunks[i]->posInWorld[2] = (float)(int)(i % CHUNKCNT) * CHUNKSIZE;

    for(int x = 0; x < CHUNKSIZE; ++x){
      for(int y = 0; y < CHUNKSIZE; ++y){
        for(int z = 0; z < CHUNKSIZE; ++z){
          renderer.chunks[i]->block[x][y][z] = debugBlock;

          for(int k = 0; k < NOFV; ++k){
            renderer.chunks[i]->block[x][y][z].vertices[k].pos[0] = vertices[k * 3 + 0] + x + renderer.chunks[i]->posInWorld[0];
            renderer.chunks[i]->block[x][y][z].vertices[k].pos[1] = vertices[k * 3 + 1] + y + renderer.chunks[i]->posInWorld[1];
            renderer.chunks[i]->block[x][y][z].vertices[k].pos[2] = vertices[k * 3 + 2] + z + renderer.chunks[i]->posInWorld[2];
          }
        }
      }
    }
  }


}

void updateChunk(){ }

inline void updateFaces(struct vector *verticesRender, uint32_t *indicesRender, uint32_t *indexIdx, uint32_t chunkID, ivec3 pos, uint8_t offset) {
  pushToArray(verticesRender, renderer.chunks[chunkID]->block[pos[0]][pos[1]][pos[2]].vertices[offset]);
  pushToArray(verticesRender, renderer.chunks[chunkID]->block[pos[0]][pos[1]][pos[2]].vertices[1 + offset]);
  pushToArray(verticesRender, renderer.chunks[chunkID]->block[pos[0]][pos[1]][pos[2]].vertices[2 + offset]);
  pushToArray(verticesRender, renderer.chunks[chunkID]->block[pos[0]][pos[1]][pos[2]].vertices[3 + offset]);

  *indexIdx += 6;

  indicesRender[*indexIdx - 6] = verticesRender->amountOfElements - 4;
  indicesRender[*indexIdx - 5] = verticesRender->amountOfElements + 1 - 4;
  indicesRender[*indexIdx - 4] = verticesRender->amountOfElements + 2 - 4;
  indicesRender[*indexIdx - 3] = verticesRender->amountOfElements - 4;
  indicesRender[*indexIdx - 2] = verticesRender->amountOfElements + 3 - 4;
  indicesRender[*indexIdx - 1] = verticesRender->amountOfElements + 2 - 4;
}


void deleteChunk(uint16_t chunkIdx){
  if(!renderer.chunks[chunkIdx])
    free(renderer.chunks[chunkIdx]);
  renderer.chunks[chunkIdx] = NULL;

  printf("\n\n\n");
  for(int i = 0; i < CHUNKCNTCUBIC; ++i)
    printf("%d | %p\n", i, (void *)renderer.chunks[i]);
}
void deleteChunks() {
  for(int i = 0; i < CHUNKCNTCUBIC; ++i){
    if(!renderer.chunks[i])
      free(renderer.chunks[i]);
  }
}
