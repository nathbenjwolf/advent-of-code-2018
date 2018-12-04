#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FABRIC_SIZE 1000
#define MAX_CLAIMS 2000
#define MAX_LINE_SIZE 30

char* filename = "data";

struct FabricClaim {
	int id;
	int xOffset;
	int yOffset;
	int width;
	int height;
};

// TOOK THIS CODE FROM ONLINE BECAUSE MINGW DOESN't HAVE STRTOK_R FOR SOME REASON
char* strtok_r(
    char *str, 
    const char *delim, 
    char **nextp)
{
    char *ret;

    if (str == NULL)
    {
        str = *nextp;
    }

    str += strspn(str, delim);

    if (*str == '\0')
    {
        return NULL;
    }

    ret = str;

    str += strcspn(str, delim);

    if (*str)
    {
        *str++ = '\0';
    }

    *nextp = str;

    return ret;
}
// TOOK THIS CODE FROM ONLINE BECAUSE MINGW DOESN't HAVE STRTOK_R FOR SOME REASON

void replaceChar( char* line, char prevChar, char newChar ) {
	for( char* curChar = line; *curChar == '\n'; curChar++ )  {
		if( *curChar == prevChar ) {
			*curChar = newChar;
		}
	}
}

struct FabricClaim parseInput( char* line ) {
	struct FabricClaim claim;
	char* lineId;
	char* delim = " ";

	// ClaimId (#123)
	char* claimId = strtok_r( line, delim, &lineId );
	// Skip the #
	claimId++;
	claim.id = atoi( claimId );

	// Skip @
	strtok_r( NULL, delim, &lineId );

	// Coordinates (308,562:)
	char* coordId;
	char* coord = strtok_r( NULL, delim, &lineId );
	replaceChar( coord, ':', '\0' );
	claim.xOffset = atoi( strtok_r( coord, ",", &coordId ) );
	claim.yOffset = atoi( strtok_r( NULL, ",", &coordId ) );

	// Size (15x13)
	char* sizeId;
	char* size = strtok_r( NULL, delim, &lineId );
	claim.width = atoi( strtok_r( size, "x", &sizeId ) );
	claim.height = atoi( strtok_r( NULL, "x", &sizeId ) );

	return claim;	
}

void addClaim( int* fabric[], struct FabricClaim claim ) {
	for( int x=claim.xOffset; x<(claim.xOffset+claim.width); x++ ) {
		for( int y=claim.yOffset; y<(claim.yOffset+claim.height); y++ ) {
			if( fabric[x][y] != 0 ) {
				// Overlapping fabric
				fabric[x][y] = -1;
			} else {
				fabric[x][y] = claim.id;
			}
		}
	}
}

int numOverlappingClaims( int* fabric[] ) {
	int count=0;
	for( int x=0; x<MAX_FABRIC_SIZE; x++ ) {
		for( int y=0; y<MAX_FABRIC_SIZE; y++ ) {
			if( fabric[x][y] == -1 ) {
				count++;
			}
		}
	}

	return count;
}

int main( void ) {
	int* fabric[MAX_FABRIC_SIZE];
	for( int i=0; i<MAX_FABRIC_SIZE; i++ ) {
		fabric[i] = (int* )calloc( MAX_FABRIC_SIZE, sizeof(int) );
	}

	FILE* fp;
	char line[MAX_LINE_SIZE];

	fp = fopen( filename, "r" );

	while( fgets(line, sizeof(line), fp ) ) {
		struct FabricClaim claim = parseInput( line );
		addClaim( fabric, claim );
	}

	int result = numOverlappingClaims( fabric );
	printf( "Number of overlapping inches: %d\n", result );


	for( int i; i<MAX_FABRIC_SIZE; i++ ) {
		free( fabric[i] );
	}
}
