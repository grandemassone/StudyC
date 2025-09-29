/*
 •	Scrivi un programma che esplora ricorsivamente una directory ricevuta da riga di comando.
 •	Per ogni file regolare trovato, scrive il nome del file e la dimensione in byte in una pipe.
 •	Un processo figlio scrive nella pipe i dati ricevuti.
 •	Infine stampa tramite il main tutto il contenuto della pipe
 
 Syscall utilizzate: close(), fork(), exit(), pipe(), write(), readdir(), open(), getpid(), waitpid()
 
*/

/*
#include <utilsF.h>

//	Creazione pipeFd globale
int pipeFd[2];
*/
/*void visitaDirRic(char* path);
 *Funzione in utilità alla ricerca ricorsiva all'interno di una directory*/

/*
void visitaDirRicPipe(char* path)
{
//	Apro la directory
	DIR *dir = opendir(path);
	if(dir == NULL){
		err_sys("Errore opendir:");
	}
	
//	Visita ricorsiva della directory
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		//	Ignoriamo . e ..
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		
		//	Recuperiamo il path attuale
		char newPath[PATH_MAX];
		snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
		
		//	Creazione stat
		struct stat fdStat;
		//	Lo impostiamo su newPath
		if(stat(newPath, &fdStat) < 0){
			err_sys("Errore stat:");
		}
		
		//	Stampiamo sempre il newPath
		printf("%s\n", newPath);
		
		//	Controlliamo se nella posizione attuale si trova una directory, un file o altro
		if(S_ISDIR(fdStat.st_mode)){
			printf("Directory.\n");
			printf("------------------------------------\n");
			
			//	Chiamata ricorsiva
			visitaDirRicPipe(newPath);
		}else if(S_ISREG(fdStat.st_mode)){//Siamo in un file
			printf("File regolare.\n");
			printf("------------------------------------\n");
			
			//	Apriamo il file in cui ci troviamo
			int fileFd = open(newPath, O_RDONLY);
			if(fileFd < 0){
				err_sys("Errore apertura file:");
			}
			
			//	Scriviamo nella pipe il nome e la grandezza del file
			char msg[100];
			snprintf(msg, sizeof(msg), "Nome file: %s, grandezza in byte: %lld.\n", entry->d_name, fdStat.st_size);
			write(pipeFd[WRITE], msg, strlen(msg));
		}else{
			printf("Altro\n");
			printf("------------------------------------\n");
		}
	}
//	Chiudo la directory
	closedir(dir);
}

int main(int argc, char* argv[])
{
//	Controllo numero argomenti
	if (argc != 2) {
		err_sys("Errore numero argomenti:");
	}
	
//	Inizializzo la pipe()
	if(pipe(pipeFd) < 0){
		err_sys("Errore creazione pipe:");
	}
	
//	Creiamo un processo
	pid_t pid1;
	if((pid1 = fork()) < 0){
		err_sys("Errore fork");
	}
	
	if(pid1 == 0){ //Siamo nel figlio
		// Chiudo la pipe in lettura qui e non nella funzione, perché è ricorsiva
		close(pipeFd[READ]);
		
		printf("Figlio, pid: %d.\n", getpid());
		
		// Chiamo la funzione per visitare ricorsivamente la directory e scrivere nella pipe
		visitaDirRicPipe(argv[1]);
		
		// Chiudo la pipe in scrittura, perché deve essere gestita all'interno del figlio e non nella funzione
		close(pipeFd[WRITE]);

		// Il figlio termina con un valore di 0
		exit(0);
	}else if(pid1 > 0){ // Siamo nel padre
		// Chiudo la pipe in scrittura
		close(pipeFd[WRITE]);
		
		// Attendo il figlio con waitpid()
		int status;
		pid_t figlio_atteso = waitpid(pid1, &status, 0);
		if(WIFEXITED(status)){ // Controllo uscita corretta del figlio tramite "exit(int)";
			printf("Padre: il figlio con pid: %d, ha terminato con status: %d.\n", figlio_atteso, WEXITSTATUS(status));
		}
		
		// Stampo il contenuto della pipe all'interno del buffer e poi stampo tutto su stdout
		char buffer[256];
		ssize_t byteLetti;
		while ((byteLetti = read(pipeFd[READ], buffer, sizeof(buffer) - 1)) > 0) {
			buffer[byteLetti] = '\0';  // Aggiungo terminatore
			write(1, buffer, byteLetti);
		}
		
		// Chiudo la pipe in lettura
		close(pipeFd[READ]);
	}
	
	// Termino con successo
	exit(0);
}
*/
