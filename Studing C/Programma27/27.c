/*
 1.The father creates a child process.
 2.The child generates random numbers from 1 to 1000 every second and writes them to separate binary files in the current directory, with names numX.bin where X is a sequence number (0,1,2,...).
 3.The father, every 2 seconds, opens the current directory (opendir(“.”)), reads all .bin files (readdir and entry->d_name), and calculates the sum of all the numbers contained in all .bin files.
 4.When the total sum exceeds 5000, the father:
  ends son (kill(pid, SIGKILL)),
  prints out the name of the file that allowed the threshold to be crossed,
  deletes all .bin files of the directory (unlink(entry->d_name)),
  end the program.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	pid_t pid = fork();
	if (pid < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) {
		srand((unsigned int)time(NULL));
		int i = 0;
		while (1) {
			//Waits a second
			sleep(1);
			
			int X = (rand() % 1000) + 1;
			
			//Recovering the file name
			char nomeFile[30];
			snprintf(nomeFile, sizeof(nomeFile), "num%d.bin", i);
			
			//I open the file
			int fdFile = open(nomeFile, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (fdFile < 0) {
				err_sys("open() error: ");
			}
			
			//I write the random number in the file
			if (write(fdFile, &X, sizeof(int)) < 0) {
				err_sys("write() error: ");
			}
			
			//I close the current file
			close(fdFile);
			
			//I increase the counter to name the different files
			i++;
		}
	}
	
	//FATHER
	DIR* dir = opendir(".");
	if (!dir) {
		err_sys("opendir() error: ");
	}
	
	struct dirent* entry;
	int total = 0;
	char nameFFile[NAME_MAX] = "";
	
	while (total <= 5000) {
		//Set from where to read the directory, the beginning
		rewinddir(dir);
		
		//Wait 2 seconds
		sleep(2);
		
		while ((entry = readdir(dir)) != NULL) {
			//We ignore "." and ".."
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
				continue;
			
			//If the file is binary
			if (strlen(entry->d_name) > 4 &&
				strcmp(entry->d_name +
				strlen(entry->d_name) - 4, ".bin") == 0) {
				
				//I open the file
				int fdFileBin = open(entry->d_name, O_RDONLY);
				if (fdFileBin < 0) {
					err_sys("open fdFileBin, error: ");
				}
				
				//I read the file and enter the number inside temp
				int temp;
				ssize_t rByte = read(fdFileBin, &temp, sizeof(int));
				if (rByte < 0) {
					err_sys("read fdFileBin, error: ");
				}
				
				//Summit temp to total
				total += temp;
				
				if (total >= 5000) {
					strcpy(nameFFile, entry->d_name);
				}
				
				close(fdFileBin);
				unlink(entry->d_name);
			}
		}
	}
	
	printf("Total is: %d.\n\n", total);
	printf("The file that crossed the threshold was: %s.\n\n", nameFFile);
	
	if (kill(pid, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}
	
	//I'll close the dir
	closedir(dir);
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
