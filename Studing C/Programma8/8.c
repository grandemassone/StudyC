/*
1.	Apre un file test4.txt in scrittura (creandolo se non esiste).
2.	Duplica il file descriptor dello standard output (stdout) sul file usando dup2.
3.	Dopo il dup2, qualsiasi printf o write(1, …) deve andare direttamente sul file invece che sul terminale.
4.	Stampa qualche messaggio e chiudi correttamente i file descriptor.
5.	(Opzionale) Ripristina lo standard output originale e stampa un messaggio sul terminale.
*/
/*

#include <utilsF.h>

int main(void)
{
//	Open file
	int fdfile = open("test4.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fdfile < 0) {
		err_sys("Error open:");
	}
	
//	Save a backup of STDOUT_FILE
	int stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup < 0) {
		err_sys("Error save stdout_backup:");
	}
	
//	Duplicate stdout on fdfile
	if (dup2(fdfile, STDOUT_FILENO) < 0) {
		err_sys("Erro dup2,  fdfile -> STDOUT_FILENO:");
	}
	
//	Close fdfile now, because I write on it by STDOUT_FILENO
	close(fdfile);
	
	const char *msg = "Ciao, questo va sul file!\n";
	ssize_t byteWrite1 = write(STDOUT_FILENO, msg, strlen(msg));
	if (byteWrite1 < 0) {
		err_sys("Error first write:");
	}
	
//	Ripristine STDOUT_FILENO by stdou_backup
	if (dup2(stdout_backup, STDOUT_FILENO) < 0) {
		err_sys("Error dup2, stdout_backup -> STDOUT_FILENO:");
	}
	
	msg = "Ciao, questo va sul terminale!\n";
	ssize_t byteWrite2 = write(STDOUT_FILENO, msg, strlen(msg));
	if (byteWrite2 < 0) {
		err_sys("Error second write:");
	}
	
//	Close stdout_backup
	close(stdout_backup);
	
	
	//Exit with success
	exit(EXIT_SUCCESS);
}

*/
