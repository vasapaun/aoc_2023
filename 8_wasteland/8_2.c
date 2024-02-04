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

int  find_key            (const char* needle, char** haystack, int haystack_size);
bool check_locations     (const int* locations, int num_of_locations, char** haystack, int haystack_size);

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
    }

    free(tmp);
    fclose(input);
   
    int* locations = (int*) malloc(MAP_LENGTH * sizeof(int));
    check_error(locations != NULL, "malloc");

    int num_of_locations = 0;
    for(int i = 0; i < MAP_LENGTH; i++) if(map_keys[i][2] == 'A')   locations[num_of_locations++] = i;
    
    int lr_index = 0, count = 0;
    while(check_locations(locations, num_of_locations, map_keys, MAP_LENGTH) == false){
        lr_index %= 307; // loop LR instrunctions

        for(int i = 0; i < num_of_locations; i++)
        {
            if(lr_instructions[lr_index] == 'L')
                locations[i] = find_key(map_lvalues[locations[i]], map_keys, MAP_LENGTH);
            else
                locations[i] = find_key(map_rvalues[locations[i]], map_keys, MAP_LENGTH);
        }

        lr_index++;
        count++;
    }

    // Free allocated memory
    for(int i = 0; i < MAP_LENGTH; i++)
    {
        free(map_keys[i]);
        free(map_lvalues[i]);
        free(map_rvalues[i]);
    }
    free(map_keys);
    free(map_lvalues);
    free(map_rvalues);
    free(lr_instructions);
    free(locations);

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

bool check_locations(const int* locations, int num_of_locations, char** haystack, int haystack_size)
{
    for(int i = 0; i < num_of_locations; i++)
    {
        if(haystack[locations[i]][2] != 'Z')    return false;
    }

    return true;
}
