#include <stdio.h>
#include <stdlib.h>

char filename[] = "data";

int main( void ) {

	int frequency = 0;
	FILE *f;
	f = fopen( filename, "r" );
	int num;
	while( fscanf( f, "%d", &num ) != -1 ) {
		printf( "Found num: %d, new total: %d\n", num, frequency );
		frequency += num;
	}

	fclose( f );
	printf( "Frequency is: %d\n", frequency );
	return 0;

}
