#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define check_error(cond, msg) \
    do{ \
        if(!(cond)){ \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define power_of_set(max) (max.red * max.green * max.blue)

#define MAX_LINE_LEN (1024)

typedef struct max{
    int red;
    int green;
    int blue;
} Max;

int main(int argc, char** argv){
    check_error(argc == 2, "./cube_conundrum input.txt");

    FILE* in_file = fopen(argv[1], "r");
    check_error(in_file != NULL, "fopen");

    char* amount = malloc(MAX_LINE_LEN * sizeof(char));
    char* color  = malloc(MAX_LINE_LEN * sizeof(char));
    check_error(amount != NULL && color != NULL, "malloc");

    int count = 0;
    Max max;
    max.red = max.green = max.blue = 0;

    int current_id = -1;
    while(2 == fscanf(in_file, "%s%s", amount, color))
    {
        if(amount[0] == 'G'){
            current_id++;
            printf("%d: %d %d %d\n", current_id, max.red, max.green, max.blue);

            count += power_of_set(max);
            max.red = max.green = max.blue = 0;
            continue;
        }

        int am = atoi(amount);

        if(strncmp(color, "red", 3) == 0)
            max.red = (am > max.red) ? am : max.red;
        else if(strncmp(color, "green", 5) == 0)
            max.green = (am > max.green) ? am : max.green;
        else if(strncmp(color, "blue", 4) == 0)
            max.blue = (am > max.blue) ? am : max.blue;

        if(color[0] == 'r')
            max.red = (am > max.red) ? am : max.red;
        else if(color[0] == 'g')
            max.green = (am > max.green) ? am : max.green;
        else if(color[0] == 'b')
            max.blue = (am > max.blue) ? am : max.blue;
    }

    free(amount);
    free(color);
    fclose(in_file);

    printf("%d\n", count);

    return 0;
}
