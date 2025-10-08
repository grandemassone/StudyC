/*
 1. Create a pipe.
 2. The parent process:
	•	reads a line of text from stdin (max 200 characters);
	•	writes it in the pipe;
	•	he waits for his son to finish.
 3. The child process:
	•	reads the string from the pipe;
	•	count how many words it contains (words are separated by spaces);
	•	print the number of words found on the screen.
*/

/*
#include <utilsF.h>

int main(void)
{
	int fdpipe[2];
	if (pipe(fdpipe) < 0) {
		err_sys("Error pipe: ");
	}
	
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("Error fork: ");
	} else if (pid == 0) { //Son
		close(fdpipe[WRITE]);
		
		char buffer[200];
		ssize_t r_byte = read(fdpipe[READ], buffer, sizeof(buffer));
		if (r_byte < 0) {
			err_sys("Error read pipe, son: ");
		}
		
		int words = 0;
		int in_word = 0;
		for (int i = 0; i < r_byte; i++) {
			if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n') {
				if (!in_word) {
					words++;
					in_word = 1; //In the word
				}
			} else {
				in_word = 0; //End of the word
			}
		}
		
		printf("Number of words: %d.\n", words);
		fflush(stdout);
		
		//Exit with status
		exit(21);
	} else { //Father
		close(fdpipe[READ]);
		
		char msg[] = {"Hello, insert your message (max 200 characters): "};
		write(1, msg, strlen(msg));
		
		char buffer[200];
		ssize_t r_byte = read(0, buffer, sizeof(buffer));
		if (r_byte < 0) {
			err_sys("Error read: ");
		}
		
		if (write(fdpipe[WRITE], buffer, r_byte) < 0) {
			err_sys("Error write pipe, father: ");
		}
		
		close(fdpipe[WRITE]);
		
		//Wait the son
		int status;
		pid_t wait_pid;
		
		//Retry waitpid() if it is interrupted by a signal (errno == EINTR),
		//ensuring the parent properly waits for the child to terminate.
		do {
			wait_pid = waitpid(pid, &status, 0);
		} while (wait_pid < 0 && errno == EINTR);

		if (wait_pid < 0) {
			err_sys("Error waitpid: ");
		}

		if (WIFEXITED(status)) {
			printf("Child terminated with status: %d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("Child terminated due to signal %d\n", WTERMSIG(status));
		} else {
			printf("Child terminated abnormally.\n");
		}
	}
	
	
	//Exit with success
	exit(EXIT_SUCCESS);
}

*/
