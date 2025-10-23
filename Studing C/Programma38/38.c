/*
•The father creates a son.
•The son generates random numbers 1–50 and sends them via pipe to the father.
•The father reads the numbers and calculates the sum.
•When the sum exceeds 500, the father finishes the son.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	int fdPipe[2];
	if (pipe(fdPipe) < 0) {
		err_sys("pipe() error: ");
	}
	
	pid_t pid = fork();
	if (pid < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) {
		close(fdPipe[READ]);
		srand((unsigned int)time(NULL) ^ getpid());
		
		while (1) {
			int N = (rand() % 50) + 1;
			
			if (write(fdPipe[WRITE], &N, sizeof(int)) < 0) {
				err_sys("write() fdPipe, error: ");
			}
		}
	}
	
	//FATHER
	close(fdPipe[WRITE]);
	
	int total = 0;
	while (total < 500) {
		usleep(500000);
		ssize_t rByte;
		
		int temp = 0;
		rByte = read(fdPipe[READ], &temp, sizeof(int));
		if (rByte < 0) {
			err_sys("read() fdPipe, error: ");
		}
		
		total += temp;
		
		printf("[FATHER]: Progression: %d.\n", total);
	}
	
	if (kill(pid, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}
	
	wait(NULL);
	
	printf("[FATHER]: The total is: %d.\n\n", total);
	
	
	close(fdPipe[READ]);
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
