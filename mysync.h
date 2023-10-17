// mysync.h

#ifndef MYSYNC_H
#define MYSYNC_H

#include <time.h>  // Include time.h for time_t

#define MAX_FILENAME_LENGTH 256

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    time_t modification_time;
} FileInfo;

void get_file_info(const char *directory, FileInfo **files, int *num_files);
int compare_file_info(const void *a, const void *b);

#endif  // MYSYNC_H
