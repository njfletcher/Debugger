
#include "commandHelpers.h"

void singleStep(pid_t pid, void * data){


	if(ptrace(PTRACE_SINGLESTEP, pid, NULL, data) != 0){

		perror("Single step\n");

	}


}

struct iovec getRegs( pid_t pid,struct user_regs_struct * regPtr){

	struct iovec data;
	int retVal = 0;
	data.iov_base = (void *) regPtr;
	data.iov_len = sizeof(struct user_regs_struct);

	retVal = ptrace(PTRACE_GETREGSET, pid, (void *) NT_PRSTATUS, (void *) &data);

	if(retVal != 0){

		perror("Get register info\n");
	}
	return data;


}

void printX8664Regs(struct user_regs_struct regs){

	printf("REGISTER INFORMATION =================\n");
	printf("r15 : %lu  ", regs.r15);
	printf("r14 : %lu  ", regs.r14);
	printf("r13 : %lu  ", regs.r13);
	printf("r12 : %lu  ", regs.r12);
	printf("bp : %lu ", regs.rbp);
	printf("bx: %lu ", regs.rbx);
	printf("r11 : %lu  \n", regs.r11);
	printf("r10 : %lu  ", regs.r10);
	printf("r9 : %lu  ", regs.r9);
	printf("r8 : %lu  ", regs.r8);
	printf("ax : %lu  ", regs.rax);
	printf("cx : %lu  ", regs.rcx);
	printf("dx : %lu  ", regs.rdx);
	printf("si : %lu  ", regs.rsi);
	printf("di : %lu  \n", regs.rdi);
	printf("orig_ax : %lu  ", regs.orig_rax);
	printf("ip : %lu  ", regs.rip);
	printf("cs : %lu  ", regs.cs);
	printf("flags : %lu  ", regs.eflags);
	printf("sp : %lu   ", regs.rsp);
	printf("ss : %lu   ", regs.ss);
	printf("fs_base : %lu  ", regs.fs_base);
	printf("gs_base : %lu \n", regs.gs_base);
	printf("ds : %lu  ", regs.ds);
	printf("es  : %lu  ", regs.es);
	printf("fs : %lu  ", regs.fs);
	printf("gs : %lu \n", regs.gs);
	printf("======================================\n");

}
