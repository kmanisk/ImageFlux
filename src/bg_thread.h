
#ifndef BG_THREAD_H
#define BG_THREAD_H

#include <SDL2/SDL.h>

// Structure describing the background loading task
typedef struct {
    SDL_Renderer *renderer;   // Renderer to create textures
    const char **paths;       // Array of file paths
    int total;                // Total number of images
    int start;                // Start index for background loading
    SDL_Texture **textures;   // Array of textures to fill
    int *loaded;              // Array of flags indicating loaded textures
    SDL_mutex *lock;          // Mutex protecting loaded flags
    int *running;             // Pointer to the main running flag
} BG_ThreadData;

// Start background loading thread
SDL_Thread *start_background_thread(BG_ThreadData *info);

#endif
