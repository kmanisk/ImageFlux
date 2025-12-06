
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/dirscan.h"
#include "src/imageload.h"
#include "src/bg_thread.h"
#include "src/utils.h"

#define WINDOW_W 800
#define WINDOW_H 600
#define PRELOAD_LIMIT 100

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <file_or_dir> [...]\n", argv[0]);
        return 1;
    }

    char *images[MAX_IMAGES] = {0};
    int num_images = 0;

    // Handle multiple arguments: directories or files
    for (int i = 1; i < argc && num_images < MAX_IMAGES; i++) {
        const char *target = argv[i];

        if (is_directory(target))
            num_images += scan_directory(target, images + num_images);
        else
            num_images += scan_single_file(target, images + num_images);
    }

    if (num_images == 0) {
        printf("No images found.\n");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("ImageViewer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
        printf("Window Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Preload first PRELOAD_LIMIT images
    int preload_count = (num_images < PRELOAD_LIMIT) ? num_images : PRELOAD_LIMIT;
    SDL_Texture *textures[MAX_IMAGES] = {0};
    int loaded_flags[MAX_IMAGES] = {0};

    for (int i = 0; i < preload_count; i++) {
        textures[i] = load_texture(renderer, images[i]);
        loaded_flags[i] = (textures[i] != NULL);
    }

    // Background loader
    BG_ThreadData *bg_data = NULL;
    SDL_Thread *bg_thread = NULL;
    if (num_images > PRELOAD_LIMIT) {
        bg_data = malloc(sizeof(BG_ThreadData));
        bg_data->renderer = renderer;
        bg_data->paths = (const char **)images;
        bg_data->total = num_images;
        bg_data->start = PRELOAD_LIMIT;
        bg_data->textures = textures;
        bg_data->loaded = loaded_flags;
        bg_data->lock = SDL_CreateMutex();
        bg_data->running = malloc(sizeof(int));
        *bg_data->running = 1;

        bg_thread = start_background_thread(bg_data);
    }

    int current = 0;
    int running = 1;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q: running = 0; break;
                    case SDLK_RIGHT:
                    case SDLK_l:
                        current = (current + 1) % num_images;  // wrap around
                        break;
                    case SDLK_LEFT:
                    case SDLK_h:
                        current = (current - 1 + num_images) % num_images;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (textures[current]) {
            int texW, texH;
            SDL_QueryTexture(textures[current], NULL, NULL, &texW, &texH);

            int winW, winH;
            SDL_GetWindowSize(window, &winW, &winH);

            float imgAspect = (float)texW / texH;
            float winAspect = (float)winW / winH;

            SDL_Rect dst;
            if (winAspect > imgAspect) {
                dst.h = winH;
                dst.w = (int)(winH * imgAspect);
            } else {
                dst.w = winW;
                dst.h = (int)(winW / imgAspect);
            }
            dst.x = (winW - dst.w) / 2;
            dst.y = (winH - dst.h) / 2;

            SDL_RenderCopy(renderer, textures[current], NULL, &dst);
        } else {
            // Show "Loading..." for images not yet loaded
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderClear(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Stop background thread
    if (bg_data) {
        *bg_data->running = 0;
        SDL_WaitThread(bg_thread, NULL);
        SDL_DestroyMutex(bg_data->lock);
        free(bg_data->running);
        free(bg_data);
    }

    for (int i = 0; i < num_images; i++)
        free_texture(textures[i]);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    for (int i = 0; i < num_images; i++)
        free(images[i]);

    return 0;
}
