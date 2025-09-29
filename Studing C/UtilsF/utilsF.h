#ifndef UTILS_F_H
#define UTILS_F_H

//DEFINIZIONE DELLE LIBRERIA DI SISTEMA

#include <stdio.h>      /*perror(), printf(), fprintf(), snprintf() → solo per debug o messaggi 					  di errore (non vere syscall). */
/*--------------*/

#include <stdlib.h>     // exit(), malloc(), free() → gestione memoria e terminazione processo.
/*--------------*/

#include <unistd.h>     /* read(), write(), close(), fork(), _exit(), pipe(), dup(), dup2(),
						   getpid(), getppid(), unlink(), rmdir(), sleep(). */
/*--------------*/

#include <fcntl.h>      /* open(), creat(), O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC, 					   O_APPEND → apertura/creazione file e flags. */
/*--------------*/

#include <sys/types.h>  // pid_t, off_t, mode_t → tipi dati usati dalle syscall.
/*--------------*/

#include <sys/stat.h>   /* stat(), fstat(), chmod(), mkdir() → informazioni e permessi 					   file/directory. */
/*--------------*/

#include <dirent.h>     // opendir(), readdir(), closedir() → gestione directory.
/*--------------*/

#include <string.h>     /* strerror(), memcpy(), memset(), strlen(), strcmp() → Utilità per 					   gestione stringhe/errore. */
/*--------------*/

#include <errno.h>      // errno → codice errore dell’ultima syscall.
/*--------------*/

#include <sys/wait.h>   /* wait(), waitpid(), WIFEXITED(), WEXITSTATUS() → gestione terminazione 					   processi figli. */
/*--------------*/

#include <signal.h>     /* signal(), kill(), raise(), sigaction(), sigprocmask() → gestione 					   segnali. */
/*--------------*/

#include <limits.h>		//Varie define di limiti --> PATH_MAX (Esempio)
/*---------------------------------------------------------------------------------------------*/

//Definizione di WRITE e READ per la gestione della pipe
#define WRITE 1
#define READ 0

//Prototipo di funzione "err_sys"
void err_sys(const char *messaggio);

//Prototipi delle funzioni per il conteggio
void startCounting(void);
void stopCounting(void);
void printResourceUsage(void);

#endif
