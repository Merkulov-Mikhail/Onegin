#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include "buffer.h"


// strcmp, but backwards.
// Starts compairing from the end of both strings, non alpha symbols are ignored
int strcmpBack( const void* l, const void* r );
// Start compairing from the start of both string, non alpha symbols are ignored
int strcmpFront( const void* l, const void* r );
