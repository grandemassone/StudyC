/*
•The father reads from command line N.
•Create N children, each with a dedicated pipe.
•Each child generates numbers 1–100 and sends them to the father every 0.3 sec.
•The father reads cyclically from all pipes and calculates the total sum.
•When it exceeds 2000, it finishes all the children and prints the final sum.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(int argc, char** argv)
{
	if (argc != 2) {
		err_sys("Number of arguments passed by command line, incorrect: ");
	}
	
	//I make the number passed as a command line string an integer
	int N = atoi(argv[1]);
	
	int fdPipe[N][2];
	for (int i = 0; i < N; i++) {
		if (pipe(fdPipe[i]) < 0) {
			err_sys("pipe() error: ");
		}
	}
	
	int pids[N];
	
	for (int i = 0; i < N; i++) {
		pid_t pid = fork();
		srand((unsigned int)time(NULL) ^ getpid());
		if (pid < 0) {
			err_sys("fork() error: ");
		} else if (pid == 0) {
			close(fdPipe[i][READ]);
			while (1) {
//				usleep(500000);
				sleep(1);
				int N = (rand() % 100) + 1;
				
				if (write(fdPipe[i][WRITE], &N, sizeof(int)) < 0) {
					err_sys("write() error: ");
				}
			}
		} else {
			pids[i] = pid;
		}
	}

	for (int i = 0; i < N; i++) {
		close(fdPipe[i][WRITE]);
	}
	
	int total = 0;
	while (total < 2000) {
		for (int i = 0; i < N; i++) {
			int temp = 0;
			ssize_t rByte = read(fdPipe[i][READ], &temp, sizeof(int));
			if (rByte < 0) {
				err_sys("read() error: ");
			}
			
			total += temp;
			printf("[FATHER]: Progression: %d.\n", total);
		}
	}
	
	for (int i = 0; i < N; i++) {
		kill(pids[i], SIGKILL);
	}
	
	for (int i = 0; i < N; i++) {
		wait(NULL);
	}
	
	printf("[FATHER]: The total is: %d.\n\n", total);
	
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
