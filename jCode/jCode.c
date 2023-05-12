#include <stdio.h>
#include <strings.h>
#include <string.h>
int main(void)
{
	char lineIn[128];
	char cmd[4];
	char filename[64];

	printf("Enter [GET|PUT|BYE} and an optional filename: ");
	scanf("%127s", lineIn);
	
	memset(cmd, 0, sizeof cmd);	//NOTE: a null byte \0 is equivatent to 0
	memcpy(cmd, lineIn, 3);

	if (strcasecmp(cmd, "GET") == 0 || strcasecmp(cmd, "PUT")) {
		memset(filename, 0, sizeof filename);
		scanf("%63s", filename);
	}

	printf("Command = %s\nFilename = %s\n", cmd, filename);	//[i gives function sumthin
	
	return 0;
}
