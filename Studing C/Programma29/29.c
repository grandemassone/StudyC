/*
1.	Creates a child process with fork().
2.	The child prints “Active child...” every second and continues to do so until the child receives a SIGUSR1 signal from the father.
3.	When the child receives SIGUSR1, it prints “Received signal, ending” and ends.
4.	The father, after 5 seconds, sends SIGUSR1 to his son with kill(pidSon, SIGUSR1) and waits for its termination with wait().
*/

/*
#include <utilsF.h>

void handler_signal(int signum)
{
	printf("SIGUSR1: Received signal, ending...\n");
	
	exit(EXIT_SUCCESS);
}

int main(void)
{
	pid_t pid = fork();
	if (pid < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) { //Child
		signal(SIGUSR1, handler_signal);
		
		while (1) {
			sleep(1);
			printf("Active child...\n");
		}
	}
	
	//FATHER
	sleep(5);
	
	kill(pid, SIGUSR1);
	
	wait(NULL);
	printf("\nFather: child terminated successfully.\n");
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
