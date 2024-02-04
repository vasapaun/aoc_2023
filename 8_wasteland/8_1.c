#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

#define LR_LENGTH   (307)
#define MAP_LENGTH  (714)


int main(int argc, char **argv)
{
    check_error(argc == 2, "argc");

    char* tmp = (char*)malloc(10 * sizeof(char));

    // allocate space needed for raw map and lr instructions
    char* raw_lr = (char*) malloc (LR_LENGTH * sizeof(char));
    char** raw_map_keys =    (char**) malloc(MAP_LENGTH * sizeof(char*));
    char** raw_map_lvalues = (char**) malloc(MAP_LENGTH * sizeof(char*));
    char** raw_map_rvalues = (char**) malloc(MAP_LENGTH * sizeof(char*));
    check_error(raw_map_keys != NULL && raw_map_lvalues != NULL && raw_map_rvalues != NULL && raw_lr != NULL, "malloc");
    for(int i = 0; i < MAP_LENGTH; i++)
    {
        raw_map_keys[i] =    (char*) malloc(3 * sizeof(char));
        raw_map_lvalues[i] = (char*) malloc(3 * sizeof(char));
        raw_map_rvalues[i] = (char*) malloc(3 * sizeof(char));
        check_error(raw_map_keys[i] != NULL && raw_map_lvalues[i] != NULL && raw_map_rvalues[i] != NULL, "malloc");
    }

    FILE* input = fopen(argv[1], "r");
    fscanf(input, "%s", raw_lr);

    for(int i = 0; i < MAP_LENGTH; i++)
    {
        fscanf(input, "%s", tmp);
        for(int j = 0; j < 3; j++) raw_map_keys[i][j] = tmp[j];

        fscanf(input, "%s", tmp); // discard "="

        fscanf(input, "%s", tmp);
        for(int j = 0; j < 3; j++) raw_map_lvalues[i][j] = tmp[j + 1];

        fscanf(input, "%s", tmp);
        for(int j = 0; j < 3; j++) raw_map_rvalues[i][j] = tmp[j];
        printf("%s %s %s\n", raw_map_keys[i], raw_map_lvalues[i], raw_map_rvalues[i]);
    }
    fclose(input);

    // process LR instructions [translate them to binary - L = 0, R = 1]
    bool* lr_instructions = (bool*) malloc(LR_LENGTH * sizeof(bool));
    for(int i = 0; i < LR_LENGTH; i++)
    {
        if(raw_lr[i] == 'L')    lr_instructions[i] = 0;
        else                    lr_instructions[i] = 1;
    }


    return 0;
}
