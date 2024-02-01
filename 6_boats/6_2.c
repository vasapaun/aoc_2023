#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define check_error(cond, msg)\
    do\
    {\
        if (!(cond))\
        {\
            perror(msg);\
            fprintf(stderr, "file: %s\nfunc: %s\nline: %d\n", __FILE__, __func__, __LINE__);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)


int main(int argc, char **argv)
{
    uint64_t time = 54708275, distance = 239114212951253, count = 0;

    for(int j = 1; j < time; j++)
        if((j * (time - j)) > distance) count++;

    printf("%ld\n", count);

    return 0;
}
