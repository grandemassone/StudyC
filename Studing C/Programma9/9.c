/*
 Processi, file e pipe
 1. Processo figlio1 recupera da linea di comando i numeri e li scrive nella pipe
 2. Processo figlio2 recupera i numeri dalla pipe e li scrive in un file, riga per riga
 3. Processo padre attende i processi figli e stampa il loro status di uscita
 4. Processo padre recupera i numeri dal file e li moltiplica, dopo di che stampa in output
*/

/*

#include <utilsF.h>

int main(int argc, char** argv)
{
	if (argc != 3) {
		err_sys("Error, number arguments:");
	}
	int fdpipe[2];
	if (pipe(fdpipe) < 0) {
		err_sys("Error pipe:");
	}
	
	pid_t pid1, pid2;
	
	if ((pid1 = fork()) < 0) {
		err_sys("Error fork, pid1:");
	} else if (pid1 == 0) { // Figlio pid1
		close(fdpipe[READ]);
		
		int msg[] = {atoi(argv[1]), atoi(argv[2])};
		ssize_t len = sizeof(msg);

		// Scrivo la lunghezza nell'intestazione
		if (write(fdpipe[WRITE], &len, sizeof(len)) < 0) {
			err_sys("Error write len, pid1:");
		}
		if (write(fdpipe[WRITE], msg, sizeof(msg)) < 0) {
			err_sys("Error write, pid1:");
		}
		close(fdpipe[WRITE]);
		
		exit(2);
	}
	
	if ((pid2 = fork()) < 0) {
		err_sys("Error fork, pid2:");
	} else if (pid2 == 0) { // Figlio pid2
		close(fdpipe[WRITE]);
		
		int file = open("test5.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file < 0) {
			err_sys("Error open file, pid2:");
		}
		
		ssize_t byteAttesi;
		if (read(fdpipe[READ], &byteAttesi, sizeof(byteAttesi)) < 0) {
			err_sys("Error first read byteAttesi, pid2:");
		}
	
		int *buffer = malloc(byteAttesi);
		if (!buffer) {
			err_sys("Error malloc buffer, pid2:");
		}
		
		if (read(fdpipe[READ], buffer, byteAttesi) < 0) {
			err_sys("Error second read buffer, pid2:");
		}
		close(fdpipe[READ]);
		
		if (write(file, buffer, byteAttesi) < 0) {
			err_sys("Error write file, pid2:");
		}
		
		close(file);
		free(buffer);
		
		exit(3);
	}
	
	//Padre
	close(fdpipe[READ]);
	close(fdpipe[WRITE]);
	int status;
	
	// "Error waitpid1:: Interrupted system call" può esserci questo problema dunque chiamiamo la syscall fino a quando non si risolve
	pid_t figlio_atteso;
	do {
		figlio_atteso = waitpid(pid1, &status, 0);
	} while (figlio_atteso < 0 && errno == EINTR);
	
	if (WIFEXITED(status)) {
		printf("Padre: primo figlio con pid: %d ha terminato correttamente con status: %d.\n", figlio_atteso, WEXITSTATUS(status));
	}
	
//	figlio_atteso = waitpid(pid2, &status, 0);
	do {
		figlio_atteso = waitpid(pid2, &status, 0);
	} while (figlio_atteso < 0 && errno == EINTR);
	
	if (WIFEXITED(status)) {
		printf("Padre: secondo figlio con pid: %d ha terminato correttamente con status: %d.\n", figlio_atteso, WEXITSTATUS(status));
	}
	
	int file = open("test5.txt", O_RDONLY, 0644);
	if (file < 0) {
		err_sys("Error open file, padre:");
	}
	
	int buffer[2];
	
	ssize_t byteLetti = read(file, buffer, sizeof(buffer));
	if (byteLetti < 0) {
		err_sys("Error read file, padre:");
	}
	
	close(file);
	
	int risultato = buffer[0] * buffer[1];
	
	printf("Risultato: %d.\n", risultato);
	
	
	exit(EXIT_SUCCESS);
}

*/
