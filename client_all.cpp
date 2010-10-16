#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARDS 135

int main(int argc, char *argv[]) {
	int i, result, success = 0;
	char command[100];
	int results[BOARDS];

	for(i = 1; i < BOARDS; i++) {
	   	printf("checking board %d\n", i);
	   	snprintf(command ,100, "./client %d", i);
	   	result = system(command);
	   	printf("board %d %s\n-------------\n\n", i, result ? "failed" : "success");
		if(!result)
			success++;
		results[i] = result;
		sleep(2);
	}

	for(i = 1; i < BOARDS; i++) {
	   	printf("board %d %s\n", i, results[i] ? "failed" : "success");
	}
	printf("%d board(s) solved out of %d\n", success, BOARDS-1);
	return 0;
}
