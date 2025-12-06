# ImageViewer

**Repository Name:** `SDL2-ImageViewer`  
**Project Name:** `ImageViewer`  
**Short Description:** Lightweight, fast image viewer built with SDL2, supporting directory browsing, background image preloading, and keyboard navigation.

---

## Overview

ImageViewer is a minimal and efficient image viewer written in C using SDL2. It allows viewing images from a single file or an entire directory, preloading images in the background, and navigating with keyboard controls.  

---

## Features

- Supports common image formats: JPG, PNG, BMP  
- Navigate images with arrow keys or `h/l` keys  
- Quit anytime with `q`  
- Background loading of images for smooth UI  
- Dynamically resizes images to fit the window while maintaining aspect ratio  

---

## Installation

Ensure you have the following libraries installed:

- SDL2
- SDL2_image

On Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev
