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


int main(int argc, char **argv)
{
    check_error(argc == 2, "argc");

    char* raw_lr = (char*) malloc (LR_LENGTH * sizeof(char));
    check_error(raw_lr != NULL, "malloc");

    FILE* input = fopen(argv[1], "r");
    fscanf(input, "%s", raw_lr);

    // TODO: process whole map before closing input file
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
