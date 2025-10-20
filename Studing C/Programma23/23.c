/*
 Scrivere un programma C con il seguente comportamento: all’avvio viene creato un processo figlio che in un loop infinito genera un numero casuale 0 <= x <=9 e scrive in un file binario x.bin (nella directory corrente, se non esiste lo crea se esiste appende i dati) un intero casuale compreso tra 0 e 1000.
 Il padre, una volta al secondo, legge la directory corrente e calcola la somma degli interi contenuti in tutti i file *.bin. Se la somma è maggiore di 1.000.000 termina il processo figlio, stampa il nome del file (il cui contenuto verifica la condizione) e termina dopo aver cancellato tutti i file *.bin.
*/

#include <utilsF.h>
#include <time.h>

int main(void)
{
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("Fork error: ");
	} else if (pid == 0) {
		while (1) {
			//I initialize srand and son-in-law x for the file and casualNumber for the number to put inside
			srand((unsigned int) time(NULL) ^ getpid());
			int x = rand() % 10;
			int casualNumber = rand() % 1000;
			
			//File name retrieval via snprintf
			char nameFile[100];
			snprintf(nameFile, sizeof(nameFile), "%d.%s", x, ".bin");
			
			//I open the file
			int fdFile = open(nameFile, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (fdFile < 0) {
				err_sys("Open fdFile child, error: ");
			}
			
			//I write the random number in the file
			if (write(fdFile, &casualNumber, sizeof(int))< 0) {
				err_sys("Write in fdFile error: ");
			}
			
			//I close the file
			close(fdFile);
		}
	}
	
	//FATHER
	
	//I open the directory
	DIR* dir = opendir(".");
	if (!dir) {
		err_sys("Opendir error: ");
	}
	
	struct dirent* entry;
	char sPath[PATH_MAX];
	
	int total = 0;
	while (total <= 1000000) {
		rewinddir(dir);
		while ((entry = readdir(dir)) != NULL) {
			//Ignore "." and ".."
			if (strcmp(entry->d_name, ".") == 0 ||
				strcmp(entry->d_name, "..") == 0)
				continue;
			
			//If the file has the extension ".bin" do everything contained in the if
			if (strlen(entry->d_name) > 4 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".bin") == 0) {
				int fdFile = open(entry->d_name, O_RDONLY);
				if (fdFile < 0) {
					err_sys("Open file error: ");
				}
				
				//I read the integers from the file and insert them into the num variable, plus all a total
				int num = 0;
				ssize_t rb;
				while ((rb = read(fdFile, &num, sizeof(int))) == sizeof(int)) {
					total += num;
					if (total > 1000000) {
						strcpy(sPath, entry->d_name);
						break;
					}
				}
				
				//I close the file
				close(fdFile);
			}
		}
		//Waits a second
		sleep(1);
	}
	//I kill the son with SIGKILL
	kill(pid, SIGKILL);
	
	printf("The file that made it possible to exit the loop was: %s.\n\n", sPath);
	
	//Serves to bring the directory pointer to the beginning
	rewinddir(dir);
	
	//I read the directory to close the ".bin" files
	while ((entry = readdir(dir)) != NULL) {
		//Ignore "." and ".."
		if (strcmp(entry->d_name, ".") == 0 ||
			strcmp(entry->d_name, "..") == 0)
			continue;
		
		if (strlen(entry->d_name) > 4 && strcmp(entry->d_name + strlen(entry->d_name) - 4, ".bin") == 0) {
			unlink(entry->d_name);
		}
	}
	
	//I close the directory altogether
	closedir(dir);
	
	
	//I end successfully
	exit(EXIT_SUCCESS);
}
