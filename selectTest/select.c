#include <sys/select.h>
#include <sys/time.h>

#include <err.h>
#include <stdio.h>
#include <unistd.h>

enum CONSTANTS {
	MAX_BUF = 256,
	QTR_SECS = 20
};

int
main(void)
{
	fd_set rfds;
	struct timeval tv;
	int retval;
	int stay_in_loop;

	while(stay_in_loop) {
		FD_ZERO(&rfds);
		FD_SET(STDIN_FILENO, &rfds);

		tv.tv_sec = 0;
		tv.tv_usec = 250000;
		
		retval = select(STDIN_FILENO+1, &rfds, NULL, NULL, &tv);

		if (retval == -1) {
			warn("select(2)");
		}
		
		if(retval > 0) {
			printf("Data is available now->\t");
			char str[MAX_BUF];
			fgets(str, sizeof str, stdin);
			printf("%s", str);
		}

		stay_in_loop--;
	}
	return 0;
}
