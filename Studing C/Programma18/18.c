/*
1.	Create a pipe between parent and child.
2.	Fork a child process.
3.	Parent:
	 •	Reads a line of text from stdin (stop or somenthing else).
	 •	Writes it to the pipe.
	 •	If the message contains “stop”, sends SIGUSR1 to the child.
4.	Child:
	 •	Reads the message from the pipe.
	 •	Prints the message.
	 •	Handles SIGUSR1 prints: Received SIGUSR1, terminating early, then exits with status 99.
5.	Parent:
	•	Waits for the child with waitpid().
	•	Prints the child’s exit status.
*/

/*

#include <utilsF.h>

void handler_signal(int signum)
{
	printf("Received SIGUSR1, terminating early.\n\n");
	
	exit(99);
}

int main(void)
{
	int fdpipe[2];
	if (pipe(fdpipe) < 0) {
		err_sys("Error pipe: ");
	}
	
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("Error fork: ");
	} else if (pid == 0) { //Child
		close(fdpipe[WRITE]);
		signal(SIGUSR1, handler_signal);
		
		char buffer[201];
		ssize_t r_byte = read(fdpipe[READ], buffer, sizeof(buffer));
		if (r_byte < 0) {
			err_sys("Error read pipe, child: ");
		}
		
		printf("[CHILD] Message: %s.\n", buffer);
		
		exit(21);
	} else { //Parent
		close(fdpipe[READ]);
		
		char msg[] = {"Insert \"stop\" or somenthing else (maximum 200 character spaces included: "};
		if (write(1, msg, strlen(msg)) < 0) {
			err_sys("Error write, parent: ");
		}
		
		char buffer[201];
		ssize_t r_byte = read(0, buffer, sizeof(buffer));
		if (r_byte < 0) {
			err_sys("Error read: ");
		}
		
		//Comparison with "stop\n" and not with "stop" because
		//in the buffer there is "stop\n" and not just "stop"
		if (strcmp(buffer, "stop\n") == 0) {
			kill(pid, SIGUSR1);
		}
		
		if (write(fdpipe[WRITE], buffer, r_byte) < 0) {
			err_sys("Error write in pipe, parent: ");
		}
		
		close(fdpipe[WRITE]);
		
		int status;
		pid_t w_pid;
		
		do {
			w_pid = waitpid(pid, &status, 0);
		} while (w_pid <= 0 && errno == EINTR);
		
		if (WIFEXITED(status)) {
			printf("Child exit with success: %d.\n", WEXITSTATUS(status));
		} else {
			printf("Child terminated abnormally!\n\n");
		}
	}
	
	
	//Exit with success
	exit(EXIT_SUCCESS);
}

*/
