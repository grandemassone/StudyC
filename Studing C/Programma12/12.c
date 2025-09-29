/*
1.Apre (o crea) un file chiamato test6.txt.
2.Duplica lo stdout (fd = 1) sul file usando dup2, così che tutte le printf vadano dentro al file.
3.Stampa due righe di testo:
	•Una con printf("Ciao dal processo!\n");
	•Un’altra con write(1, "Scrivo con write()\n", 19);
4.Chiudi il file descriptor e termina.
*/

/*
#include <utilsF.h>

int main(void)
{
	int fdfile = open("test6.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
	
	int saved_stdout = dup(STDOUT_FILENO); //Copy of STDOUT_FILENO (1) on saved_stdout
	
	printf("Prima stampa su terminale!\n");
	
	if (dup2(fdfile, STDOUT_FILENO) < 0) {
		err_sys("Error dup2:");
	}
	
	printf("Ciao dal processo!\nScrivo con write()\n");
	
	if (dup2(saved_stdout, STDOUT_FILENO) < 0) {
		err_sys("Error dup2:");
	}
	
	printf("Stampa su terminale\n");
	
	close(fdfile);
	
	exit(EXIT_SUCCESS);
}
*/
