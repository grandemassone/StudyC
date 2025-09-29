/*
	1.	Riceve da riga di comando il path di una directory.
	2.	Apre la directory usando opendir().
	3.	Conta quanti file regolari ci sono (ignora . e ..).
	4.	Stampa il numero totale di file trovati.
	5.	Chiude la directory correttamente.
 */
/*
#include <utilsF.h>

int main(int argc, const char* argv[])
{
	//Controlliamo numero argomenti
	if(argc != 2){
		err_sys("Errore numero argomenti:");
	}
	
	//Apriamo la directory
	DIR* dir = opendir(argv[1]);
	if(dir == NULL){
		err_sys("Errore opendir.");
	}
	
	//Creiamo una directory entry
	struct dirent* entry;
	
	//Contatore
	int count = 0;
	
	
	//Leggiamo la directory corrente
	while ((entry = readdir(dir)) != NULL) {
		//Ignoriamo . e ..
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		
		//Recupero il path
		char path[PATH_MAX];
		snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
		
		//Creo la stat
		struct stat fdStat;
		if(stat(path, &fdStat) < 0){
			err_sys("Errore stat, while");
		}
		
		//Controllo se attualmente mi trovo in un file o in una directory in altro e conto
		printf("%s\n", path);
		if(S_ISDIR(fdStat.st_mode)){
			printf("\nSiamo in una directory, non incremento.\n");
			printf("-------------------------------------------\n");
		}else if(S_ISREG(fdStat.st_mode)){
			count++;
			printf("Siamo in file regolare, incremento.\n");
			printf("-------------------------------------------\n");
		}else{
			printf("Siamo in 'Altro', non incremento.\n");
			printf("-------------------------------------------\n");
		}
	}
	//Chiudo la directory
	closedir(dir);
	
	//Stampo il risultato finale
	printf("\n\nNumero di file regolari: %d.\n", count);
	
	
	//Termino con successo
	exit(0);
}
*/
