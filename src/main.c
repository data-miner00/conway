#include "hello.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    srand(time(NULL));
    printf("Welcome to C game template!\n");

    while (true) {
        printf("Game loop\n");

        int ch = getchar();
        if (ch == 'q') {
            break;
        }
    }

    printf("1 + 2 = %d\n", add(1, 2));

    return 0;
}
