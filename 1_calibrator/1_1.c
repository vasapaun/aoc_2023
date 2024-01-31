#include <stdio.h>
#include <stdlib.h>

#define check_error(cond, msg) \
    do{ \
        if(!(cond)){ \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX_LINE_LEN (1024)

int main(int argc, char** argv){
    check_error(argc == 2, "./calibrator calibration_values.txt");

    FILE* in_file = fopen(argv[1], "r");
    check_error(in_file != NULL, "fopen");

    char* line = malloc(MAX_LINE_LEN * sizeof(char));
    check_error(line != NULL, "malloc");

    int first_num = -1, last_num = -1, sum = 0;
    int i = 0, len = 0;

    while(1 == fscanf(in_file, "%s", line)){
        len = 0, first_num = last_num = -1;

        for(i = 0; line[i] != '\0'; i++, len++){
            if(line[i] >= '0' && line[i] <= '9' && first_num == -1){
                first_num = line[i] - '0';
            }
        }

        for(i = len; i >= 0; i--){
            if(line[i] >= '0' && line[i] <= '9' && last_num == -1){
                last_num = line[i] - '0';
            }
        }

        sum += first_num * 10 + last_num;
        printf("Line: %s \t %d: %d0 + %d \t sum: %d\n", line, first_num * 10 + last_num, first_num, last_num, sum);
    }

    free(line);
    fclose(in_file);

    printf("%d\n", sum);
    
    return 0;
}
