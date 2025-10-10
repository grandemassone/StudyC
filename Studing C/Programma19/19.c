/*
1.	The parent process creates one pipe and then performs a fork().
2.	The child process must:
	 •	Read from the pipe the directory path sent by the parent.
	 •	Open that directory using opendir().
	 •	Count how many regular files (not subdirectories) are inside it.
	 •	Write this number into a file called test8.txt.
	 •	When finished, send a SIGUSR1 signal to the parent to notify completion.
3.	The parent process must:
	 •	Read a directory path from argv.
	 •	Send the path to the child through the pipe.
	 •	Wait for the SIGUSR1 signal from the child.
	 •	When the signal is received, print: "Child has completed. Check test8.txt" and then terminate.
*/

#include <utilsF.h>

void handler_signal(int signum)
{
	printf("Child has completed. Check test8.txt.\n\n");
	
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		err_sys("Error number argc: ");
	}
	
	int fdpipe[2];
	if (pipe(fdpipe) < 0) {
		err_sys("Error pipe: ");
	}
	
	int pid;
	if ((pid = fork()) < 0) {
		err_sys("Error fork: ");
	} else if (pid == 0) { //Child
		close(fdpipe[WRITE]);
		
		char path[PATH_MAX];
		ssize_t b_read = read(fdpipe[READ], path, sizeof(path));
		if (b_read < 0) {
			err_sys("Error read fdpipe, child: ");
		}
		path[b_read] = '\0';
		
		//Close the read of the fdpipe
		close(fdpipe[READ]);
		
		//Counter for the regular files
		int count = 0;
		
		DIR* dir = opendir(path);
		if (dir == NULL) {
			err_sys("Error opendir, child: ");
		}
		struct dirent* entry;
		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			
			char currentPath[PATH_MAX];
			snprintf(currentPath, sizeof(currentPath), "%s/%s", path, entry->d_name);
			
			struct stat fdstat;
			if (stat(currentPath, &fdstat) < 0) {
				err_sys("Error stat: ");
			}
			
			if (S_ISREG(fdstat.st_mode)) {
				count++;
			}
		}
		
		//Write the number in the file test8.txt
		int fdfile = open("test8.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fdfile < 0) {
			err_sys("Error open file, child: ");
		}
		
		if (write(fdfile, &count, sizeof(count)) < 0) {
			err_sys("Error write count in fdfile, child: ");
		}
		
		//Send signal SIGUSR1 to the parent
		kill(getppid(), SIGUSR1);
		
		//Close the file and directory
		closedir(dir);
		close(fdfile);
	} else { //Parent
		close(fdpipe[READ]);
		signal(SIGUSR1, handler_signal);
		
		char path[PATH_MAX];
		strcpy(path, argv[1]);
	
		if (write(fdpipe[WRITE], path, strlen(path) + 1) < 0) {
			err_sys("Error write in fdpipe, parent: ");
		}
		
		//Wait for signal SIGUSR1
		pause();
		
		close(fdpipe[WRITE]);
	}
	
	
	
	exit(EXIT_SUCCESS);
}

