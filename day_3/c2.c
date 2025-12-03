#include "stdlib.h"
#include "stdio.h"

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
    
    char line_buffer[MAX_LINE_LENGTH]; 
    unsigned long total = 0;
    // Read the file line by line using fgets()
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        unsigned long digits[12];
        char* line_end = line_buffer;
        while( *line_end != '\0' ) {
            if( *line_end == '\n' ) {
                *line_end = '\0';
                break;
            }
            line_end++;
        }
        int len = line_end - line_buffer;
        
        int max = 0;
        int end;
        for( int i = 0; i < len - 11; ++i ) {
            int val = line_buffer[i] - '0';
            if( val > max ) {
                max = val;
                end = i + 1;
            }
        }
        digits[0] = max;

        for( int digit = 1; digit < 12; ++digit ) {
            max = 0;
            for( int i = end; i < len - (11 - digit); ++i ) {
                int val = line_buffer[i] - '0';
                if( val > max ) {
                    max = val;
                    end = i + 1;
                }
            }
            digits[digit] = max;
        }
        
        unsigned long line_val = 
            digits[0]  * 100000000000 + 
            digits[1]  * 10000000000 + 
            digits[2]  * 1000000000 + 
            digits[3]  * 100000000 + 
            digits[4]  * 10000000 + 
            digits[5]  * 1000000 + 
            digits[6]  * 100000 + 
            digits[7]  * 10000 + 
            digits[8]  * 1000 +
            digits[9]  * 100 + 
            digits[10] * 10 + 
            digits[11]; 
       
        printf("in: %s, %ld, len: %d\n", line_buffer, line_val, len);
        
        total += line_val;
    }
 
    fclose( file );

    printf("\n%ld\n", total);  

    return EXIT_SUCCESS;
}
