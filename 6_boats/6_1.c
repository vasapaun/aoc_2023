#include <stdio.h>
#include <stdlib.h>

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
    int times[4] = {54, 70, 82, 75}, distances[4] = {239, 1142, 1295, 1253}, count[4] = {0, 0, 0, 0};

    for(int i = 0; i < 4; i++)
        for(int j = 1; j < times[i]; j++)
            if((j * (times[i] - j)) > distances[i]) count[i]++;

    printf("%ld\n", count[0] * count[1] * count[2] * count[3]);

    return 0;
}
