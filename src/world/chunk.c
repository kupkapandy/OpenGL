#include "chunk.h"
#include "world.h"

void initChunks(){
  for(int i = 0; i < CHUNKCNTCUBIC; ++i){
    world.chunks[i] = NULL;
  }
}

void createChunk(){
  size_t bytesToMalloc = CHUNKCNTCUBIC * sizeof(struct chunk);

  for(int i = 0; i < CHUNKCNTCUBIC; ++i){
    if(!world.chunks[i]){
      world.chunks[i] = malloc(bytesToMalloc);
      world.chunks[i]->posInWorld[0] = (float)(int)(i / (CHUNKCNT * CHUNKCNT));
      world.chunks[i]->posInWorld[1] = -(float)(int)((i / CHUNKCNT) % CHUNKCNT);
      world.chunks[i]->posInWorld[2] = (float)(int)(i % CHUNKCNT);

      printf("%d | %p %f %f %f\n",
             i,
             (void *)world.chunks[i],
             world.chunks[i]->posInWorld[0],
             world.chunks[i]->posInWorld[1],
             world.chunks[i]->posInWorld[2]
      );
    }
  }
}

void updateChunk(){

}

void deleteChunk(uint16_t chunkIdx){
  if(!world.chunks[chunkIdx])
    free(world.chunks[chunkIdx]);
  world.chunks[chunkIdx] = NULL;

  printf("\n\n\n");
  for(int i = 0; i < CHUNKCNTCUBIC; ++i)
    printf("%d | %p\n", i, (void *)world.chunks[i]);
}

void deleteChunks(){
  for(int i = 0; i < CHUNKCNTCUBIC; ++i){
    if(!world.chunks[i])
      free(world.chunks[i]);
  }
}
