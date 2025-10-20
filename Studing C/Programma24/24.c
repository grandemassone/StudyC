/*
 •The father creates a child process.
 •The son generates random numbers from 1 to 50 and sends them to the father via pipe.
 •The father reads the numbers from the pipe and calculates the partial sum.
 •If the sum exceeds 500, the father finishes the child, prints the total sum and finishes.
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
		//I close the pipe reading end
		close(fdPipe[READ]);
		
		//I initialize srand
		srand((unsigned int)time(NULL) ^ getpid());
		
		while (1) {
			//A pause at each iteration of 0.5s
			usleep(500000);
			
			//I generate a number between 1 and 50
			int x = (rand() % 50) + 1;
			
			//I write one number at a time in the pipe
			if (write(fdPipe[WRITE], &x, sizeof(int)) < 0) {
				err_sys("write() error: ");
			}
		}
	}
	
	//Father
	
	//I close the writing end of the pipe
	close(fdPipe[WRITE]);
	
	int sum = 0;
	while (sum <= 500) {
		int temp = 0;
		ssize_t rByte = read(fdPipe[READ], &temp, sizeof(int));
		if (rByte < 0) {
			err_sys("read() fdPipe, error: ");
		}
		
		sum += temp;
	}
	
	//Sending SIGKILL to son
	kill(pid, SIGKILL);
	
	//I close the pipe reading end
	close(fdPipe[READ]);
	
	printf("The final sum is: %d.\n\n", sum);
	
	
	exit(EXIT_SUCCESS);
}

*/
