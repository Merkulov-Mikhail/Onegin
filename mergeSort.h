#include <inttypes.h>
#include <stdlib.h>


// Algorithm of merge sort (https://en.wikipedia.org/wiki/Merge_sort)
void mergeSort( void* toSort, uint64_t length, uint64_t width, int ( *cmp ) ( const void*, const void* ) );
void _mergeSort( void* toSort, void* buf, uint64_t length, uint64_t width, int ( *cmp ) ( const void*, const void* ) );
void copyBuf( void* dest, const void* src, uint64_t nBytes );
