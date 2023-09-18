#include "main.h"



void printStrings( const struct stringData* mas, uint64_t size, FILE* file );


int main(){

    FILE* file = fopen( INPUT_FILE_NAME, "r" );

    if ( !file ){
        printf( "File %s does not exists\n", INPUT_FILE_NAME );
        return ERRORS::ERROR_NO_FILE;
    }

    uint64_t fileSize = getFileSize( INPUT_FILE_NAME );

    // bufText - buffer, that contains text from file
    char* bufText = ( char* ) calloc( sizeof( char ), fileSize + 1 );
    loadBuffer( bufText, &fileSize, file );

    // number on '\n' in text
    uint64_t nLines = countNewLines(fileSize, bufText);

    // text5[i] refers to the i'th string from original file
    struct stringData* text5 = ( struct stringData* ) calloc( sizeof( struct stringData ),  nLines + 1);

    text5[0].ptr  = bufText;

    uint64_t line = 0;

    makePtrs( bufText, text5, fileSize, &line );
    // ----------------------------------------
    mergeSort( text5, line, line * sizeof( stringData ), strcmpFront );

    FILE* front = fopen(FRONT_SORTED_NAME, "w");
    printStrings( text5, nLines, front );
    fclose(front);

    // ----------------------------------------
    mergeSort( text5, line, line * sizeof( stringData ), strcmpBack );

    FILE* back = fopen(BACK_SORTED_NAME, "w");
    printStrings( text5, nLines, back );
    fclose( back );

    // ----------------------------------------
    FILE* orig = fopen(ORIGINAL_NAME, "w");
    fprintf( orig, "%s\n", bufText );

    for ( uint64_t pos = 0; pos < fileSize; pos++ ){
        if ( bufText[pos] != 0 ){
            continue;
        }
        fprintf( orig, "%s\n", bufText + pos + 1 );
    }

    free( bufText );
    free( text5 );

    printf("ended");
    return 0;
}


void printStrings( const struct stringData* mas, uint64_t size, FILE* file ){

    for( uint64_t pos = 0; pos < size; pos++)
        fprintf(file, "%s\n", mas[pos].ptr );

}
