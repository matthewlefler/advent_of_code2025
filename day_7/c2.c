#include "stdlib.h"
#include "stdio.h"
#include <string.h>

#define MAX_LINE_LENGTH 1000

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

    char input[1000][MAX_LINE_LENGTH];
    int line_count = 0;
    char line_buffer[MAX_LINE_LENGTH]; 
    // Read the file line by line using fgets()
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        memcpy(input[line_count], line_buffer, sizeof(line_buffer));
        line_count++;
    }
 
    fclose( file );
    
    int width;
    for( int i = 0; input[0][i] != '\0'; i++) {
        width = i;
    }
    unsigned long long *beam_weights = malloc( sizeof(unsigned long long) * width);
    memset( beam_weights, 0, sizeof(unsigned long long) * width );

    for( int character = 0; input[0][character] != '\0'; character++ ) {
        if( input[0][character] == 'S' ) {
            beam_weights[character] = 1;
        }  
    }
    
    
    unsigned long long *new_beam_weights = malloc( sizeof(unsigned long long) * width );
    for( int y = 0; y < line_count; y++ ) {
        char* line = input[y];

        memset( new_beam_weights, 0, sizeof(unsigned long long) * width );
        
        for( int i = 0; i < width; i++ ) {
            unsigned long long weight = beam_weights[i];
            if( weight == 0 ) {
                continue;
            }
            
            if( line[i] == '^' ) {
                // split
                int left = i - 1;
                int right = i + 1;
                
                new_beam_weights[left] += weight;
                new_beam_weights[right] += weight;
            } else {
                new_beam_weights[i] += weight;
            }
        }

        unsigned long long* tmp = beam_weights;
        beam_weights = new_beam_weights;
        new_beam_weights = tmp;

        for( int i = 0; i < width; i++ ) {
            if(beam_weights[i] > 0) {
                printf("%2.2lld", beam_weights[i]);
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }  
    unsigned long long total = 0;
    for (size_t i = 0; i < width; i++) {
        total += beam_weights[i];
    }
    
    printf("%lld\n", total);  

    return EXIT_SUCCESS;
}
