/*
1.Il programma prende come argomento il percorso di un file di testo (argv[1]).
2.Crea una pipe tra padre e figlio.
3.Il figlio:
	 •Legge il file.
	 •Conta le parole (separate da spazi o tab o newline).
	 •Scrive il numero totale di parole nella pipe.
	 •Termina.
4.Il padre:
	 •Legge dalla pipe il numero totale di parole.
	 •Stampa a video: "Numero totale di parole nel file: X".
*/

/*

#include <utilsF.h>

int main(int argc, char** argv)
{
	if (argc != 2) {
		err_sys("Error number arguments:");
	}
	
	int fdpipe[2];
	if (pipe(fdpipe) < 0) {
		err_sys("Error pipe:");
	}
	
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("Error fork:");
	} else if (pid == 0) { //Son
		close(fdpipe[READ]);
		
		int fdfile = open(argv[1], O_RDONLY, 0644);
		if (fdfile < 0) {
			err_sys("Error open file, son:");
		}
		
		off_t sizeFile = lseek(fdfile, 0, SEEK_END);
		
		char* buffer = malloc(sizeFile);
		if (!buffer) {
			err_sys("Error malloc, son:");
		}
		
		lseek(fdfile, 0, SEEK_SET);
		
		if (read(fdfile, buffer, sizeFile) < 0) {
			err_sys("Error read, son:");
		}
		
		int in_word = 0;
		int words = 0;
		for (int i = 0; i < sizeFile; i++) {
			if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n') {
				if (in_word == 1) {
					words++;
					in_word = 0;
				}
			} else {
				in_word = 1; //Siamo dentro una parola
			}
		}
		//Count the last word, in case there is not any separator
		if(in_word)
			words++;
		
		if (write(fdpipe[WRITE], &words, sizeof(int)) < 0) {
			err_sys("Error write in fdpipe, son:");
		}
		
		close(fdpipe[WRITE]);
		close(fdfile);
		
		exit(21);
	} else { //Father
		wait(NULL);
		close(fdpipe[WRITE]);
		
		int wordsNumber;
		if (read(fdpipe[READ], &wordsNumber, sizeof(int)) < 0) {
			err_sys("Error read pipe:");
		}
		
		close(fdpipe[READ]);
		
		printf("Il numero di parole del file è: %d.\n", wordsNumber);
		
		
		//Exit with success
		exit(EXIT_SUCCESS);
	}
}

*/
