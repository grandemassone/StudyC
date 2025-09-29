/**
 1.Legge un percorso di directory da linea di comando.
 2.Crea un processo figlio che esplora la directory e stampa tutti i file presenti.
 3.Il processo padre può inviare il segnale:
		•SIGUSR1 → il figlio stampa “Segnale ricevuto: SIGUSR1”.
 4.Dopo aver letto tutti i file, il figlio termina con uno status che indica il numero di file trovati.
 5.Il padre aspetta il figlio con waitpid() e poi stampa il numero di file trovati.
*/

/*

#include <utilsF.h>

void handler_signal(int signum)
{
	const char* msg = "Figlio: segnale SIGUSR1 ricevuto.\n";
	write(1, msg, strlen(msg));
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		err_sys("Error number arguments:");
	}
	
	DIR* dir = opendir(argv[1]);
	if (dir == NULL) {
		err_sys("Error opendir:");
	}
	
	struct dirent* entry;
	
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("Error fork:");
	} else if (pid == 0) { //Child
		if (signal(SIGUSR1, handler_signal) == SIG_ERR) {
			err_sys("Error signal, child:");
		}
	
		int count = 0;

		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
		
			char path[PATH_MAX];
			snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
			
			struct stat fdstat;
			if (stat(path, &fdstat) < 0) {
				err_sys("Error stat, child:");
			}
			
			if (S_ISDIR(fdstat.st_mode)) {
				continue;
			} else if (S_ISREG(fdstat.st_mode)) {
				count++;
				printf("%s\n------------------------\n", path);
			} else continue;
		}
		
		closedir(dir);
		
		pause();
		
		exit(count);
	} else { //Father
		sleep(2); // Serve da sync
		
		kill(pid, SIGUSR1);
		
		sleep(2); // Serve da sync
		
		int status;
		pid_t child = waitpid(pid, &status, 0);
	
		if (WIFEXITED(status)) {
			printf("\n\nPadre: figlio con pid: %d ha terminato.\nNumero di file REG: %d.\n", child, WEXITSTATUS(status));
		} else if (child < 0) {
			err_sys("Error child, father:");
		}
		
		
		
//		Esco con successo
		exit(EXIT_SUCCESS);
	}
}

*/
