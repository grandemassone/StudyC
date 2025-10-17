/*
Test of mmap and munmap.
Testing for using n process son
*/

#include <utilsF.h>
#include <sys/mman.h>
#include <semaphore.h>

int main(void)
{
	int x = 10; //Quantity of son's
	
	//Creating of a counter with map shared between the various child
	int* counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	//Check
	if (counter < 0) {
		err_sys("Error mmap on sem and/or counter: ");
	}
	
	//Setting "counter" at 0
	*counter = 0;
	
	//Setting the semaphore at one
	char const* nameSemaphore = "/semaphore";
	sem_t* sem = sem_open(nameSemaphore, O_CREAT | O_EXCL, 0666, 1);
	if(sem < 0) {
		err_sys("Error sem_open: ");
	}
	
	for (int i = 0; i < x; i++) {
		pid_t pid = fork();
		if (pid < 0 ) {
			err_sys("Error fork: ");
		} else if (pid == 0) {
			//I enter the critical section
			sem_wait(sem);
			
			//Increment counter
			(*counter)++;
			
			//Print
			printf("I'm the son with pid %d and I increased the counter to %d, now I'm done.\n\n" , getpid(), *counter);
			
			//I exit the critical section
			sem_post(sem);
			
			//The
			_exit(0);
		}
	}
	
	//Waiting for all the son's
	for (int i = 0; i < x; i++) {
		wait(NULL);
	}
	
	printf("I'm the father, this is the result of the counter: %d.\n\n", *counter);
	
	
	//Close sem and counter
	munmap(counter, sizeof(int));
	sem_close(sem);
	sem_unlink(nameSemaphore);
	
	
	_exit(EXIT_SUCCESS);
}
