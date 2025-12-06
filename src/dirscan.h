
#ifndef DIRSCAN_H
#define DIRSCAN_H

#include <stdbool.h>

#define MAX_IMAGES 2048

// Returns 1 if path is directory, 0 otherwise
bool is_directory(const char *path);

// Scans directory and fills 'out'
int scan_directory(const char *dir, char **out);

// Loads a single file into out[0], return 1
int scan_single_file(const char *filepath, char **out);

// Helper: check if filename is an image file
bool is_image_file(const char *name);

#endif
