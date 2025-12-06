
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// Returns 1 if filename ends with any extension in ext_list[]
// ext_list is NULL-terminated
int has_extension(const char *filename, const char **ext_list);

// Joins two path components: dir + "/" + file
// Output must be at least out_size bytes
void join_path(char *out, size_t out_size, const char *dir, const char *file);

#endif
