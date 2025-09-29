/*
Scrivere un programma C con il seguente comportamento:
 all’avvio viene creato un processo figlio
 che in un loop infinito genera un numero casuale 0 <= x <=9
 e scrive in un file binario x.bin (nella directory corrente,
 se non esiste lo crea se esiste appende i dati) un intero casuale compreso tra 0 e 1000.
Il padre, una volta al secondo, legge la directory corrente
 e calcola la somma degli interi contenuti in tutti i file *.bin.
 Se la somma è maggiore di 1.000.000 termina il processo figlio,
 stampa il nome del file (il cui contenuto verifica la condizione)
 e termina dopo aver cancellato tutti i file *.bin.
*/

/*

#include <utilsF.h>
#include <time.h>

int main(int argc, char** argv)
{
	//Create process
	pid_t pid;
	
	if ((pid = fork()) < 0) {
		err_sys("Error fork:");
	} else if (pid == 0) { //Son
		srand((unsigned int)time(NULL));
		while (1) {
			int x = rand() % 10;
			int randomInt = rand() % 1001;
			
			char filename[128];
			snprintf(filename, sizeof(filename), "%d.bin", x);
			
			int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0) {
				err_sys("Error open file:");
			}
			
			if(write(fd, &randomInt, sizeof(int)) < 0) {
				err_sys("Error write:");
			}
			
			//Close file
			close(fd);
		}
	} else { //Dad
		while (1) {
			sleep(1);
			int total = 0;
			
			DIR* dir = opendir(argv[1]);
			if (!dir) {
				err_sys("Error opendir:");
			}
			struct dirent *entry;
			
			while ((entry = readdir(dir)) != NULL) {
				//Skip "." and ".."
				if (entry->d_name[0] == '.') continue;
				
				//Attual path
				char path[PATH_MAX];
				snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
				
				struct stat st;
				if (stat(path, &st) < 0) continue;
				if (!S_ISREG(st.st_mode)) continue;
				
				ssize_t len = strlen(entry->d_name);
				if (len < 4 || strcmp(entry->d_name + len - 4, ".bin") != 0) continue;
				
				//Open and sum the int
				int fd = open(path, O_RDONLY);
				if (fd < 0) {
					err_sys("Error open:");
				}
				int value;
				while (read(fd, &value, sizeof(int)) == sizeof(int)) {
					total += value;
				}
				close(fd);
			}
			closedir(dir);
			if (total > 1000000) {
				//Kill the son
				kill(pid, SIGKILL);
				printf("Condition met!\n");
				
				//Close the bin files
				DIR* dir2 = opendir(argv[1]);
				if (dir2 < 0) {
					err_sys("Error opendir (2):");
				}
				struct dirent* entry;
				while ((entry = readdir(dir2)) != NULL) {
					if (entry->d_name[0] == '.') continue;
					size_t len = strlen(entry->d_name);
					if (len >= 4 && strcmp(entry->d_name + len - 4, ".bin") == 0) {
						remove(entry->d_name);
					}
				}
				closedir(dir2);
				
				
				//Exit with succes
				exit(EXIT_SUCCESS);
			}
		}
	}
}

*/
