#include <stdio.h>
#include <string.h>

int
main(int argc, char* argv[]) {
    // make sure we have an argumen
    if (argc <= 1) {
        printf("Usage: ./fizzbuzz <num>\n");
        return -1;
    }
    else {
        long num_times = atol(argv[1]);
        for (long ii = 1; ii <= num_times; ii++) {
            char* acc = "";
            if (ii % 3 == 0) {
                acc = acc + "fizz";
            }
            if (ii % 3 == 0) {
                acc = acc + "buzz";
            }
        }
        return 0;
    }
}