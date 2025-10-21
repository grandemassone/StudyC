/*
1.The father creates a child process.
2.The child, every 2 seconds, generates a text file named X.txt (with progressive X: 0, 1, 2, ...) and writes a random sentence to it from a list of predefined sentences (eg. “Hello world”, “Operating systems are interesting”, “Fork and pipe”...).
3.The father, every 3 seconds:
	•opens the current directory with opendir(“.”),
	•scroll through all .txt files using readdir() and entry->d_name,
	•opens each file and reads its contents with read(),
	•count how many total words (space separated or newline) are present in all .txt files.
4.When the total number of words exceeds 50, the father:
	•end son (kill(pid, SIGKILL)),
	•prints the name of the last file read that made it past the threshold,
	•delete all .txt files (unlink(entry->d_name)),
	•terminate program.
*/

/*
 
#include <utilsF.h>
#include <time.h>

int main(void)
{
	pid_t pid = fork();
	char nameLastFile[NAME_MAX];
	
	//Char pointer arrays
	char *stringsM[] = {
		"Hello  world!",
		"Operating systems are interesting!",
		"Fork and pipe!"
	};
	
	if (pid < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) {
		srand((unsigned int)time(NULL));
		int X = 0;
		int casualNumber;
		while (1) {
			//Always waiting two seconds
			sleep(2);
			
			//I generate a random number between 0 and 2, to choose a phrase at random
			casualNumber = (rand() % 3);
			
			//I create each file name: X.txt
			char nameFile[NAME_MAX];
			snprintf(nameFile, sizeof(nameFile), "%d.txt", X);
			
			int fdFile = open(nameFile, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fdFile < 0) {
				err_sys("open() error: ");
			}
			
			//I write a random sentence in the file
			if (write(fdFile, stringsM[casualNumber], strlen(stringsM[casualNumber])) < 0) {
				err_sys("write() fdFile, error: ");
			}
			
			//I close the file
			close(fdFile);
			
			//Increment X at the end of each iteration
			X++;
		}
	}
	
	//FATHER
	int totalWords = 0;
	while (totalWords < 50) {
		//Waits 3 seconds at each iteration
		sleep(3);
		
		DIR* dir = opendir(".");
		if (!dir) {
			err_sys("opendir() error: ");
		}
		
		struct dirent* entry;
		while ((entry = readdir(dir)) != NULL) {
			//Ignoro "." e ".."
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
				continue;
			
			//If it is, then it is a.txt
			if (strlen(entry->d_name) > 4 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".txt") == 0) {
				int fdFile = open(entry->d_name, O_RDONLY);
				if (fdFile < 0) {
					err_sys("open() error: ");
				}
				
				//I read everything there is from the file
				char buffer[256];
				ssize_t rByte;
				rByte = read(fdFile, buffer, sizeof(buffer));
				if (rByte < 0) {
					err_sys("read() error: ");
				}
				
				//Basic algorithm for counting words
				int inWord = 0;
				for (int i = 0; i < rByte; i++) {
					if (buffer[i] != '\n' && buffer[i] != ' ' && buffer[i] != '\t') {
						//We're in a word
						inWord = 1;
					} else {
						if (inWord == 1) {
							totalWords++;
							inWord = 0;
						}
						
					}
				}
				//This is needed in case the file ends with a word and not with a separator of any kind
				if (inWord == 1) {
					totalWords++;
				}
				
				if (totalWords > 50) {
					strcpy(nameLastFile, entry->d_name);
				}
				
				//I close the file I just read from
				close(fdFile);
			}
		}
		
		//Close dir
		closedir(dir);
	}
	
	//I kill the son with SIGKILL
	kill(pid, SIGKILL);
	
	printf("The filename that got us past 50 words is: %s.\n\n", nameLastFile);
	
	wait(NULL);
	
	//I read the directory and delete the .txt files from inside
	DIR* dir = opendir(".");
	if (!dir) {
		err_sys("opendir() error: ");
	}
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL) {
		//Ignoro "." e ".."
		if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
			continue;
		
		//If it is, then it is a.txt
		if (strlen(entry->d_name) > 4 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".txt") == 0) {
			unlink(entry->d_name);
		}
	}
	
	//Close directory
	closedir(dir);
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
