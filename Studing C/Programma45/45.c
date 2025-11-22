/*
1.Open a file with open().
2.Save the original stdout descriptor file (optional, if you want to restore it).
3.Use dup2(fd_file, 1) to make printf() go to the file.
4.Printing with printf().
5.Close the file and restore stdout if you want.
*/

/*
 
#include <utilsF.h>

int main(void)
{
    int fdFile = open("test1.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fdFile < 0) {
        err_sys("open() error: ");
    }
    
    int saveStdout = dup(STDOUT_FILENO);
    if (saveStdout < 0) {
        err_sys("dup() error: ");
    }
    
    if (dup2(fdFile, STDOUT_FILENO) < 0) {
        err_sys("dup2() 1 error: ");
    }
    
    printf("Hi, I'm printing with printf on the file.");
    
    if (dup2(saveStdout, STDOUT_FILENO) < 0) {
        err_sys("dup2() 2 error: ");
    }
    printf("Hi, I'm writing with printf on stdout.\n\n");
    
    close(saveStdout);
    close(fdFile);
    
    
    exit(EXIT_SUCCESS);
}

*/
