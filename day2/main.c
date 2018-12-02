#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 256

char filename[] = "data";

struct CharData {
	char character;
	int count;
};

int isLetterRepeated( struct CharData* data, int size, int numTimes ) {
	for( int i=0; i<size; i++ ) {
		if( data[i].count == numTimes ) {
			return 1;
		}
	}

	return 0;
}

int main( void ) {
	FILE *fp;
	char line[ MAX_LINE_LEN ];
	
	// Open file
	fp = fopen( filename, "r" );
	
	// 2 and 3 repeated letter counters
	int num2LetterCodes = 0;
	int num3LetterCodes = 0;

	// storage for the line
	struct CharData charData[ MAX_LINE_LEN ];
	int numChars = 0;

	// Parse data line by line
	while( fgets(line, sizeof(line), fp ) ) {

		// Walk through each character in the line
		for( int j=0; line[j] != '\n'; j++ ) {
			int charInList = 0;

			// Check if the character has already been seen
			for( int i=0; i<numChars; i++ ) {
				if( charData[i].character == line[j] ) {
					charData[i].count++;
					charInList = 1;
					break;
				}
			}

			// If we didn't see the char in the list then add a new entry for it
			if( !charInList ) {
				charData[numChars].character = line[j];
				charData[numChars++].count = 1;
			}
		}

		printf( "numChars is: %d\n", numChars );

		// Parse our charData to see if we have any 2 or 3 repeated letters
		num2LetterCodes += isLetterRepeated( charData, numChars, 2 );
		num3LetterCodes += isLetterRepeated( charData, numChars, 3 );

		// Reset numChars back to 0 for the new line
		numChars = 0;
	}

	// Close the file
	fclose( fp );

	// Calculate checksum
	int checksum = num2LetterCodes * num3LetterCodes;
	printf( "checksum is: %d\n", checksum );
}
