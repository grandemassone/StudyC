/*
1.Apre una directory passata come argomento (argv[1]).
2.Il figlio conta i file regolari (DT_REG) al suo interno.
3.Gestione segnali:
	 •Quando riceve SIGUSR1 → stampa a video il conteggio parziale dei file trovati fino a quel momento.
4.Alla fine del conteggio, crea un file test7.txt e scrive dentro:
				Numero totale di file trovati: X
*/

/*

#include <utilsF.h>

volatile sig_atomic_t countFileS = 0;

void handler_signal(int sig)
{
	if (sig != SIGUSR1) {
		err_sys("Error signal:");
	}
	
	printf("Siamo nel segnale SIGUSR1, il numero di file conteggiati è: %d.\n", countFileS);
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		err_sys("Error number arguments argc:");
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
		signal(SIGUSR1, handler_signal);
		
		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			
			char path[PATH_MAX];
			snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
			
			struct stat fdstat;
			if (stat(path, &fdstat) < 0) {
				err_sys("Error stat, child:");
			}
			
			if (S_ISREG(fdstat.st_mode)) {
				countFileS++;
			}else continue;
		}
		
		sleep(3);
		
		exit(countFileS); //Max 255 file
	} else { //Father
		sleep(2);
		kill(pid, SIGUSR1);
		
		int status;
		pid_t figlio_atteso = waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			printf("Padre: il figlio con pid %d che ha terminato con status: %d.\n", figlio_atteso, WEXITSTATUS(status));
		}
		
		int fdfile = open("test7.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fdfile < 0) {
			err_sys("Error open file, father:");
		}
		
		int saved_stdout = dup(1);
		
		if (dup2(fdfile, 1) < 0) {
			err_sys("Error dup2, father:");
		}
		
		printf("Numero totale di file trovati: %d.\n", WEXITSTATUS(status));
		
		if (dup2(saved_stdout, 1) < 0) {
			err_sys("Error dup2, father:");
		}
		
		closedir(dir);
		close(fdfile);
		
		
		exit(EXIT_SUCCESS);
	}
}

*/
