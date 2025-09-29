/*
1.Il programma riceve come argomento un file di testo e un numero N (numero di figli).
2.Divide il file in N parti circa uguali.
3.Crea N figli:
	•Ogni figlio legge solo la propria porzione del file (usando lseek e read).
	•Conta le parole nella sua porzione (usando la logica in_word di cui parlavamo).
4.Ogni figlio comunica il conteggio parziale al padre tramite pipe.
5.Il padre somma tutti i conteggi parziali e stampa il numero totale di parole.
*/

/*

#include <utilsF.h>

#define N 5

int main(int argc, char** argv)
{
	if (argc != 2) {
		err_sys("Error number arguments:");
	}
	
	int fdfile = open(argv[1], O_RDONLY, 0644);
	if (fdfile < 0) {
		err_sys("Error open file:");
	}
	
	off_t sizeFile = lseek(fdfile, 0, SEEK_END);
	lseek(fdfile, 0, SEEK_SET);
	
	off_t filePart = sizeFile / N;
	off_t remaining = sizeFile % N;
	
	int fdpipe[N][2];
	pid_t figli[N];
	for (int i = 0; i < N; i++) {
		if (pipe(fdpipe[i]) < 0) {
			err_sys("Error pipe:");
		}
	}
	
	//Creazione figli
	for (int i = 0; i < N; i++) {
		pid_t pid;
		if ((pid = fork()) < 0) {
			err_sys("Error fork:");
		} else if (pid == 0) {
			close(fdpipe[i][READ]);
			
			off_t myPart = filePart;
			if (i == N - 1) {
				myPart += remaining;
			}
			
			char* buffer = malloc(myPart);
			if (!buffer) {
				err_sys("Error malloc:");
			}
			
			lseek(fdfile, i * filePart, SEEK_SET);
			if (read(fdfile, buffer, myPart) < 0) {
				err_sys("Error read file, son:");
			}
			
			int words = 0;
			int inWord = 0;
			for (off_t j = 0; j < myPart; j++) {
				if (buffer[j] == ' ' || buffer[j] == '\t' || buffer[j] == '\n') {
					if (inWord) { //Se siamo in una parola
						words++;
						inWord = 0;
					}
				} else {
					inWord = 1; //Siamo in una parola allora
				}
			}
			if (inWord) { //Se siamo ancora dentro una parola alla fine ma non abbiamo separatori di alcun tipo, incrementiamo words
				words++;
			}
			
			if (write(fdpipe[i][WRITE], &words, sizeof(int)) < 0) {
				err_sys("Error write fdpipe, son:");
			}

			free(buffer);
			exit(10 + i);
		} else {
			figli[i] = pid; //Salviamo pid in figli
			close(fdpipe[i][WRITE]);
		}
	}
	int total = 0;
	for (int i = 0; i < N; i++) {
		int temp;
		if (read(fdpipe[i][READ], &temp, sizeof(int)) < 0) {
			err_sys("Error read pipe, father:");
		}
		close(fdpipe[i][READ]);
		total += temp;
		
		int status;
		pid_t figlioAtteso = waitpid(figli[i], &status, 0);
		if (WIFEXITED(status)) {
			printf("Sono il padre e il figlio con pid: %d, ha terminato con status: %d.\n\n", figlioAtteso, WEXITSTATUS(status));
		} else {
			err_sys("Error WIFEXITED, father:");
		}
	}
	
	printf("Numero totale di parole: %d.\n\n", total);
	close(fdfile);
	
	//Exit with success
	exit(EXIT_SUCCESS);
}

*/
