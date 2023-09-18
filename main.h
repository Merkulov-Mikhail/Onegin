#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "build/sources/buffer.h"
#include "build/sources/mergeSort.h"
#include "build/sources/comparator.h"


#define min(a, b) (a > b) ? b : a

// self explaining variable name
const char* INPUT_FILE_NAME   = "input.txt";
const char* BACK_SORTED_NAME  = "back.txt";
const char* FRONT_SORTED_NAME = "front.txt";
const char* ORIGINAL_NAME     = "orig.txt";


enum ERRORS{
    ERROR_NO_FILE = -1,
    ERROR_NO_MEM  = -2
};
