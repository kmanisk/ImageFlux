
#include "imageload.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Load an image file into an SDL_Texture
SDL_Texture *load_texture(SDL_Renderer *renderer, const char *filepath) {
    if (!renderer || !filepath) return NULL;

    SDL_Surface *surface = IMG_Load(filepath);
    if (!surface) {
        printf("IMG_Load failed for %s: %s\n", filepath, IMG_GetError());
        return NULL;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (!tex) {
        printf("SDL_CreateTextureFromSurface failed for %s: %s\n", filepath, SDL_GetError());
    }

    SDL_FreeSurface(surface);
    return tex;
}

// Safely free an SDL_Texture
void free_texture(SDL_Texture *tex) {
    if (tex) SDL_DestroyTexture(tex);
}
