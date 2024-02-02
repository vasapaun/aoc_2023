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
    check_error(argc == 2, "argc");

    int* times = (int*) malloc(4 * sizeof(int));
    int* distances = (int*) malloc(4 * sizeof(int));
    char* throwaway = (char*) malloc(20 * sizeof(char));
    check_error(times != NULL && distances != NULL && throwaway != NULL, "malloc");
     
    FILE* input = fopen(argv[1], "r");
    fscanf(input, "%s", throwaway); // Ignore text at the beginning of the line
    for(int i = 0; i < 4; i++)  fscanf(input, "%d", &times[i]);
    fscanf(input, "%s", throwaway); // Ignore text at the beginning of the line
    for(int i = 0; i < 4; i++)  fscanf(input, "%d", &distances[i]);
    fclose(input);

    uint64_t time, distance, count;

    sprintf(throwaway, "%d%d%d%d", times[0], times[1], times[2], times[3]);
    free(times);
    time = atoll(throwaway);

    sprintf(throwaway, "%d%d%d%d", distances[0], distances[1], distances[2], distances[3]);
    free(distances);
    distance = atoll(throwaway);
   
    free(throwaway);

    for(int i = 1; i < time; i++)
        if((i * (time - i)) > distance) count++;

    printf("%ld\n", count);

    return 0;
}
