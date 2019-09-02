#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "common.h"

//to handle signal when the main proc is forked
void handle_signal(int signal){
	switch (signal){
		case SIGINT:
			write(1 , "\n" , 2);
			kill(getpid() , SIGCONT);
			fflush(stdout);
			return;
		case SIGCHLD:
			fflush(stdout);
			return;
		case SIGQUIT:
			kill(getppid() , SIGKILL);
			return;
		case SIGTSTP:
			write(1 , "\n" , 2);
			printf("To exit from terminal you need to press ESC\n");
			fflush(stdout);
			return;
	}
}

//to handle signal when before fork
void handle_signal_less(int signal){
	switch (signal){
		case SIGQUIT:
			kill(getppid() , SIGKILL);
			return;
		case SIGTSTP:
			write(1 , "\n" , 2);
			printf("To exit from terminal you need to press ESC\n");
			fflush(stdout);
			return;
		case SIGINT:
			write(1 , "\n" , 2);
			fflush(stdout);
			return;
		case SIGWINCH:
			write(1 , "\n" , 2);
			printf("La dimensione del terminale sta cambiando\n");
			fflush(stdout);
			return;
	}
}