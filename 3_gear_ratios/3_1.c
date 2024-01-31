#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define check_error(cond, msg) \
    do{ \
        if(!(cond)){ \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX_LINE_LEN (140)
#define MAX_PARTS (2048)

#define is_num(line, pos) \
    return (line[pos] <= '9' && line[pos] >= '0') ? true : false;

bool is_symbol(char c){
    return ((c <= '9' && c >= '0') || c == '.') ? false : true;
}

int add_to_parts(const char* line, int pos, unsigned* parts, unsigned* parts_len); 
void parse_symbol(char** lines, int posx, int posy, unsigned* parts, unsigned* parts_len); 
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);
int remove_duplicates(int arr[], int n);

int main(int argc, char** argv){
    check_error(argc == 2, "./gear_ratios input.txt");

    FILE* in_file = fopen(argv[1], "r");
    check_error(in_file != NULL, "fopen");

    char** lines = malloc(MAX_LINE_LEN * sizeof(char*));
    check_error(lines != NULL, "malloc");
    for(int i = 0; i < MAX_LINE_LEN; i++){
        lines[i] = malloc((MAX_LINE_LEN) * sizeof(char));
        check_error(lines[i] != NULL, "line malloc");
    }

    unsigned* parts = malloc(MAX_PARTS * sizeof(unsigned));
    check_error(parts != NULL, "parts_malloc");

    unsigned parts_len = 0;

    for(int i = 0; 1 == fscanf(in_file, "%s", lines[i]); i++);

    for(int i = 1; i < MAX_LINE_LEN; i++){
        for(int j = 1; lines[i][j] != '\0'; j++){
            if(is_symbol(lines[i][j])) parse_symbol(lines, j, i, parts, &parts_len);
        }
    }

    quicksort(parts, 0, parts_len);
    parts_len = remove_duplicates(parts, parts_len);
    for(int i = 0; i < parts_len; i++)  printf("%d ", parts[i]);

    fclose(in_file);
    for(int i = 0; i < 3; i++)  free(lines[i]);
    free(lines);

    return 0;
}

int add_to_parts(const char* line, int pos, unsigned* parts, unsigned* parts_len)
{ 
    if(!isdigit(line[pos])) return -1;

    int i, num = 0, exp = 0;

    for(i = 0; line[pos + i] != '\0' && isdigit(line[pos + i]); i++);

    pos += i - 1;

    for(i = 0; (pos - i) >= 0 && isdigit(line[pos - i]); i++, exp++){
            num += (line[pos - i] - '0') * pow(10, exp); 
    }
        
    parts[(*parts_len)++] = num;

    return num;
}

void parse_symbol(char** lines, int posx, int posy, unsigned* parts, unsigned* parts_len)
{ 
    if(posx < 1 || posy < 1)    return;

    if(isdigit(lines[posy-1][posx-1]))     add_to_parts(lines[posy-1], posx-1, parts, parts_len);
    if(isdigit(lines[posy-1][posx]))       add_to_parts(lines[posy-1], posx, parts, parts_len);
    if(isdigit(lines[posy-1][posx+1]))     add_to_parts(lines[posy-1], posx+1, parts, parts_len);

    if(isdigit(lines[posy][posx-1]))     add_to_parts(lines[posy], posx-1, parts, parts_len);
    if(isdigit(lines[posy][posx+1]))     add_to_parts(lines[posy], posx+1, parts, parts_len);

    if(isdigit(lines[posy+1][posx-1]))     add_to_parts(lines[posy+1], posx-1, parts, parts_len);
    if(isdigit(lines[posy+1][posx]))       add_to_parts(lines[posy+1], posx, parts, parts_len);
    if(isdigit(lines[posy+1][posx+1]))     add_to_parts(lines[posy+1], posx+1, parts, parts_len);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int remove_duplicates(int arr[], int n) {
    // Check if the array is empty or has only one element
    if (n <= 1) {
        return n;
    }

    // Initialize index for the unique elements
    int uniqueIndex = 0;

    // Iterate through the array
    for (int i = 1; i < n; i++) {
        // If the current element is different from the previous one
        if (arr[i] != arr[uniqueIndex]) {
            // Move to the next unique element
            uniqueIndex++;
            // Copy the current element to its correct position
            arr[uniqueIndex] = arr[i];
        }
    }

    // The array is now modified to contain only unique elements
    return uniqueIndex + 1; // Return the new size of the array
}











