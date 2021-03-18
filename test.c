#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
int main (int argc, char** argv) {
	pid_t pid = fork ();
	
	switch (pid) {
		case -1 :
			printf ("Erreur dans la creation du processus fils.\n");
			perror ("Erreur : ");
			break;
		case  0 :
			printf ("On se trouve dans le processus fils.\n");
			printf (" - PID du processus courant : %d\n", getpid());
			printf (" - PID du processus pere    : %d\n", getppid());
			break;
		default :
			printf ("On se trouve dans le processus pere.\n");
			printf (" - PID du processus courant : %d\n", getpid());
			printf (" - PID du processus fils    : %d\n", pid);
	}
	
	return 0;
}
