#include <stdio.h>
#include <inttypes.h>
#include <sys/stat.h>


// Loads first N symbols from file to buf
void loadBuffer( char* buf, uint64_t* N, FILE* file );
// Gets file's size via stat from sys/stat.h
uint64_t getFileSize( const char* fileName );
// Goes through buf and counts number of '\n' symbols
uint64_t countNewLines( uint64_t size, char* buf );
void setZeros(char* bufText, const char** text5, uint64_t fileSize, uint64_t* line);
