/*
 •The program accepts an integer X (with X > 0) from the command line, which represents the number of children to create.
 •The father creates X child processes.
 • Each child generates random numbers between 1 and 100, sends them to the father via dedicated pipe and then waits 0.3 seconds before generating another.
 •The father reads the numbers coming from all the pipes, calculates the total sum and periodically prints the values received (with indication of the son who sent them).
 •When the total sum exceeds 2000, the father:
  1.End all children with kill(pid, SIGKILL)
  2.Print the final sum and the total number of values received by each child
  3.Finish the program correctly
*/

/*

#include <utilsF.h>
#include <time.h>

int main(int argc, char** argv)
{
	if (argc < 2) {
		err_sys("Number of incorrect command line arguments passed: ");
	}
	
	//I take the value passed by parameter and make it an integer
	int X = atoi(argv[1]);
	
	//I create a two-dimensional pipe for use with different children
	int fdPipe[X][2];
	for (int i = 0; i < X; i++) {
		if (pipe(fdPipe[i]) < 0) {
			err_sys("pipe() error: ");
		}
	}
	
	//I create an array to save children's pids and use them later
	pid_t pids[X];
	
	//This "for" is used to manage what each child must do
	for (int i = 0; i < X; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			printf("%d° fork() error", i);
			err_sys(": ");
		} else if (pid == 0) {
			//I initialize srand
			srand((unsigned int)time(NULL) ^ getpid());
			
			//I close the pipe reading end
			close(fdPipe[i][READ]);
			while (1) {
				//Waits 0.3s
				usleep(300000);
				
				//I generate a random number between 1 and 100
				int num = (rand() % 100) + 1;
				
				if (write(fdPipe[i][WRITE], &num, sizeof(int)) < 0) {
					err_sys("write() error: ");
				}
			}
		} else {
			pids[i] = pid;
		}
	}
	
	//FATHER
	//I close all the writing ends because I just need to read anyway
	for (int i = 0; i < X; i++) {
		close(fdPipe[i][WRITE]);
	}
	
	int total = 0;
	int rVal = 0;
	while (total <= 2000) {
		for (int i = 0; i < X; i++) {
			//I read the value inside each pipe written from each file
			int temp;
			ssize_t rByte = read(fdPipe[i][READ], &temp, sizeof(int));
			if (rByte < 0) {
				err_sys("read() error: ");
			}
			
			//Every time he does a reading I increase the counter
			rVal++;
			
			//I add the value just taken to total
			total += temp;
		}
	}
	
	//I close the pipe reading end
	for (int i = 0; i < X; i++) {
		close(fdPipe[i][READ]);
	}
	
	
	//I kill all child processes
	for (int i = 0; i < X; i++) {
		kill(pids[i], SIGKILL);
	}
	
	printf("Total is: %d.\n\n", total);
	printf("The number of received values are: %d.\n\n", rVal);
	
	
	//I successfully terminate the program
	exit(EXIT_SUCCESS);
}

*/
