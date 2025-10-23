/*
•Il padre crea un figlio.
•Il figlio genera file numX.bin (X va da 0 a X in maniera crescente) con numeri casuali da 1–100 ogni secondo.
•Il padre, ogni 2 s, legge la directory e calcola la somma di tutti i .bin cancellandoli mano a mano.
•Quando la somma supera 1500 termina il figlio.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
	pid_t pid = fork();
	int i = 0;
	if (pid < 0) {
		err_sys("fork() error: ");
	} else if (pid == 0) {
		srand((unsigned int)time(NULL));
		while (1) {
			sleep(1);
			
			int X = (rand() % 500) + 1;
			
			char nameFile[NAME_MAX];
			snprintf(nameFile, sizeof(nameFile), "num%d.bin", i);
			
			int fdFile = open(nameFile, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (fdFile < 0) {
				err_sys("open() error: ");
			}
			
			if (write(fdFile, &X, sizeof(int)) < 0) {
				err_sys("write() error: ");
			}
			
			close(fdFile);
			
			i++;
		}
	}
	
	//I open the dir
	DIR* dir = opendir(".");
	if (!dir) {
		err_sys("opendir() error: ");
	}
	
	struct dirent *entry;
	int total = 0;
	while (total < 1500) {
		//I wait 2 seconds
		sleep(2);
		
		//Ripartiamo dall'inizio
		rewinddir(dir);
		while ((entry = readdir(dir)) != NULL) {
			//I ignore "." and ".."
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			
			//I only open “.bin” files and add their contents to the total
			if ((strlen(entry->d_name) > 4) && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".bin") == 0) {
				int fdFile = open(entry->d_name, O_RDONLY);
				if (fdFile < 0) {
					err_sys("open() error: ");
				}
				
				int temp = 0;
				ssize_t rByte;
				while((rByte = read(fdFile, &temp, sizeof(int))) == sizeof(int)) {
					total += temp;
				}
				if (rByte < 0) {
					err_sys("read() error: ");
				}
				
				close(fdFile);
				unlink(entry->d_name);
			}
			printf("[FATHER]: Progression: %d.\n", total);
		}
	}
	
	//I kill the son
	if (kill(pid, SIGKILL) < 0) {
		err_sys("kill() error: ");
	}

	//I collect the son
	wait(NULL);
	
	//Close the directory
	closedir(dir);
	
	printf("[FATHER]: The total is: %d\n\n", total);
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
