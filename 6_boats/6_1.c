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
    check_error(argc == 2, "argc");

    int* times = (int*) malloc(4 * sizeof(int));
    int* distances = (int*) malloc(4 * sizeof(int));
    int* count = (int*) malloc(4 * sizeof(int));
    char* throwaway = (char*) malloc(20 * sizeof(char));
    check_error(times != NULL && distances != NULL && count != NULL && throwaway != NULL, "malloc");
     
    FILE* input = fopen(argv[1], "r");
    fscanf(input, "%s", throwaway); // Ignore text at the beginning of the line
    for(int i = 0; i < 4; i++)  fscanf(input, "%d", &times[i]);
    fscanf(input, "%s", throwaway); // Ignore text at the beginning of the line
    for(int i = 0; i < 4; i++)  fscanf(input, "%d", &distances[i]);
    fclose(input);
    free(throwaway);

    for(int i = 0; i < 4; i++)
        for(int j = 1; j < times[i]; j++)
            if((j * (times[i] - j)) > distances[i]) count[i]++;

    printf("%d\n", count[0] * count[1] * count[2] * count[3]);

    free(times);
    free(distances);
    free(count);
    return 0;
}
