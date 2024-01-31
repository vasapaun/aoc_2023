#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define check_error(cond, msg) \
    do{ \
        if(!(cond)){ \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX_NUM_LEN (8)
#define NUM_OF_SCRATCHCARDS (192)

int process_scratchcard(int* winning, int* potential);
void print_scratchcard(int* winning, int* potential);

int main(int argc, char** argv){
    check_error(argc == 2, "./scratchcards input.txt");

    FILE* in_file = fopen(argv[1], "r");
    check_error(in_file != NULL, "fopen");

    char* num = malloc(MAX_NUM_LEN * sizeof(char));    
    check_error(num != NULL, "malloc");

    int* winning = malloc(10 * sizeof(int));
    int* potential = malloc(25 * sizeof(int));
    int* results = malloc(NUM_OF_SCRATCHCARDS * sizeof(int));
    int* scratchcards = malloc(NUM_OF_SCRATCHCARDS * sizeof(int));
    check_error(winning != NULL && potential != NULL && results != NULL && scratchcards != NULL, "malloc");
    
    for(int i = 0; i < NUM_OF_SCRATCHCARDS; i++)    scratchcards[i] = 1;

    int winning_index = 0;
    int potential_index = 0;
    int count = 0;
    int scratchcards_index = 0;
    int scratchcard_value = 0;
    bool reading_winning = true; 

    fscanf(in_file, "%s%s", num, num);
    while(1 == fscanf(in_file, "%s", num))
    {
        if(num[0] == 'C')
        {
            scratchcard_value = process_scratchcard(winning, potential); 
            for(int i = 0; i < scratchcard_value; i++)  scratchcards[scratchcards_index + i + 1] += scratchcards[scratchcards_index];
            scratchcards_index++;

            print_scratchcard(winning, potential);
            fscanf(in_file, "%s", num);
            reading_winning = true;
            winning_index = potential_index = 0;
            continue;
        }

        else if(num[0] == '|')
        {
            reading_winning = false;
            continue;
        }

        if(reading_winning)
            winning[winning_index++] = atoi(num);
        
        else
            potential[potential_index++] = atoi(num);
        
    }
    count += process_scratchcard(winning, potential);
    print_scratchcard(winning, potential);

    for(int i = 0; i < scratchcards_index; i++){
        printf("%d ", scratchcards[i]);
        count += scratchcards[i];
    }
    printf("\n");

    printf("\n Count: %d\n", count);

    return 0;
}

int process_scratchcard(int* winning, int* potential)
{
    int count = 0;

    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 10; j++)
            count += potential[i] == winning[j];
    }

    return count;
}

void print_scratchcard(int* winning, int* potential)
{
    for(int i = 0; i < 10; i++) printf("%d ", winning[i]);
    printf(" | ");
    for(int i = 0; i < 25; i++) printf("%d ", potential[i]);
    printf(" Value: %d\n", process_scratchcard(winning, potential));
    printf("\n");
}
