#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "mergeSort.h"


#define uint64_t long long
#define min(a, b) (a > b) ? b : a

// self explaining variable name
const char* FILE_NAME = "input.txt";



enum ERRORS{
    ERROR_NO_FILE = -1,
    ERROR_NO_MEM  = -2
};


// Gets file's size via stat from sys/stat.h
uint64_t getFileSize( const char* fileName );
// Goes through buf and counts number of '\n' symbols
uint64_t countNewLines( uint64_t size, char* buf );
// Loads first N symbols from file to buf
void loadBuffer( char* buf, uint64_t* N, FILE* file );
// strcmp, but backwards.
// Starts compairing from the end of both strings, non alpha symbols are ignored
int strcmpBack( const void* l, const void* r );
// Start compairing from the start of both string, non alpha symbols are ignored
int strcmpFront( const void* l, const void* r );
void printStrings( const char** mas, uint64_t size );


int main(){

    FILE* file = fopen( FILE_NAME, "r" );

    if ( !file ){
        printf( "File %s does not exists\n", FILE_NAME );
        return ERRORS::ERROR_NO_FILE;
    }

    uint64_t fileSize = getFileSize( FILE_NAME );

    // bufText - buffer, that contains text from file
    char* bufText = ( char* ) calloc( sizeof( char ), fileSize + 1 );
    loadBuffer( bufText, &fileSize, file );

    // number on '\n' in text
    uint64_t nLines = countNewLines(fileSize, bufText);

    // text5[i] refers to the i'th string from original file
    const char** text5 = ( const char** ) calloc( sizeof( char* ),  nLines + 1);

    uint64_t line = 1;
    text5[0] = bufText;

    for ( uint64_t pos = 0; pos < fileSize; pos++ ){
        if ( bufText[pos] == '\n' ) {

            bufText[pos] = '\0';
            text5[line++] = bufText + pos + 1;

        }
    }

    mergeSort( text5, line, line * sizeof( const char** ), strcmpFront );
    printf("FRONT\n-------------------------\n");
    printStrings( text5, nLines );

    mergeSort( text5, line, line * sizeof( const char** ), strcmpBack );
    printf( "\n\n\n\n\n\n\n\n\n\nBACKWARDS\n-------------------------\n" );
    printStrings( text5, nLines );

    printf( "\n\n\n\n\n\n\n\n\n\nORIGINAL\n-------------------------\n" );
    printf( "%s\n", bufText );

    for ( uint64_t pos = 0; pos < fileSize; pos++ ){
        if ( bufText[pos] != 0 ){
            continue;
        }
        printf( "%s\n", bufText + pos + 1 );
    }

    free( bufText );
    free( text5 );

    return 0;
}


uint64_t countNewLines( uint64_t size, char* buf ){
    uint64_t nLines = 0;

    for ( uint64_t pos = 0; pos < size; pos++ )
        if ( buf[pos] == '\n' ) nLines++;

    return nLines;
}


uint64_t getFileSize( const char* fileName ){
    struct stat buf  = {};

    stat( fileName, &buf );

    return buf.st_size;
}


void loadBuffer( char* buf, uint64_t *N, FILE* file ){

    *N = fread( buf, sizeof( char ), *N, file );
    buf[*N] = 0;

}


int strcmpBack( const void* l, const void* r ){

    const char* left  = * ( char** ) l;
    const char* right = * ( char** ) r;

    uint64_t sizeL = strlen( left );
    uint64_t sizeR = strlen( right );
    for ( ; sizeL && sizeR; sizeL--, sizeR-- ){

        if ( !isalpha( left[sizeL] ) ){
            sizeR++;
            continue;
        }
        if ( !isalpha( right[sizeR] ) ){
            sizeL++;
            continue;
        }

        if ( left[sizeL] > right[sizeR] )
            return 1;

        if ( left[sizeL] < right[sizeR] )
            return -1;
    }

    if ( sizeL )
        return 1;

    if ( sizeR )
        return -1;

    return 0;
}


int strcmpFront( const void* l, const void* r ){

    const char* left  = * ( char** ) l;
    const char* right = * ( char** ) r;


    uint64_t sizeL = strlen( left );
    uint64_t sizeR = strlen( right );

    uint64_t a = 0, b = 0;

    for ( ; a < sizeL && b < sizeR; a++, b++ ){

        if ( !isalpha( left[a] ) ){
            b--;
            continue;
        }
        if ( !isalpha( right[b] ) ){
            a--;
            continue;
        }

        if ( left[a] > right[b] )
            return 1;

        if ( left[a] < right[b] )
            return -1;
    }

    if ( sizeL - a )
        return 1;
    if ( sizeR - b )
        return -1;
    return 0;
}


void printStrings( const char** mas, uint64_t size ){

    for( uint64_t pos = 0; pos < size; pos++)
        printf( "%s\n", mas[pos] );

}
