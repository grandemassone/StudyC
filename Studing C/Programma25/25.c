/*
•The father creates a son
•The child generates random numbers from 0 to 200 every 0.5 seconds and writes them to test9.bin binary files (append).
•The father, every 0.5 seconds, reads the file and calculates the maximum number generated so far.
•If the maximum exceeds 150, the father finishes the child, prints the maximum and deletes the file.
*/

/*
 
#include <utilsF.h>
#include <time.h>

int main(void)
{
	int fdFile = open("test9.bin", O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fdFile < 0) {
		err_sys("open() fdFile, error: ");
	}
	
	pid_t pid = fork();
	if (pid < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) {
		srand((unsigned int) time(NULL));
		
		while (1) {
			//Pause of 0.5 second
			usleep(500000);
			
			//I generate a random number between 0 and 200
			int x = rand() % 201;
			
			if (write(fdFile, &x, sizeof(int)) < 0) {
				err_sys("write() fdFile, error: ");
			}
		}
	}
	
	//FATHER
	int max = 0;
	
	while (max <= 150) {
		//Father waits 0.5 second
		usleep(500000);
		
		ssize_t rByte = read(fdFile, &max, sizeof(int));
		if (rByte < 0) {
			err_sys("read() fdFile, error: ");
		}
	}
	
	close(fdFile);
	unlink("test9.bin");
	
	//Sending the SIGKILL signal to the child
	if (kill(pid, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}
	
	printf("The largest number generated is: %d.\n\n", max);
	
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
