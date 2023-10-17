#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Flag to indicate whether to display the number of lines
int display_lines = 0;

void report_lines(int lines, char *filename) {
    printf("%8d", lines);
    if (filename != NULL)
        printf("\t\t%s", filename);
    printf("\n");
}

void count_lines(FILE *fp, char *filename) {
    int lines = 0;
    char line[BUFSIZ];

    while (fgets(line, sizeof line, fp) != NULL) {
        ++lines;
    }

    report_lines(lines, filename);
}

void usage(char *argv0) {
    fprintf(stderr, "Usage: %s [-l] [file ...]\n", argv0);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "l")) != -1) {
        switch (opt) {
            case 'l':
                display_lines = 1;
                break;
            default:
                usage(argv[0]);
                break;
        }
    }

    // If no options provided, use line count as default
    if (!display_lines)
        display_lines = 1;

    // If no arguments provided, read from stdin
    if (optind == argc) {
        count_lines(stdin, NULL);
    } else {
        for (int a = optind; a < argc; ++a) {
            FILE *fp = fopen(argv[a], "r");
            if (fp == NULL) {
                fprintf(stderr, "Cannot open %s\n", argv[a]);
                exit(EXIT_FAILURE);
            }
            count_lines(fp, argv[a]);
            fclose(fp);
        }
    }

    return 0;
}
