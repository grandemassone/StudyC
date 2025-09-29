/*
•Ricevi da riga di comando una directory.
•Per ogni file regolare, crea un figlio con fork().
•Il figlio esegue wc -l tramite execlp() per contare le righe del file.
•Il padre legge l’output del figlio tramite pipe e scrive in un file test3.txt il nome del file + numero di righe.
*/

/*

#include <utilsF.h>

int main(int argc, char** argv)
{
//	Check the number of arguments
	if(argc != 2) err_sys("Error argc:");
	
//	opendir()
	DIR* dir = opendir(argv[1]);
	if (dir == NULL) {
		err_sys("Errore opendir:");
	}
	
//	Directory entry
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
//		I ignore "." and ".."
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		
//		Get the currently path
		char path[PATH_MAX];
		snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
		
//		Get the stat of the path
		struct stat statfd;
		if(stat(path, &statfd) < 0){
			err_sys("Error stat: while");
		}
		
		if(S_ISDIR(statfd.st_mode)){
			continue;
		}else if(S_ISREG(statfd.st_mode)){
			//	Create pipe
			int fdpipe[2];  //Local pipe for this file
			if ((pipe(fdpipe)) < 0) err_sys("Error pipe:");
			
			pid_t child;
			if ((child = fork()) < 0) {
				err_sys("Error fork: child");
			}else if (child == 0){ // CHILD
				close(fdpipe[READ]); // Close read fdpipe
				dup2(fdpipe[WRITE], STDOUT_FILENO); // Dup the write of the pipe in the stdout
				close(fdpipe[WRITE]); // Close write fdpipe
				execlp("wc", "wc", "-l", path, NULL);
				err_sys("Error execlp: child");
			}else{
				//	---------------------------------FATHER---------------------------------
				//	Close the write of the fdpipe
					close(fdpipe[WRITE]);
					
				//	Create buffer
					char buffer[PATH_MAX];
					ssize_t size = read(fdpipe[READ], buffer, sizeof(buffer) - 1);
					if (size < 0) {
						err_sys("Errore read fdpipe: father");
					}
					buffer[size] = '\0';
					
				//	I'm going to create a file…
					int fdfile = open("test3.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
					if (fdfile < 0) {
						err_sys("Error open file: father");
					}
					
				//	…now i'm going to write in the file the entire buffer
					if ((write(fdfile, buffer, size) != size)) {
						err_sys("Error write in fdfile: father");
					}
					
				//	Close file
					close(fdfile);
					
				//	Close read pipefd
					close(fdpipe[READ]);
			}
		}else {
			continue;
		}
	}
	
//	Close dir
	closedir(dir);
	
//	Exit with success
	exit(EXIT_SUCCESS);
}

*/
