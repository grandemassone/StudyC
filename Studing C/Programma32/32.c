/*
1.Create N children (you choose N, for example 3).
2.Everyone reads from the same text file (eg. text.txt), but each child reads a different portion of the file.
3.Each child must print the part they have read on the screen, preceded by a message such as:
					[Son 1]: <bed text>
					[Son 2]: <bed text>
					...
 4.The father waits for all the children to finish.
*/

/*
 
#include <utilsF.h>

int main(void)
{
	int X = 3;
	
	int fdFile = open("file1.txt", O_RDONLY);
	if (fdFile < 0) {
		err_sys("open() error: ");
	}
	
	//Recover X split file length
	off_t byteFile = lseek(fdFile, 0, SEEK_END);
	lseek(fdFile, 0, SEEK_SET);
	off_t portionByteFile = byteFile / X;
	
	for (int i = 0; i < X; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			err_sys("fork() error: ");
		} else if (pid == 0) {
			char buffer[portionByteFile + 1];
			ssize_t rByte = read(fdFile, buffer, portionByteFile);
			if (rByte < 0) {
				err_sys("read() error: ");
			}
			buffer[rByte] = '\0';
			
			printf("[SON %d]: <%s>\n", i + 1, buffer);
		
			exit(EXIT_SUCCESS);
		}
	}
	
	//FATHER
	for (int i = 0; i < X; i++) {
		wait(NULL);
	}
	
	printf("[FATHER]: the children have all finished.\n\n");
	
	//I close the file
	close(fdFile);
	
	//I end successfully
	exit(EXIT_SUCCESS);
}

*/
