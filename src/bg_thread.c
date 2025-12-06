
#include "bg_thread.h"
#include "imageload.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

static int bg_thread_fn(void *data) {
    BG_ThreadData *t = (BG_ThreadData *)data;

    for (int i = t->start; i < t->total && *t->running; i++) {
        SDL_Texture *tex = load_texture(t->renderer, t->paths[i]);
        
        SDL_LockMutex(t->lock);
        t->textures[i] = tex;
        t->loaded[i] = (tex != NULL);
        SDL_UnlockMutex(t->lock);

        // Small delay to avoid CPU spike (optional)
        SDL_Delay(5);
    }

    return 0;
}

SDL_Thread *start_background_thread(BG_ThreadData *info) {
    if (!info) return NULL;
    return SDL_CreateThread(bg_thread_fn, "BG_Loader", info);
}
