
#include "dirscan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define IMAGE_EXTS_COUNT 4
static const char *image_exts[IMAGE_EXTS_COUNT] = {".jpg", ".jpeg", ".png", ".bmp"};

// Check if path is a directory
bool is_directory(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return false;
    return S_ISDIR(st.st_mode);
}

// Check if filename has an image extension
bool is_image_file(const char *name) {
    size_t len = strlen(name);
    for (int i = 0; i < IMAGE_EXTS_COUNT; i++) {
        size_t ext_len = strlen(image_exts[i]);
        if (len >= ext_len && strcasecmp(name + len - ext_len, image_exts[i]) == 0)
            return true;
    }
    return false;
}

// Scan directory and return full paths
int scan_directory(const char *dir, char **out) {
    DIR *dp = opendir(dir);
    if (!dp) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dp)) != NULL && count < MAX_IMAGES) {
        if (entry->d_type == DT_REG && is_image_file(entry->d_name)) {
            char fullpath[1024];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, entry->d_name);
            out[count] = strdup(fullpath);
            count++;
        }
    }

    closedir(dp);
    return count;
}

// Single file scan
int scan_single_file(const char *filepath, char **out) {
    if (!is_image_file(filepath)) return 0;
    out[0] = strdup(filepath); // already full path
    return 1;
}
