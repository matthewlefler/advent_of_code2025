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
    
    unsigned long zero_count = 0;
    ssize_t value = 50;
    
    char line_buffer[MAX_LINE_LENGTH];    
    // Read the file line by line using fgets()
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        int number = strtol( line_buffer + 1, NULL, 10);
        if( line_buffer[0] == 'L' ) {
            value -= number;
        } else {
            value += number;
        }

        if( value % 100 == 0 ) {
            zero_count++;
        }
    }
 
    fclose( file );
    
    printf( "number of zeros hit = %lu\n", zero_count );

    return EXIT_SUCCESS;
}
