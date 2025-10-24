/*
•The father creates 2 children.
•Son 1 generates random numbers 0–50 and sends them via pipe to the father.
•Son 2 generates random numbers 50–100 and sends them via pipe to the father
•The father receives the numbers from both, averages the values read and prints them every second.
• If the average exceeds 50, both children end.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	pid_t pid1, pid2;
	int fdPipe1[2], fdPipe2[2];
	
	if (pipe(fdPipe1) < 0) {
		err_sys("pipe() error: ");
	}
	if (pipe(fdPipe2) < 0) {
		err_sys("pipe() error: ");
	}
	
	
	if ((pid1 = fork()) < 0) {
		err_sys("fork() error: ");
	} else if (pid1 == 0) {
		close(fdPipe1[READ]);
		srand((unsigned int)time(NULL) ^ getpid());
		
		while (1) {
			usleep(100000);
			int N = rand() % 50;
			
			if (write(fdPipe1[WRITE], &N, sizeof(int)) < 0) {
				err_sys("write in fdPipe1, error: ");
			}
		}
	}
	
	if ((pid2 = fork()) < 0) {
		err_sys("fork() error: ");
	} else if (pid2 == 0) {
		close(fdPipe2[READ]);
		srand((unsigned int)time(NULL) ^ getpid());
		
		while (1) {
			usleep(100000);
			int N = (rand() % 51) + 50;
			
			if (write(fdPipe2[WRITE], &N, sizeof(int)) < 0) {
				err_sys("write in fdPipe2, error: ");
			}
		}
	}
	
	//FATHER
	int total1 = 0, total2 = 0;
	int count = 0;
	int average = 0;
	
	close(fdPipe1[WRITE]);
	close(fdPipe2[WRITE]);
	

	while (average < 50) {
		int val;
		ssize_t rByte = read(fdPipe1[READ], &val, sizeof(int));
		if (rByte < 0) {
			err_sys("read() in fdPipe1, error: ");
		}
		total1 += val;
		count++;
		
		rByte = read(fdPipe2[READ], &val, sizeof(int));
		if (rByte < 0) {
			err_sys("read() in fdPipe2, error: ");
		}
		total2 += val;
		count++;
		
		if (count > 0) {
			average = (total1 + total2) / count;
			printf("[FATHER]: Current average: %d.\n", average);
		}
	}
	
	if (kill(pid1, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}
	if (kill(pid2, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}
	
	wait(NULL);
	wait(NULL);
	
	printf("[FATHER]: The total average is: %d.\n\n", average);
	

	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
