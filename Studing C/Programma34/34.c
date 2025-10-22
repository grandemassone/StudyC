/*
•Son 1 generates a random number between 1 and 100 and sends it via pipe to Son 2.
• Son 2 receives the number, doubles it and prints it.
•The father waits for both sons to finish and prints a final message.
*/

/*
 
#include <utilsF.h>
#include <time.h>

int main(void)
{
	int fdpipe[2];
	if (pipe(fdpipe) < 0) {
		err_sys("pipe() error: ");
	}
	
	pid_t pid1, pid2;
	
	if ((pid1 = fork()) < 0) {
		err_sys("fork() 1 error: ");
	} else if (pid1 == 0) {
		close(fdpipe[READ]);
		
		srand((unsigned int)time(NULL));
		int N = (rand() % 100) + 1;
		
		printf("[SON 1]: The newly generated number is: %d.\n", N);
		
		if (write(fdpipe[WRITE], &N, sizeof(int)) < 0) {
			err_sys("write() error: ");
		}
		
		close(fdpipe[WRITE]);
		
		exit(EXIT_SUCCESS);
	}
	
	if ((pid2 = fork()) < 0) {
		err_sys("fork() 2 error: ");
	} else if (pid2 == 0) {
		close(fdpipe[WRITE]);
		
		int Nx2;
		ssize_t rByte = read(fdpipe[READ], &Nx2, sizeof(int));
		if (rByte < 0) {
			err_sys("read() error:");
		}
		
		printf("[SON 2]: The doubled number is: %d.\n\n", Nx2 * 2);
		
		close(fdpipe[READ]);
		
		exit(EXIT_SUCCESS);
	}
	
	//FATHER
	close(fdpipe[READ]);
	close(fdpipe[WRITE]);
	for (int i = 0; i < 2; i++) {
		wait(NULL);
	}
	
	
	printf("[FATHER]: The children are both finished, bye.\n\n");
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
