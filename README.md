# SDL2 ImageViewer

A lightweight, fast, and minimalistic image viewer built in C using
**SDL2** and **SDL2_image**.\
Designed for browsing individual images or entire folders, with smooth
navigation, window-resizing support, and background preloading for
seamless image transitions.

## Table of Contents

1.  Introduction
2.  Features
3.  Dependencies
4.  Building
5.  Usage
6.  Configuration
7.  How It Works
8.  Troubleshooting
9.  Future Improvements
10. License

## Introduction

**ImageViewer** is a compact SDL2-based utility that loads one image or
an entire directory of images and displays them in a resizable window.
It uses background threads to preload textures for fast navigation and
maintains an internal texture array for cycling through images.

This project is ideal as a reference or starting point for anyone
learning SDL2, texture handling, directory iteration, or threaded
loading.

## Features

-   Open a single image or a whole directory
-   Background thread-based image preloading for fast switching
-   Stores textures in a dynamically allocated array
-   Window resizing support
-   Keyboard navigation
-   Image cycling using modulo logic
-   Graceful handling of empty folders or load errors
-   Clean SDL shutdown

## Dependencies

-   SDL2
-   SDL2_image
-   pthreads (for background loading)

## Building

### Using gcc

    gcc -Wall -Wextra -O2 `sdl2-config --cflags` -o iv main.c src/dirscan.c src/imageload.c src/bg_thread.c src/utils.c `sdl2-config --libs` -lSDL2_image -pthread 

## Usage

    ./iv path/to/image_or_directory

### Keys

-   LEFT / h → previous
-   RIGHT / l → next
-   ESC → quit

## How It Works

-   Initializes SDL, window, renderer
-   Loads file or iterates directory
-   Preloads textures in background thread
-   Stores all images in texture array
-   Scales textures to window size
-   Cycles through images with modulo logic

## Troubleshooting

-   Black window: usually missing texture or render call
-   Some images won't load: extension unsupported
-   Crashes: bounds or NULL texture checks missing

## Future Improvements

-   Fullscreen toggle
-   EXIF rotation
-   Zoom/pan
-   Animated GIF support


