#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include "commandHelpers.h"
#include <string.h>
//malloced data list
//-inner args list

//argc and argv represent the original(outer) arguments given to the debugger.
char ** loadInnerArgs(int argc, char ** argv){
	
	char ** innerArgs;
	// leave out arg[0], since this is the debugger's name
	int numDebugeeArgs = argc -1;
	//add 1 to size to include required NULL ending
	int sizeOfArgArr = numDebugeeArgs + 1;


	innerArgs = (char **)malloc(sizeof(char *) * sizeOfArgArr);
	if(innerArgs == NULL){
		perror("malloc args\n");
		return NULL;
	}

	for(int i =0; i < numDebugeeArgs; i++){
		innerArgs[i] = argv[i +1];
			
	}
	innerArgs[sizeOfArgArr - 1] = NULL;

	return innerArgs;
	
}


void commandLoop(pid_t pid){

	char commandBuffer[100];

	while(1){

		scanf("%s", commandBuffer);
			

		if(strcmp(commandBuffer,"step") == 0){
			
			printf("Step taken\n");
			singleStep(pid,NULL);
			
			int wstatus = 0;	
			waitpid(pid,&wstatus,0);
			printf("%i\n", wstatus);
			//debuggee is stopped by SIGTRAP signal, ready to debug.
			if(WIFSTOPPED(wstatus)){
				
				continue;	
			}
			else{
				if(kill(pid,SIGKILL) != 0){
					perror("Failed to kill debuggee.\n");
					
				}
			}

		}
		if(strcmp(commandBuffer,"regs") == 0){

			struct user_regs_struct regs;	
			getRegs(pid, &regs);
			printX8664Regs(regs);
		}
		if(strcmp(commandBuffer,"quit") == 0){

			return;

		}

	}
}

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
			
			if(ptrace(PTRACE_TRACEME,0,NULL,NULL) == 0){
				
				const char * path = executablePath;
				char * const envp[1] ={NULL}; // environmental variables not currently used.
				char * const * args = loadInnerArgs(argc, argv);
				
				if(execve(path, args, envp) == -1){
					perror("Failed to launch debuggee.\n");
					free((void*)args);
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
			int wstatus = 0;	
			waitpid(pid,&wstatus,0);
			printf("%i\n", wstatus);
			//debuggee is stopped by SIGTRAP signal, ready to debug.
			if(WIFSTOPPED(wstatus)){
				
				printf("debugee started! pid %i \n", pid);
				commandLoop(pid);				
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
