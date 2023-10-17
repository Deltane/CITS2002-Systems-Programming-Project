#include "mysync.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_FILENAME_LENGTH 256

void get_file_info(const char *directory, FileInfo **files, int *num_files) {
    struct dirent *entry;
    DIR *dir = opendir(directory);

    if (!dir) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_REG) {  // Regular file
            char filepath[MAX_FILENAME_LENGTH];
            snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

            struct stat file_stat;
            if (stat(filepath, &file_stat) == 0) {
                (*files)[*num_files].modification_time = file_stat.st_mtime;
                strcpy((*files)[*num_files].filename, entry->d_name);
                (*num_files)++;
            }
        }
    }

    closedir(dir);
}

int compare_file_info(const void *a, const void *b) {
    return difftime(((FileInfo *)b)->modification_time, ((FileInfo *)a)->modification_time);
}
