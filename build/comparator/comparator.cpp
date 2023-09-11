#include "comparator.h"


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
