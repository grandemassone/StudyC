/*
•The father creates a son.
•The son writes random sentences into.txt sentences every second.
•The father, every 3 sec, reads the file and counts the total words.
•When the total exceeds 50 words, finish the child and print the total number.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	char *phrases[] = {
		"hello ",
		"sun ",
		"antonio has short feet ",
		"michele doesn't have shoes at home ",
		"the moon is red "
	};
	
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) {
		srand((unsigned int) time(NULL) ^ getpid());
		
		int fdFile = open("phrases.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fdFile < 0) {
			err_sys("open() fdFile child, error: ");
		}
		
		while (1) {
			sleep(1);
			int N = rand() % 5;
			
			if (write(fdFile, phrases[N], strlen(phrases[N])) < 0) {
				err_sys("write() error: ");
			}
		}
	}
	
	//FATHER
	
	int total = 0;
	int inWord = 0;
	while (total < 50) {
		sleep(3);
		
		int fdFile = open("phrases.txt", O_RDONLY);
		if (fdFile < 0) {
			err_sys("open() fdFile father, error: ");
		}
		
		char buffer[2048];
		ssize_t rByte = read(fdFile, buffer, sizeof(buffer));
		if (rByte < 0) {
			err_sys("read() error: ");
		}
		
		for (int i = 0; i < rByte; i++) {
			if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n') {
				if (inWord == 1) {
					total++;
					inWord = 0;
				}
			} else {
				inWord = 1;
			}
		}
		//I count the last word
		if (inWord == 1) {
			total++;
		}
		
		close(fdFile);
	}
	
	if (kill(pid, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}
	int status;
	wait(&status);
	
	printf("[FATHER]: The child process ended with status: %d.\n", WEXITSTATUS(status));
	
	printf("[FATHER]: The total number of words read is greater than 50: %d.\n\n", total);

	unlink("phrases.txt");
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
