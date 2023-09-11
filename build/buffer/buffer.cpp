#include "buffer.h"


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

void setZeros( char* bufText, const char** text5, uint64_t fileSize, uint64_t* line ){
    for ( uint64_t pos = 0; pos < fileSize; pos++ ){
        if ( bufText[pos] == '\n' ) {

            bufText[pos] = '\0';
            text5[( *line )++] = bufText + pos + 1;
        }
    }
}
