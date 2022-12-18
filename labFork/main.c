#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t Pid;	//child process pid

void child_Exit(void)
{
	printf("CHILD: Exit\n");
}

void sig_Term_Handler(int sig)
{
    if(Pid == 0)
    {
        printf("\nSigterm %d received from child process\n", sig);
    }
}

void sig_Int_Handler(int sig)
{
    if(Pid == 0)
    {
        printf("\nSigint %d received from child process\n", sig);
        kill(getpid(), SIGTERM);
    }
}

int main(int argc, char** argv)
{
		int code_exit;
		int error_exit;
		
		struct sigaction newAction;
		newAction.saHandler = sig_Term_Handler;
		sigemptyset(&newAction.saMask);
		newAction.saFlags = 0;
		sigaction(SIGTERM, &newAction, NULL);
		signal(SIGINT, sig_Int_Handler);
		switch(Pid = fork())
		{
				case -1:
					perror("Fork error");
					exit(1);
				case 0:
					printf("CHILD: My PID is %d\n", getpid());
					printf("CHILD: My parent's PID is %d\n", getppid());
					printf(">>> You can stop child process immediatly by using Ctrl+C (or wait 10 sec)\n");
					sleep(10);
					
					printf("CHILD: Enter child's exit code: ");
					scanf("%d", &code_exit);
					error_exit = atexit(child_Exit);
					
					if(error_exit != 0)
					{
						printf("Child process exit error\n");
					}
					exit(code_exit);
				default:
					printf("PARENT: My PID is %d\n", getpid());
					printf("PARENT: My child's PID is %d\n", Pid);
					printf("PARENT: Waiting...\n");
					wait(&code_exit);
					printf("PARENT: Real child's exit code is %d\n", WEXITSTATUS(code_exit));
					printf("PARENT: Exit\n");
		}
		return 0;
}