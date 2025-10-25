/*
•The father creates N children and reads N from the command line.
•Each child generates a random number between 0 and 200 every 0.5 s and writes it to a childX.bin binary file.
•The father, every second, reads all the .bin files and calculates the total sum.
•When the sum exceeds 5000, it terminates all children, prints which file wrote the largest number, and deletes the.bins.
*/

#include <utilsF.h>
#include <time.h>

int main(int argc, char** argv)
{
	if (argc != 2) {
		err_sys("Incorrect number of arguments passed from the command line: ");
	}
	
	//Recovering the number of children to be generated from the command line
	int N = atoi(argv[1]);
	
	pid_t pids[N];
	
	for (int i = 0; i < N; i++) {
		pid_t pid = fork();
		srand((unsigned int)time(NULL) ^ getpid());
		int y = 0;
		if (pid < 0) {
			err_sys("fork() error: ");
		} else if (pid == 0) {
			while (1) {
                usleep(500000);
				char nameFile[NAME_MAX];
				snprintf(nameFile, sizeof(nameFile), "child%d.bin", y);
				
				int fdFile = open(nameFile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				if (fdFile < 0) {
					err_sys("open() error: ");
				}
				
				int x = rand() % 200;
				if (write(fdFile, &x, sizeof(int)) < 0) {
					err_sys("write() error: ");
				}
				
				close(fdFile);
				y++;
                if (y > 1000) {
                    err_sys("NUMBER OF FILES THAT ARE TOO HIGH: ");
                }
			}
		} else {
			pids[i] = pid;
		}
	}
	
	//FATHER
	
	DIR* dir = opendir(".");
	if (!dir) {
		err_sys("opendir() error: ");
	}
	
	struct dirent* entry;
	
	int total = 0;
    int max = 0;
	char nameFileMax[NAME_MAX];
	while (total < 5000) {
		sleep(1);
		for (int i = 0; i < N; i++) {
			
			//Ricomincio da capo
			rewinddir(dir);
			while ((entry = readdir(dir)) != NULL) {
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
					continue;
				
				//If it is a binary file
				if (strlen(entry->d_name) > 4 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".bin") == 0) {
					int temp;
					int fdFile = open(entry->d_name, O_RDONLY);
					if (fdFile < 0) {
						err_sys("open() error: ");
					}
					
					ssize_t rByte = read(fdFile, &temp, sizeof(int));
					if (rByte < 0) {
						err_sys("read() error: ");
					}
					
					total += temp;
					
					if (max < temp) {
						max = temp;
						strcpy(nameFileMax, entry->d_name);
					}
					
					printf("[FATHER]: Sommma attuale: %d.\n", total);
					
					close(fdFile);
                    unlink(entry->d_name);
				}
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		if (kill(pids[i], SIGKILL) < 0) {
			err_sys("kill() error: ");
		}
	}
	
	for (int i = 0; i < N; i++) {
		wait(NULL);
	}
	
	closedir(dir);
	
	printf("\n[FATHER]: Total is: %d.\n", total);
	printf("[FATHER]: The file that generated the largest number was: %s.\n\n", nameFileMax);
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}
