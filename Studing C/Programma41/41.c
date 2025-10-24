/*
•The father creates a son.
•The child creates textX.txt files with random sentences every 2s.
•The father scrolls through the directory every 3s and counts all the words present in the .txt files.
•If the total words exceed 80, finish the child and print the file with more words.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	char* phrases[] = {
		"hello",
		"world",
		"mario has 3 dogs",
		"ole",
		"happy birthday"
	};
	
	pid_t pid = fork();
	if (pid < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) {
		srand((unsigned int)time(NULL));
		int i = 0;
		
		while (1) {
			sleep(2);
			int N = rand() % 5;
			
			char nameFile[NAME_MAX];
			snprintf(nameFile, sizeof(nameFile), "text%d.txt", i);
			
			int fdFile = open(nameFile, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fdFile < 0) {
				err_sys("open() error: ");
			}
			
			if (write(fdFile, phrases[N], strlen(phrases[N])) < 0) {
				err_sys("write() error: ");
			}

			i++;
			close(fdFile);
		}
	}
	
	DIR* dir = opendir(".");
	if (!dir) {
		err_sys("opendir() error: ");
	}
	struct dirent* entry;
	
	int total = 0;
	int max = 0;
	char nameFileMax[NAME_MAX];
	while (total < 80) {
		sleep(2);
		
		
		rewinddir(dir);
		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			
			if ((strlen(entry->d_name) > 4) && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".txt") == 0) {
				int fdFile = open(entry->d_name, O_RDONLY);
				if (fdFile < 0) {
					err_sys("open() error: ");
				}
				
				char buffer[2048];
				ssize_t rByte = read(fdFile, buffer, sizeof(buffer));
				if (rByte < 0) {
					err_sys("read() error: ");
				}
				//Adding string termination
				buffer[rByte] = '\0';
				
				int countFileMax = 0;
				int inWord = 0;
				for (int i = 0; i < rByte; i++) {
					if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n') {
						if (inWord == 1) {
							total++;
							countFileMax++;
							inWord = 0;
						}
					} else {
						inWord = 1;
					}
				}
				if (inWord == 1) {
					total++;
					countFileMax++;
				}
				
				if (countFileMax > max) {
					max = countFileMax;
					strcpy(nameFileMax, entry->d_name);
				}
				max = countFileMax;
				
				printf("[Father]: Progression: %d.\n", total);
				
				unlink(entry->d_name);
			}
		}
	}
	
	if (kill(pid, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}
	
	wait(NULL);

	printf("\nThe total is: %d.\n", total);
	printf("The file with most words is: %s.\n\n", nameFileMax);
	
	//I close the dir
	closedir(dir);
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
