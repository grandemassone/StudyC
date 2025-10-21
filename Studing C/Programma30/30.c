/*
1.The parent process creates 3 child processes.
2.Each child performs an infinite loop in which:
	• it prints its own PID and a message such as “Son I active...” every second;
	• it remains active until it receives a signal.
3.The father waits 5 seconds, then:
	•send SIGUSR1 to first child → child prints "Received SIGUSR1, end softly" and ends with exit(0);
	•send SIGUSR2 to the second child → he also ends with a different message (e.g. "Received SIGUSR2, goodbye!");
	•send SIGKILL to the third child → this is terminated abruptly (without being able to handle the signal).
4.Finally, the father waits for the termination of all the children (wait() or waitpid()) and prints a summary message: All the children are terminated.
*/

/*
 
#include <utilsF.h>

//Handler for the first child
void handler_signal1(int signum)
{
	printf("Received SIGUSR1, end softly.\n\n");
	
	exit(EXIT_SUCCESS);
}

//Handler for the second child
void handler_signal2(int signum)
{
	printf("Received SIGUSR2, goodbye!\n\n");
	
	exit(EXIT_SUCCESS);
}

int main(void)
{
	pid_t pids[3];
	
	for (int i = 0; i < 3; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			printf("i° fork() error");
			err_sys(": ");
		} else if (pid == 0) {
			signal(SIGUSR1, handler_signal1);
			signal(SIGUSR2, handler_signal2);
			while (1) {
				sleep(1);
				printf("%d° son I active... (PID=%d)\n", i, getpid());
			}
		} else {
			pids[i] = pid;
		}
	}
	
	//FATHER
	sleep(5);
	
	//First process
	if (kill(pids[0], SIGUSR1) < 0) {
		err_sys("kill() 1 error: ");
	}
	
	//Second process
	if (kill(pids[1], SIGUSR2) < 0) {
		err_sys("kill() 2 error: ");
	}
	
	//Terzo process
	if (kill(pids[2], SIGKILL) < 0) {
		err_sys("kill() 3 error: ");
	} else {
		printf("SIGKILL was successful.\n\n");
	}
	
	for (int i = 0; i < 3; i++) {
		wait(NULL);
	}
	
	printf("Father: all childs are terminated!!!\n\n");
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
