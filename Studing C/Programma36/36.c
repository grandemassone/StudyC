/*
•The father creates a son.
•The child generates 1–100 numbers and writes them to a binary data.bin file every 0.5 sec.
•The father, every second, reads the file and calculates the sum.
•When the sum exceeds 1000:
•finish son,
•print sum,
•delete data.bin.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("fork() error: ");
	} else if(pid == 0) {
		srand((unsigned int)time(NULL) ^ getpid());
		
		int fdFile = open("data.bin", O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fdFile < 0) {
			err_sys("open() fdFile error: ");
		}
		
		while (1) {
			usleep(500000);
			int N = (rand() % 100) + 1;
			
			if (write(fdFile, &N, sizeof(int)) < 0) {
				err_sys("write() error: ");
			}
		}
	}
	
	//FATHER
	
	int total = 0;
	off_t offset = 0;
	while (total < 1000) {
		sleep(1);
		
		int fdFile = open("data.bin", O_RDONLY);
		if (fdFile < 0) {
			err_sys("open() error: ");
		}
		
		if (lseek(fdFile, offset, SEEK_SET) < 0) {
			err_sys("lseek() error: ");
		}
		
		int temp = 0;
		ssize_t rByte;
		//Read until an int returns
		while ((rByte = read(fdFile, &temp, sizeof(int))) == sizeof(int)) {
			total += temp;
			offset += sizeof(int);
		}
		
		printf("[FATHER]: Progession %d.\n", total);
		
		close(fdFile);
	}
	
	if (kill(pid, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}
	
	//I delete the file
	unlink("data.bin");
	
	printf("The total is: %d.\n\n", total);
	
	exit(EXIT_SUCCESS);
}

*/
