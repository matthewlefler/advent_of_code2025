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
    int total = 0;
    // Read the file line by line using fgets()
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        int max = 0;
        for( char* i = line_buffer; (*i) != '\0'; ++i ) {
            for( char* j = i + 1; *j != '\0'; ++j ) {
                int val = (*i - '0') * 10 + (*j - '0');
                if( val > max ) {
                    max = val;
                }
            }
        }
        total += max;
    }
 
    fclose( file );

    printf("%d\n", total);  

    return EXIT_SUCCESS;
}
