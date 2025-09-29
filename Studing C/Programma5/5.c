/*
• Crea due figli.
• Il padre scrive numeri da 1 a 100 nella prima pipe.
• Il primo figlio legge dalla prima pipe, raddoppia i numeri e li scrive nella seconda pipe.
• Il secondo figlio legge dalla seconda pipe e stampa i numeri su stdout.
*/
/*

#include <utilsF.h>

int main(void)
{
//	Make two pipe, pipefd1[] and pipefd2[]
	int pipefd1[2], pipefd2[2];
	if(pipe(pipefd1) < 0){
		err_sys("Errore pipe: pipefd1");
	}
	if(pipe(pipefd2) < 0){
		err_sys("Error pipe: pipefd2");
	}
	
//	I create two process
	pid_t pid1, pid2;
	
	if((pid1 = fork()) < 0){
		err_sys("Error fork: pid1");
	}else if(pid1 == 0){
					//-----------------FIRST CHILD----------------------
		
//		I'm closing the write in pipefd1 and the read in pipefd2
		close(pipefd1[WRITE]);
		close(pipefd2[READ]);
		
//		I read the dimension sent by the father
		int size;
		if (read(pipefd1[READ], &size, sizeof(size)) != sizeof(size)) {
			err_sys("Error read: pid1");
		}
		
//		I create a buffer for reading pipefd1[]
		char *buffer = malloc(size);
		if (!buffer) err_sys("Errore malloc buffer: pid1");
		if (read(pipefd1[READ], buffer, size) != size) {
			err_sys("Errore read");
		}
		
//		Close pipefd1[READ]
		close(pipefd1[READ]);
		
//		I'm going to double every single number in the buffer
		char *out = malloc(size * 2);
		if(!out) err_sys("Error malloc out: pid1");
		
		char *tok = strtok(buffer, " ");
		int len = 0;
		while (tok) {
			int val = atoi(tok) * 2;
			len += sprintf(out + len, "%d ", val);
			tok = strtok(NULL, " ");
		}
		out[len] = '\0';

//		I'm going to write the entire buffer in the pipefd2
		if (write(pipefd2[WRITE], &len, sizeof(len)) != sizeof(len)) {
			err_sys("Error write size in pipefd2: pid1");
		}
		if (write(pipefd2[WRITE], out, len) != len) {
			err_sys("Error write data in pipefd2: pid1");
		}
		
//		Close pipefd2[WRITE]
		close(pipefd2[WRITE]);
		
//		Free buffer and out
		free(buffer);
		free(out);
		
		
//		Exit from first child with status 21
		exit(21);
	}
	
	if((pid2 = fork()) < 0){
		err_sys("Error for: pid2");
	}else if(pid2 == 0){
					//-----------------SECOND CHILD----------------------
//		Now I'm closing the read and the write in the pipefd1 cause I don't
//		need it in the second child, and I'm closing the write in the pipefd2 too.
		close(pipefd1[READ]);
		close(pipefd1[WRITE]);
		close(pipefd2[WRITE]);
		
//		I read the dimensione sent by the father
		int size;
		if (read(pipefd2[READ], &size, sizeof(size)) != sizeof(size)) {
			err_sys("Error read size pipefd2: pid2");
		}
		
//		I'm reading the entire pipefd2 in a buffer then I'm going to print it
//		on stdout.
		char *buffer = malloc(size + 1);
		if (!buffer) err_sys("Error malloc buffer: pid2");
		
		if (read(pipefd2[READ], buffer, size) != size) {
			err_sys("Error read data: pid2");
		}
		buffer[size] = '\0';
//		Close reading, pipefd2[READ]
		close(pipefd2[READ]);
		
//		Print on stdout through write
		write(1, buffer, size);
		write(1, "\n", 1);
		
//		Free buffer
		free(buffer);
		
//		Exit from the second child with status 22
		exit(22);
	}
	
//	We're in the father
//	I'm going to close the read and the write of the pipefd2 and the read
//	of the pipefd1
	close(pipefd1[READ]);
	close(pipefd2[READ]);
	close(pipefd2[WRITE]);
	
//	Write in the buffer 100 number, from 1 to 100
	int n = 100;
	int maxlen = n * 4; // massimo: "100 " = 4 char
	char *buffer = malloc(maxlen);
	if (!buffer) err_sys("Error malloc buffer: father");
	
	int len = 0;
	for (int i = 1; i <= n; i++) {
		len += sprintf(buffer + len, "%d ", i);
	}
	buffer[len] = '\0';
	
//	I send before the lenght and then the data
	if (write(pipefd1[WRITE], &len, sizeof(len)) != sizeof(len)) {
		err_sys("Error write size in pipefd1: father");
	}
	
	if (write(pipefd1[WRITE], buffer, len) < 0) {
		err_sys("Error write data in pipefd1: father");
	}

//	Close pipefd1[WRITE]
	close(pipefd1[WRITE]);
	
//	Free buffer
	free(buffer);
	
	
//	Exit with success
	exit(0);
}

*/
