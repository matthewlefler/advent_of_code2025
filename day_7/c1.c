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
    long long total = 0;
    // Read the file line by line using fgets()
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        memcpy(input[line_count], line_buffer, sizeof(line_buffer));
        line_count++;
    }
 
    fclose( file );
    
    int *beam_locations = malloc( sizeof(int) * 1000);
    int num_beams = 0;
    for( int character = 0; input[0][character] != '\0'; character++ ) {
        if( input[0][character] == 'S' ) {
            beam_locations[num_beams] = character;
            num_beams++;
        }  
    }
    
    
    int *new_beam_locations = malloc( sizeof(int) * 1000 );
    for( int y = 0; y < line_count; y++ ) {
        char* line = input[y];

        int new_num_beams = 0;
        
        for( int i = 0; i < num_beams; i++ ) {
            int beam = beam_locations[i];
            
            if( line[beam] == '^' ) {
                // split
                total++;
                int left = beam - 1;
                int right = beam + 1;
                for( int j = 0; j < new_num_beams; j++ ) {
                    int beam_loc = new_beam_locations[j];
                    if( beam_loc == left ) {
                        left = -1;
                    }   
                    if( beam_loc == right ) {
                        right = -1;
                    }
                }
                
                if( right != -1 ) {
                    new_beam_locations[new_num_beams] = right;
                    new_num_beams++;
                }
                if( left != -1 ) {
                    new_beam_locations[new_num_beams] = left;
                    new_num_beams++;
                }
            } else {
                for( int j = 0; j < new_num_beams; j++ ) {
                    int beam_loc = new_beam_locations[j];
                    if( beam_loc == beam ) {
                        beam = -1;
                    }
                }
                if( beam != -1 ) {
                    new_beam_locations[new_num_beams] = beam;
                    new_num_beams++;
                }
            }
        }

        int* tmp = beam_locations;
        beam_locations = new_beam_locations;
        new_beam_locations = tmp;
        
        num_beams = new_num_beams;  
    }  

    printf("%lld\n", total);  

    return EXIT_SUCCESS;
}
