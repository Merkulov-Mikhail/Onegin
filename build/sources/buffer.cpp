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

void makePtrs( char* bufText, struct stringData* text5, uint64_t fileSize, uint64_t* line ){
    uint64_t currLength = 0;
    for ( uint64_t pos = 0; pos < fileSize; pos++ ){
        if ( bufText[pos] == '\n' ) {

            bufText[pos] = '\0';
            text5[*line].size = currLength;

            (*line)++;
            text5[*line].ptr  = bufText + pos + 1;

            currLength = 0;
        }
        else{
            currLength++;
        }
    }
    if ( currLength )
        text5[*line].size = currLength;
}


void copyBuf( void* dest, const void* src, uint64_t nBytes ){
    uint64_t pos = 0;
    for ( ; nBytes ; ){

        if ( nBytes >= 8 ){
            *( uint64_t* ) (dest + pos) = *( uint64_t* ) ( src + pos );
            pos += 8;
            nBytes -= 8;
        }

        else if ( nBytes >= 4 ){
            *( uint32_t* ) (dest + pos) = *( uint32_t* ) ( src + pos );
            pos += 4;
            nBytes -= 4;
        }

        else if ( nBytes >= 2){
            *( uint16_t* ) (dest + pos) = *( uint16_t* ) ( src + pos );
            pos += 2;
            nBytes -= 2;
        }

        else{
            *( uint8_t* ) (dest + pos) = *( uint8_t* ) ( src + pos );
            pos += 1;
            nBytes -= 1;
        }
    }
}
