
#include "commandHelpers.h"



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
	printf("r15 : %lu \n", regs.r15);
	printf("r14 : %lu \n", regs.r14);
	printf("r13 : %lu \n", regs.r13);
	printf("r12 : %lu \n", regs.r12);
	printf("bp : %lu \n", regs.rbp);
	printf("bx: %lu \n", regs.rbx);
	printf("r11 : %lu \n", regs.r11);
	printf("r10 : %lu \n", regs.r10);
	printf("r9 : %lu \n", regs.r9);
	printf("r8 : %lu \n", regs.r8);
	printf("ax : %lu \n", regs.rax);
	printf("cx : %lu \n", regs.rcx);
	printf("dx : %lu \n", regs.rdx);
	printf("si : %lu \n", regs.rsi);
	printf("di : %lu \n", regs.rdi);
	printf("orig_ax : %lu \n", regs.orig_rax);
	printf("ip : %lu \n", regs.rip);
	printf("cs : %lu \n", regs.cs);
	printf("flags : %lu \n", regs.eflags);
	printf("sp : %lu \n", regs.rsp);
	printf("ss : %lu \n", regs.ss);
	printf("fs_base : %lu \n", regs.fs_base);
	printf("gs_base : %lu \n", regs.gs_base);
	printf("ds : %lu \n", regs.ds);
	printf("es  : %lu \n", regs.es);
	printf("fs : %lu \n", regs.fs);
	printf("gs : %lu \n", regs.gs);
	printf("======================================\n");

}
