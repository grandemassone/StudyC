/*
•The father creates 2 children.
•Each child generates random numbers 0–500 every 0.5s and writes them to separate binary files (childX_Y.bin).
• Every second the father reads all the files and calculates the total sum.
•When the total sum exceeds 2000: terminates the children, prints the name of the file that contributed the most and deletes all the files.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	pid_t pid1, pid2;
	
	if ((pid1 = fork()) < 0) {
		err_sys("fork() 1 error: ");
	} else if (pid1 == 0) {
		srand((unsigned int)time(NULL) ^ getpid());
		while (1) {
			usleep(500000);
			int N = rand() % 500;
			
			int fdFile = open("figlio1.bin", O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fdFile < 0) {
				err_sys("open() error: ");
			}
			
			if (write(fdFile, &N, sizeof(int)) < 0) {
				err_sys("write() 1 error: ");
			}
			
			close(fdFile);
		}
	}
	
	if ((pid2 = fork()) < 0) {
		err_sys("fork() 2 error: ");
	} else if (pid2 == 0) {
		srand((unsigned int)time(NULL) ^ getpid());
		while (1) {
			usleep(500000);
			int N = rand() % 500;
			
			int fdFile = open("figlio2.bin", O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fdFile < 0) {
				err_sys("open() error: ");
			}
			
			if (write(fdFile, &N, sizeof(int)) < 0) {
				err_sys("write() 2 error: ");
			}
			
			close(fdFile);
		}
	}
	
	//FATHER
	int total1 = 0;
	int total2 = 0;
	while (total1 + total2 < 2000) {
		sleep(1);
		
		//Reset of the two totals to reread everything from 0
		total1 = 0;
		total2 = 0;
		
		int fdFile1 = open("figlio1.bin", O_RDONLY);
		if (fdFile1 < 0) {
			err_sys("open() error");
		}
		
		int temp;
		ssize_t rByte;
		//Read until you find something smaller than sizeof(int)
		while ((rByte = read(fdFile1, &temp, sizeof(int))) == sizeof(int)) {
			total1 += temp;
		}
		if (rByte < 0) {
			err_sys("read() error");
		}
		close(fdFile1);
		
		int fdFile2 = open("figlio2.bin", O_RDONLY);
		if (fdFile2 < 0) {
			err_sys("open() error");
		}
		
		//Read until you find something smaller than sizeof(int)
		while ((rByte = read(fdFile2, &temp, sizeof(int))) == sizeof(int)) {
			total2 += temp;
		}
		if (rByte < 0) {
			err_sys("read() error");
		}
		close(fdFile2);

		printf("[FATHER]: Current total = %d\n", total1 + total2);
	}
	
	//I kill both sons
	kill(pid1, SIGKILL);
	kill(pid2, SIGKILL);
	
	
	printf("[FATHER]: The total is: %d.\n", total1 + total2);
	if (total1 > total2) {
		printf("[FATHER]: The file that contributed the most was figlio1.bin.\n\n");
	} else if (total1 == total2) {
		printf("[FATHER]: Both files contributed in the same way.\n\n");
	} else {
		printf("[FATHER]: The file that contributed the most was figlio2.bin.\n\n");
	}
	
	//Delete both files
	unlink("figlio1.bin");
	unlink("figlio2.bin");
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
