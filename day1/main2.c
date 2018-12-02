#include <stdio.h>
#include <stdlib.h>

#define MAX_VALS 1000000

char filename[] = "data";
int previousValues[ MAX_VALS ];

int main( void ) {

	int frequency = 0;
	int idx = 0;
	int repeatFrequencyFound = 0;
	FILE *f;
	f = fopen( filename, "r" );
	int num;
	while( !repeatFrequencyFound ) {
		while( fscanf( f, "%d", &num ) != -1 ) {
			// Assign frequency at the start so we handle initial frequency of 0
			previousValues[ idx ] = frequency;

			// Update frequency and index for new num
			idx++;
			frequency += num;

			printf( "Found num: %d, frequency: %d index: %d\n", num, frequency, idx );

			// Search for same previous frequencies
			for( int i=0; i<idx; i++ ) {
				if( frequency == previousValues[ i ] ) {
					repeatFrequencyFound = 1;
					break;
				}
			}

			if( repeatFrequencyFound ) {
				printf( "Repeat frequency is: %d\n", frequency );
				break;
			}
		}

		fseek( f, 0, SEEK_SET );
	}

	fclose( f );
	return 0;
}
