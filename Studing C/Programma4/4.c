/*
•	Il programma apre un file di log (test2.txt) in scrittura + appending.
•	Installa un handler per SIGINT che scrive nel file: “Segnale ricevuto!” invece di terminare.
•	Poi entra in un ciclo infinito che scrive numeri progressivi nel file ogni secondo (sleep(1)).
•	Verifica che premendo Ctrl+C il programma non termini ma scriva nel log.
•	Usa: signal(), open(), write(), sleep().
 */

/*

#include <utilsF.h>

// fd globale per il log
int fd;

// Handler per SIGINT
void handlerSignal(int signum)
{
	char *msg = "Segnale ricevuto!\n";
	write(fd, msg, strlen(msg));
	
//	"exit()" non serve perché non termina 
}

int main(void)
{
//	Apriamo o creiamo il file log.txt in append
	fd = open("test2.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0) {
		err_sys("Errore file:");
	}

//	Installiamo il signal handler
	if (signal(SIGINT, handlerSignal) < 0) {
		close(fd);
		err_sys("Errore installazione signal:");
	}

	int counter = 1;
	char buffer[64];

// 	Entriamo nel ciclo infinito,
	while (1) {
		int len = snprintf(buffer, sizeof(buffer), "Contato: %d volte\n", counter++);
		write(fd, buffer, len);
		sleep(1); //Attende un secondo e poi continua
	}

//	Codice mai eseguito
	close(fd);
	exit(0);
}

*/
