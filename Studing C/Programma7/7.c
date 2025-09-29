/*
 1.	Il processo padre crea un figlio con fork().
 2.	Viene creata una pipe tra padre e figlio.
 3.	Il figlio apre un file chiamato test1.txt in lettura usando open().
 4.	Il figlio legge il contenuto del file (read()) e lo memorizza in un buffer.
 5.	Il figlio installa un handler per SIGUSR1. Quando riceve il segnale:
		•scrive il contenuto del buffer sulla pipe usando write().
		•termina il programma (exit()).
 6.	Il padre attende 2 secondi (sleep()), poi invia SIGUSR1 al figlio (kill()).
 7.	Il padre legge dalla pipe (read()) il contenuto inviato dal figlio e lo stampa a video.
 8.	Entrambi chiudono correttamente file e pipe (close()).
*/

/*

#include <utilsF.h>

int fdpipe[2]; //Global pipe
char *buffer = NULL; //Global buffer

void handler_signal(int sign)
{
//	Write byteLetti in the fdpipe
	ssize_t byteLetti = strlen(buffer);
	if (write(fdpipe[WRITE], &byteLetti, sizeof(byteLetti)) < 0) {
		err_sys("Error write length to fdpipe, handler_signal:");
	}
	
//	Write buffer's content in fdpipe[WRITE]
	if (write(fdpipe[WRITE], buffer, strlen(buffer)) < 0) {
		err_sys("Error write buffer to fdpipe, handler_signal:");
	}
	
//	Free the buffer
	free(buffer);
	
//	Exit with status: 21
	exit(21);
}

int main(void)
{
	if (pipe(fdpipe) < 0) {
		err_sys("Error pipe");
	}
	
//	Create process and I fork it
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("Error fork");
	} else if (pid == 0) {
//		-------------------------------SON-------------------------------
//		Close the READ's part of the fdpipe
		close(fdpipe[READ]);
		
//		Open a file "test1.txt" and read it, then save the content in the buffer
		int fdfile = open("test1.txt", O_RDONLY, 0644);
		if (fdfile < 0) {
			err_sys("Error open fdfile, son:");
		}
		struct stat fdstat;
//		We use fstat() cause we've already the file descriptor opened by "open()"
		if (fstat(fdfile, &fdstat) == 0) {
			buffer = malloc(fdstat.st_size + 1); // +1 for the terminator
			if (!buffer) {
				err_sys("Error malloc, son:");
			}
			ssize_t byteLetti = read(fdfile, buffer, fdstat.st_size);
			if (byteLetti < 0) {
				err_sys("Error read, son:");
			}
			buffer[byteLetti] = '\0'; //Add terminator at the end of the buffer
		}else err_sys("Error fstat, son:");

//		Setting handler_signal for SIGUSR1
		if ((signal(SIGUSR1, handler_signal) == SIG_ERR)) { //SIG_ERR = -1
			err_sys("Error signal, son:");
		}
//		Waiting the signal
		pause();
		
//		Close the fdpipe[WRITE]
		close(fdpipe[WRITE]);
//		Close the fdfile
		close(fdfile);
	}else{
//		-------------------------------FATHER-------------------------------
//		Close the fdpipe[WRITE]
		close(fdpipe[WRITE]);
		
//		Waiting 2 second's
		sleep(2);
		
//		Kill signal
		if (kill(pid, SIGUSR1) == -1) {
			if (errno == ESRCH) {
				fprintf(stderr, "The son process %d doesn't exist.\n", pid);
			} else if (errno == EPERM) {
				fprintf(stderr, "You don't have the permission for send signal to pid: %d.\n", pid);
			} else {
				err_sys("Error kill:");
			}
			exit(EXIT_FAILURE);
		}
		
//		Read lenght fdfrom pipe
		ssize_t size_pipe;
		if (read(fdpipe[READ], &size_pipe, sizeof(size_pipe)) < 0) {
			err_sys("Error read lenght, father:");
		}
		char *buffer_father = malloc(size_pipe + 1);
		if (!buffer_father) {
			err_sys("Error malloc buffer_father, father:");
		}
		
//		Read data from fdpipe
		if (read(fdpipe[READ], buffer_father, size_pipe) < 0) {
			err_sys("Error read data, father:");
		}
		
//		Add the terminator at the end of the buffer
		buffer_father[size_pipe] = '\0';
		
//		Print it on the STDOUT
		write(1, buffer_father, size_pipe);
		write(1, "\n", 1);
		
//		Close fdpipe[READ]
		close(fdpipe[READ]);
		
//		Free buffer_father
		free(buffer_father);
		
		
//		Exit with success
		exit(EXIT_SUCCESS);
	}
}

*/
