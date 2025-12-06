
#include "utils.h"
#include <string.h>
#include <stdio.h>

int has_extension(const char *filename, const char **ext_list) {
    if (!filename || !ext_list) return 0;

    size_t len = strlen(filename);
    for (int i = 0; ext_list[i]; i++) {
        size_t ext_len = strlen(ext_list[i]);
        if (len >= ext_len && strcasecmp(filename + len - ext_len, ext_list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void join_path(char *out, size_t out_size, const char *dir, const char *file) {
    if (!out || !dir || !file) return;

    size_t dir_len = strlen(dir);
    int need_slash = (dir_len > 0 && dir[dir_len - 1] != '/');

    if (need_slash) {
        snprintf(out, out_size, "%s/%s", dir, file);
    } else {
        snprintf(out, out_size, "%s%s", dir, file);
    }
}
