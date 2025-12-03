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
    
    size_t max_input_len = 100;
    size_t input_len = 0;
    char* input = malloc( max_input_len );
    char c;
    // Read the file line by line using fgets()
    while ( (c = fgetc(file)) != EOF) {
        if( input_len >= max_input_len ) {
            max_input_len *= 2;
            input = realloc( input, max_input_len );
        }

        input[input_len] = c;        
    }
 
    fclose( file );

    char* first = input;
    char* second = input;

    while( 1 ) {
        
    }

    return EXIT_SUCCESS;
}
