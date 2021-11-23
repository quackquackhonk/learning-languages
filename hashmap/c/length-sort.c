#include <stdio.h>
#include <string.h>

#include "svec.h"

void
sort(svec* xs)
{
    // see "man 3 strlen"
    // using gnome sort because it seems super simple
    int ii = 0;
    int ss = xs->size;
    while (ii < ss) {
        if (ii == 0) {
            ii++;
        }
        else if (strlen(svec_get(xs, ii)) >= strlen(svec_get(xs, ii - 1))) {
            ii++;
        }
        else {
            svec_swap(xs, ii, ii - 1);
            ii--;
        }
    }
}

void
chomp(char* text)
{
    if (text) {
        text[strlen(text) - 1] = '\0';
    }
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage:\n  %s input-file\n", argv[0]);
        return 1;
    }

    FILE* fh = fopen(argv[1], "r");
    if (!fh) {
        perror("open failed");
        return 1;
    }

    svec* xs = make_svec();
    char temp[128];

    while (1) {
        char* line = fgets(temp, 128, fh);
        if (!line) {
            break;
        }

        chomp(line);
        svec_push_back(xs, line);
    }

    fclose(fh);

    sort(xs);

    for (int ii = 0; ii < xs->size; ++ii) {
        char* line = svec_get(xs, ii);
        printf("%s\n", line);
    }

    free_svec(xs);
    return 0;
}
