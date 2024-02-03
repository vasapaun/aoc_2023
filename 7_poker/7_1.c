#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

#define NUM_OF_HANDS  (1000)
#define CARDS_IN_HAND (5)

void print_arr              (const int* arr, int size);
void print_matrix           (const int** matrix, int height, int width);
int  compare_two_numbers    (const void* num1, const void* num2);
void process_hand           (const char* str, int* arr);
int  type_of_hand           (const int* hand);

int main(int argc, char **argv)
{
    check_error(argc == 2, "./poker path-to-input-file.txt");    

    // allocate needed space for all hands and bids
    int** hands = (int**) malloc(NUM_OF_HANDS * sizeof(int*));
    check_error(hands != NULL, "malloc");
    for(int i = 0; i < NUM_OF_HANDS; i++){
        hands[i] = (int*) malloc(CARDS_IN_HAND * sizeof(int));
        check_error(hands[i] != NULL, "malloc");
    }

    int* bids = (int*) malloc(NUM_OF_HANDS * sizeof(int));
    check_error(bids != NULL, "malloc");
    
    // read from input file and store into hands matrix and bids array
    FILE* input = fopen(argv[1], "r");
    char* tmp = (char*) malloc(CARDS_IN_HAND * sizeof(char));
    check_error(input != NULL && tmp != NULL, "");
    for(int i = 0; i < NUM_OF_HANDS; i++)
    {
        fscanf(input, "%s %d", tmp, &bids[i]);
        process_hand(tmp, hands[i]);
        printf("%d: ", i + 1);
        print_arr(hands[i], CARDS_IN_HAND);
        puts("\n");
        // TODO: print types of hands.

    }
    fclose(input);
    free(tmp);

    //TODO: sort main matrix of hands by type and number. Later, calculate the winnings based off the ranks.



    for(int i = 0; i < NUM_OF_HANDS; i++)   free(hands[i]);
    free(hands);
    return 0;
}

// Functions

void print_arr(const int* arr, int size)
{
    for(int i = 0; i < size; i++)   printf("%d ", arr[i]);
    return;
}

void print_matrix(const int** matrix, int height, int width)
{
    for(int i = 0; i < height; i++)
    {
        print_arr(matrix[i], width);
        puts("\n");
    }
    return;
}

int  compare_two_numbers(const void* num1, const void* num2) { // in descending order
    return *((int*)num2) - *((int*)num1); 
}

void process_hand(const char* str, int* arr)
{
    for(int i = 0; i < CARDS_IN_HAND; i++)
    {
        if(isdigit(str[i]))         arr[i] = str[i] - '0';
        else if(str[i] == 'A')      arr[i] = 1;
        else if(str[i] == 'T')      arr[i] = 10;
        else if(str[i] == 'J')      arr[i] = 11;
        else if(str[i] == 'Q')      arr[i] = 12;
        else if(str[i] == 'K')      arr[i] = 13;
    }

    return;
}

int type_of_hand(const int* hand)
{
    int* cards = calloc(13, sizeof(int));
    check_error(cards != NULL, "calloc");

    for(int i = 0; i < CARDS_IN_HAND; i++)  cards[hand[i] - 1]++;

    qsort(cards, 13, sizeof(int), compare_two_numbers);

    if(cards[0] == 5)                   return 7;
    if(cards[0] == 4)                   return 6;
    if(cards[0] == 3 && cards[1] == 2)  return 5;
    if(cards[0] == 3)                   return 4;
    if(cards[0] == 2 && cards[1] == 2)  return 3;
    if(cards[0] == 2)                   return 2;
                                        return 1;
}

/*
    types in order from strongest to weakest:
    
    7: Five of a kind, where all five cards have the same label: AAAAA
    6: Four of a kind, where four cards have the same label and one card has a different label: AA8AA
    5: Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
    4: Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
    3: Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
    2: One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
    1: High card, where all cards' labels are distinct: 23456 
*/
