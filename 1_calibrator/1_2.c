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

#define MAX_LINE_LEN (1024)

// put all written digits in global array for easier access and comparison
const char digits[3][4][5] =
{ 
    {"one" , "two", "six"},
    {"zero", "four", "five", "nine"},
    {"three", "seven", "eight"}
};

int compare(const char* line, const char* digit, unsigned offset, unsigned digitLen){
    for(int i = 0; i < digitLen; i++){
        if(line[offset + i] != digit[i])    return 0;
    }

    return 1;
}

int check_for_number(const char* line, unsigned offset, unsigned len){
    if(line[offset] >= '0' && line[offset] <= '9')  return line[offset] - '0';

    if(len - offset >= 3){
        if(compare(line, digits[0][0], offset, 3))  return 1;  
        if(compare(line, digits[0][1], offset, 3))  return 2;  
        if(compare(line, digits[0][2], offset, 3))  return 6;  
    } 
    if(len - offset >= 4){
        if(compare(line, digits[1][0], offset, 4))  return 0;  
        if(compare(line, digits[1][1], offset, 4))  return 4;  
        if(compare(line, digits[1][2], offset, 4))  return 5;  
        if(compare(line, digits[1][3], offset, 4))  return 9;  
    }
    if(len - offset >= 5){
        if(compare(line, digits[2][0], offset, 5))  return 3;  
        if(compare(line, digits[2][1], offset, 5))  return 7;  
        if(compare(line, digits[2][2], offset, 5))  return 8;  
    } 

    return -1;
}

int main(int argc, char** argv){
    check_error(argc == 2, "./calibrator calibration_values.txt");

    FILE* in_file = fopen(argv[1], "r");
    check_error(in_file != NULL, "fopen");

    char* line = malloc(MAX_LINE_LEN * sizeof(char));
    check_error(line != NULL, "malloc");

    int first_num = -1, last_num = -1, sum = 0;
    int i = 0, len = 0, found_num;

    while(1 == fscanf(in_file, "%s", line)){
        len = strlen(line);
        first_num = last_num = -1;
        for(i = 0; line[i] != '\0'; i++, len++){
            found_num = check_for_number(line, i, len);
            if(first_num == -1 && found_num != -1){
                first_num = found_num;
            }
            if(found_num != -1){
                last_num = found_num; 
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

