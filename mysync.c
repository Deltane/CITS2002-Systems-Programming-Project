/*
determine what activities are to be performed by the program. Determine what data needs to be stored during the execution of the program. Design one of more data types and data structures to store this long-term data, and create a new mysync.h header file to define these constructs.
break up the activities into fairly independent sets. Write a number of "empty" C files, each of which includes your mysync.h header file, to implement the activities. Ensure that the main() function is in a file named mysync.c
write a Makefile to compile and link your C files, each of which will be dependent on the header file.
write the main() function, whose initial task is simply to receive and validate the command-line options and arguments. Write a usage() function to report the program's synopsis, should command-line processing detect any errors.*/

// use my wordcount to determine which file has more words
// if file x has more then y then update x else update y
// use the get opt, use -l num lines) crucial

//use reverse method to implement pointer to vector of lines

#include "mysync.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No directories provided.\n");
        fprintf(stderr, "Usage: %s <directory1> <directory2> [directory3 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Dynamically allocate memory for FileInfo arrays based on the number of directories
    FileInfo **files = malloc(sizeof(FileInfo *) * (argc - 1));
    int *num_files = malloc(sizeof(int) * (argc - 1));
    for (int i = 0; i < argc - 1; i++) {
        files[i] = malloc(sizeof(FileInfo) * MAX_FILENAME_LENGTH);
        num_files[i] = 0;
        get_file_info(argv[i + 1], &files[i], &num_files[i]);
        qsort(files[i], num_files[i], sizeof(FileInfo), compare_file_info);
    }

    for (int i = 0; i < argc - 1; i++) {
        printf("Most recently modified file in %s:\n", argv[i + 1]);
        if (num_files[i] > 0) {
            printf("%s\n", files[i][0].filename);  // Print the most recently modified file
        } else {
            printf("No files found in this directory.\n");
        }
        printf("\n");

        // Cleanup for each directory
        free(files[i]);
    }

    // Cleanup
    free(files);
    free(num_files);

    return EXIT_SUCCESS;
}
