#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define LL long long
#define min(a, b) (a > b) ? b : a

// self explaining variable name
const char* FILE_NAME = "input.txt";



enum ERRORS{
    ERROR_NO_FILE = -1,
    ERROR_NO_MEM  = -2
};


// Gets file's size via stat from sys/stat.h
LL getFileSize( const char* fileName );
// Goes through buf and counts number of '\n' symbols
LL countNewLines( LL size, char* buf );
// Loads first N symbols from file to buf
void loadBuffer( char* buf, LL N, FILE* file );
// strcmp, but backwards.
// Starts compairing from the end of both strings, non alpha symbols are ignored
int strcmpBack( const char* left, const char* right );
// Start compairing from the start of both string, non alpha symbols are ignored
int strcmpFront( const char* left, const char* right );
// Algorithm of merge sort (https://en.wikipedia.org/wiki/Merge_sort)
const char** mergeSort( const char** toSort, LL length, int ( *cmp ) ( const char*, const char* ) );
void printStrings(const char** mas, LL size);


int main(){

    FILE* file = fopen( FILE_NAME, "r" );

    if ( !file ){
        printf( "File %s does not exists\n", FILE_NAME );
        return ERRORS::ERROR_NO_FILE;
    }

    LL fileSize = getFileSize( FILE_NAME );

    // bufText - buffer, that contains text from file
    char* bufText = ( char* ) calloc( sizeof( char ), fileSize + 1 );
    loadBuffer( bufText, fileSize, file );

    // number on '\n' in text
    LL nLines = countNewLines(fileSize, bufText);

    // text5[i] refers to the i'th string from original file
    const char** text5 = ( const char** ) calloc( sizeof( char* ),  nLines + 1);

    LL line = 1;
    text5[0] = bufText;

    for ( LL pos = 0; pos < fileSize; pos++ ){
        if ( bufText[pos] == '\n' ) {
            bufText[pos] = '\0';
            text5[line++] = bufText + pos + 1;
        }
    }

    const char** sortedFrontText5 = mergeSort( text5, line, strcmpFront );
    const char** sortedBackwText5 = mergeSort( text5, line, strcmpFront );

    printf("FRONT\n-------------------------\n");

    printStrings(sortedFrontText5, nLines);

    printf("\n\n\n\n\n\n\n\n\n\nBACKWARDS\n-------------------------\n");

    printStrings(sortedBackwText5, nLines);

    printf("\n\n\n\n\n\n\n\n\n\nORIGINAL\n-------------------------\n");

    printStrings(text5, nLines);


    free(sortedFrontText5);
    free(sortedBackwText5);
    free(bufText);
    free(text5);

    return 0;
}


LL countNewLines(LL size, char* buf){
    LL nLines = 0;
    for ( LL pos = 0; pos < size; pos++ )
        if ( buf[pos] == '\n' ) nLines++;
    return nLines;
}


LL getFileSize( const char* fileName ){
    struct stat buf  = {};

    stat( fileName, &buf );

    return buf.st_size;
}


void loadBuffer( char* buf, LL N, FILE* file ){
    fread( buf, sizeof( char ), N, file );
    buf[N] = 0;
}


const char** mergeSort( const char** toSort, LL length, int ( *cmp ) ( const char*, const char* ) ){
    if ( length <= 1 )
        return toSort;

    LL leftLen  = length / 2;
    LL rightLen = length - leftLen;

    const char** leftSide  = mergeSort( toSort,           leftLen, cmp );
    const char** rightSide = mergeSort( toSort + leftLen, rightLen, cmp );

    const char** resArr = ( const char** ) calloc( sizeof( char* ), length );

    LL l = 0, r = 0;
    while ( l < leftLen && r < rightLen ){

        if ( cmp( leftSide[l], rightSide[r] ) > 0 ){
            resArr[l + r] = rightSide[r];
            r++;
        }
        else {
            resArr[l + r] = leftSide[l];
            l++;
        }
    }

    for ( ; l < leftLen; l++ )
        resArr[l + r] = leftSide[l];
    for ( ; r < rightLen; r++ )
        resArr[l + r] = rightSide[r];

    return resArr;
}

int strcmpBack( const char* left, const char* right ){

    LL sizeL = strlen(left);
    LL sizeR = strlen(right);

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


int strcmpFront( const char* left, const char* right ){
    LL sizeL = strlen(left);
    LL sizeR = strlen(right);

    LL a = 0, b = 0;

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


void printStrings(const char** mas, LL size){
    for( LL pos = 0; pos < size; pos++)
        printf("%s\n", mas[pos]);
}
