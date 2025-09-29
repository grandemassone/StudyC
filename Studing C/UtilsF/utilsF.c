#include "utilsF.h"

void err_sys(const char* messaggio)
{
	perror(messaggio);
	exit(EXIT_FAILURE);
}

/*------------------------------FUNZIONI PER IL CONTEGGIO------------------------------*/
static struct rusage startUsage;
static struct rusage endUsage;
static int counting = 0;

/*
 * --> startCounting(void);
 * Inizia a raccogliere le statistiche di utilizzo risorse del processo corrente.
 * Salva i valori iniziali della CPU, memoria e page fault per calcolare le differenze.
 */
void startCounting(void) {
	if(getrusage(RUSAGE_SELF, &startUsage) < 0) {
		perror("Errore startCounting");
		exit(EXIT_FAILURE);
	}
	counting = 1;
}

/*
 * --> stopCounting(void);
 * Termina il conteggio delle risorse.
 * Salva i valori finali della CPU, memoria e page fault per poterli confrontare
 * con quelli iniziali.
 */
void stopCounting(void) {
	if(!counting) return;
	if(getrusage(RUSAGE_SELF, &endUsage) < 0) {
		perror("Errore stopCounting");
		exit(EXIT_FAILURE);
	}
	counting = 0;
}

/*
 * --> printResourceUsage(void);
 * Stampa a schermo le statistiche di utilizzo risorse del processo:
 *  - Tempo CPU in user mode e system mode
 *  - Massima memoria residente (RSS)
 *  - Page faults soft e hard
 *  - Operazioni di swap
 *
 * Deve essere chiamata dopo stopCounting() per ottenere valori corretti.
 */
void printResourceUsage(void) {
	long userTime = (endUsage.ru_utime.tv_sec - startUsage.ru_utime.tv_sec) * 1000
					+ (endUsage.ru_utime.tv_usec - startUsage.ru_utime.tv_usec)/1000;
	long sysTime  = (endUsage.ru_stime.tv_sec - startUsage.ru_stime.tv_sec) * 1000
					+ (endUsage.ru_stime.tv_usec - startUsage.ru_stime.tv_usec)/1000;

	printf("CPU user time: %ld ms\n", userTime);
	printf("CPU sys time:  %ld ms\n", sysTime);
	printf("Max resident size: %ld KB\n", endUsage.ru_maxrss);
	printf("Page reclaims (soft page faults): %ld\n", endUsage.ru_minflt - startUsage.ru_minflt);
	printf("Page faults (hard page faults): %ld\n", endUsage.ru_majflt - startUsage.ru_majflt);
	printf("Swaps: %ld\n", endUsage.ru_nswap - startUsage.ru_nswap);
}
