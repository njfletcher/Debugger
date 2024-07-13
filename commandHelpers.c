struct iovec getDebugeeRegisters(int normalRegFlag, pid_t pid){

	struct iovec regInfo;
	int retVal = 0;

	if(normalRegFlag == 0){

		retVal = ptrace(PTRACE_GETREGSET, pid, (void *) NT_foo, (void *) &regInfo);
	}
	else{

		retVal = ptrace(PTRACE_GETREGSET, pid, (void *) NT_PRSTATUS, (void *) & regInfo);

	}

	if(retVal != 0){

		perror("Get register info\n");
		return NULL;
	}
	else return regInfo;


}
