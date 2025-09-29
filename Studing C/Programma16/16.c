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

#include <utilsF.h>
#include <time.h>

int main(void)
{
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("Error fork:");
	} else if (pid == 0) { //Son
		srand((unsigned int)time(NULL));
		while (1) {
			int x = rand() % 10;
		}
	}
}
