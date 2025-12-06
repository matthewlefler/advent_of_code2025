#include "stdlib.h"
#include "stdio.h"
#include <string.h>

#define MAX_LINE_LENGTH 10000

static void print_usage_info( char* prgm_name ) {
    fprintf( stderr, "usage: %s <input file name>\n", prgm_name );
}

int main(int argc, char *argv[]) {
    if( argc != 2 ) {
        print_usage_info( argv[0] );
        return EXIT_FAILURE;
    }

    FILE* file = fopen( argv[1], "r" );
    
    if( file == NULL ) {
        perror("file could not be opened: ");
        return EXIT_FAILURE;
    }

    char input[100][MAX_LINE_LENGTH];
    int line_count = 0;
    char line_buffer[MAX_LINE_LENGTH]; 
    long long total = 0;
    // Read the file line by line using fgets()
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        memcpy(input[line_count], line_buffer, sizeof(line_buffer));
        line_count++;
    }
 
    fclose( file );

    size_t operator_pos = 0;
    long operator_idx = 0;

    char operators[MAX_LINE_LENGTH];
    long long outputs[MAX_LINE_LENGTH] = {0};
    int outputs_len[MAX_LINE_LENGTH] = {0};
    long number_idx = 0;

    long long numbers[1000][10];
    while (1)
    {
        while( !(input[line_count - 1][operator_pos] == '\0' || input[line_count - 1][operator_pos] == '+' || input[line_count - 1][operator_pos] == '*')) { 
            operator_pos++; 
        }
        char operator = input[line_count - 1][operator_pos];
        
        if(operator == '\0') {
            break;
        }
        printf("\nop: %c\n", operator);

        size_t next_operator_pos = operator_pos + 1;
        while( input[line_count - 1][next_operator_pos] != '\0' && input[line_count - 1][next_operator_pos] != '+' && input[line_count - 1][next_operator_pos] != '*') { 
            next_operator_pos++; 
        }

        operators[operator_idx] = operator;
        
        number_idx = 0;

        for (size_t x = operator_pos; x < next_operator_pos - 1; x++)
        {
            char buf[100];
            int buf_len = 0;
            for (size_t i = 0; i < line_count - 1; i++)
            {
                char character = input[i][x];
                if(character == ' ') {
                    continue;
                }
                buf[buf_len] = character;
                buf_len++;
            }
            buf[buf_len] = '\0';
            numbers[operator_idx][number_idx] = strtol(buf, NULL, 10);
            printf("%lld\n", numbers[operator_idx][number_idx]);
            number_idx++;
        }
        outputs_len[operator_idx] = number_idx;

        operator_idx++;
        operator_pos++; 
    }
    
    for (size_t i = 0; i < operator_idx; i++)
    {
        if(operators[i] == '+') {
            outputs[i] = 0;

            for (size_t j = 0; j < outputs_len[i]; j++)
            {
                outputs[i] += numbers[i][j];
            }
        } else {
            outputs[i] = 1;
            for (size_t j = 0; j < outputs_len[i]; j++)
            {
                outputs[i] *= numbers[i][j];
            }
        }
    }
    
    for (size_t i = 0; i < operator_idx; i++)
    {
        printf("out: %lld \n", outputs[i]);
        total += outputs[i];
    }
    

    printf("%lld\n", total);  

    return EXIT_SUCCESS;
}
