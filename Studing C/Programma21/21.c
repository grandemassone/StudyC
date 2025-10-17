/*
 1.Processes
	•Upon startup the program creates 2 children:
	•Son A: Generates random numbers from 1 to 500 and writes them to test9.bin (append).
	•Son B: Generates random numbers from 500 to 1000 and writes them to test10.bin (append).
	•Both children spin in an infinite loop and write a number every 0.5 seconds.
 2.Parent process
	• Every second reads all *.bin files in the directory.
	• Calculate:
	• Total sum of the numbers of all files.
	• Separate sum of test9.bin and test10.bin files.
	• If the total sum exceeds 50,000:
	• Terminate both sons (kill()).
	• Printing:
		Total: <total sum>
		Sum A.bin: <sum A>
		Sum B.bin: <sum B>
	• Delete all .bin files (unlink()).
	• End the program.
*/


#include <utilsF.h>
#include <time.h>

int main(void)
{
	int fdFile1 = open("test9.bin", O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fdFile1 < 0) {
		err_sys("Open fdFile1 error: ");
	}
	int fdFile2 = open("test10.bin", O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fdFile2 < 0) {
		err_sys("Open fdFile2 error: ");
	}
	
	srand((unsigned int)time(NULL));
	
	pid_t pid1, pid2;
	pid_t pids[2];
		
	//First child
	if ((pid1 = fork()) < 0) {
		err_sys("Fork pid1 error: ");
	} else if (pid1 == 0) {
		while (1) {
			int x1 = (rand() % 500) + 1; //Random number 1 to 500
			
			if(write(fdFile1, &x1, sizeof(int)) < 0) {
				err_sys("Write pid1 error: ");
			}
			
			usleep(500000);
		}
	} else {
		pids[0] = pid1; //Let's save the pid to position 0 of the array
	}
	
	//Second child
	if ((pid2 = fork()) < 0) {
		err_sys("Fork pid2 error: ");
	} else if (pid2 == 0) {
		while (1) {
			int x2 = (rand() % (1000 - 500 + 1)) + 500; //Random number 500 to 1000
			
			if (write(fdFile2, &x2, sizeof(int)) < 0) {
				err_sys("Write pid2 error: ");
			}
			
			usleep(500000);
		}
	} else {
		pids[1] = pid2; //Let's save the pid to position 1 of the array
	}
	//FATHER
	
	while (1) {
		int numFile1, numFile2;
		int sumFile1 = 0, sumFile2 = 0;
		ssize_t bytesRead;
		
		//Go back to the beginning of the file
		lseek(fdFile1, 0, SEEK_SET);
		lseek(fdFile2, 0, SEEK_SET);
		
		//I read and add all the numbers within the two files, and then add them together
		while ((bytesRead = read(fdFile1, &numFile1, sizeof(int))) == sizeof(int)) {
			sumFile1 += numFile1;
		}
		if (bytesRead < 0) {
			err_sys("Read fdFile1 error: ");
		}
		while ((bytesRead = read(fdFile2, &numFile2, sizeof(int))) == sizeof(int)) {
			sumFile2 += numFile2;
		}
		if (bytesRead < 0) {
			err_sys("Read fdFile2 error: ");
		}
		
		int totalSum = sumFile1 + sumFile2;
		
		if (totalSum >= 50000) {
			kill(pids[0], SIGKILL);
			kill(pids[1], SIGKILL);
			
			//I'm waiting for all the children
			waitpid(pids[0], NULL, 0);
			waitpid(pids[1], NULL, 0);
			
			//Print the results
			printf("Total: %d.\n\n", totalSum);
			printf("Result test9.bin: %d.\n\n", sumFile1);
			printf("Result test10.bin: %d.\n\n", sumFile2);
			
			
			//Close & Clear
			close(fdFile1);
			close(fdFile2);
			unlink("test9.bin");
			unlink("test10.bin");
			
			break; //Exit loop
		}
		
		//Hang on a second
		sleep(1);
	}
}
