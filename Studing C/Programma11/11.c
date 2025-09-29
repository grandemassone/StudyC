/**
1.	Il programma riceve da linea di comando un percorso di directory.
2.	Il processo padre apre la directory e, per ogni sottodirectory trovata (diversa da "." e ".."), crea un figlio che si occupa 	di esplorarla ricorsivamente.
3.	Ogni processo figlio stampa a video i file regolari che trova nella directory che sta esplorando.
4.	Ogni processo termina restituendo al padre il numero di file regolari trovati nella propria directory (e sottodirectory).
5.	Il padre raccoglie i risultati con waitpid() e stampa il totale.
*/


//*************************************DISCLAIMER*************************************
/*
FUNZIONA MA SOLO CON DIRECTORY SENZA TROPPI FILE REGOLARI, PERCHÉ "EXIT"
RIESCE A RESTITUIRE NUMERI DA 0 A 255 E NON DI PIÙ, QUALORA
AVESTE DIRECTORY CON ALL'INTERNO PIÙ DI 255 FILE REGOLARI COMPARIREBBERO DEI PROBLEMI
PER RISOLVERE BISOGNA USARE LE PIPE PER TRASFERIRE COUNT INVECE DI EXIT
*/

/*

#include <utilsF.h>

int visita_dir_ric(pid_t pid, char* path)
{
	int count = 0;
	
	DIR* dir = opendir(path);
	if (dir == NULL) {
		err_sys("Error opendir, visita_dir_ric:");
	}
	
	char newpath[PATH_MAX];
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		snprintf(newpath, sizeof(newpath), "%s/%s", path, entry->d_name);
		
		struct stat fdstat;
		if (stat(newpath, &fdstat) < 0) {
			err_sys("Error stat, visita_dir_ric:");
		}
		
		if (S_ISREG(fdstat.st_mode)) {
			count++;
			printf("[Figlio pid: %d] :: %s\n-----------------\n", pid, newpath);
		} else if (S_ISDIR(fdstat.st_mode)) {
			visita_dir_ric(pid, newpath);
		} else continue;
	}
	
	closedir(dir);
	
	return count;
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		err_sys("Error number arguments:");
	}
	
	DIR* dir = opendir(argv[1]);
	if (dir == NULL) {
		err_sys("Error opendir, father:");
	}
	
	pid_t figli[1024];  // Array per salvare i pid dei figli
	int nfigli = 0;
	
	struct dirent* entry;
	
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		
		char path[PATH_MAX];
		snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
		
		struct stat fdstat;
		if (stat(path, &fdstat) < 0) {
			err_sys("Error stat, father:");
		}
		
		if (S_ISDIR(fdstat.st_mode)) {
			pid_t pid;
			if ((pid = fork()) < 0) {
				err_sys("Error fork:");
			} else if (pid == 0) {
				int count = visita_dir_ric(getpid(), path);
				exit(count);
			} else {
				figli[nfigli++] = pid;
			}
		} else continue;
	}
	
	closedir(dir);
	
	sleep(1);
	
	int totale = 0;
	int status;
	for (int i = 0; i < nfigli; i++) {
		if (waitpid(figli[i], &status, 0) > 0) {
			if (WIFEXITED(status)) {
				totale += WEXITSTATUS(status);
			}
		}
	}
	
	printf("\n\nTotale file regolari trovati dai figli: %d.\n\n", totale);
	
	
	
	exit(EXIT_SUCCESS);
}
	
*/
