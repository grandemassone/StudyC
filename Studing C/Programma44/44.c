/*
1.The father creates two child processes.
2.Every child does:
     It generates a certain number of binary files (child1_X.bin or child2_X.bin), each containing 10 random numbers between 0 and 1000.
     Files must be created in the current directory.
     Each child can generate files in a limited cycle (for), not infinite, so as not to saturate the disk.
3.The father every second:
     Reads directory and all .bin files created by children.
     Calculate the sum total of all integers present.
     Print the total periodically.
4.If the total sum exceeds 10,000:
      Father finishes sons (kill(pid1, SIGKILL); kill(pid2, SIGKILL);)
      Prints the file name with the highest sum.
      Deletes all generated binaries (unlink()).
*/

/*

#include <utilsF.h>
#include <time.h>

int main(void)
{
    pid_t pid1, pid2;
    int i = 0, y = 0;
    if ((pid1 = fork()) < 0) {
        err_sys("fork() 1 error: ");
    } else if (pid1 == 0) {
        srand((unsigned int)time(NULL) ^ getpid());
        while (1) {
            //Wait a second
            sleep(1);
            
            char nameFile[NAME_MAX];
            snprintf(nameFile, sizeof(nameFile), "childOne%d.bin", i);
            
            int fdFile = open(nameFile, O_CREAT | O_APPEND | O_WRONLY, 0644);
            if (fdFile < 0) {
                err_sys("open() error: ");
            }
            
            for (int i = 0; i < 10; i++) {
                int x = rand() % 1000;
                if (write(fdFile, &x, sizeof(int)) < 0) {
                    err_sys("write() error: ");
                }
            }
            
            close(fdFile);
            
            i++;
            if (i > 2000) {
                err_sys("Too high number of files generated.\n\n");
            }
        }
    }
    
    if ((pid2 = fork()) < 0) {
        err_sys("fork() 2 error: ");
    } else if (pid2 == 0) {
        srand((unsigned int)time(NULL) ^ getpid());
        while (1) {
            //Wait a second
            sleep(1);
            
            char nameFile[NAME_MAX];
            snprintf(nameFile, sizeof(nameFile), "childTwo%d.bin", y);
            
            int fdFile = open(nameFile, O_CREAT | O_APPEND | O_WRONLY, 0644);
            if (fdFile < 0) {
                err_sys("open() error: ");
            }
            
            for (int i = 0; i < 10; i++) {
                int x = rand() % 1000;
                if (write(fdFile, &x, sizeof(int)) < 0) {
                    err_sys("write() error: ");
                }
            }
            
            close(fdFile);
            
            y++;
            if (y > 2000) {
                err_sys("Too high number of files generated.\n\n");
            }
        }
    }
    //FATHER
    int total = 0;
    int max = 0;
    char fileMax[NAME_MAX];
    
    DIR* dir = opendir(".");
    if (!dir) {
        err_sys("opendir() error: ");
    }
    
    struct dirent* entry;
    while (total < 10000) {
        //Waits 2 seconds
        sleep(2);
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            
            //Let's check if we are in a binary
            if (strlen(entry->d_name) > 4 || strcmp(entry->d_name + strlen(entry->d_name) - 4, ".bin") == 0) {
                int fdFile = open(entry->d_name, O_RDONLY);
                if (fdFile < 0) {
                    err_sys("open() fdFile father, error: ");
                }
                
                int tempTotal = 0;
                int temp;
                ssize_t rByte;
                while((rByte = read(fdFile, &temp, sizeof(int))) == sizeof(int)) {
                    //Let's increase total
                    total += temp;
                    tempTotal += temp;
                    if (rByte < 0) {
                        err_sys("read() error: ");
                    }
                }
                
                if (tempTotal > max) {
                    max = tempTotal;
                    strcpy(fileMax, entry->d_name);
                }
                
                printf("[FATHER]: The current total is: %d.\n", total);
                
                close(fdFile);
            } else { continue; }
        }
    }
    
    if (kill(pid1, SIGKILL) < 0) {
        err_sys("kill() 1 error: ");
    }
    if (kill(pid2, SIGKILL) < 0) {
        err_sys("kill() 2 error: ");
    }
    
    //Delete all binaries
    rewinddir(dir);
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        //Let's check if we are in a binary
        if (strlen(entry->d_name) > 4 || strcmp(entry->d_name + strlen(entry->d_name) - 4, ".bin") == 0) {
            unlink(entry->d_name);
        }
    }
    
    printf("\n[FATHER]: The total is: %d.\n", total);
    printf("[FATHER]: File con la somma totale più alta: %s.\n\n", fileMax);
    
    
    //I end successfully
    exit(EXIT_SUCCESS);
}

*/
