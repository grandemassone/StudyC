/*
1.Define N: A number of children to create.
2.Create N children with fork().
  Every child has to do something simple, for example:
  Generate a random number and print it.
  Terminate using _exit() with a return code (e.g. 0 or the generated number).
3.Father:
  Must save children's PIDs.
  At the end, wait for all children to finish using wait() or waitpid().
  Print the PID of each terminated child and its exit code.
4.Cleaning:
  Print a final message when all children are finished.
*/

/*

#include <utilsF.h>
#include <time.h>

#define N 10

int main(void)
{
	pid_t pids[N];
	
	for (int i = 0; i < N; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			err_sys("Fork error: ");
		} else if (pid == 0) {
			//I generate a different seed depending on the pid of each child
			srand((unsigned int)time(NULL) ^ getpid());
			
			//Generate a number between 1 and 50
			int x = (rand() % 50) + 1;
			
			printf("I'm the %d° child with pid %d and the number I generated is: %d.\n\n", i + 1, getpid(), x);
			
			_exit(x);
		} else {
			pids[i] = pid;
		}
	}
	
	//Father
	int status;
	for (int i = 0; i < N; i++) {
		pid_t wpid;
		// Wait for the child process to terminate, retrying if interrupted by a signal
		do {
			wpid = waitpid(pids[i], &status, 0);
		} while (wpid == - 1 && errno == EINTR);
		if (wpid < 0) {
			err_sys("Waitpid error: ");
		}
		
		if (WIFEXITED(status)) {
			printf("#%d° Child with pid %d correctly ended with status: %d.\n\n", i + 1, wpid, WEXITSTATUS(status));
		}
	}
	
	printf("Father: All children are finished correctly.\n\n");
	
	
	//I exit successfully
	exit(EXIT_SUCCESS);
}

*/
