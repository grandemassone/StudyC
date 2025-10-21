/*
1.	Creates a child process with fork().
2.	The child replaces himself by executing the ls -l command using execlp.
3.	The father waits for their son to terminate with wait(), and then prints “Command terminated.”.
 */

/*

#include <utilsF.h>

int main(void)
{
	pid_t pid = fork();
	if (pid < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) {
		execlp("ls", "ls", "-l", NULL);
		
		err_sys("execlp() error: ");
	}
	wait(NULL);
		
	printf("Command finished.\n\n");
		
		
	exit(EXIT_SUCCESS);
}

*/
