#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char** argv){


	if(argc < 2){
		printf("Provide the path of the executable that should be debugged.\n");
		return -1;
	}

	char* executablePath = argv[1];

	pid_t pid = fork();
	if(pid == -1){
		perror("Could not fork\n");
		return -1;

	}
	else{
		//child process, to be debugged.
		if(pid == 0){
			if(ptrace(__ptrace_request.PTRACE_TRACEME,0,NULL,NULL) == 0){
				
				const char * path = executablePath;
				char * const argv[2] = {executablePath,NULL};
				char * const envp[1] ={NULL};	
				if(execve(path, argv, envp) == -1){
					perror("Failed to launch debuggee.\n");
					return -1;
				}
				//on success a SIGTRAP signal is delivered to child

			}
			else{
				perror("could not start trace.\n");
				return -1;
			}
		}
		//parent process, the one doing the debugging.
		else{
			int * wstatus;	
			waitpid(pid,wstatus,0);
			//debuggee is stopped by SIGTRAP signal, ready to debug.
			if(WIFSTOPPED(*wstatus)){
				
			}
			else{
				if(kill(pid,SIGKILL) != 0){
					perror("Failed to kill debuggee.\n");
					return -1;
				}
			}
		}


	}









}
