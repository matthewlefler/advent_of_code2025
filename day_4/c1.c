#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

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
    
    size_t max_input_len = 100;
    size_t input_len = 0;
    char* input = malloc( max_input_len );
    int line_width = 0;
    int flag = 1;
    char c;
    // Read the file line by line using fgets()
    while ( (c = fgetc(file)) != EOF) {
        if( c == '\n' ) { flag = 0; continue; } else { if(flag) {line_width++;} }

        if( input_len >= max_input_len ) {
            max_input_len *= 2;
            input = realloc( input, max_input_len );
        }

        input[input_len] = c;
        input_len++; 
    }
    
    printf("line_width: %d\n", line_width); 
    fclose( file );
    
    int num_access_rolls = 0;
        
        for( int i = 0; i < input_len; ++i ) {

            int left_idx = i - 1;
            int right_idx = i + 1;
            int up_idx = i - line_width;
            int down_idx = i + line_width;
            int ul_idx = i - line_width - 1;
            int ur_idx = i - line_width + 1;
            int dl_idx = i + line_width - 1;
            int dr_idx = i + line_width + 1;
        
            int x = i % line_width;
            int y = i / line_width;
 
            int rolls = 0; 
            if( x > 0 ) {
                if( input[left_idx] == '@') { rolls++; }
            }
            if( x < line_width - 1 ) {
               if( input[right_idx] == '@') { rolls++; }
            }
            if( y > 0 ) {
                if( input[up_idx] == '@') { rolls++; }
            }
            if( y < (input_len / line_width) - 1 ) {
                if( input[down_idx] == '@') { rolls++; }
            }
            if( x > 0 && y > 0 ) {
                if( input[ul_idx] == '@') { rolls++; }
            }
            if( x < line_width - 1 && y > 0 ) {
                if( input[ur_idx] == '@') { rolls++; }
            }
            if( x > 0 && y < (input_len / line_width) - 1 ) {
                if( input[dl_idx] == '@') { rolls++; }
            }
            if( x < line_width - 1 && y < (input_len / line_width) - 1 ) {
                if( input[dr_idx] == '@') { rolls++; }
            }
        
            if( rolls < 4 && input[i] == '@') {
                num_access_rolls++;
                printf("x %d, ",  rolls);
            } else {
                printf("%c %d, ", input[i], rolls);
            }
            if( i % line_width == line_width - 1 ) {
                printf("\n");
            }
        }
 
    printf("output: %d\n", num_access_rolls);
    return EXIT_SUCCESS;
}
