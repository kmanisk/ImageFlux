
#ifndef IMAGELOAD_H
#define IMAGELOAD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Load an image file into an SDL_Texture
SDL_Texture *load_texture(SDL_Renderer *renderer, const char *filepath);

// Frees an SDL_Texture safely
void free_texture(SDL_Texture *tex);

#endif
