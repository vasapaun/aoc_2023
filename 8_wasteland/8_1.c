#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

int find_key(const char* needle, char** haystack, int haystack_size);

int main(int argc, char **argv)
{
    check_error(argc == 2, "argc");

    char* tmp = (char*)malloc(10 * sizeof(char));

    // allocate space needed for raw map and lr instructions
    char* lr_instructions = (char*) malloc (LR_LENGTH * sizeof(char));
    char** map_keys =    (char**) malloc(MAP_LENGTH * sizeof(char*));
    char** map_lvalues = (char**) malloc(MAP_LENGTH * sizeof(char*));
    char** map_rvalues = (char**) malloc(MAP_LENGTH * sizeof(char*));
    check_error(map_keys != NULL && map_lvalues != NULL && map_rvalues != NULL && lr_instructions != NULL, "malloc");
    for(int i = 0; i < MAP_LENGTH; i++)
    {
        map_keys[i] =    (char*) malloc(3 * sizeof(char));
        map_lvalues[i] = (char*) malloc(3 * sizeof(char));
        map_rvalues[i] = (char*) malloc(3 * sizeof(char));
        check_error(map_keys[i] != NULL && map_lvalues[i] != NULL && map_rvalues[i] != NULL, "malloc");
    }

    FILE* input = fopen(argv[1], "r");

    fscanf(input, "%s", lr_instructions);

    for(int i = 0; i < MAP_LENGTH; i++)
    {
        fscanf(input, "%s", tmp);
        for(int j = 0; j < 3; j++) map_keys[i][j] = tmp[j];

        fscanf(input, "%s", tmp); // discard "="

        fscanf(input, "%s", tmp);
        for(int j = 0; j < 3; j++) map_lvalues[i][j] = tmp[j + 1];

        fscanf(input, "%s", tmp);
        for(int j = 0; j < 3; j++) map_rvalues[i][j] = tmp[j];
        printf("%s %s %s\n", map_keys[i], map_lvalues[i], map_rvalues[i]);
    }

    free(tmp);
    fclose(input);

    int lr_index = 0, location = find_key("AAA", map_keys, MAP_LENGTH), count = 0;
    while(strcmp(map_keys[location], "ZZZ") != 0){
        lr_index %= 307; // loop LR instrunctions
        if(location == 0)   puts(map_keys[location]);
        // printf("%d %d\n", count, lr_index);

        location = (lr_instructions[lr_index] == 'L') ? find_key(map_lvalues[location], map_keys, MAP_LENGTH) : find_key(map_rvalues[location], map_keys, MAP_LENGTH);
        check_error(location != -1, "find_key");
        lr_index++;
        count++;
    }

    printf("Steps needed: %d\n", count);

    return 0;
}

// Functions


int find_key(const char* needle, char** haystack, int haystack_size)
{
    for(int i = 0; i < haystack_size; i++)
    {
        if(strcmp(needle, haystack[i]) == 0)
        {
            return i;
            break;
        }
    }

    return -1;
}
