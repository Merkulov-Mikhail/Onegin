#include "mergeSort.h"


void mergeSort( void* toSort, uint64_t length, uint64_t width, int ( *cmp ) ( const void*, const void* ) ){

    void* buf = calloc( width / length, length );

    _mergeSort( toSort, buf, length, width, cmp );

    free( buf );

}


void _mergeSort( void* toSort, void* buf, uint64_t length, uint64_t width, int ( *cmp ) ( const void*, const void* ) ){

    if ( length <= 1 )
        return;

    uint64_t leftLen  = length / 2;
    uint64_t rightLen = length - leftLen;

    size_t elSize = width / length;

    _mergeSort( toSort,                    buf, leftLen,  elSize * leftLen,  cmp );
    _mergeSort( toSort + leftLen * elSize, buf, rightLen, elSize * rightLen, cmp );

    uint64_t l = 0, r = 0;

    void *ptrLeft = nullptr, *ptrRight = nullptr;

    while ( l < leftLen && r < rightLen ){

        ptrLeft  = toSort + l * elSize;
        ptrRight = toSort + (r + leftLen) * elSize;

        if ( cmp( ptrLeft, ptrRight ) > 0 ){
            copyBuf( buf + (l + r) * elSize, ptrRight, elSize );
            r++;
        }
        else {
            copyBuf( buf + (l + r) * elSize, ptrLeft, elSize );
            l++;
        }
    }

    for ( ; l < leftLen; l++)
        copyBuf( buf + ( l + r ) * elSize, toSort + l * elSize,              elSize );

    for ( ; r < rightLen; r++)
        copyBuf( buf + ( l + r ) * elSize, toSort + (r + leftLen) * elSize,  elSize );

    copyBuf( toSort, buf, width );
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
