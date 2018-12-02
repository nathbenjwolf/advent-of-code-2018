#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define MAX_INPUTS 1000

char filename[] = "data";

struct CodeData {
	char code[ MAX_LINE_LEN ];
};

// Assumes codes are same length
int findMatchingCode( struct CodeData* data, int numCodes, char* code ) {
	int foundDiffChar = 0;
	for( int i=0; i<numCodes; i++ ) {
		for( int j=0; data[i].code[j] != '\n'; j++ ) {
			if( data[i].code[j] != code[j] ) {
				if( !foundDiffChar ) {
					foundDiffChar = 1;	
				} else {
					foundDiffChar = 0;
					break;
				}
			}
		}

		if( foundDiffChar ) {
			return i;
		}
	}

	return -1;
}

int main( void ) {
	FILE *fp;
	char line[ MAX_LINE_LEN ];
	
	// Open file
	fp = fopen( filename, "r" );

	// storage for the line
	struct CodeData codeData[ MAX_INPUTS ];
	int numCodes = 0;

	// Parse data line by line
	while( fgets(line, sizeof(line), fp ) ) {

		int matchingIdx = 0;
		if( ( matchingIdx = findMatchingCode( codeData, numCodes, line ) ) != -1 ) {
			printf( "found matching codes: \n%s%s", codeData[ matchingIdx ].code, line );
		}

		// Add line to data
		strcpy( codeData[numCodes++].code, line );
	}

	// Close the file
	fclose( fp );

	return 0;
}
