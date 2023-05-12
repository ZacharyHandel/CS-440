#include <sys/types.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef BASIC_DIR_LIST_H
#define BASIC_DIR_LIST_H

char* getDirListing(const char*);
int noHiddenFiles(const struct dirent*);
int compareFileNames(const struct dirent**, const struct dirent**);

#endif /* BASIC_DIR_LIST_H */

