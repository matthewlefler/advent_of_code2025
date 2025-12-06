#include "stdlib.h"
#include "stdio.h"
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

    long long ranges[1000][2];
    int i = -1;
    char line_buffer[MAX_LINE_LENGTH]; 
    long long total = 0;
    int values_flag = 0;
    // Read the file line by line using fgets()
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        if( strlen(line_buffer) <= 1 ) {
            printf("Done parseing Ranges: %d\n", i);
            values_flag = 1;
            break;
        }
    
        if( !values_flag ) {
            i++;
            unsigned long long val_1 = strtol(line_buffer, NULL, 10);
            ranges[i][0] = val_1;  
            char* second_num_start = line_buffer;
            while( *second_num_start != '-' ) {
                second_num_start++;
            }
            second_num_start++;
            unsigned long long val_2 = strtol(second_num_start, NULL, 10);
            ranges[i][1] = val_2;
            printf("%lld, %lld\n", val_1, val_2);
            
        }
    }
 
    fclose( file );
    
    
    for( int j = 0; j <= i; ++j ) {
        long long low = ranges[j][0];
        long long high = ranges[j][1];
        total += high - low + 1;
        for( int k = j+1; k <= i; ++k ) {
            // get over lap     
            long long overlap_start = ranges[k][0] > low ? ranges[k][0] : low;
            long long overlap_end = ranges[k][1] > high ? high : ranges[k][1];
            
            if( overlap_start <= overlap_end ) {
                total -= overlap_end - overlap_start + 1;
                printf("found overlap: %lld - %lld \n", overlap_start, overlap_end);
            }
        }
    }

    printf("%lld\n", total);  

    return EXIT_SUCCESS;
}
