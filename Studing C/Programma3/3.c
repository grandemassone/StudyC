/*
•	Il programma principale conta il numero di file in una directory.
•	Poi crea un figlio con fork().
•	Il figlio sostituisce il processo con "/bin/ls" usando execlp(),
	per stampare i nomi dei file nella directory.
•	Il padre aspetta il figlio con wait().
•	Bonus: fai passare la directory come argomento a execlp().
*/

/*
 
#include <utilsF.h>

void figlio1(char* path)
{
//	Il figlio sostituisce il processo con "/bin/ls" stampando i nomi dei file della directory passata come parametro
	execlp("ls", "ls", "-l", path, NULL);
	
//	Execlp sostituendo il processo non dovrebbe far andare avanti, quindi: se arriva qui c'è stato un problema
	err_sys("Errore execlp (figlio1): ");
}

int main(int argc, char* argv[])
{
//	Controllo numero di argomenti
	if(argc != 2){
		err_sys("Errore numero argomenti:");
	}
	
//	Conto il numero di file della directory
//	Apro la directory
	DIR* dir = opendir(argv[1]);
	if(dir == NULL){
		err_sys("Errore apertura dir:");
	}
	
//	Creo un contatore
	int count = 0;
	
//	Visito la directory contando il numero di file regolari all'interno
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL) {
//		Ignoro "." e ".."
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		
//		Recupero il file attuale
		char filePath[PATH_MAX];
		snprintf(filePath, sizeof(filePath), "%s/%s", argv[1], entry->d_name);
		
//		Creo una stat per collegarla al file in cui sono
		struct stat fdStat;
		if(stat(filePath, &fdStat) < 0){
			err_sys("Errore stat:");
		}
		
//		Controllo se il punto in cui ci troviamo attualmente è un file o una directory
		if(S_ISREG(fdStat.st_mode)){ // Se è un file, aumento il contatores
			count++;
		}
	}
	
//	Chiudo la directory
	closedir(dir);
	
//	Creo un processo
	pid_t pid1;
	if((pid1 = fork()) < 0){ //Fork sul processo
		err_sys("Errore fork:");
	}else if(pid1 == 0){ // Siamo nel figlio
//		Chiamo la gestione figlio
		figlio1(argv[1]); //Gli passo come parametro il path della directory
		
//		Esco dal figlio
		exit(0);
	}else{ //Siamo nel padre
//		Attende il figlio che termina
		wait(NULL);
		
//		Stampa il numero di file
		printf("Padre: numero di file: %d.\n\n", count);
	}
	
	
//	Termino con successo
	exit(0);
}

*/
