/*
* Demonstrate a basic file listing of a single directory
* jajerkins@una.edu, 04/29/2023
*/

#include "basicDirList.h"

char*
getDirListing(const char* dirName)
{
    struct dirent** nameList;
    int files;
	char foundFilesMsg[32];
	char filesListMsg[512];
	char message[1000];

	memset(foundFilesMsg, 0, sizeof foundFilesMsg);
	memset(message, 0, sizeof message);
	memset(filesListMsg, 0, sizeof filesListMsg);
    files = scandir(dirName, &nameList, noHiddenFiles, compareFileNames);
    if (files > -1) {
        sprintf(foundFilesMsg, "found %d files in %s directory\n", files, dirName);
	for (int i=0; i<files; i++) {
		strcat(filesListMsg, nameList[i]->d_name);
		strcat(filesListMsg, "\n");
	}

	for (int i=0; i<files; i++)
		free(nameList[i]);

	free(nameList);
    } else
		sprintf(message, "error %s\n", dirName);

	strcpy(message, foundFilesMsg);
	strcat(message, filesListMsg);

	return message;
}

int
noHiddenFiles(const struct dirent* filename)
{
    return (filename[0].d_name[0] != '.');
}

int
compareFileNames(const struct dirent** a, const struct dirent** b)
{
    return strcmp(a[0]->d_name, b[0]->d_name);
}
