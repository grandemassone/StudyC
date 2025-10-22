/*
•The father creates N pipes (one for each child).
•Children generate a random number between 1 and 100 and write it on their pipe.
•The father reads all the numbers and calculates the average.
•Print the average and finish.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	//X = number of children
	int X = 7;
	
	//I create a pipe for each child
	int fdPipe[X][2];
	for (int i = 0; i < X; i++) {
		if (pipe(fdPipe[i]) < 0) {
			err_sys("pipe() error: ");
		}
	}
	
	for (int i = 0; i < X; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			err_sys("fork() error: ");
		} else if (pid == 0) {
			//I initialize srand
			srand((unsigned int)time(NULL) ^ getpid());
			
			//I close the pipe reading end
			close(fdPipe[i][READ]);
			
			//I generate a random number between 1 and 100
			float N = (rand() % 100) + 1;
			
			printf("[SON %d]: The number I generated is: %.0f.\n", i + 1, N);
			
			//I write the random number on the pipe
			if (write(fdPipe[i][WRITE], &N, sizeof(float)) < 0) {
				err_sys("write() error: ");
			}
			
			//I close the pipe writing end
			close(fdPipe[i][WRITE]);
			
			//Exit with status i
			exit(i);
		}
	}
	
	//FATHER
	
	//Let's wait for all the children to finish
	for (int i = 0; i < X; i++) {
		wait(NULL);
	}

	float total = 0;
	for (int i = 0; i < X; i++) {
		//I close the pipe writing end
		close(fdPipe[i][WRITE]);
		
		float temp = 0;
		ssize_t rByte = read(fdPipe[i][READ], &temp, sizeof(float));
		if (rByte < 0) {
			err_sys("read() error: ");
		}
		
		total += temp;
		
		//I close the pipe reading end
		close(fdPipe[i][READ]);
	}
	
	
	printf("\n[FATHER]: The total is: %.0f.\n", total);
	printf("[FATHER]: The average of all numbers is: %.2f.\n\n", total / X);
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
