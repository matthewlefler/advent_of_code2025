#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_LINE_LENGTH 256
#define DEBUG 1

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
    
    unsigned long zero_count = 0;
    ssize_t value = 50;
    
    char line_buffer[MAX_LINE_LENGTH];    
    // Read the file line by line using fgets()
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        if( line_buffer[0] == 'L' ) {
            line_buffer[0] = '-';
        } else {
            line_buffer[0] = '+';
        }
        
        int number = strtol( line_buffer, NULL, 10 );
        int number_mod = number % 100;
        zero_count += abs( number/100 );
        if( value != 0 ) {
            if( value + number_mod <= 0 || value + number_mod >= 100 ) {
                zero_count++;
            }
        }

#if DEBUG
        printf("val: %zd, num: %d, zero_cnt: %zu,\n", value, number, zero_count);
#endif

        value += number;

        value = value % 100;
        if( value < 0 ) {
            value += 100;
        }
    }
 
    fclose( file );
    
    printf( "number of zeros hit = %lu, test: %d\n", zero_count, (-10)/100 );

    return EXIT_SUCCESS;
}
